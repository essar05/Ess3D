#include "IGame.h"
#include <iostream>
#include <memory>

namespace Ess3D {

  IGame::IGame() {
    _config = Config::get();
    _state = State::get();
  };

  IGame::~IGame() = default;

  void IGame::boot() {
    std::cout << "Booting from " << SDL_GetBasePath() << std::endl;

    init();

    _state->setExecutionStatus(ExecutionStatus::RUNNING);
  }

  void IGame::destroy() {
    if(_state->getExecutionStatus() != ExecutionStatus::DESTROYED) {
      _state->setExecutionStatus(ExecutionStatus::DESTROYED);

      SDL_StopTextInput();
      onExit();
    }
  }

  void IGame::run() {
    _state->getFPSLimiter()->init(_config->getMaxFPS(), _config->getLimitFPS());
    _state->getTimestepAccumulator()->init();
    const float timestep = _state->getTimestepAccumulator()->getTimestep();

    while(_state->getExecutionStatus() == ExecutionStatus::RUNNING) {
      _state->getFPSLimiter()->begin();
      const int simulationSteps = _state->getTimestepAccumulator()->step();

      update(timestep, simulationSteps);
      render();

      _state->setFPS(_state->getFPSLimiter()->end());

      _state->getWindow()->SwapBuffer();
    }
  }

  bool IGame::init() {
    onInit();

    initSystems();

    _screenManager = std::make_shared<ScreenManager>();

    addScreens();

    _currentScreen = _screenManager->getCurrent();
    _currentScreen->onEntry();
    _currentScreen->setRunning();

    return true;
  }

  bool IGame::initSystems() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_ShowCursor(false);
    SDL_StartTextInput();

    _state->getFPSLimiter()->init(_config->getMaxFPS(), _config->getLimitFPS());

    std::shared_ptr<Window> window = std::make_shared<Window>(_config->getTitle(), (int) _config->getWidth(), (int) _config->getHeight(), _config->getWindowMode());
    window->SetVSync(_config->getVSync());
    _state->setWindow(window);

    return true;
  }

  void IGame::onSDLEvent(SDL_Event& event) {
    switch(event.type) {
      case SDL_QUIT:
        _state->setExecutionStatus(ExecutionStatus::EXIT);
        break;
      case SDL_KEYDOWN:
        _state->getInputManager()->pressKey(event.key.keysym.sym);
        break;      
      case SDL_KEYUP:
        _state->getInputManager()->releaseKey(event.key.keysym.sym);
        break;
      case SDL_MOUSEMOTION:
        _state->getInputManager()->setCursorPosition(glm::vec2(event.motion.x, event.motion.y));
        _state->getInputManager()->setCursorDeltaPosition(glm::vec2(event.motion.xrel, event.motion.yrel));
        _state->getInputManager()->setHasMouseMoved(true);
        break;
    }
  }

  void IGame::update(float deltaTime, int simulationSteps) {
    Ess3D::InputManager* inputManager = _state->getInputManager();

    if(_currentScreen) {
      switch(_currentScreen->getState()) {
        case ScreenState::RUNNING:
          for(int i = 0; i < simulationSteps; i++) {
            this->processInput(_currentScreen);

            _currentScreen->input(inputManager);
            _currentScreen->step(deltaTime);
          }
          _currentScreen->update();
          break;
        case ScreenState::CHANGE_NEXT:
          _currentScreen->onExit();
          _currentScreen = _screenManager->moveNext();
          if(_currentScreen != nullptr) {
            _currentScreen->setRunning();
            _currentScreen->onEntry();
          }
          break;
        case ScreenState::CHANGE_PREV:
          _currentScreen->onExit();
          _currentScreen = _screenManager->movePrevious();
          if(_currentScreen != nullptr) {
            _currentScreen->setRunning();
            _currentScreen->onEntry();
          }
          break;
        case ScreenState::EXIT_APPLICATION:
          destroy();
          break;
        default:
          break;
      }
    } else {
      destroy();
    }

    onUpdate();
  }

  void IGame::processInput(IGameScreen* screen) {
    Ess3D::InputManager* inputManager = _state->getInputManager();

    SDL_Event event;

    inputManager->reset();
    while(SDL_PollEvent(&event) != 0) {
      this->onSDLEvent(event);
      screen->onSDLEvent(event);
    }
  }

  void IGame::render() {
    if(_currentScreen && _currentScreen->getState() == ScreenState::RUNNING) {
      _currentScreen->render();
    }
  }

};
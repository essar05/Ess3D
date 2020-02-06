#include "GameplayScreen.h"
#include <gl/FBORenderer.h>
#include <SDL_events.h>

GameplayScreen::GameplayScreen() {
  _game = Game::GetInstance();
  _screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen() {}

int GameplayScreen::getNextScreenIndex() const {
  return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
  return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::onEntry() {
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

void GameplayScreen::onExit() {
  
}

void GameplayScreen::build() {
  srand(time(NULL));

  _fboRenderer = new Ess3D::FBORenderer();
  _fboRenderer->initShader();
  _sceneFBO = new Ess3D::FrameBufferObject(_game->getWindow(), (GLsizei) _game->getWidth(), (GLsizei) _game->getHeight(), Ess3D::DepthBufferType::TEXTURE);
  _sceneRenderer = new SceneRenderer(_game->getWidth(), _game->getHeight());
}

void GameplayScreen::destroy() {
  delete _fboRenderer;
  delete _sceneFBO;
  delete _sceneRenderer;
}

void GameplayScreen::draw() {
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //bind FBO, all rendering will be done to this FBO's color buffer
  _sceneFBO->bind();
  
  //render scene
  _sceneRenderer->render();

  //unbind FBO, rendering will now be done to screen
  _sceneFBO->unbind();

  _fboRenderer->render(_sceneFBO);
}

void GameplayScreen::update(float deltaTime, int simulationSteps) {
    for(int i = 0; i < simulationSteps; i++) {
      processInput(deltaTime);  
    }
}

void GameplayScreen::processInput(float deltaTime) {
  SDL_Event event;
  Ess3D::InputManager* inputManager = _game->getInputManager();

  inputManager->setHasMouseMoved(false);
  while(SDL_PollEvent(&event) != 0) {
    _game->onSDLEvent(event);
  }
 
  if(inputManager->isKeyDown(SDLK_ESCAPE)) {
    _currentState = Ess3D::ScreenState::EXIT_APPLICATION;
  }
  if (inputManager->isKeyDown(SDLK_w)) {
    _sceneRenderer->getCamera()->moveForward();
  }
  if (inputManager->isKeyDown(SDLK_s)) {
    _sceneRenderer->getCamera()->moveBackward();
  }
  if (inputManager->isKeyDown(SDLK_a)) {
    _sceneRenderer->getCamera()->moveLeft();
  }
  if (inputManager->isKeyDown(SDLK_d)) {
    _sceneRenderer->getCamera()->moveRight();
  }
  if (inputManager->hasMouseMoved()) {
    _sceneRenderer->getCamera()->look(inputManager->getCursorDeltaPosition());
  }
}
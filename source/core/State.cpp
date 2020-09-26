#include <Ess3D/core/State.h>
#include <utility>

namespace Ess3D {

  State::State() = default;

  State::~State() {
    delete _instance;
  }

  State* State::_instance = nullptr;

  State *State::get() {
    if (_instance == nullptr) {
      _instance = new State();
    }

    return _instance;
  }

  float State::getFPS() {
    return _fps;
  }

  void State::setFPS(float fps) {
    _fps = fps;
  }

  ExecutionStatus State::getExecutionStatus() {
    return _executionStatus;
  }

  void State::setExecutionStatus(ExecutionStatus executionStatus) {
    _executionStatus = executionStatus;
  }

  std::shared_ptr<Window> State::getWindow() {
    return _window;
  }

  void State::setWindow(std::shared_ptr<Window> window) {
    _window = std::move(window);
  }

  InputManager *State::getInputManager() {
    return &_inputManager;
  }

  FPSLimiter *State::getFPSLimiter() {
    return &_fpsLimiter;
  }

  TimestepAccumulator *State::getTimestepAccumulator() {
    return &_timestepAccumulator;
  }
}
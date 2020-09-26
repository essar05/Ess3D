#include <Ess3D/core/Config.h>

namespace Ess3D {

  Config::Config() = default;

  Config::~Config() {
    delete _instance;
  }

  Config* Config::_instance = nullptr;

  Config *Config::get() {
    if (_instance == nullptr) {
      _instance = new Config();
    }

    return _instance;
  }

  float Config::getMaxFPS() const {
    return _maxFPS;
  }

  void Config::setMaxFPS(float maxFPS) {
    _maxFPS = maxFPS;
  }

  bool Config::getLimitFPS() const {
    return _limitFPS;
  }

  void Config::setLimitFPS(bool limitFPS) {
    _limitFPS = limitFPS;
  }

  bool Config::getDebugMode() const {
    return _debugMode;
  }

  void Config::setDebugMode(bool debugMode) {
    _debugMode = debugMode;
  }

  std::string Config::getTitle() {
    return _title;
  }

  void Config::setTitle(const std::string &title) {
    _title = title;
  }

  WindowMode Config::getWindowMode() {
    return _windowMode;
  }

  void Config::setWindowMode(WindowMode windowMode) {
    _windowMode = windowMode;
  }

  float Config::getWidth() const {
    return _width;
  }

  void Config::setWidth(float width) {
    _width = width;
  }

  float Config::getHeight() const {
    return _height;
  }

  void Config::setHeight(float height) {
    _height = height;
  }

  bool Config::getVSync() const {
    return _vSync;
  }

  void Config::setVSync(bool vSync) {
    _vSync = vSync;
  }
}
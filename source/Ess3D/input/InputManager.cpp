#include "InputManager.h"

namespace Ess3D {

  InputManager::InputManager() {
  }

  InputManager::~InputManager() {
  }

  void InputManager::pressKey(unsigned int keyId) {
    _keyMap[keyId] = true;
  }

  void InputManager::releaseKey(unsigned int keyId) {
    _keyMap[keyId] = false;
  }

  bool InputManager::isKeyDown(unsigned int keyId) {
    auto it = _keyMap.find(keyId);
    if(it == _keyMap.end()) {
      return false;
    }
    return it->second;
  }

  glm::vec2 InputManager::getCursorPosition() {
    return this->_cursorPosition;
  }

  glm::vec2 InputManager::getCursorDeltaPosition() {
    return this->_cursorDeltaPosition;
  }

  void InputManager::setCursorPosition(glm::vec2 newPosition) {
    this->_cursorPosition = newPosition;
  }

  void InputManager::setCursorDeltaPosition(glm::vec2 deltaPosition) {
    this->_cursorDeltaPosition = deltaPosition;
  }

  bool InputManager::hasMouseMoved() {
    return this->_hasMouseMoved;
  }

  void InputManager::setHasMouseMoved(bool hasMouseMoved) {
    this->_hasMouseMoved = hasMouseMoved;
  }

}
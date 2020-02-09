#pragma once

#include "definitions.h"
#include <unordered_map>
#include <glm/glm.hpp>

namespace Ess3D {
  class API InputManager {
    public:
      InputManager();
      ~InputManager();

      void pressKey(unsigned int keyId);
      void releaseKey(unsigned int keyId);

      bool isKeyDown(unsigned int keyId);
      glm::vec2 getCursorPosition();
      glm::vec2 getCursorDeltaPosition();
      void setCursorPosition(glm::vec2 newPosition);
      void setCursorDeltaPosition(glm::vec2 deltaPosition);

      bool hasMouseMoved();
      void setHasMouseMoved(bool hasMouseMoved);

    private:
      std::unordered_map<unsigned int, bool> _keyMap;
      glm::vec2 _cursorPosition;
      glm::vec2 _cursorDeltaPosition;
      bool _hasMouseMoved = false;
  };
}
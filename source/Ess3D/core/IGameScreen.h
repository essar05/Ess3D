#pragma once

#include <2d/rendering/Renderer2D.h>
#include "definitions.h"

#define SCREEN_INDEX_NO_SCREEN -1

namespace Ess3D {

  enum class ScreenState {
    NONE,
    RUNNING,
    EXIT_APPLICATION,
    CHANGE_NEXT,
    CHANGE_PREV
  };

  class API IGameScreen {
    public:
      friend class ScreenManager;

      IGameScreen() = default;

      ~IGameScreen() = default;

      virtual int getNextScreenIndex() const = 0;
      virtual int getPreviousScreenIndex() const = 0;

      //called at beggining and end of application
      virtual void build() = 0;
      virtual void destroy() = 0;

      // called when a screen enters and exists focus
      virtual void onEntry() = 0;
      virtual void onExit() = 0;

      // called in the main game loop
      virtual void update(float deltaTime, int simulationSteps) = 0;
      virtual void draw() = 0;

      int getIndex() const {
        return _screenIndex;
      }

      ScreenState getState() const { return _currentState; }

      void setRunning() {
        _currentState = ScreenState::RUNNING;
      }

    protected:
      ScreenState _currentState = ScreenState::NONE;

      int _screenIndex = -1;

  };

}
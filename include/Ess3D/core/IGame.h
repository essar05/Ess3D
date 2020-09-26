#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/core/ScreenManager.h>
#include <Ess3D/gl/Window.h>
#include <Ess3D/utils/Timing.h>
#include <Ess3D/input/InputManager.h>
#include <Ess3D/core/Config.h>
#include <Ess3D/core/State.h>

namespace Ess3D {

  class API IGame {
    public:
      virtual ~IGame();

      virtual void boot();
      virtual void destroy();
      virtual void run();

      virtual void addScreens() = 0;
      virtual void onInit() = 0;
      virtual void onExit() = 0;
      void onSDLEvent(SDL_Event& event);

    protected:
      IGame();

      void update(float deltaTime, int simulationSteps);
      void render();

      virtual void onUpdate() {}

      bool init();
      bool initSystems();

      std::shared_ptr<ScreenManager> _screenManager;
      IGameScreen* _currentScreen = nullptr;

      State* _state{};
      Config* _config{};

    private:
      void processInput(IGameScreen* screen);
  };

}
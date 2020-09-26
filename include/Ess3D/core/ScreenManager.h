#pragma once

#include <Ess3D/definitions.h>
#include <vector>
#include <Ess3D/core/IGameScreen.h>

namespace Ess3D {

  class API ScreenManager {
    public:
      ScreenManager();
      ~ScreenManager();

      IGameScreen* moveNext();
      IGameScreen* movePrevious();

      void setScreen(int screenIndex);
      void addScreen(IGameScreen* newScreen);

      IGameScreen* getCurrent();

    private:
      std::vector<IGameScreen*> _screens;
      int _currentScreenIndex = -1;
  };

}

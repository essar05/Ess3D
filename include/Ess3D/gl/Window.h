#pragma once

#include <Ess3D/definitions.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Ess3D {

  enum WindowMode {
    NORMAL = 0x0,
    INVISIBLE = 0x1,
    FULLSCREEN = 0x2,
    BORDERLESS = 0X4,
    FULLSCREEN_DESKTOP = 0x8
  };

  class API Window {
    public:
      Window(const std::string& windowName, int width, int height, unsigned int windowModes);
      ~Window();

      void swapBuffer();
      void enableVSync();
      void disableVSync();

      int getWidth();
      int getHeight();

      int getCurrentWidth();
      int getCurrentHeight();

      int getMonitorRefreshRate();

    private:
      int _height;
      int _width;
      int _currentWidth{};
      int _currentHeight{};
      SDL_Window* _sdlWindow;

  };

}
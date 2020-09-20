#include <iostream>
#include "Window.h"


namespace Ess3D {

  Window::Window(const std::string& windowName, int width, int height, unsigned int windowModes): _width(width), _height(height) {
    unsigned int windowFlags = SDL_WINDOW_OPENGL;

    if (windowModes & WindowMode::INVISIBLE) {
      windowFlags |= SDL_WINDOW_HIDDEN;
    }
    if (windowModes & WindowMode::FULLSCREEN) {
      windowFlags |= SDL_WINDOW_FULLSCREEN;
    }
    if (windowModes & WindowMode::FULLSCREEN_DESKTOP) {
      windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (windowModes & WindowMode::BORDERLESS) {
      windowFlags |= SDL_WINDOW_BORDERLESS;
    }

    _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, windowFlags);
    if (_sdlWindow == nullptr) {
      throw Ess3D::ERuntimeException(SDL_GetError());
    }

    SDL_GetWindowSize(_sdlWindow, &_currentWidth, &_currentHeight);

    //Create OpenGL Context;
    SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
    if (glContext == nullptr) {
      throw Ess3D::ERuntimeException("GL Context creation failed");
    }

    glewExperimental=true;
    GLenum error = glewInit();
    if (error != GLEW_OK) {
      throw Ess3D::ERuntimeException("GLEW initialization failed");
    }

    std::printf("GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    //Set VSYNC to disabled
    this->disableVSync();
  }

  Window::~Window() {
  }

  int Window::getMonitorRefreshRate() {
    SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
    int windowDisplayIndex = SDL_GetWindowDisplayIndex(this->_sdlWindow);
    if(windowDisplayIndex < 0) {
      std::string sdlError = SDL_GetError();
      throw Ess3D::ERuntimeException("Error in Window::getMonitorRefreshRate: " + sdlError);
    }

    if(SDL_GetDisplayMode(windowDisplayIndex, 0, &mode) < 0) {
      std::string sdlError = SDL_GetError();
      throw Ess3D::ERuntimeException("Error in Window::getMonitorRefreshRate: " + sdlError);
    }

    return mode.refresh_rate;
  }

  void Window::enableVSync() {
    if (SDL_GL_SetSwapInterval(1) == -1) {
      std::cout << "Warning: Enabling VSync failed with error \"" << SDL_GetError() << "\"" << std::endl;
    }
  }

  void Window::disableVSync() {
    if (SDL_GL_SetSwapInterval(0) == -1) {
      std::cout << "Warning: Disabling VSync failed with error \"" << SDL_GetError() << "\"" << std::endl;
    }
  }

  void Window::swapBuffer() {
    SDL_GL_SwapWindow(this->_sdlWindow);
  }

  int Window::getWidth() {
    return _width;
  }

  int Window::getHeight() {
    return _height;
  }

  int Window::getCurrentWidth() {
    return _currentWidth;
  }

  int Window::getCurrentHeight() {
    return _currentHeight;
  }


}
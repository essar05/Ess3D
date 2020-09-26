#pragma once

#include <Ess3D/gl/Window.h>

namespace Ess3D {

  class API Config {
    public:
      virtual ~Config();

      static Config* get();

      float getMaxFPS() const;
      void setMaxFPS(float maxFPS);

      bool getLimitFPS() const;
      void setLimitFPS(bool limitFPS);

      bool getDebugMode() const;
      void setDebugMode(bool debugMode);

      std::string getTitle();
      void setTitle(const std:: string& title);

      WindowMode getWindowMode();
      void setWindowMode(WindowMode windowMode);

      float getWidth() const;
      void setWidth(float width);

      float getHeight() const;
      void setHeight(float height);

      bool getVSync() const;
      void setVSync(bool vSync);

    protected:
      Config();

      float _maxFPS = 60.0f;
      bool _debugMode = false;
      bool _limitFPS = false;

      std::string _title = "Ess3D";
      WindowMode _windowMode = WindowMode::NORMAL;
      float _width = 1280.f;
      float _height = 720.f;
      bool _vSync = false;

      static Config* _instance;
  };

}
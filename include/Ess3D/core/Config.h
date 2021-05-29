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

      bool isInterpolationEnabled() const;
      void enableInterpolation();
      void disableInterpolation();

    protected:
      Config();

      float _maxFPS = 300.0f;
      bool _debugMode = false;
      bool _limitFPS = true;

      std::string _title = "Ess3D";
      WindowMode _windowMode = WindowMode::NORMAL;
      float _width = 1280.f;
      float _height = 720.f;
      bool _vSync = false;

      bool _interpolationEnabled = true;

      static Config* _instance;
  };

}
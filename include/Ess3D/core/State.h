#pragma once

#include <Ess3D/input/InputManager.h>
#include <Ess3D/gl/Window.h>
#include <Ess3D/utils/Timing.h>
#include <memory>

namespace Ess3D {

  enum class ExecutionStatus {
      INITIALIZING, RUNNING, EXIT, DESTROYED
  };

  class API State {
    public:
      virtual ~State();

      static State* get();

      float getFPS();
      void setFPS(float fps);

      ExecutionStatus getExecutionStatus();
      void setExecutionStatus(ExecutionStatus executionStatus);

      std::shared_ptr<Window> getWindow();
      void setWindow(std::shared_ptr<Window> window);

      InputManager* getInputManager();
      FPSLimiter* getFPSLimiter();
      TimestepAccumulator* getTimestepAccumulator();

    protected:
      State();

      float _fps = 0.0f;

      ExecutionStatus _executionStatus = ExecutionStatus::INITIALIZING;
      std::shared_ptr<Window> _window;
      InputManager _inputManager;
      FPSLimiter _fpsLimiter;
      TimestepAccumulator _timestepAccumulator;

      static State* _instance;
  };

}

#pragma once

#include <Ess3D/definitions.h>
#include <chrono>

namespace Ess3D {

  class API FPSLimiter {
    public:
      FPSLimiter();
      void init(float maxFPS, bool limitFPS);

      void begin();
      float end(); //returns current FPS

      void setMaxFPS(float fps);

      float getFPS() { return _fps; }

    private:
      void calculateFPS();
    
      float _maxFPS;

      std::chrono::high_resolution_clock::time_point _startTicks;
      std::chrono::high_resolution_clock::time_point _newTicks;
      float _fps;
      float _frameTime;
      float _time;
      bool _limitFPS;

  };

  class API TimestepAccumulator {
    public:
      TimestepAccumulator();
      ~TimestepAccumulator();

      void init();
      int step();

      float getTimestep() const { return _timestep; }
      float getAccumulator() const { return _accumulator; }
      float getAccumulatorRatio() const { return _accumulatorRatio; }

    private:
      int _maxStepsSimulated = 500;
      float _timestep = 1.0f / 100.f;
      float _frameTime = 0.0f;
      float _accumulator = 0.0f;
      float _accumulatorRatio = 0.0f;
      std::chrono::high_resolution_clock::time_point _prevTicks;
      std::chrono::high_resolution_clock::time_point _newTicks;

  };

}
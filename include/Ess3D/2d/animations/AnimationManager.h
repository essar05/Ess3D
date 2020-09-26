#pragma once

#include <Ess3D/definitions.h>
#include <Ess3D/2d/animations/Animation.h>
#include <unordered_map>

namespace Ess3D {

  class API AnimationManager {
    public:
      AnimationManager();
      ~AnimationManager();

      Animation* add(std::string name);
      void play(std::string name);
      void update(float deltaTime);
      Animation* getCurrent();
      std::string getCurrentAnimationName();
      bool isPlaying();

    private:
      std::unordered_map<std::string, Animation*> _animations;
      std::string _currentAnimation = "";

  };

}
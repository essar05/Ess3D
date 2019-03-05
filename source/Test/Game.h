#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <IGame.h>
#include <AudioManager.h>
#include "GameplayScreen.h"
#include <rapidjson.h>
#include <document.h>

class GameplayScreen;

class Game : public Ess3D::IGame {
  public:
	  static Game* GetInstance();
    ~Game();

    virtual void addScreens() override;
    virtual void onInit() override;
    virtual void onExit() override;

    Ess3D::AudioManager* getAudioManager();
    GameplayScreen* getGameplayScreen();

  protected:
    Game();
    virtual void onUpdate() override;
    void loadConfig();

    float _volume = 1.0f;
	bool _isConfigEnabled;

    Ess3D::AudioManager _audioManager;

  private:
    static Game* instance;
    GameplayScreen* _gameplayScreen;

};

#endif // GAME_H

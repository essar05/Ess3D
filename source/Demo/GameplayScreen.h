#pragma once

#include <core/IGameScreen.h>
#include "Game.h"
#include "ScreenIndices.h"
#include "SceneRenderer.h"
#include <gl/FBORenderer.h>

class Game;

class GameplayScreen : public Ess3D::IGameScreen {
  public:
    GameplayScreen();
    ~GameplayScreen();

    int getNextScreenIndex() const override;
    int getPreviousScreenIndex() const override;

    void build() override;
    void destroy() override;
    void draw() override;
    void update(float deltaTime, int simulationSteps) override;

    void onEntry() override;
    void onExit() override;
    
  private:
    void processInput(float deltaTime);
    
    Game* _game = nullptr;
    Ess3D::FrameBufferObject* _sceneFBO;

    Ess3D::FBORenderer* _fboRenderer;
    SceneRenderer* _sceneRenderer;
};


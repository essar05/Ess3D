#pragma once

#include <core/IGameScreen.h>
#include "Game.h"
#include <textures/TextureCache.h>
#include "ScreenIndices.h"
#include "SceneRenderer.h"
#include <gl/FBORenderer.h>

class Game;

class GameplayScreen : public Ess3D::IGameScreen {
  public:
    GameplayScreen();
    ~GameplayScreen();

    virtual int getNextScreenIndex() const override;
    virtual int getPreviousScreenIndex() const override;

    virtual void build() override;
    virtual void destroy() override;
    virtual void draw() override;
    virtual void update(float deltaTime, int simulationSteps) override;

    virtual void onEntry() override;
    virtual void onExit() override;
    
  private:
    void processInput(float deltaTime);
    
    Game* _game = nullptr;
    Ess3D::FrameBufferObject* _sceneFBO;

    Ess3D::FBORenderer* _fboRenderer;
    SceneRenderer* _sceneRenderer;
};


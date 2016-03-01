#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include "GameState.h"
#include "MainMenuState.h"
#include "MyGameComponentFactory.h"
#include "PlayerController.h"

class GameRunningState :
    public GameState
{
public:
    GameRunningState(GameApp* gameApp);
    virtual ~GameRunningState();
    virtual bool update(yam2d::ESContext *context, float deltaTime);
    virtual void render(yam2d::ESContext *context);
    yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor);
    yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor);
    float getZoom();
    void setZoom(float newZoom);

private:
    GameApp* m_gameApp; /// < Dont use Ref here to avoid "issues"
    yam2d::Ref<yam2d::TmxMap> m_tmap;
    yam2d::Ref<MyGameComponentFactory> m_compfactory;
    yam2d::Ref<yam2d::GameObject> player;
    float m_zoom;
};

#endif
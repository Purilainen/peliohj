#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include "GameState.h"
#include "MainMenuState.h"


class GameRunningState :
    public GameState
{
public:
    GameRunningState(GameApp* gameApp);
    virtual ~GameRunningState();
    virtual bool update(yam2d::ESContext *context, float deltaTime);
    virtual void render(yam2d::ESContext *context);
    float getZoom();
    void setZoom(float newZoom);

private:
    GameApp* m_gameApp; /// < Dont use Ref here to avoid "issues"
    yam2d::Ref<yam2d::TmxMap> m_tmap;
    yam2d::Ref<yam2d::ComponentFactory> m_compfactory;
    float m_zoom;
};

#endif
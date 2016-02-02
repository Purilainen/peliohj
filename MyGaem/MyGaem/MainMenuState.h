#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Map.h"
#include "Input.h"
#include "Layer.h"
#include <TileComponent.h>
#include <SpriteComponent.h>
#include <Camera.h>
#include "GameRunningState.h"


class MainMenuState :
	public GameState
{
public:
	MainMenuState(GameApp* gameApp);
	virtual ~MainMenuState();

	virtual bool update(yam2d::ESContext *context, float deltaTime);
	virtual void render(yam2d::ESContext *context);
    yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor);
    yam2d::GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor);
private:
    yam2d::Ref<yam2d::Layer> m_backGroundLayer, m_objectLayer;
	yam2d::Ref<yam2d::Map> m_map;
    float count = 0;
    float m_totalTime = 0;
	GameApp* m_gameApp;
    
};

#endif
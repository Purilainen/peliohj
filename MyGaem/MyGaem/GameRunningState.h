#ifndef GAMERUNNINGSTATE_H
#define GAMERUNNINGSTATE_H

#include "GameState.h"
#include "Map.h"

class GameRunningState :
	public GameState
{
public:
	GameRunningState(GameApp* gameApp)
		: GameState(gameApp)
		, m_gameApp(gameApp)
		, m_map(0)
	{}
	virtual ~GameRunningState() {}

	virtual bool update(yam2d::ESContext *context, float deltaTime) { return true; }
	virtual void render(yam2d::ESContext *context) {}
	
private:
	yam2d::Ref<yam2d::Map> m_map;
	GameApp* m_gameApp;
};

#endif
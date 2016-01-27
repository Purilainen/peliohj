#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameApp.h"

class GameApp;
class GameState : public yam2d::Object
{
public:
	GameState(GameApp* gameApp);
	virtual ~GameState();

	virtual bool update(yam2d::ESContext *context, float deltaTime);
	virtual void render(yam2d::ESContext *context);
	GameApp* getApp();

private:
	GameApp *m_gameApp;
};

#endif
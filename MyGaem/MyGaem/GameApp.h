#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <assert.h>
#include <es_util.h>
#include "Ref.h"
#include "Object.h"

#include "GameState.h"

class GameState;
class GameApp : public yam2d::Object
{
public:
	GameApp();
	~GameApp();

	bool update(yam2d::ESContext *context, float deltaTime);
	void render(yam2d::ESContext *context);
	void setState(GameState *gameState);
private:
	yam2d::Ref<GameState> m_currentState;
};

#endif
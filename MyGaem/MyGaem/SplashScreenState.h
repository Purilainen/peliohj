#ifndef SPLASHSCREENSTATE_H
#define SPLASHSCREENSTATE_H


#include "GameState.h"
#include "MainMenuState.h"
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <Text.h>
#include <Texture.h>


class SplashScreenState :
	public GameState
{
public:
	SplashScreenState(GameApp* gameApp);
	virtual ~SplashScreenState();
	virtual bool update(yam2d::ESContext *context, float deltaTime);
	virtual void render(yam2d::ESContext *context);
private:
	yam2d::Ref < yam2d::Sprite > m_sprite;
	GameApp* m_gameApp;
	float m_totalTime = 0;
	yam2d::Ref<yam2d::SpriteBatchGroup> m_batch;
	yam2d::Ref<yam2d::Texture> m_newTexture;
	float count = 0;
};

#endif
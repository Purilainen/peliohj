#include "GameState.h"


GameState::GameState(GameApp* gameApp)
	: Object()
	, m_gameApp(gameApp)
{
}

GameState::~GameState()
{
}

bool GameState::update(yam2d::ESContext *context, float deltaTime)
{
	//assert(m_gameApp != 0);
	//If return false - esQuitApp
	return true;
};

void GameState::render(yam2d::ESContext *context)
{};

GameApp* GameState::getApp()
{
	return m_gameApp;
};
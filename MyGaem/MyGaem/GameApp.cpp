#include "GameApp.h"


GameApp::GameApp()
	: Object()
	, m_currentState(0)
{
}


GameApp::~GameApp()
{
	delete m_currentState;
}

bool GameApp::update(yam2d::ESContext *context, float deltaTime)
{
	assert(m_currentState != 0);

	return m_currentState->update(context, deltaTime);

	return true;
}

void GameApp::setState(GameState *gameState)
{
	m_currentState = gameState;
}

void GameApp::render(yam2d::ESContext *context)
{
	m_currentState->render(context);
}
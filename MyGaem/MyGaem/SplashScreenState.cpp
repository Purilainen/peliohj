#include "SplashScreenState.h"


SplashScreenState::SplashScreenState(GameApp* gameApp)
    : GameState(gameApp)
	, m_gameApp(gameApp)
	, m_totalTime(0)
	, m_sprite(0)
	, m_newTexture(0)
	, m_batch(0)
{
	m_batch = new yam2d::SpriteBatchGroup();

	m_newTexture = new yam2d::Texture("burger_01.png");

	m_sprite = new yam2d::Sprite(0);
}


SplashScreenState::~SplashScreenState()
{
}

bool SplashScreenState::update(yam2d::ESContext *context, float deltaTime)
{
	m_totalTime += deltaTime;

	count += deltaTime;
	// Clear sprite before add new dynamic sprites.
	m_batch->clear();
	if (m_totalTime <= 3.0f)
	{
		// Add sprite. Rotate it. Scale it.
		m_batch->addSprite(m_newTexture, m_sprite, yam2d::vec2(0, 0), count * 2, yam2d::vec2(400, 300));
	}
	else
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}
	return true;
}

void SplashScreenState::render(yam2d::ESContext *context)
{
	// Set OpenGL clear color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the viewport to be full window area.
	glViewport(0, 0, context->width, context->height);

	// Set projection to identity
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate half screen size
	float left = -0.5f*context->width;
	float right = 0.5f*context->width;
	float bottom = -0.5f*context->height;
	float top = 0.5f*context->height;

	// Set OpenGL orthogonal projection for screen size <esContext->width,esContext->height>
	glOrthof(float(int(left)), float(int(right)), float(int(bottom)), float(int(top)), -1.0, 1.0f);

	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable alpha blending (transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw batched objects to screen.
	m_batch->render();
}
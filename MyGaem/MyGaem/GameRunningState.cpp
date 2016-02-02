#include "GameRunningState.h"


GameRunningState::GameRunningState(GameApp* gameApp)
    : GameState(gameApp)
    , m_gameApp(gameApp)
    , m_compfactory(0)
    , m_tmap(0)
    , m_zoom(1.0f)
{
    m_compfactory = new yam2d::DefaultComponentFactory();
    m_tmap = new yam2d::TmxMap();

    bool checker = m_tmap->loadMapFile("level01.tmx", m_compfactory);

    if (checker)
    {
        m_tmap->getCamera()->setPosition(yam2d::vec2(m_tmap->getWidth() / 2.0f - 0.5f, m_tmap->getHeight() / 2.0f - 0.5f));
    }
    else
    {
        yam2d::esLogMessage("Could not load tile map");
    }
}

GameRunningState::~GameRunningState()
{
}

bool GameRunningState::update(yam2d::ESContext *context, float deltaTime)
{
   //Set zoom via mouse wheel
    setZoom(getZoom() - yam2d::getMouseWheelDelta());

    

    if (yam2d::getKeyState(yam2d::KEY_ESCAPE) == 1)
    {
        getApp()->setState(new MainMenuState(getApp()));
        return true;
    }

    m_tmap->update(deltaTime);
    return true;   
}

void GameRunningState::render(yam2d::ESContext *context)
{
    // Set OpenGL clear color
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set screen size to camera
    m_tmap->getCamera()->setScreenSize(context->width, context->height, 400 / getZoom());

    m_tmap->render();
}

float GameRunningState::getZoom()
{
    return m_zoom;
}

void GameRunningState::setZoom(float newZoom)
{
    m_zoom = slm::clamp(newZoom, 0.25f, 8.0f);
}
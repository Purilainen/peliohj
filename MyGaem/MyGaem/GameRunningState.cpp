#include "GameRunningState.h"


GameRunningState::GameRunningState(GameApp* gameApp)
    : GameState(gameApp)
    , m_gameApp(gameApp)
    , m_compfactory(0)
    , m_tmap(0)
    , m_zoom(1.0f)
{
    m_compfactory = new MyGameComponentFactory();
    m_tmap = new yam2d::TmxMap();

    bool checker = m_tmap->loadMapFile("map01.tmx", m_compfactory);

    if (checker)
    {
        m_tmap->getCamera()->setPosition(yam2d::vec2(m_tmap->getWidth() / 2.0f - 0.5f, m_tmap->getHeight() / 2.0f - 0.5f));
    }
    else
    {
        yam2d::esLogMessage("Could not load tile map");
    }

    m_tmap->findGameObjectByName("PlayerPad")->getComponent<PlayerController>();
}

GameRunningState::~GameRunningState()
{
}

bool GameRunningState::update(yam2d::ESContext *context, float deltaTime)
{
   //Set zoom via mouse wheel
    setZoom(getZoom() - yam2d::getMouseWheelDelta());
    //std::string name;
    
    
    yam2d::vec2 pos = m_tmap->findGameObjectByName("PlayerPad")->getPosition();

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

yam2d::GameObject* GameRunningState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
{
    // Load texture to be used as texture for sprite.
    yam2d::Ref<yam2d::Texture> texture = new yam2d::Texture(bitmapFileName.c_str());

    // If user wants to create texture which white colors is treated as a transparent color.
    if (isWhiteTransparentColor)
    {
        // Set white to transparent. Here color values are from 0 to 255 (RGB)
        texture->setTransparentColor(255, 255, 255);
    }

    // Create new sprite GameObject from texture.
    yam2d::GameObject* gameObject = new yam2d::GameObject(0, 0);
    yam2d::Ref<yam2d::SpriteComponent> sprite = new yam2d::SpriteComponent(gameObject, texture);

    // Resize the sprite to be correct size
    gameObject->setSize(sizeX, sizeY);

    // Add sprite component to game object
    gameObject->addComponent(sprite);
    return gameObject;
}

yam2d::GameObject* GameRunningState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor)
{
    // Load texture to be used as texture for sprite.
    yam2d::Ref<yam2d::Texture> texture = new yam2d::Texture(bitmapFileName.c_str());

    // If user wants to create texture which white colors is treated as a transparent color.
    if (isWhiteTransparentColor)
    {
        // Set white to transparent. Here color values are from 0 to 255 (RGB)
        texture->setTransparentColor(255, 255, 255);
    }

    // Create new sprite GameObject from texture.
    yam2d::GameObject* gameObject = new yam2d::GameObject(0, 0);
    yam2d::Ref<yam2d::SpriteComponent> sprite = new yam2d::SpriteComponent(gameObject, texture);

    // Resize the sprite to be correct size
    gameObject->setSize(sizeX, sizeY);

    // Specify clip area by start point and size in pixels
    yam2d::Sprite::PixelClip clip;
    clip.topLeft.x = clipStartX;
    clip.topLeft.y = clipStartY;
    clip.clipSize.x = clipSizeX;
    clip.clipSize.y = clipSizeY;

    // Set pixel clip for sprite
    sprite->getSprite()->setClip(float(texture->getWidth()), float(texture->getHeight()), clip);

    // Add sprite component to game object
    gameObject->addComponent(sprite);
    return gameObject;
}

float GameRunningState::getZoom()
{
    return m_zoom;
}

void GameRunningState::setZoom(float newZoom)
{
    m_zoom = slm::clamp(newZoom, 0.25f, 8.0f);
}
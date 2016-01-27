#include "MainMenuState.h"
#include <iostream>


yam2d::GameObject* MainMenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
{
    // Load texture to be used as texture for sprite.
	yam2d::Texture* texture = new yam2d::Texture(bitmapFileName.c_str());

    // If user wants to create texture which white coros is treated as atransparent color.
    if (isWhiteTransparentColor)
    {
        // Set white to transparent. Here color values are from 0 to 255 (RGB)
        texture->setTransparentColor(255, 255, 255);
    }

    // Create new sprite GameObject from texture.
	yam2d::GameObject* gameObject = new yam2d::GameObject(0,0);
	yam2d::SpriteComponent* sprite = new yam2d::SpriteComponent(gameObject, texture);

    // Resize the sprite to be correct size
    gameObject->setSize(sizeX, sizeY);

    // Add sprite component to game object
    gameObject->addComponent(sprite);
    return gameObject;
}
yam2d::GameObject* MainMenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false)
{
    // Load texture to be used as texture for sprite.
	yam2d::Texture* texture = new yam2d::Texture(bitmapFileName.c_str());

    // If user wants to create texture which white coros is treated as atransparent color.
    if (isWhiteTransparentColor)
    {
        // Set white to transparent. Here color values are from 0 to 255 (RGB)
        texture->setTransparentColor(255, 255, 255);
    }

    // Create new sprite GameObject from texture.
    yam2d::GameObject* gameObject = new yam2d::GameObject(0, 0);
    yam2d::SpriteComponent* sprite = new yam2d::SpriteComponent(gameObject, texture);

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
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(GameApp* gameApp)
    : GameState(gameApp)
	, m_gameApp(gameApp)
	, m_map(0)
	
{
    //batch = new SpriteBatchGroup();
    yam2d::vec2 tileSize(64, 64);
    //startButtonTexture = new yam2d::Texture("startButton.png");
    //exitButtonTexture = new yam2d::Texture("exitButton.png");

    m_map = new yam2d::Map(tileSize.x, tileSize.y);
    //map = m_map;

    yam2d::Layer* backgroundLayer = new yam2d::Layer(m_map, "Background", 1.0f, true, false);
    yam2d::Layer* objectLayer = new yam2d::Layer(m_map, "Objects", 1.0f, true, false);

    m_map->addLayer(yam2d::Map::BACKGROUND0, backgroundLayer);
    m_map->addLayer(yam2d::Map::MAPLAYER0, objectLayer);

    yam2d::GameObject* exitGameObject = createSpriteGameObject("exitButton.png", 64.0f, 64.0f, true);
    objectLayer->addGameObject(exitGameObject);
    exitGameObject->setPosition(yam2d::vec2(0, 0));

    yam2d::GameObject* startGameObject = createSpriteGameObject("startButton.png", 64.0f, 64.0f, true);
    objectLayer->addGameObject(startGameObject);
    startGameObject->setPosition(yam2d::vec2(0, 2.0f));

	exitGameObject->setName("exit");
	startGameObject->setName("start");

}

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::update(yam2d::ESContext *context, float deltaTime)
{
	float mouseX = float(yam2d::getMouseAxisX());
	float mouseY = float(yam2d::getMouseAxisY());
    count += deltaTime;
    
	yam2d::vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);
    
	yam2d::GameObject* pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);

	
	std::string start = "start";
	std::string exit = "exit";
	if (pickedObject != nullptr)
	{
		std::string test1 = pickedObject->getName();

		if (test1.compare(start) == 0)
		{
			//getApp()->setState(new GameRunningState(getApp()));
			//return true;
			yam2d::esLogMessage("Object %s picked!", pickedObject->getName().c_str());
			return true;
		}
		else if (test1.compare(exit) == 0)
		{
			yam2d::esLogMessage("Object %s picked!", pickedObject->getName().c_str());
			return true;
		}
	}

    
    m_map->update(deltaTime);

    return true;
}

void MainMenuState::render(yam2d::ESContext *context)
{
    // Set OpenGL clear color (dark gray)
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Set screen size to camera.
    m_map->getCamera()->setScreenSize(context->width, context->height, 720, 1280.0f / 720.0f);

    // Render map and all of its layers containing GameObjects to screen.
    m_map->render();
}


#include "MainMenuState.h"
#include <iostream>


yam2d::GameObject* MainMenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
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
	yam2d::GameObject* gameObject = new yam2d::GameObject(0,0);
	yam2d::Ref<yam2d::SpriteComponent> sprite = new yam2d::SpriteComponent(gameObject, texture);

    // Resize the sprite to be correct size
    gameObject->setSize(sizeX, sizeY);

    // Add sprite component to game object
    gameObject->addComponent(sprite);
    return gameObject;
}
yam2d::GameObject* MainMenuState::createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, int clipStartX, int clipStartY, int clipSizeX, int clipSizeY, bool isWhiteTransparentColor = false)
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
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(GameApp* gameApp)
    : GameState(gameApp)
	, m_gameApp(gameApp)
	, m_map(0)
    , m_backGroundLayer(0)
    , m_objectLayer(0)
    , m_totalTime(0)
	
{
    yam2d::vec2 tileSize(64, 64);

    m_map = new yam2d::Map(tileSize.x, tileSize.y);

    
    m_objectLayer = new yam2d::Layer(m_map, "Objects", 1.0f, true, false);
    m_backGroundLayer = new yam2d::Layer(m_map, "Background", 1.0f, true, false);

    m_map->addLayer(yam2d::Map::BACKGROUND0, m_backGroundLayer);
    m_map->addLayer(yam2d::Map::MAPLAYER0, m_objectLayer);

    //Creating background gameObject - image, size, bool isWhiteTransparentColor
    yam2d::Ref<yam2d::GameObject> background = createSpriteGameObject("background.png", 1336.0f, 768.0f, false);
    m_backGroundLayer->addGameObject(background);

    // Creating start button game object
    // First image size, second clipStart X & Y, third clipSize
    yam2d::Ref<yam2d::GameObject> start = createSpriteGameObject("buttons.png", 402.0f / 2, 102.0f / 2, 0, 0, 402, 102, true);
    m_objectLayer->addGameObject(start);
    start->setPosition(yam2d::vec2(-1.0f, 1.0f));
    start->setName("start");

    // Creating exit button game object
    // First image size, second clipStart X & Y, third clipSize
    yam2d::Ref<yam2d::GameObject> exit = createSpriteGameObject("buttons.png", 402.0f / 2, 102.0f / 2, 0, 103.0f, 402, 102, true);
    m_objectLayer->addGameObject(exit);
    exit->setPosition(yam2d::vec2(3.0f, 1.0f));
    exit->setName("exit");
    	
}

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::update(yam2d::ESContext *context, float deltaTime)
{
	float mouseX = float(yam2d::getMouseAxisX());
	float mouseY = float(yam2d::getMouseAxisY());
    count += deltaTime;
    m_totalTime += deltaTime;
    
    yam2d::vec2 originSize = { 201.0f, 51.0f };
	yam2d::vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);
    
	yam2d::GameObject* pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);
    
	std::string start = "start";
	std::string exit = "exit";
	if (pickedObject != nullptr)
	{
        yam2d::vec2 sizeEffect = { 300.0f, 75.0f };
        
		std::string test1 = pickedObject->getName();

		if (test1.compare(start) == 0)
		{
            
			//getApp()->setState(new GameRunningState(getApp()));
			//return true;
			yam2d::esLogMessage("Object %s picked!", pickedObject->getName().c_str());
            if (yam2d::getMouseButtonState(yam2d::MOUSE_LEFT) == 1)
            {
                getApp()->setState(new GameRunningState(getApp()));
                return true; 
            }
            else
            {
                pickedObject->setSize(sizeEffect);
            }
            
            return true;
		}
        else if (test1.compare(exit) == 0)
        {
            yam2d::esLogMessage("Object %s picked!", pickedObject->getName().c_str());
            

            if (yam2d::getMouseButtonState(yam2d::MOUSE_LEFT) == 1)
            {
                //return false - quit app
                return false;
            }
            else
            {
                pickedObject->setSize(sizeEffect);
                return true; 
            }
            
            
        }
	}
    else
    {
        m_map->findGameObjectByName("start")->setSize(originSize);
        m_map->findGameObjectByName("exit")->setSize(originSize);
        m_totalTime = 0;
        return true;
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


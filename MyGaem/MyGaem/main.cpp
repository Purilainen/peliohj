// Include OpenGL ES Engine utils
#include <es_util.h>

#include "GameApp.h"
#include "GameState.h"
#include "SplashScreenState.h"


float count = 0.0f;

using namespace yam2d;

namespace
{
    GameApp* gameApp;
}


// Initialize the game
bool init(ESContext *esContext)
{
 
    gameApp = new GameApp;

    gameApp->setState(new SplashScreenState(gameApp));

	return true;
}


// Deinitialize the game
void deinit(ESContext *esContext)
{
    delete gameApp;
}


// Draw game
void draw(ESContext *esContext)
{
	gameApp->render(esContext);
}


// update game
void update(ESContext *esContext, float deltaTime)
{
	count += deltaTime;
	if (count > 1.0f)
		count = 0.0f;

	gameApp->update(esContext, deltaTime);
}

//extern "C" void app_dummy();

int main(int argc, char *argv[])
{


	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "MY GAEM WINDOW", 1280, 720, ES_WINDOW_DEFAULT);

	esRegisterInitFunc(&esContext, init);
	esRegisterDrawFunc(&esContext, draw);
	esRegisterUpdateFunc(&esContext, update);
	esRegisterDeinitFunc(&esContext, deinit);

	esMainLoop(&esContext);
	return 0;
}

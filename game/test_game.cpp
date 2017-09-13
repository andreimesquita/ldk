#include <ldare/game.h>
#include <stdio.h>

using namespace ldare;
using namespace ldare::game;
using namespace ldare::render;

static ldare::game::GameContext gameContext;

// here goes all persistent stuff the game needs along its execution
// the goal here is to request enough memory to do whatever the game needs
// this is what most game engines does behind the scenes to make it 'friendly'
// to programmers but charges 
struct GameData
{
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	Shader shader;
} *gameMemory;

//---------------------------------------------------------------------------
// Game Engine Initialization
//---------------------------------------------------------------------------
ldare::game::GameContext gameInit()
{
	gameContext.windowWidth = 600; 						// game window width
	gameContext.windowHeight = 600; 					// game window height
	gameContext.gameMemorySize = MEGABYTE(10);// requested game memory size
	gameContext.clearColor[0] = 0;
	gameContext.clearColor[1] = 1.0f;
	gameContext.clearColor[2] = 1.0f;
	return gameContext; 											// let the engine know what we want
}

//---------------------------------------------------------------------------
// Game start callback
//---------------------------------------------------------------------------
void gameStart(void* mem)
{
	LogInfo("Game started");
	if(!mem)
	{
		LogError("initial memory allocation failed");
	}
	gameMemory = (GameData*) mem;
	gameMemory->shader = render::loadShader(nullptr, nullptr);

	Sprite sprite;
	sprite.color = Vec3{0.0, 1.0, 1.0};
	sprite.width = sprite.height = 0.2f;
	sprite.position = Vec3{-.1, -.1, 0};
	gameMemory->sprite1 = sprite;
	
	sprite.color = Vec3{0.0, 1.0, 0.0};
	sprite.width = sprite.height = 0.5f;
	sprite.position = Vec3{0.7, 0.2, 0};
	gameMemory->sprite2 = sprite;
	
	sprite.color = Vec3{0.0, 0.0, 1.0};
	sprite.width = sprite.height = 0.4f;
	sprite.position = Vec3{-0.8, -0.5, 0};
	gameMemory->sprite3 = sprite;

}

//---------------------------------------------------------------------------
// Game update
//---------------------------------------------------------------------------
float x=0;
float y=0;
const float step = 0.01;
void gameUpdate(const Input& input)
{
	ldare::game::KeyState keyValue = input.keyboard[KBD_W];

	if ( input.keyboard[KBD_W].state )
		y += step;

	if ( input.keyboard[KBD_S].state )
		y -= step;

	if ( input.keyboard[KBD_A].state )
		x -= step;

	if ( input.keyboard[KBD_D].state )
		x += step;

	if (x >1) x = -1;
	if (y >1) y = -1;
	gameMemory->sprite1.position.x = x;
	gameMemory->sprite1.position.y = y;

	gameMemory->sprite3.color.y = 1-y; 
	gameMemory->sprite3.color.y = 1-x; 

	render::begin();
		render::submit(gameMemory->shader, gameMemory->sprite1);
		render::submit(gameMemory->shader, gameMemory->sprite2);
		render::submit(gameMemory->shader, gameMemory->sprite3);
	render::end();
	render::flush();

	gameMemory->sprite2.position.y = y;
	gameMemory->sprite3.position.x = gameMemory->sprite3.position.y = -x;
}

//---------------------------------------------------------------------------
// Game finalization
//---------------------------------------------------------------------------
void gameStop()
{
	LogInfo("Game stopped");
}

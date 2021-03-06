#pragma once
#include <lua/lua.hpp>
#include <string>
#include "../_vs2015/Component.hpp"
#include "../_vs2015/GameObject_.hpp"
#include "../_vs2015/collider.h"
using namespace Engine::Core;

class LuaScript : public Component
{
public:
	LuaScript();
	void registerFunctions();
	static int MovePlayer(lua_State* state);
	void Initialize();
	static int ShowHint(lua_State * state);
	static int OpenDoor(lua_State * state);
	static int OnTriggerEnter(lua_State * state);
	static int PushBackObj(lua_State * state);
	static int CollisionBetween(lua_State * state);
	static int SphereCollisionBetween(lua_State * state);
	static int GetGameTime(lua_State* state);
	static int NewButton(lua_State* state);
	static int NewSprite(lua_State* state);
	static int NewText(lua_State* state);
	static int AddToMenu(lua_State* state);
	static int SetEvent(lua_State* state);
	static int PlaySoundOneShot(lua_State* state);
	static int SetButtonSpriteNormal(lua_State* state);
	static int SetButtonSpriteHover(lua_State* state);
	static int SetButtonSpriteClick(lua_State* state);
	static int SetUIPosition(lua_State* state);
	static int SetText(lua_State* state);

	//static int KeyDown(lua_State * state);
	void stackDump(lua_State *state, const char * pre);
	void update() override;
	void start() override;
	glm::vec3 GetPos();
private:
	glm::vec3 lastPos;
	lua_State *  state_;
	static std::string message;
	collider* parent;
};


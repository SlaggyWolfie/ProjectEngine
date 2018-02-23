#pragma once
#include <lua/lua.hpp>
#include <string>
#include "Component.hpp"
using namespace Engine::Core;

class LuaScript: public Component
{
public:
	LuaScript();
	void LuaScript::registerFunctions();
	void GameLoop();
	static int MovePlayer(lua_State* state);
	void Initialize();
	static int ShowHint(lua_State * state);
	static int OpenDoor(lua_State * state);
	void printMsg();
	void stackDump(lua_State *state, const char * pre);
	void update() override;
	void start() override;
private:
	lua_State *  state_;
	static std::string message;
};


#pragma once
#ifndef KEYZ_HPP
#define KEYZ_HPP
#include <set>
#include <SFML/Window.hpp>
#include <map>

enum KeyState
{
	NONE, PRESSED, NOT_PRESSED, RELEASED
};

class InputHandler
{
private:
	static std::map<sf::Mouse::Button, KeyState> _mouseButtons;
	static std::map<sf::Keyboard::Key, KeyState> _keyboardKeys;
	static void testKey(sf::Keyboard::Key key);
	static void testKey(sf::Mouse::Button key);
public:
	static bool keyDown(sf::Mouse::Button key);
	static bool keyUp(sf::Mouse::Button key);
	static bool keyPressed(sf::Mouse::Button key);
	static bool keyDown(sf::Keyboard::Key key);
	static bool keyUp(sf::Keyboard::Key key);
	static bool keyPressed(sf::Keyboard::Key key);
	static void updateEvent(sf::Event event);
	static void reset();
};

#endif
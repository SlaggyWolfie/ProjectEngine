#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../../_vs2015/Service.hpp"
#include <memory>

/**
 * Defines the basic structure for a game, with defaults already filled in.
 * The only item that MUST be overridden/implemented is _initializeScene()
 * where you build up your world, the rest is optional to override (with care/caution).
 */
namespace Engine
{
	class SceneManager;

	namespace Rendering
	{
		class RenderManager;
		class LightManager;
	}
	namespace Core
	{
		class GameLoop;
	}
	class Game : public Engine::Service
	{
	public:
		Game();
		virtual ~Game();

		//creates a window, initializes glew, a renderer and a world instance
		void initialize() override;
		sf::RenderWindow* getWindow() const;
		void processEvents();
		void run();
		bool isRunning() const;
		void exit();

	private:
		//print info about the current driver version etc
		static void printVersionInfo();
		//initialize the extension wrangler
		static void initializeGlew();
		void initializeWindow();
		void initializeServices();

		//initialize the actual scene, HAS to be done by a subclass
		void initializeScene() const;
		void initializeScene(const std::string& filepath) const;
		std::unique_ptr<sf::RenderWindow> _window;  //sfml window to render into
		//Renderer* _renderer;        //the renderer class to render the world
		//World* _world;              //the root game object that represents our scene
		//float _fps;                 //stores the real fps
		Rendering::RenderManager* _renderManager;
		Rendering::LightManager* _lightManager;
		Core::GameLoop* _gameLoop;
		SceneManager* _sceneManager;

		std::string _defaultScenePath;

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	};
}

#endif // GAME_HPP

#include <iostream>

#include "Game.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "GameLoop.hpp"

//#include "RenderManager.hpp"
#include "../_vs2015/RenderManager.hpp"

namespace Engine
{
	Game::Game()
	{
		//ctor
	}

	Game::~Game()
	{
		//dtor
		_window.release();
	}

	void Game::initialize()
	{
		std::cout << "Initializing engine..." << std::endl << std::endl;
		initializeWindow();
		printVersionInfo();
		initializeGlew();
		initializeServices();
		std::cout << std::endl << "Engine initialized." << std::endl << std::endl;

		initializeScene();
	}

	sf::RenderWindow* Game::getWindow() const
	{
		return _window.get();
	}

	bool Game::running()
	{
		return _window->isOpen();
	}

	void Game::exit()
	{
		_window->close();
		delete this;
	}

	///SETUP

	void Game::initializeWindow() {
		std::cout << "Initializing window..." << std::endl;
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Thot", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
		//_window = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game!", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
		//_window->setVerticalSyncEnabled(true);
		std::cout << "Window initialized." << std::endl << std::endl;
	}

	void Game::printVersionInfo()
	{
		std::cout << "Context info:" << std::endl;
		std::cout << "----------------------------------" << std::endl;
		//print some debug stats for whoever cares
		const GLubyte *vendor = glGetString(GL_VENDOR);
		const GLubyte *renderer = glGetString(GL_RENDERER);
		const GLubyte *version = glGetString(GL_VERSION);
		const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		//nice consistency here in the way OpenGl retrieves values
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		printf("GL Vendor : %s\n", vendor);
		printf("GL Renderer : %s\n", renderer);
		printf("GL Version (string) : %s\n", version);
		printf("GL Version (integer) : %d.%d\n", major, minor);
		printf("GLSL Version : %s\n", glslVersion);

		std::cout << "----------------------------------" << std::endl << std::endl;
	}

	void Game::initializeGlew()
	{
		std::cout << "Initializing GLEW..." << std::endl;
		//initialize the opengl extension wrangler
		const GLint glewStatus = glewInit();
		std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
	}

	void Game::initializeServices()
	{
		//Create
		_renderManager = new Engine::Rendering::RenderManager();

		//Register
		Engine::ServiceLocator::instance()->addService(static_cast<Service*>(_renderManager));
	}

	void Game::initializeScene() const
	{
		initializeScene(_defaultScenePath);
	}


	void Game::initializeScene(const std::string& filepath) const
	{
		std::cout << "Loading Scene..." << std::endl;
		//load scene
		std::cout << "Loaded Scene." << std::endl;
	}

	void Game::processEvents()
	{
		sf::Event event{};
		bool exit = false;

		//we must empty the event queue
		while (_window->pollEvent(event))
		{
			//give all system event listeners a chance to handle events
			//optionally to be implemented by you for example you could implement a
			//SystemEventDispatcher / SystemEventListener pair which allows Listeners to
			//register with the dispatcher and then do something like:
			//SystemEventDispatcher::dispatchEvent(event);

			switch (event.type)
			{

			case sf::Event::MouseWheelMoved:
			case sf::Event::MouseWheelScrolled:
			{
				//mouseScrollWheel += (event.mouseWheel.delta * 0.01f);
				//if (mouseScrollWheel < 0) mouseScrollWheel = 0;
				break;
			}
			case sf::Event::Closed:
				exit = true;
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					exit = true;
				}
				break;
			case sf::Event::Resized:
				//would be better to move this to the renderer
				//this version implements nonconstrained match viewport scaling
				glViewport(0, 0, event.size.width, event.size.height);
				break;

			default:
				break;
			}
		}

		if (exit) Game::exit();
		//return event;
	}
}
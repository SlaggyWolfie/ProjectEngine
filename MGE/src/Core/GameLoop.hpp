#pragma once
#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <memory>
#include "../../_vs2015/Service.hpp"
#include "../../_vs2015/FunctionGroup.hpp"
#include "../_vs2015/RenderManager.hpp"

namespace Engine
{
	class Game;

	namespace Core
	{
		class Component;
		class GameLoop : public Service
		{
		public:

			GameLoop();
			virtual ~GameLoop();
			GameLoop(const GameLoop& other) = delete;
			GameLoop& operator=(const GameLoop& other) = delete;
			void initialize() override;
			void subscribe(Component* component);
			void unsubscribe(Component* component);
			bool isSubscribed(Component* component);

			void run();

		private:

			//std::vector<Component*> _components;
			std::vector<std::shared_ptr<Component>> _components;
			std::shared_ptr<Component> find(Component* component);
			void update();
			void fixedUpdate();
			void lateUpdate();
			Rendering::RenderManager* _renderManager{};
			//AnimationManager _animationManager;
			//CollisionManager _collisionManager;
			//PhysicsManager _physicsManager;

			void createOwnedLoops();
			void destroyOwnedLoops();


			//sf::RenderWindow* _window;
			Game* _game{};
		};
	}
}

#endif // GAMELOOP_HPP

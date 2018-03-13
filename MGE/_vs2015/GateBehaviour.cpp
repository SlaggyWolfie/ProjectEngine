#include "GateBehaviour.h"
#include "Camera_.hpp"
#include "GameObject_.hpp"
#include "Transform.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ServiceLocator.hpp"
#include "Core/Game.hpp"
#include "Time.hpp"
using namespace Engine::Core;
using namespace Engine;


GateBehaviour::GateBehaviour()
{

	
}

void GateBehaviour::update()
{
	TogglePositions();
	CheckCollision();

	
}

bool GateBehaviour::AllPressed()
{
	for (int i = 0; i < _plates.size(); i++)
	{
		if (_plates[i]->IsPressed() == false)
			return false;
	}
	return true;
}
void GateBehaviour::CheckCollision()
{
	//std::vector<collider*> colList= ServiceLocator::instance()->getService<ColliderManager>()->CheckBoxCollision(this->getGameObject()->getComponent<collider>());
	///*std::cout << colList.size()<<" size " << std::endl;*/
	///*std::cout << this->getGameObject()->getComponent<collider>()->GetPos() << " pos " << std::endl;*/

	//for (int i = 0; i < colList.size(); i++)
	//{
	//}
}

void GateBehaviour::start()
{
	Transform* transform = getGameObject()->getTransform();
	_notActivatedPos = transform->getPosition();
	_activatedPos = transform->getPosition() + glm::vec3(0, 400, 0);
}

void GateBehaviour::AddPlate(PressurePlateBehaviour * plate)
{
	_plates.push_back(plate);
}

bool GateBehaviour::IsActivated()
{
	return false;
}

void GateBehaviour::TogglePositions()
{
	if (AllPressed())
	{
		this->getGameObject()->getTransform()->setPosition(lerp(this->getGameObject()->getTransform()->getPosition(), _activatedPos, 0.05f));
	}
	else
	{
		this->getGameObject()->getTransform()->setPosition(lerp(this->getGameObject()->getTransform()->getPosition(), _notActivatedPos, 0.05f));
	}
}
void GateBehaviour::destroy()
{
	delete this;
}

bool GateBehaviour::isUniquePerGameObject()
{
	return true;
}
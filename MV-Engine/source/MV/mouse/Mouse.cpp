#include "Mouse.hpp"
#include <iostream>
namespace mv
{
	void Mouse::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(object, states);
	}

	void Mouse::positionUpdate()
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*mv::Scene::getInstance().GetPointerToWindow());
		sf::Vector2f worldPos = mv::Scene::getInstance().GetPointerToWindow()->mapPixelToCoords(pixelPos);
		object.setPosition(worldPos);
	}

	void Mouse::checkBorders()
	{
		auto windowDimensions = mv::Scene::getInstance().GetPointerToWindow()->getSize();
		
		if (windowDimensions.y - sf::Mouse::getPosition(*mv::Scene::getInstance().GetPointerToWindow()).y < tolerance.y)
		{
			mv::Scene::getInstance().moveView(mv::Scene::DIRECTION::DOWN);
		}
		else if (sf::Mouse::getPosition(*mv::Scene::getInstance().GetPointerToWindow()).y < tolerance.y)
		{
			mv::Scene::getInstance().moveView(mv::Scene::DIRECTION::TOP);
		}

		if (windowDimensions.x - sf::Mouse::getPosition(*mv::Scene::getInstance().GetPointerToWindow()).x < tolerance.x)
		{
			mv::Scene::getInstance().moveView(mv::Scene::DIRECTION::RIGHT);
		}
			
		else if (sf::Mouse::getPosition(*mv::Scene::getInstance().GetPointerToWindow()).x < tolerance.x)
		{
			mv::Scene::getInstance().moveView(mv::Scene::DIRECTION::LEFT);
		}

	}

	Mouse::Mouse(const Mouse::TYPE & type, bool movingBorderPermission)
		:tolerance(mv::constants::defaults::BORDER_TOLERANCE.x, mv::constants::defaults::BORDER_TOLERANCE.y),
		Ticker(this)
	{
		//texture to do
	}

	Mouse::~Mouse()
	{
		Ticker::removePointer(this);
	}

	void Mouse::changeType(const Mouse::TYPE & type)
	{
		//to do
	}

	void Mouse::setBorderMovingMode(bool mode)
	{
		movingPermission = mode;
	}

	void Mouse::setTolerance(sf::Vector2u value)
	{
		tolerance = value;
	}

	void Mouse::setTolerance(unsigned long value_x, unsigned long value_y)
	{
		setTolerance(sf::Vector2u(value_x, value_y));
	}

	void Mouse::tick()
	{
		positionUpdate();

		if(movingPermission)
			checkBorders();
	}
}

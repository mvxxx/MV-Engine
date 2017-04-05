#include "Scene.hpp"

namespace mv
{
	Scene* Scene::instance;

	void Scene::display()
	{
		window->display();
	}

	Scene & Scene::getInstance()
	{
		if (instance == 0)
			Logger::Log(constants::error::singleton::SINGLETON_NOT_INITED, Logger::STREAM::BOTH, Logger::TYPE::ERROR);
	
		return *instance;
	}

	void Scene::createInstance(const std::string& title, const sf::Vector2f& dimensions)
	{
		if (instance == 0)
		{
			instance = new Scene(title, dimensions);
			instance->view.setCenter((MapManager::getInstance().getCellDimensions().x*MapManager::getInstance().getUnitWorldSize().x)/2.f,(MapManager::getInstance().getCellDimensions().y*MapManager::getInstance().getUnitWorldSize().y)/2.f);
			instance->window->setView(instance->view);
			instance->window->setFramerateLimit(128);
		}
	}


	void Scene::clear()
	{
		window->clear();
	}

	Scene::Scene(const std::string& title, const sf::Vector2f& dimensions)
		:speed(2.f)
	{
		window = new sf::RenderWindow(sf::VideoMode(dimensions.x, dimensions.y), title);
	}

	Scene::~Scene()
	{
		if (window != nullptr)
			delete window;
	}

	bool Scene::isOpen() const
	{
		return window->isOpen();
	}

	void Scene::zoom(ZOOM_STATE state)
	{
		switch (state)
		{
			case ZOOM_STATE::ZOOM:
			{
				instance->view.zoom(1+constants::scene::ZOOM_SPEED);
				break;
			}

			case ZOOM_STATE::DECREASE:
			{
				instance->view.zoom(1-constants::scene::ZOOM_SPEED);
				break;
			}
		}

		instance->window->setView(instance->view);
	}

	void Scene::moveView(DIRECTION direction)
	{
		switch (direction)
		{
			case DIRECTION::TOP:
			{
				view.move(0,-speed);
				break;
			}
			case DIRECTION::RIGHT:
			{
				view.move(speed,0);
				break;
			}
			case DIRECTION::DOWN:
			{
				view.move(0, speed);
				break;
			}
			case DIRECTION::LEFT:
			{
				view.move(-speed, 0);
				break;
			}
		}
	}

	sf::RenderWindow * Scene::GetPointerToWindow()
	{
		return window;
	}

	void Scene::close()
	{
		window->close();
	}

	void Scene::moveViewRight()
	{
		moveView(DIRECTION::RIGHT);
	}

	void Scene::moveViewLeft()
	{
		moveView(DIRECTION::LEFT);
	}

	void Scene::moveViewTop()
	{
		moveView(DIRECTION::TOP);
	}

	void Scene::moveViewDown()
	{
		moveView(DIRECTION::DOWN);
	}

}

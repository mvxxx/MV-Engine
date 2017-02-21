#pragma once
#include <type_traits>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "MV/config/Config.hpp"
#include "MV/logger/logger.hpp"
#include "MV/cell/Cell.hpp"


namespace mv
{
	class Scene
	{
	public:
		//Constructor which creates a window
		Scene(std::string title = constants::defaults::UNNAMED, sf::Vector2f dimensions = constants::defaults::WINDOW_DIMENSIONS);

		~Scene();

		//Display on screen what has been rendered to the window so far
		void display();

		//Clears window
		void clear();

		//Tell whether or not the window is open
		bool isOpen() const;

		//Draws given collection of T objects
		//returns false if T doesn't inhert from sf::Drawable
		template < typename T= typename std::enable_if< std::is_base_of<sf::Drawable,T>::value,T>::type>
		bool drawCollection(std::vector<T> *collection);


		sf::RenderWindow *GetPointerToWindow();

		void close();

		void viewUpdate(sf::View *view);

	private:

		sf::RenderWindow *window;
	};


	template<typename T>
	inline bool Scene::drawCollection(std::vector<T>* collection)
	{
		for (auto&var : *collection)
			window->draw(var);

		return true;
	}

}
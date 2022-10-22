#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableInNewWindow.h"

class DrawableInNewWindow: public sf::Drawable
{
public:
	virtual void calcOptions(int size_x, int size_y) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	void drawInNewWindow(int size_x, int size_y, bool calc_settings=true) const;
};

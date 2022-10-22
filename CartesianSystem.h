#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class CartesianSystem: public sf::Drawable
{
	sf::Vector2f location, sizePix, scale;
	sf::Color axisColor, textColor;
	const std::map<double, std::string> *vertical, *gorisontal;

public:
	CartesianSystem();
	CartesianSystem& setLocation(float x, float y);
	CartesianSystem& setSizePixels(float x, float y);
	CartesianSystem& setScale(float x, float y);
	CartesianSystem& setVerticalSigns(const std::map<double, std::string> *arr);
	CartesianSystem& setGorisontalSigns(const std::map<double, std::string> *arr);
	CartesianSystem& setAxisColor(int r, int g, int b, int a=255);
	CartesianSystem& setTextColor(int r, int g, int b, int a = 255);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


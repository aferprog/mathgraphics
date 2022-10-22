#include "CartesianSystem.h"

CartesianSystem::CartesianSystem()
{
	vertical = gorisontal = nullptr;
	setAxisColor(0,0,0);
	setTextColor(255,0,0);
	location = { 0,0 };
	sizePix = { 100,100 };
	sizePix = { 1,1 };
}

CartesianSystem& CartesianSystem::setLocation(float x, float y)
{
	location = { x,y };
	return *this;
}

CartesianSystem& CartesianSystem::setSizePixels(float x, float y)
{
	sizePix = { x,y };
	return *this;
}

CartesianSystem& CartesianSystem::setScale(float x, float y)
{
	scale = { x,y };
	return *this;
}

CartesianSystem& CartesianSystem::setVerticalSigns(const std::map<double, std::string> *arr)
{
	vertical = arr;
	return *this;
}

CartesianSystem& CartesianSystem::setGorisontalSigns(const std::map<double, std::string> *arr)
{
	gorisontal = arr;
	return *this;
}

CartesianSystem& CartesianSystem::setAxisColor(int r, int g, int b, int a)
{
	axisColor = sf::Color(r, g, b, a);
	return *this;
}

CartesianSystem& CartesianSystem::setTextColor(int r, int g, int b, int a)
{
	textColor = sf::Color(r, g, b, a);
	return *this;
}

void CartesianSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	// vertical axis
	{
		sf::RectangleShape axis(sf::Vector2f(sizePix.x, 3));
		axis.setFillColor(axisColor);
		axis.setPosition({ location.x, location.y + sizePix.y });
		target.draw(axis);

		sf::Vector2f tip = { axis.getPosition().x + sizePix.x, axis.getPosition().y };

		sf::RectangleShape stick1(sf::Vector2f(15, 3));
		stick1.setRotation(160);
		stick1.setFillColor(axisColor);
		stick1.setPosition(sf::Vector2f(tip.x, tip.y + 2));
		target.draw(stick1);

		sf::RectangleShape stick2(sf::Vector2f(15, 3));
		stick2.setRotation(-161);
		stick2.setFillColor(axisColor);
		stick2.setPosition(sf::Vector2f(tip.x, tip.y + 3));
		target.draw(stick2);
	}
	// horisontal axis
	{
		sf::RectangleShape axis(sf::Vector2f(3, sizePix.y));
		axis.setFillColor(axisColor);
		axis.setPosition(location);
		target.draw(axis);

		sf::Vector2f tip = axis.getPosition();

		sf::RectangleShape stick1(sf::Vector2f(15, 3));
		stick1.setRotation(160 - 90);
		stick1.setFillColor(axisColor);
		stick1.setPosition(sf::Vector2f(tip.x + 3, tip.y + 2));
		target.draw(stick1);

		sf::RectangleShape stick2(sf::Vector2f(15, 3));
		stick2.setRotation(-161 - 90);
		stick2.setFillColor(axisColor);
		stick2.setPosition(sf::Vector2f(tip.x + 3, tip.y + 3));
		target.draw(stick2);
	}

	sf::Font font;
	font.loadFromFile("./font.ttf");
	for (const auto& el : *gorisontal) {
		sf::Vector2f pos (location.x + el.first*scale.x+7, location.y + sizePix.y + 8);
		sf::Text t(el.second.c_str(), font, 15);
		t.setFillColor(textColor);
		t.setPosition(pos);
		t.setRotation(90);
		target.draw(t);
	}

	char t = 1;
	for (const auto& el : *vertical) {
		t = -t;
		sf::Vector2f pos(location.x, location.y + sizePix.y - el.first * scale.y);
		sf::RectangleShape dot({ 6, 2 });
		dot.setPosition({pos.x-2, pos.y-1});
		dot.setFillColor(axisColor);
		target.draw(dot);
		
		sf::Vector2f posText;
		if (t > 0) {
			posText.x = pos.x + 5;
			posText.y = pos.y - 10;
		}
		else {
			posText.x = pos.x - el.second.size() * 10;
			posText.y = pos.y - 10;
		}
		sf::Text t(el.second.c_str(), font, 15);
		t.setFillColor(textColor);
		t.setPosition(posText);
		target.draw(t);
	}
}

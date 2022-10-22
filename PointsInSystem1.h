#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "DrawableInNewWindow.h"

template <class InputIt>
class PointsInSystem1 : public DrawableInNewWindow {
	bool toDrawAxis;
	InputIt begin, end;
	float lenght;
	sf::Vector2f location;
	sf::Color dotsColor, axisColor;

	sf::RectangleShape getPoint() const;
	sf::Vector2f getPointPosition(double val) const;
	sf::Text numToText(double num) const;

public:
	PointsInSystem1(InputIt begin, InputIt end);
	PointsInSystem1<InputIt>& setLenght(float lenght);
	PointsInSystem1<InputIt>& setDrawingAxis(bool status);
	PointsInSystem1<InputIt>& setDotsCollor(int r, int g, int b, int a = 255);
	PointsInSystem1<InputIt>& setAxisCollor(int r, int g, int b, int a = 255);
	PointsInSystem1<InputIt>& setLocation(float loc_x, float loc_y);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void calcOptions(int size_x, int size_y) override;
};


template<class InputIt>
inline sf::RectangleShape PointsInSystem1<InputIt>::getPoint() const
{
	sf::RectangleShape dot(sf::Vector2f(3, 6));
	dot.setFillColor(dotsColor);
	
	return dot;
}

template<class InputIt>
inline sf::Vector2f PointsInSystem1<InputIt>::getPointPosition(double val) const
{
	double min = *begin;
	double max = *(end - 1);
	double range = max - min;
	double scale = lenght * 0.95 / range;
	double offset = lenght * 0.025 + (val - min) * scale;
	return sf::Vector2f(location.x + offset, location.y + 1.5);
}

template<class InputIt>
inline sf::Text PointsInSystem1<InputIt>::numToText(double num) const
{
	std::ostringstream oss;
	oss << num;
	std::string str = oss.str();
	
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text(str.c_str(), font, 5);
	text.setFillColor(axisColor);
	return text;
}

template<class InputIt>
inline PointsInSystem1<InputIt>::PointsInSystem1(InputIt begin, InputIt end)
	:begin(begin), end(end)
{
	toDrawAxis = true;
	lenght = 200;
	location = { 10,10 };
	dotsColor = sf::Color(255, 0, 0);
	axisColor = sf::Color(0, 0, 0);
	//std::sort(begin, end);
}

template<class InputIt>
inline PointsInSystem1<InputIt>& PointsInSystem1<InputIt>::setLenght(float lenght)
{
	this->lenght = lenght;
	return *this;
}

template<class InputIt>
inline PointsInSystem1<InputIt>& PointsInSystem1<InputIt>::setDrawingAxis(bool status)
{
	toDrawAxis = status;
	return *this;
}

template<class InputIt>
inline PointsInSystem1<InputIt>& PointsInSystem1<InputIt>::setDotsCollor(int r, int g, int b, int a)
{
	this->dotsColor = sf::Color(r, g, b, a);
	return *this;
}

template<class InputIt>
inline PointsInSystem1<InputIt>& PointsInSystem1<InputIt>::setAxisCollor(int r, int g, int b, int a)
{
	this->axisColor = sf::Color(r,g,b,a);
	return *this;
}

template<class InputIt>
inline PointsInSystem1<InputIt>& PointsInSystem1<InputIt>::setLocation(float loc_x, float loc_y)
{
	this->location = sf::Vector2f(location);
	return *this;
}

template<class InputIt>
inline void PointsInSystem1<InputIt>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (toDrawAxis) {
		sf::RectangleShape axis(sf::Vector2f(lenght, 3));
		axis.setFillColor(axisColor);
		axis.setPosition(location);
		target.draw(axis);
	}
	
	double step = 10000;
	for (auto it = begin; it < end && step>=0; it++) {
		//if (it + 2 == end)
		sf::Vector2f pp = getPointPosition(*it);
		sf::Text text = numToText(*it);
		sf::RectangleShape point = getPoint();

		text.setPosition({pp.x, pp.y+ point.getSize().y / 2 +3});

		point.setPosition(sf::Vector2f(pp.x, pp.y-point.getSize().y/2));
		target.draw(point);
		//////////target.draw(text);


	}
	if (step < 0)
		throw std::runtime_error("Data isn't sorted");
}

template<class InputIt>
inline void PointsInSystem1<InputIt>::calcOptions(int size_x, int size_y)
{
	lenght = 0.9f * size_x;
	location = {size_x*0.05f, size_y/2.f};
}
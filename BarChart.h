#pragma once
#include "DrawableInNewWindow.h"
#include <vector>
#include <cmath>
#include <string>
#include "CartesianSystem.h"

template <class InputIt>
class BarChart: public DrawableInNewWindow {
	std::vector<std::pair<double, int>> bars;
	sf::Vector2f location, size;
	sf::Color barsColor, axisColor;
	
	double min, range;

	void makeBars(InputIt begin, InputIt end);
public:
	BarChart(InputIt begin, InputIt end);
	BarChart<InputIt>& setLocation(float x, float y);
	BarChart<InputIt>& setSize(float x, float y);
	BarChart<InputIt>& setAxisColor(int r, int g, int b, int a=255);
	BarChart<InputIt>& setBarsColor(int r, int g, int b, int a=255);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void calcOptions(int size_x, int size_y) override;
};


template<class InputIt>
inline void BarChart<InputIt>::makeBars(InputIt begin, InputIt end)
{
	size_t m = static_cast<size_t>(1+3.3221*log(end-begin));
	double step = (*(end - 1) - *begin) / m;

	InputIt curr = begin;
	double limit = *begin;

	for (size_t i = 0; i < m; i++) {
		std::pair <double, int> el = {limit+step/2, 0};
		limit += step;
		for (; curr<end && *curr < limit; curr++, el.second++);
		bars.push_back(el);
	}
	bars[bars.size() - 1].second++;
}

template<class InputIt>
inline BarChart<InputIt>::BarChart(InputIt begin, InputIt end)
{
	min = *begin;
	range = *(end-1)-*begin;
	makeBars(begin, end);

	setLocation(0,0);
	setAxisColor(0,0,0);
	setBarsColor(50,50,255);
	setSize(100, 100);
}

template<class InputIt>
inline BarChart<InputIt>& BarChart<InputIt>::setLocation(float x, float y)
{
	location = {x, y};
	return *this;
}

template<class InputIt>
inline BarChart<InputIt>& BarChart<InputIt>::setSize(float x, float y)
{
	size = {x, y};
	return *this;
}

template<class InputIt>
BarChart<InputIt>& BarChart<InputIt>::setAxisColor(int r, int g, int b, int a) {
	axisColor = sf::Color(r,g,b,a);
	return *this;
}

template<class InputIt>
BarChart<InputIt>& BarChart<InputIt>::setBarsColor(int r, int g, int b, int a) {
	barsColor = sf::Color(r, g, b, a);
	return *this;
}

template<class InputIt>
void BarChart<InputIt>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int maxHight = std::max_element(bars.begin(), bars.end(), [](const auto& l, const auto& r) {
			return l.second < r.second;
		})->second;
	sf::Vector2f scale(0.9*size.x/range, size.y*0.9/maxHight);

	float offset = 1;
	float step = (0.9 * size.x-bars.size()+1)/bars.size();
	// float k = size.y*0.9/ maxHight;

	
	for (const auto& el : bars) {
		sf::RectangleShape bar(sf::Vector2f(step, -el.second*scale.y));
		bar.setFillColor(barsColor);
		bar.setOutlineThickness(1);
		bar.setOutlineColor( sf::Color(~barsColor.r, ~barsColor.g, ~barsColor.b) );
		bar.setPosition({location.x+offset, location.y+size.y});
		target.draw(bar);

		offset += step+1;
	}

	CartesianSystem system;
	system.setSizePixels(size.x, size.y);
	system.setAxisColor(axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	system.setLocation(location.x, location.y);
	system.setTextColor(axisColor.r, axisColor.g, axisColor.b, axisColor.a);
	system.setScale(scale.x, scale.y);

	std::map<double, std::string> vert, gor;
	for (size_t i = 0; i < bars.size(); i++) {
		gor[bars[i].first - min] = std::to_string(bars[i].first);
		vert[bars[i].second] = std::to_string(bars[i].second);
	}
	

	system.setGorisontalSigns(&gor);
	system.setVerticalSigns(&vert);
	target.draw(system);
	
}

template<class InputIt>
inline void BarChart<InputIt>::calcOptions(int size_x, int size_y)
{
	size = { size_x * 0.9f, size_y * 0.8f };
	location = { size_x * 0.05f, size_y * 0.05f };
}
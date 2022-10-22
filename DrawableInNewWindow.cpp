#include "DrawableInNewWindow.h"

void DrawableInNewWindow::drawInNewWindow(int size_x, int size_y, bool calc_settings) const
{
	if (calc_settings)
		const_cast<DrawableInNewWindow*>(this)->calcOptions(size_x, size_y);

	sf::RenderWindow window(sf::VideoMode(size_x, size_y), "Math Diagram");

	window.clear(sf::Color(255, 255, 255));
	window.draw(*this);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

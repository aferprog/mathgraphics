/*// mathgraphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
//#include <SFML/Graphics.hpp>
#include "PointsInSystem1.h"

using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode(300, 200), "test");
    vector<double> arr = {1, 2, 1.5, 10, 3.3, 3, 3.4};

    PointsInSystem1<decltype(arr.begin())> pis(arr.begin(), arr.end());
    pis.setLenght(100);
    pis.setLocation(Vector2f(100, 100));
    window.clear(Color(255,255,255));
    window.draw(pis);
    window.display();
    getchar();
}
*/
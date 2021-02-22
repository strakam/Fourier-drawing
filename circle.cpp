#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <math.h>
#include "circle.h"

using namespace sf;

Complex Circle::update(float time, Complex position){
    center_x = position.re;
    center_y = position.im;
    x = center_x + radius*cos(time*freq + phase);
    y = center_y + radius*sin(time*freq + phase);
    return {x, y};
};

void Circle::draw(sf::RenderWindow* w){
    circle.setPosition(center_x - radius, center_y - radius);
    w->draw(circle);
}

void Circle::draw_tip(sf::RenderWindow *w){
    tip.setPosition(x-1, y-1);
    w->draw(tip);
    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(center_x, center_y)),
                          sf::Vertex(sf::Vector2f(x, y)) };
    w->draw(line, 2, sf::Lines);
}

#ifndef circle_h
#define circle_h
#include "headers.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <math.h>


struct Complex{
    float re,im;
    Complex(float r, float i){
        re = r;
        im = i;
    }
};

class Circle{
public:
    float radius, freq, phase;
    float x, y, center_x, center_y;
    sf::CircleShape circle, tip;
    Circle(Complex num, float frequency, float rotation) : freq(frequency){
        radius = sqrt(num.re*num.re + num.im*num.im);
        phase = std::atan2(num.im, num.re) + rotation;
        circle.setRadius(radius);
        circle.setOutlineColor(sf::Color::White);
        circle.setFillColor(sf::Color(255, 255,255,0));
        circle.setOutlineThickness(1.f);
        /* tip.setFillColor(sf::Color::White); */
        tip.setRadius(2);
    }
    Circle(){}

    Complex update(float time, Complex position);
    void draw(sf::RenderWindow* w);
    void draw_tip(sf::RenderWindow* w);
};

#endif

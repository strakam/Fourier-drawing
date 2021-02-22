#ifndef machine_h
#define machine_h
#include "headers.h"
#include "circle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;


class Machine{
    sf::RenderWindow* window;
    
    vector<Complex> coefficients_x, coefficients_y;
    vector<Circle*> circles_x, circles_y;
    int N;
    float time = 0, pi = 3.1415926535879, time_increment;
    Complex center, center_x, center_y;

    vector<Complex> dft(const vector<float> &v);
    void make_circles();
public:
    vector<sf::Vertex> path;
    vector<Complex> pic;
    Machine(const vector<float> &x, const vector<float> &y, sf::RenderWindow* w);
    void draw_machine();    
    void update_circles();
};

#endif
#include "machine.h"
#include "path_parser.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fourier Drawing");
    vector<float> vx, vy;
    /* float f; */
    /* ifstream inputx("xs"); */
    /* ifstream inputy("ys"); */
    /* int counter = 0; */
    /* string s; */
    /* while(getline(inputx, s)){ */
    /*     f = stof(s); */
    /*     if(counter % 10 == 0) */
    /*         vx.push_back(f); */
    /*     counter++; */
    /* } */
    /* while(getline(inputy, s)){ */
    /*     f = stof(s); */
    /*     if(counter % 10 == 0) */
    /*         vy.push_back(f); */
    /*     counter++; */
    /* } */
    /* ifstream input("coords"); */
    /* int x = 0; */
    /* while(input >> f){ */
    /*     cout << f << endl; */
    /*     if(x%2) vy.push_back(f); */
    /*     else vx.push_back(f); */
    /*     x++; */
    /* } */
    Parser parser("fourier.svg");
    parser.bezierize();
    parser.centralize_picture();
    Machine fourier(parser.get_points(), &window);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        fourier.update_circles();
        fourier.draw_machine();
        fourier.path.update();
        window.draw(fourier.path);
        window.display();
    }
    return 0;
}

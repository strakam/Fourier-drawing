#include "machine.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Fourier Drawing");
    vector<float> vx, vy;
    ifstream inputx("xs");
    ifstream inputy("ys");
    int counter = 0;
    float f;
    string s;
    while(getline(inputx, s)){
        f = stof(s);
        if(counter % 50 == 0)
            vx.push_back(f);
        counter++;
    }
    while(getline(inputy, s)){
        f = stof(s);
        if(counter % 50 == 0)
            vy.push_back(f);
        counter++;
    }
    for(int i = 0; i < 100; i++){
        vx.push_back(100+30*sin(i));
        vy.push_back(100+30*sin(i));
    }
    Machine fourier(vx, vy, &window);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        fourier.update_circles();
        fourier.draw_machine();
        window.draw(&fourier.path[0], fourier.path.size(), sf::LineStrip);
        window.display();
    }
    return 0;
}

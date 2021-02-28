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
using namespace std;

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fourier Drawing");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    char opt;
    bool bezierize = false, fancy = false;
    while((opt = getopt(argc, argv, "fbc:l:")) != -1){
        switch (opt) {
            case 'b':
                bezierize = true;
                break;
            case 'g':
                break;
            case 'f':
                fancy = true;
                break;
        }
    }
    std::string filename = "lion.svg";
    /* if(optind > 0) */
    /*     filename = argv[optind]; */
    Parser parser(&filename[0]);
    /* if(bezierize) */
    /*     parser.bezierize(); */
    /* parser.centralize_picture(); */
    std::vector<Machine*> machines;
    std::vector<std::vector<Complex>> points = parser.get_points();
    for(auto && v : points){
        machines.push_back(new Machine(v, &window, fancy));
        cout << v.size() << endl;
    }
    cout << machines.size() << endl;
    int cnt = 0;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        for(auto && m : machines){
            if(cnt % 1 == 0)
                m->update_circles();
            m->draw_machine();
        }
        window.display();
        cnt++;
    }
    return 0;
}

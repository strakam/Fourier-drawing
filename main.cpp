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

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fourier Drawing");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    char opt;
    bool bezierize = false, fancy = true;
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
    std::string filename = "woman.svg";
    /* if(optind > 0) */
    /*     filename = argv[optind]; */
    Parser parser(&filename[0]);
    if(bezierize)
        parser.bezierize();
    /* parser.centralize_picture(); */
    Machine fourier(parser.get_points(), &window, fancy);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear();
        fourier.update_circles();
        fourier.draw_machine();
        window.display();
    }
    return 0;
}

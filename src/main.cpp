#include "machine.h"
#include "path_parser.h"
#include <iostream>
#include <string>

using namespace sf;

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fourier Drawing");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    char opt;
    bool fancy = false;
    int filter = 100;
    while((opt = getopt(argc, argv, "f")) != -1){
        switch (opt) {
            case 'f':
                fancy = true;
                break;
        }
    }
    try {
        std::string filename = "svgs/" + std::string(argv[optind]);
        Parser parser(&filename[0]);
        std::vector<Machine*> machines;
        std::vector<std::vector<Complex>> points = parser.get_points();
        for(auto && v : points)
            machines.push_back(new Machine(v, &window, fancy));
        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();
            window.clear();
            for(int i = 0; i < machines.size(); i++){
                machines[i]->update_circles();
                if(machines[i]->get_length() > filter)
                    machines[i]->draw_machine();
                window.draw(&machines[i]->path[0], machines[i]->path.size(), sf::LineStrip);
            }
            window.display();
        }
    } catch (std::exception &e) {
        std:: cout << "Invalid filename" << std::endl;
    }
    return 0;
}

#include "machine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"


using namespace std;
using namespace sf;
struct point{
    float x,y;
};

point quad_bezier(point p0, point p1, point p2, float t){
    point ans;
    ans.x = pow(1-t, 2) * p0.x + (1-t)*2*t*p1.x + t*t*p2.x;
    ans.y = pow(1-t, 2) * p0.y + (1-t)*2*t*p1.y + t*t*p2.y;
    return ans;
}

point cubic_bezier(point p0, point p1, point p2, point p3, float t){
    point ans;
    ans.x = pow(1-t, 3) * p0.x + pow(1-t, 2)*3*t*p1.x + (1-t) * 3 * t*t*p2.x + t*t*t*p3.x;
    ans.y = pow(1-t, 3) * p0.y + pow(1-t, 2)*3*t*p1.y + (1-t) * 3 * t*t*p2.y + t*t*t*p3.y;
    return ans;
}

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
    NSVGimage* image = nsvgParseFromFile("fourier.svg", "px", 96.f);
    NSVGshape* shape;
    NSVGpath* path;
    vector<point> points;
    for (shape = image->shapes; shape != NULL; shape = shape->next) 
		for (path = shape->paths; path != NULL; path = path->next) 
            for(int i = 0; i < path->npts; i++)
                points.push_back({path->pts[2*i], path->pts[2*i+1]});
    for(int i = 3; i < points.size(); i += 4){
        for(int j = 4; j > 0; j--){
            point p = cubic_bezier(points[i-3], points[i-2], points[i-1], points[i], 1.f/j);
            vx.push_back(p.x);
            vy.push_back(p.y);
        }
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
        fourier.path.update();
        window.draw(fourier.path);
        window.display();
    }
    return 0;
}

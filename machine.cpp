#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <bits/stdc++.h>
#include "machine.h"

/*
 * Constructor of DFT machine.
 * It runs DFT on data samples and produces parameters for circles
 */
Machine::Machine(const vector<Complex>& points, sf::RenderWindow* w)
                :center_x(800, 200), center_y(250, 500), center(800, 500){
    window = w;
    N = points.size();
    time_increment = 2*pi/(N);
    coefficients_x = dft(points, true);
    coefficients_y = dft(points, false);
    make_circles();
    set_drawing_properties();
}

vector<Complex> Machine::dft(const vector<Complex> &v, bool real){
    vector<Complex> coeffs;
    for(int n = 0; n < N; n++){
        float re = 0, im = 0; 
        for(int k = 0; k < N; k++){
            float v_k = (real)? v[k].re : v[k].im;
            float arg = 2*pi*k*n/N;
            re += v_k * cos(arg);
            im -= v_k * sin(arg);
        }
        re /= N;
        im /= N;
        coeffs.push_back({re, im});
    }
    return coeffs;
}

bool comparator(const Circle* a, const Circle* b){
    return a->radius > b->radius;
}

void Machine::make_circles(){
    for(int i = 0; i < N; i++){
        circles_x.push_back(new Circle(coefficients_x[i], i, 0));
        circles_y.push_back(new Circle(coefficients_y[i], i, pi/2));
    }
    sort(circles_x.begin(), circles_x.end(), comparator);
    sort(circles_y.begin(), circles_y.end(), comparator);
}

void Machine::draw_machine(){
    for(int i = 0; i < N; i++){
        circles_y[i]->draw(window);
        circles_x[i]->draw(window);
    }
    for(int i = 0; i < N; i++){
        circles_y[i]->draw_tip(window);
        circles_x[i]->draw_tip(window);
    }
}

void Machine::update_circles(){
    Complex position = center, px = center_x, py = center_y;
    for(int i = 0; i < N; i++){
        px = circles_x[i]->update(time, px);
        py = circles_y[i]->update(time, py);
    }
    path.addVertex(sf::Vector2f(circles_x[N-1]->x, circles_y[N-1]->y));
    time += time_increment;
}

void Machine::set_drawing_properties(){
    path.setInterpolationSteps(20u);
    path.setThickness(3);
    path.setThickCornerType(sw::Spline::ThickCornerType::Round);
    path.setBezierInterpolation(true);
    path.setColor(sf::Color(255, 142, 122));
}

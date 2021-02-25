#include "path_parser.h"
#include <algorithm>
#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

Parser::Parser(const char* filename) {
    image = nsvgParseFromFile(filename, "pre", 96.f);
    for (shape = image->shapes; shape != NULL; shape = shape->next) 
		for (path = shape->paths; path != NULL; path = path->next) 
            for(int i = 0; i < path->npts; i++)
                points.push_back({path->pts[2*i], path->pts[2*i+1]});
}

Complex quad_bezier(Complex p0, Complex p1, Complex p2, float t){
    Complex ans;
    ans.re = pow(1-t, 2) * p0.re + (1-t)*2*t*p1.re + t*t*p2.re;
    ans.im = pow(1-t, 2) * p0.im + (1-t)*2*t*p1.im + t*t*p2.im;
    return ans;
}

Complex cubic_bezier(Complex p0, Complex p1, Complex p2, Complex p3, float t){
    Complex ans;
    ans.re = pow(1-t, 3) * p0.re + pow(1-t, 2)*3*t*p1.re + (1-t) * 3 * t*t*p2.re + t*t*t*p3.re;
    ans.im = pow(1-t, 3) * p0.im + pow(1-t, 2)*3*t*p1.im + (1-t) * 3 * t*t*p2.im + t*t*t*p3.im;
    return ans;
}

void Parser::bezierize(){
    std::vector<Complex> bezier_points; 
    for(int i = 3; i < points.size(); i += 4){
        for(int j = 4; j > 0; j--){
            Complex p = cubic_bezier(points[i-3], points[i-2], points[i-1], points[i], 1.f/j);
            bezier_points.push_back(p);
        }
    }
    points = std::move(bezier_points);
}

void Parser::centralize_picture(){
    if(!points.size()) return;
    int min_x = points[0].re, min_y = points[0].im;
    for(auto && p : points){
        min_x = std::min(min_x, int(p.re));
        min_y = std::min(min_y, int(p.im));
    }
    for(auto && p : points){
        p.re -= min_x + 30;
        p.im -= min_y + 30;
    }
}

std::vector<Complex>Parser::get_points(){
    return points;
}
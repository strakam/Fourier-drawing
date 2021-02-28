#ifndef parser_H
#define parser_H
#include "basics.h"

class Parser{
    NSVGimage* image;
    NSVGshape* shape;
    NSVGpath* path;
    std::vector<std::vector<Complex>> points;
public:
    Parser(const char* filename);
    void bezierize();
    void centralize_picture();
    std::vector<std::vector<Complex>> get_points();
};

#endif

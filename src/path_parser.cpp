#include "path_parser.h"
#include <algorithm>

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

/*
 * Class for parsing and modifying samples from SVG file
 */


/*
 * Constructor input - filename of SVG file
 */
Parser::Parser(const char* filename) {
    image = nsvgParseFromFile(filename, "px", 96.f);
    for (shape = image->shapes; shape != NULL; shape = shape->next){
		for (path = shape->paths; path != NULL; path = path->next){
            points.push_back(std::vector<Complex>());
            int size = points.size();
            for(int i = 0; i < path->npts; i++)
                points[size-1].push_back({path->pts[2*i], path->pts[2*i+1]});
        }
    }
}

// Return samples
std::vector<std::vector<Complex>>Parser::get_points(){
    return points;
}

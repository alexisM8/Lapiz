
#include "lapiz.hpp" 
#include <iostream>


int main(int argc, const char * argv[]) {
    lpz::lapiz canvas(800, 800, "lines.ppm");

    lpz::point p1{10, 30};
    lpz::point p2{600, 120};
    lpz::point p3{123, 700};

    canvas.fill_canvas(lpz::color::BLACK);
    canvas.fill_rect(p1, lpz::rectangle(4, 4,lpz::color::RED));
    canvas.fill_rect(p2, lpz::rectangle(4, 4,lpz::color::RED));
    canvas.fill_rect(p3, lpz::rectangle(4, 4,lpz::color::RED));
    canvas.fill_triangle(p1, p2, p3, lpz::color::WHITE);

    canvas.write();
    return 0;
}
 

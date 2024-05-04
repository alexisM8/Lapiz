
#include "lapiz.hpp" 
#include <iostream>


int main(int argc, const char * argv[]) {
    lpz::lapiz canvas(800, 800, "lines.ppm");
    canvas.fill_canvas(lpz::color::BLACK);
    
    int numCircle{8};
    int radius{canvas.getSize().width/2};
    int xpos{0}, ypos{0};

    for(int i = 0; i < numCircle; i++){
        canvas.fill_canvas(xpos, ypos, lpz::circle(radius, lpz::color::GREEN));
        xpos+= radius;
        ypos += radius;
        radius /= 2;
    }
    canvas.write();
    return 0;
}
 

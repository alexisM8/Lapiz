
#include "lapiz.hpp" 
#include <iostream>


int main(int argc, const char * argv[]) {
    lpz::lapiz canvas(800, 800, "lines.ppm");
    canvas.fill_canvas(lpz::BLACK);

    canvas.draw_line(0, 0, canvas.getSize().width, canvas.getSize().height, lpz::YELLOW);
    canvas.draw_line(0, canvas.getSize().height, canvas.getSize().width, 0, lpz::GREEN);
    canvas.draw_line(0, canvas.getSize().height/2, canvas.getSize().width, canvas.getSize().height/2, lpz::LIGHTPINK);

    canvas.write();
    return 0;
}
 
 


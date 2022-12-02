#include "lapiz.hpp" 
#include <iostream>


int main(int argc, const char * argv[]) {
    int row{2}, col{2};
    lpz::lapiz canvas(800, 800, "circles.ppm");
    canvas.fill_canvas(lpz::BLACK);

    for(int i = 1; i <= row; i++){
        for(int j = 1; j <= col; j++){
                lpz::circle circ((canvas.getSize().width/row/2), lpz::PURPLE);
                canvas.fill_circle((i-1)*(canvas.getSize().width/col), (j-1)*(canvas.getSize().height/row), circ);
        }
    }

    canvas.write();
    return 0;
}





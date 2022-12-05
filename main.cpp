
#include "lapiz.hpp" 
#include <iostream>


int main(int argc, const char * argv[]) {
    int row{8}, col{8};
    lpz::lapiz canvas(800, 800, "checkerboard.ppm");
    canvas.fill_canvas(lpz::BLACK);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(i % 2 == 0 && j % 2 == 0){
                canvas.fill_rect(j*canvas.getSize().width/col, i*canvas.getSize().height/row,
                                 lpz::rectangle(canvas.getSize().height/row, canvas.getSize().width/col, lpz::WHITE));
            }else if(i % 2 == 1 && j % 2 == 1){
                canvas.fill_rect(j*canvas.getSize().width/col, i*canvas.getSize().height/row,
                                 lpz::rectangle(canvas.getSize().height/row, canvas.getSize().width/col, lpz::WHITE));
            }
        }
    }
    canvas.write();
    return 0;
}
 

# Lapiz

A general purpose 2d canvas for c++

## Description

Lapiz is a very simple 2d header only graphics library for c++. It was created to quickly prototype simple graphic ideas. This is possible through the use of the simple but effective .ppm file format.

## Getting Started 

### Dependecies

* CMake version >= 3.14.4
* clangd version >= 9.00

### Installing

* Clone the repository in a desired location

### Executing Program

The example program provided will draw a 2d grid of circles and output it to image.ppm

* Navigate to build directory
* execute the command:
```
cmake -S ../ -B .
```
* a makefile will be generated compile the program:
```
make
```
* run the program:
```
./Lapiz
```
## Examples
Generating lines:
```cpp
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
```
will produce the lines.ppm file which when converted to a .png looks like:
![lines](https://github.com/alexisM8/Lapiz/blob/main/examples/lines.png)

Generating rows and cols of circles
```cpp
#include "lapiz.hpp" 
#include <iostream>

int main(int argc, const char * argv[]) {
    int row{2}, col{2};
    lpz::lapiz canvas(800, 800, "circles.ppm");
    canvas.fill_canvas(lpz::BLACK);

    for(int i = 1; i <= row; i++){
        for(int j = 1; j <= col; j++){
            lpz::circle circ ((canvas.getSize().width/row/2), lpz::PURPLE);
            canvas.fill_circle((i-1)*(canvas.getSize().width/col), (j-1)*(canvas.getSize().height/row), circ);
        }
    }

    canvas.write();
    return 0;
}
```
will produce the circle.ppm file which when converted to a .png looks like:
![circles](https://github.com/alexisM8/Lapiz/blob/main/examples/circles.png)

## Authors
Alexis Rodriguez aka alexisM8


/* Copyright 2022 Alexis Rodriguez 

Permission is hereby granted, free of charge,
to any person obtaining a copy of this software and
associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons
to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.

*/
#ifndef lapiz_hpp
#define lapiz_hpp

#include <cstddef>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

namespace lpz{
    constexpr std::size_t default_height = 600; //pixles
    constexpr std::size_t default_width  = 800;  //pixles
    constexpr char default_name[] = "image.ppm";

    typedef std::int32_t color;
    
    struct  color_components{
        color r;
        color g;
        color b;
        color a;
    };

    struct size{
        std::size_t height;
        std::size_t width;
    };

    constexpr color RED        = 0xFF0000;
    constexpr color GREEN      = 0x00FF00;
    constexpr color BLUE       = 0x0000FF;
    constexpr color BROWN      = 0x5F4828;
    constexpr color LIGHTBLUE  = 0x20DDFF;
    constexpr color YELLOW     = 0xFFFF00;
    constexpr color LIGHTPINK  = 0xFFC0CB;
    constexpr color BLACK      = 0x000000;
    constexpr color WHITE      = 0xFFFFFF;
    constexpr color ORANGE     = 0xF06F0F;
    constexpr color DARKPINK   = 0x9F2B68;
    constexpr color HOTPINK    = 0xFF0092;
    constexpr color PURPLE     = 0x3C005A;

    struct rectangle{
           color c; 
           std::size_t length;
           std::size_t width;
           rectangle(std::size_t l, std::size_t w, color cl) :
               length(l), width(w), c(cl) {};
    };
    
    struct circle{
        color c;
        std::size_t radius;
        circle(std::size_t r, color cl) : radius(r), c(cl) {};
    };

    class lapiz{
        private:
            size m_size;
            std::string m_filename;
            std::vector<color> m_pixles;
        public:
            lapiz() : m_size({default_height, default_width}), m_filename(default_name) { 
                m_pixles = std::vector<color>(m_size.width*m_size.height); 
            } 

            lapiz(std::size_t WIDTH, std::size_t HEIGHT, std::string FILENAME) : m_size({HEIGHT, WIDTH}), m_filename(FILENAME) { 
                m_pixles = std::vector<color>(m_size.width*m_size.height); 
            };

            void fill_circle(std::size_t x, std::size_t y, const circle &circ){
                std::pair<int, int> center(x+circ.radius, y+circ.radius);
                for(int y1 = y; y1 < y+circ.radius*2; y1++){
                    for(int x1 = x; x1 < x+circ.radius*2; x1++){
                        auto dist = std::sqrt((std::pow(center.first-x1 , 2) + std::pow(center.second-y1 , 2)));
                        if(std::floor(dist) <= circ.radius){
                            m_pixles[x1 * m_size.width + y1] = circ.c;
                        }
                    }
                }
            }
                
            void fill_rect(std::size_t x, std::size_t y, const rectangle &rect){
               if(x + rect.length <= m_size.height && y + rect.width <= m_size.width){
                    for(std::size_t y1 = y; y1 < y+rect.width; y1++){
                        for(std::size_t x1 = x; x1 < x+rect.length; x1++){
                            m_pixles[x1 * m_size.width + y1] = rect.c;
                        }
                    }
               }else{
                    std::cerr << "ERROR: invalid rectangle dimentions <larger than canvas> !\n";
                    return;
               }
            }

            void fill_canvas(color c){
                for(std::size_t y = 0; y < m_size.height; y++){
                    for(std::size_t x = 0; x < m_size.width; x++){
                        m_pixles[x * m_size.width + y] = c;
                    }
                }
            }

            void draw_line(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const color &cl){
                if(x1 >= 0 && y1 >= 0){
                   if(x2 <= m_size.width && y2 <= m_size.height){
                        //write code for creating line
                       int dy{ static_cast<int>(y2-y1) };
                       int dx{ static_cast<int>(x2-x1) };
                       for(int i = 0; i < dx; i++){
                           int x = x1 + i;
                           int y = y1 + dy * i / dx;
                           m_pixles[x * m_size.width + y] = cl;
                       }
                   }else{
                        std::cerr << "ERROR: ending corrdiantes must be less than or equal to canvas\n";
                   }
                }else{
                    std::cerr << "ERROR: starting corrdiantes must be greater than or equal to 0\n";
                }
            }

            size const& getSize() const{
                return m_size;
            }

            void write(){
                color_components comps;
                std::ofstream file(m_filename);
                file << "P3 " << m_size.width << " " << m_size.height << " 255\n";
                for(std::size_t y = 0; y < m_size.height; y++){
                    for(std::size_t x = 0; x < m_size.width; x++){
                        color curr = m_pixles[x * m_size.width + y];
                        comps.r = (curr&0xFF0000)>>(8*2); 
                        comps.g = (curr&0x00FF00)>>(8*1);
                        comps.b = (curr&0x0000FF)>>(8*0); 
                        file << comps.r << " " << comps.g << " " << comps.b << " ";
                        // std::cout << comps.r << " " << comps.g << " " << comps.b << " ";
                    }
                    file << "\n";
                    // std::cout << "\n";
                }
            }
    };
}
#endif /* lapiz_hpp */

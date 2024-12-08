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

#include <algorithm>
#include <fstream>
#include <vector>
#include <ranges>
#include <string>
#include <iostream>

namespace lpz{
    constexpr std::size_t default_height = 600; //pixles
    constexpr std::size_t default_width  = 800;  //pixles
    constexpr char default_name[] = "image.ppm";

    // typedef std::int32_t color;

    struct point{
        std::size_t x;
        std::size_t y;
    };

    
    
    struct size{
        std::size_t height;
        std::size_t width;
    };

    enum class color{
        RED        = 0xFF0000,
        GREEN      = 0x00FF00,
        BLUE       = 0x0000FF, 
        BROWN      = 0x5F4828, 
        LIGHTBLUE  = 0x20DDFF,
        YELLOW     = 0xFFFF00, 
        LIGHTPINK  = 0xFFC0CB,
        BLACK      = 0x000000, 
        WHITE      = 0xFFFFFF,
        ORANGE     = 0xF06F0F,
        DARKPINK   = 0x9F2B68,
        HOTPINK    = 0xFF0092,
        PURPLE     = 0x3C005A
    };

    struct  color_components{
        color r;
        color g;
        color b;
        color a;
    };

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
    
    //utility functions begin
    inline std::size_t min_x(const std::vector<point>& points){
        auto copy = points;
        std::sort(copy.begin(), copy.end(), [](const auto& p1, const auto& p2){return p1.x < p2.x;});
        return copy.front().x;
    }

    inline std::size_t max_x(const std::vector<point>& points){
        auto copy = points;
        std::sort(copy.begin(), copy.end(), [](const auto& p1, const auto& p2){return p1.x > p2.x;});
        return copy.front().x;
    }

    inline std::size_t min_y(const std::vector<point>& points){
        auto copy = points;
        std::sort(copy.begin(), copy.end(), [](const auto& p1,const auto& p2){return p1.y < p2.y;});
        return copy.front().y;
    }

    inline std::size_t max_y(const std::vector<point>& points){
        auto copy = points;
        std::sort(copy.begin(), copy.end(), [](const auto& p1,const auto& p2){return p1.y > p2.y;});
        return copy.front().x;
    }
    //utility functions end

    class lapiz{
        private:
            size m_size;
            std::string m_filename;
            std::vector<color> m_pixles;
        public:
            lapiz() : m_size({default_height, default_width}), m_filename(default_name), 
                        m_pixles(std::vector<color>(default_width*default_height)) {} 

            lapiz(std::size_t WIDTH, std::size_t HEIGHT, std::string FILENAME) : m_size({HEIGHT, WIDTH}),
                        m_filename(FILENAME), m_pixles(std::vector<color>(WIDTH*HEIGHT)) {}


            void fill_circle(const point& p, const circle& circ) {
                const point center{p.x + circ.radius, p.y + circ.radius};

                for (int y1 = p.y; y1 <= p.y + 2 * circ.radius; y1++) {
                    for (int x1 = p.x; x1 <= p.x + 2 * circ.radius; x1++) {
                        auto dx = center.x - x1;
                        auto dy = center.y - y1;
                        if (dx * dx + dy * dy <= circ.radius * circ.radius) {
                            if (x1 >= 0 && x1 < static_cast<int>(m_size.width) && y1 >= 0 && y1 < static_cast<int>(m_size.height)) {
                                m_pixles[y1 * m_size.width + x1] = circ.c;
                            }
                        }
                    }
                }
            }
    
            void fill_rect(const point& p, const rectangle &rect){
               if(p.x + rect.length <= m_size.height && p.y + rect.width <= m_size.width){
                    for(std::size_t y1 = p.y; y1 < p.y + rect.width; y1++){
                        for(std::size_t x1 = p.x; x1 < p.x + rect.length; x1++){
                            m_pixles[x1 * m_size.width + y1] = rect.c;
                        }
                    }
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

            void draw_line(const point& p1, const point& p2, const color &cl){
                if(p1.x >= 0 && p1.y >= 0){
                    if(p2.x <= m_size.width && p2.y <= m_size.height){
                        const int dy{ static_cast<int>(p2.y - p1.y) };
                        const int dx{ static_cast<int>(p2.x - p1.x) };
                        if(dx != 0){
                            for(int i = 0; i < dx; i++){
                               int x = p1.x + i;
                               int y = p1.y + dy * i / dx;
                               m_pixles[x * m_size.width + y] = cl;
                           }
                        }else{
                            for(int y = p1.y; y < p2.y; y++){
                                m_pixles[p1.x * m_size.width + y] = cl;
                            }
                        }
                   }else{
                        std::cerr << "ERROR: ending corrdiantes must be less than or equal to canvas\n";
                   }
                }else{
                    std::cerr << "ERROR: starting corrdiantes must be greater than or equal to 0\n";
                }
            }
            
            void fill_triangle(const point& p1, const point& p2, const point& p3, const color& cl){
                auto points = std::vector{p1, p2, p3};
                std::sort(points.begin(), points.end(), [](const auto& p1, const auto& p2){return p1.y < p2.y;});
                auto x_min = min_x(points);
                auto x_max = max_x(points);
                auto y_min = min_y(points);
                auto y_max = max_y(points);
                
                std::size_t left_x = 0;
                std::size_t right_x = 0;
                for(auto y : std::ranges::iota_view{y_min, y_max + 1}){
                   if(points.back().y != points.front().y){
                        if(y < points.at(1).y){
                            auto factor = (y < points.at(1).y) / (points.back().y - points.front().y);
                            left_x = points.front().x + factor * (points.back().x - points.front().x);
                        }else{
                            auto factor = (y - points.at(1).y) / (points.back().y - points.at(1).y);
                            left_x = points.at(1).x + factor * (points.back().x - points.at(1).x);
                        }
                    }else{
                          left_x = points.front().x;
                    }
                    
                    if(y < points.at(1).y){
                        auto factor = (y - points.front().y) / (points.at(1).y - points.front().y);
                        right_x = points.front().x + factor * (points.at(1).x - points.front().x);
                    }else{
                        auto factor = (y - points.at(1).y) / (points.back().y - points.at(1).y);
                        right_x = points.at(1).x + factor * (points.back().x - points.at(1).x);
                    }

                    for(auto x : std::ranges::iota_view(left_x, right_x + 1)){
                        m_pixles[x * m_size.width + y] = cl;
                    }
                
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
                        comps.r = static_cast<color>((static_cast<int>(curr)&static_cast<int>(color::RED))>>(8*2)); 
                        comps.g = static_cast<color>((static_cast<int>(curr)&static_cast<int>(color::GREEN))>>(8*1)); 
                        comps.b = static_cast<color>((static_cast<int>(curr)&static_cast<int>(color::BLUE))>>(8*0)); 
                        file << static_cast<int>(comps.r) << " " << static_cast<int>(comps.g) << " " << static_cast<int>(comps.b) << " ";
                        // std::cout << comps.r << " " << comps.g << " " << comps.b << " ";
                    }
                    file << "\n";
                    // std::cout << "\n";
                }
            }
    };
}
#endif /* lapiz_hpp */

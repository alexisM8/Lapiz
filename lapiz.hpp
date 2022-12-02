//
//  lapiz.hpp
//  lapiz
//
//  Created by Alexis Rodriguez on 11/30/22.
//

#ifndef lapiz_hpp
#define lapiz_hpp

#include <cstddef>
#include <fstream>
#include <stdio.h>
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
    constexpr color YELLOW     = 0xFFFF00;
    constexpr color LIGHTPINK  = 0xFFC0CB;
    constexpr color BLACK      = 0x000000;
    constexpr color WHITE      = 0xFFFFFF;
    constexpr color DARKPINK   = 0x9F2B68;
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
            // std::size_t m_height;
            // std::size_t m_width;
            std::string m_filename;
            std::vector<color> m_pixles;
        public:
            lapiz() : m_size({default_height, default_width}), m_filename(default_name) { m_pixles = std::vector<color>(m_size.width*m_size.height); }; 
            lapiz(std::size_t WIDTH, std::size_t HEIGHT, std::string FILENAME) : m_size({HEIGHT, WIDTH}), m_filename(FILENAME) { m_pixles = std::vector<color>(m_size.width*m_size.height); };
            void fill_circle(std::size_t x, std::size_t y, const circle &circ);
            void fill_rect(std::size_t x, std::size_t y, const rectangle &rect);
            void fill_canvas(color c);
            size const& getSize() const;
            void write();
    };
}
#endif /* lapiz_hpp */

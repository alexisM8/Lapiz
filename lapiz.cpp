//
//  lapiz.cpp
//  lapiz
//
//  Created by Alexis Rodriguez on 11/30/22.
//

#include "lapiz.hpp"
#include <cmath>

namespace lpz{
void lapiz::fill_rect(std::size_t x, std::size_t y, const rectangle &rect){
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

void lapiz::fill_circle(std::size_t x, std::size_t y, const circle &circ){
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

void lapiz::fill_canvas(color c){
    for(std::size_t y = 0; y < m_size.height; y++){
        for(std::size_t x = 0; x < m_size.width; x++){
            m_pixles[x * m_size.width + y] = c;
        }
    }
}

size const& lapiz::getSize() const{
    return m_size;
}
void lapiz::write(){
    color_components comps;
    std::ofstream file(m_filename);
    file << "P3 " << m_size.width << " " << m_size.height << " 255\n";
    for(std::size_t y = 0; y < m_size.height; y++){
        for(std::size_t x = 0; x < m_size.width; x++){
            color curr = m_pixles[x * m_size.width + y];
            comps.r = (curr&0xFF0000)>>(8*2); 
            comps.g = (curr&0x00FF00)>>(8*1);
            comps.b = (curr&0x0000FF)>>(8*0); 
            // comps.a = (curr>>8*0)&0xFF; 
            file << comps.r << " " << comps.g << " " << comps.b << " ";
            // std::cout << comps.r << " " << comps.g << " " << comps.b << " ";
        }
        file << "\n";
        // std::cout << "\n";
    }
}

} //end namespace lpz

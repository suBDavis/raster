#include "Renderer.h"
#include <sstream>

Renderer::Renderer(int width, int height, double gamma): 
width(width), height(height), gamma(gamma)
{
    rowlen = width;
    pixels = new v3[width*height];
    top_color = 0;
    normalized_top_color = 255;
}

void Renderer::set_pixel(int x, int y, v3 c){
    int dex = y * rowlen + x;
    if (c.x > top_color){
        top_color = c.x;
    } else if (c.y > top_color) {
        top_color = c.y;
    } else if (c.z > top_color) {
        top_color = c.z;
    }
    pixels[dex] = c;
}

v3 Renderer::get_pixel(int x, int y){
    int dex = y * rowlen + x;
    return pixels[dex];
}
void Renderer::render_text(){
    for (int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            v3 text_color = get_pixel(i, j);
            std::cout << text_color.to_str() << " ";
        }
        std::cout << std::endl;
    }
//    std::printf("done\n");
}
void Renderer::render_ppm(const char *filename){
    
    std::ofstream myfile;
    myfile.open (filename);
    myfile << "P3\n";
    myfile << width;
    myfile << " ";
    myfile << height;
    myfile << "\n255\n";
    for (int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            v3 pcolor = get_pixel(i, j);

            //check if min = max = 0 DONT DIVIDE BY 0
            if (top_color == 0){
                myfile << " 0 0 0 ";
            } else {
                myfile << to_ppm(pcolor, top_color, normalized_top_color) << " ";
            }
        }
        myfile << "\n";
    }
    myfile.close();
    
    std::cout << "Rendered to file " << filename << std::endl;
}
int Renderer::getHeight(){
    return height;
}
int Renderer::getWidth(){
    return width;
}

std::string Renderer::to_ppm(v3 color){
    std::stringstream ss;
    ss << color.x << " " << color.y << " " << color.z;
    return ss.str();
}

std::string Renderer::to_ppm(v3 color, double oldmax, double newmax){
    double gamma = 1.0;
    //step 1: normalize to between 0 and 1
    double ri = pow(color.x / oldmax, 1/gamma) * newmax;
    double gi = pow(color.y / oldmax, 1/gamma) * newmax;
    double bi = pow(color.z / oldmax, 1/gamma) * newmax;
    return ntos(round(ri)) + " " + ntos(round(gi)) + " " + ntos(round(bi));
}

std::string Renderer::ntos(int i){
    std::ostringstream convert;
    convert << i;
    std::string out = convert.str();
    return out;
}

Renderer::~Renderer()
{
    //delete[] pixels;
}
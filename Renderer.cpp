#include "Renderer.h"

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
                myfile << to_ppm(pcolor) << " ";
            }
        }
        myfile << "\n";
    }
    myfile.close();
    
    std::cout << "Rendered to file " << filename << std::endl;
}
int Renderer::getHeight(){
    return height * sample_index;
}
int Renderer::getWidth(){
    return width * sample_index;
}

std::string Renderer::to_ppm(v3 color){
    
}

Renderer::~Renderer()
{
    //delete[] pixels;
}
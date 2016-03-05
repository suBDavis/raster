#ifndef RENDERER_H
#define RENDERER_H
#include "v3.h"
#include <iostream>
#include <cstdio>
#include <fstream>

class Renderer
{
public:
    Renderer(int width, int height, double gamma);
    ~Renderer();
    void set_pixel(int x, int y, v3 color);
    v3 get_pixel(int x, int y);
    std::string to_ppm(v3 color);
    void render_text();
    void render_ppm(const char *filename);
    int getWidth();
    int getHeight();

private:
    int rtype;
    int rowlen;
    double top_color;
    double normalized_top_color;
    int width;
    int height;
    bool antialias;
    int sample_index;
    double gamma;
    v3 *pixels;
};

#endif // RENDERER_H

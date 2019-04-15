#ifndef SVG_FUNC_H_INCLUDED
#define SVG_FUNC_H_INCLUDED
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void svg_begin(double width, double height);

void svg_end();

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");

void show_histogram_svg(const vector<size_t>& bins, size_t width);


#endif // SVG_FUNC_H_INCLUDED

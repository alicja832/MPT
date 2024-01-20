/*
	This exercise aims for implementing multithreading in generating animation.
	Your job is to create class Render that contains SwapBuffer method that uses multithreading for generating new versions of a buffer,
	To generate animations of a different RGB channels, use animationList vector, and oscilating timer.
	***IMPORTANT***
	- to generate images and context window we are using CImg library
	- to compile, CImg with graphical interface use -lX11 flag
*/


#include "Render.h"
#include <cmath>
using namespace cimg_library;

int main(){
	std::vector<std::function<int(int, int, int)>> animationList{
		[](int i, int j, int anim){
			return  std::fabs(std::sin(((std::pow((i - 1000), 2) + std::pow(j - 500, 2)) / (50000 + 100 * anim)))) * 255;
		},
		[](int i, int j, int anim){ 
			return  std::fabs(std::cos(((std::pow((i - 1000), 2) + std::pow(j - 500, 2)) / (50000 - 100 * anim)))) * 255;
		},
		[](int i, int j, int anim){ 
			return  std::fabs(std::atan(((std::pow((i - 1000), 2) + std::pow(j - 500, 2)) / (50000 + 100 * anim)))) * 255;
		}
	};
	CImg<unsigned char> buffer(2000, 1000, 1, 3, 0);
	CImgDisplay main_window(1280, 720);
	int timer{};
	Render render;
	while (!main_window.is_closed()) {

		buffer.assign(render.SwapBuffer(buffer, animationList, std::sin(timer / 10.) * 50));
		main_window.display(buffer);
		++timer %= 314;
	}
}

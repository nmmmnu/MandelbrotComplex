#include <cstdio>

constexpr auto FRAMES		= 1000;
constexpr auto MAX_CROSS	= 1.2;
constexpr auto STEP		= MAX_CROSS / FRAMES;

int main(){
	int id = 0;

	for(int i = FRAMES; i-->0;){
		printf("./mandelbrot -%.5f > %08d.ppm\n", i * STEP, id++);
	}

	for(int i = 0; i < FRAMES; ++i){
		printf("./mandelbrot +%.5f > %08d.ppm\n", i * STEP, id++);
	}

	printf("ffmpeg -i %08d.ppm -vcodec mpeg4 test.avi\n");
}



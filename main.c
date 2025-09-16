#include "raylib.h"

#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define WIN_TITLE  "Conway's Game of Life"

int main(void)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RED);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

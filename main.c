#include "raylib.h"

#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define WIN_TITLE  "Conway's Game of Life"

#define CELL_FILL_COLOR WHITE

int main(void)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	int col_count, row_count;
	col_count = 20;
	row_count = 15;
	int cell[row_count][col_count];

	for (int row = 0; row < row_count; ++row) {
		for (int col = 0; col < col_count; ++col) {
			cell[row][col] = 0;
		}
	}

	cell[5][3] = 1;

	float cell_width, cell_height;
	cell_width  = (float)WIN_WIDTH   / col_count;
	cell_height = (float)WIN_HEIGHT /  row_count;

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		for (int row = 0; row < row_count; ++row) {
			for (int col = 0; col < col_count; ++col) {
				if (cell[row][col] == 1) {
					float x = col * cell_width;
					float y = row * cell_height;
					Rectangle rec = {
						.x = x, .y = y,
						.width = cell_width, .height = cell_height
					};
					DrawRectangleRec(rec, CELL_FILL_COLOR);
				}
			}
		}


		EndDrawing();
	}

	CloseWindow();
	return 0;
}

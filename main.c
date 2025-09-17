#include <stdio.h>
#include "raylib.h"

#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define WIN_TITLE  "Conway's Game of Life"

#define CELL_FILL_COLOR WHITE
#define GRID_LINE_COLOR WHITE

int main(void)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	// Use ratio 4 : 3 for Col and Row to draw a square for when drawing
	// the rectangle. Otherwise it'll draw a rectangle. This is chose
	// by WIN_WIDTH and WIN_HEIGHT. 
	// TODO: Refactor later so it's easier to adjust cell size
	int multiplier, col_count, row_count;
	multiplier = 10;
	col_count = 4 * multiplier;
	row_count = 3 * multiplier;
	int cell[row_count][col_count];

	for (int row = 0; row < row_count; ++row) {
		for (int col = 0; col < col_count; ++col) {
			cell[row][col] = 0;
		}
	}

	float cell_width, cell_height;
	cell_width = (float)WIN_WIDTH/col_count;
	cell_height = (float)WIN_HEIGHT/row_count;

	printf("column count: %d\n", col_count);
	printf("row count: %d\n", row_count);
	printf("cell width: %f\n", cell_width);
	printf("cell height: %f\n", cell_height);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		// Draw Grid Line Here
		for (int row = 0; row < row_count; ++row) {
			Vector2 startPos = {.x = 0, .y = row * cell_height};
			Vector2 endPos = {.x = WIN_WIDTH, .y = startPos.y};
			DrawLineV(startPos, endPos, GRID_LINE_COLOR);
		}
		for (int col = 0; col < col_count; ++col) {
			Vector2 startPos = {.x = col * cell_width, .y = 0};
			Vector2 endPos = {.x = startPos.x, .y = WIN_HEIGHT};
			DrawLineV(startPos, endPos, GRID_LINE_COLOR);
		}

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

		// Handle click on cell to fill it
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePosition = GetMousePosition();
			int col_index = mousePosition.x / WIN_WIDTH * col_count;
			int row_index = mousePosition.y / WIN_HEIGHT * row_count;
			printf("x: %f, y: %f\n", mousePosition.x, mousePosition.y);
			printf("col: %d, row: %d\n", col_index, row_index);

			int cell_value = cell[row_index][col_index];
			if (cell_value) {
				cell[row_index][col_index] = 0;
			} else {
				cell[row_index][col_index] = 1;
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

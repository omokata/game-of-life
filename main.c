#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"

#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define WIN_TITLE  "Conway's Game of Life"

#define CELL_FILL_COLOR WHITE
#define GRID_LINE_COLOR WHITE

#define CELL_RENDER_TICK 1 // 1 second

#define EIGHT_NEIGHBORS_COUNT 8
static int eight_neighbors[][2] = {
	{0, -1},
	{0, 1},
	{1, 0},
	{-1, 0},
	{-1, -1},
	{-1, 1},
	{1, -1},
	{1, 1},
};

int get_neighbors_count(int col_count, int row_count,
						int current_gen[row_count][col_count],
						int curr_row, int curr_col)
{
	int n_neighbors = 0;
	for (int i = 0; i < EIGHT_NEIGHBORS_COUNT; ++i) {
		int neighbor_row = curr_row + eight_neighbors[i][0];
		int neighbor_col = curr_col + eight_neighbors[i][1];
		if ((neighbor_col < 0 || neighbor_col >= col_count) ||
			(neighbor_row < 0 || neighbor_row >= row_count)) {
			continue;
		}
		if (current_gen[neighbor_row][neighbor_col] == 1) {
			n_neighbors++;
		}
	}

	return n_neighbors;
}

int main(void)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	bool is_gol_play = false;

	// Use ratio 4 : 3 for Col and Row to draw a square for when drawing
	// the rectangle. Otherwise it'll draw a rectangle. This is chose
	// by WIN_WIDTH and WIN_HEIGHT. 
	// TODO: Refactor later so it's easier to adjust cell size
	int multiplier, col_count, row_count;
	multiplier = 10;
	col_count = 4 * multiplier;
	row_count = 3 * multiplier;
	int current_gen[row_count][col_count];
	int next_gen[row_count][col_count];

	for (int row = 0; row < row_count; ++row) {
		for (int col = 0; col < col_count; ++col) {
			current_gen[row][col] = 0;
			next_gen[row][col] = 0;
		}
	}

	float cell_width, cell_height;
	cell_width = (float)WIN_WIDTH/col_count;
	cell_height = (float)WIN_HEIGHT/row_count;

	printf("column count: %d\n", col_count);
	printf("row count: %d\n", row_count);
	printf("cell width: %f\n", cell_width);
	printf("cell height: %f\n", cell_height);

	float cell_render_time_acc = 0;

	while(!WindowShouldClose()) {
		float deltatime = GetFrameTime();
		cell_render_time_acc += deltatime;

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

		// Render current_gen
		for (int row = 0; row < row_count; ++row) {
			for (int col = 0; col < col_count; ++col) {
				if (current_gen[row][col] == 1) {
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

			int cell_value = current_gen[row_index][col_index];
			if (cell_value) {
				current_gen[row_index][col_index] = 0;
			} else {
				current_gen[row_index][col_index] = 1;
			}
		}

		if (IsKeyPressed(KEY_SPACE)) {
			is_gol_play = !is_gol_play;
		}

		// Copy next gen to current gen
		if (is_gol_play) {

			if (cell_render_time_acc >= CELL_RENDER_TICK) {
				cell_render_time_acc = 0;
				for (int row = 0; row < row_count; ++row) {
					for (int col = 0; col < col_count; ++col) {
						current_gen[row][col] = next_gen[row][col];
					}
				}
			}
		}

		// Reset the next gen
		for (int row = 0; row < row_count; ++row) {
			for (int col = 0; col < col_count; ++col) {
				next_gen[row][col] = 0;
			}
		}

		// TODO: Apply the rules of Game of Life
		for (int row = 0; row < row_count; ++row) {
			for (int col = 0; col < col_count; ++col) {
				int curr_row = row;
				int curr_col = col;
				int curr_cell = current_gen[curr_row][curr_col];
				int n_neighbors = get_neighbors_count(col_count, row_count,
									 current_gen, curr_row, curr_col);
		
				if (curr_cell) {
					if (n_neighbors == 2 || n_neighbors == 3) {
						next_gen[curr_row][curr_col] = 1;
					} else {
						next_gen[curr_row][curr_col] = 0;
					}
				} else {
					if (n_neighbors == 3) {
						next_gen[curr_row][curr_col] = 1;
					}
				}
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

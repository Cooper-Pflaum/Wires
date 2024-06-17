#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "../lib/types.h"
#include "../lib/consts.h"
#include "grid.h"
#include "input.h"

int grid[GRID_HEIGHT][GRID_WIDTH] = {0}; // Initialize grid with all cells empty

v2 SnapToGrid(Vector2 pos) {
    return (v2){(int)(pos.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f, (int)(pos.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f};
}

void drawWire(DrawingState *state, bool isPreview) {
    v2 currentPos = state->startPos;
    Color wireColor = isPreview ? (Color){255, 255, 255, 128} : BLACK; // Slightly transparent color for preview

    if (state->drawHorizontalFirst) {
        while (currentPos.x != state->endPos.x) {
            grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
            DrawRectangleRec((Rectangle){currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
            currentPos.x += (state->endPos.x > currentPos.x) ? CELL_SIZE : -CELL_SIZE;
        }

        while (currentPos.y != state->endPos.y) {
            grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
            DrawRectangleRec((Rectangle){currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
            currentPos.y += (state->endPos.y > currentPos.y) ? CELL_SIZE : -CELL_SIZE;
        }
    } else {
        while (currentPos.y != state->endPos.y) {
            grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
            DrawRectangleRec((Rectangle){currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
            currentPos.y += (state->endPos.y > currentPos.y) ? CELL_SIZE : -CELL_SIZE;
        }

        while (currentPos.x != state->endPos.x) {
            grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
            DrawRectangleRec((Rectangle){currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
            currentPos.x += (state->endPos.x > currentPos.x) ? CELL_SIZE : -CELL_SIZE;
        }
    }

    // Draw the last cell where the mouse is currently at
    grid[(int)(state->endPos.y / CELL_SIZE)][(int)(state->endPos.x / CELL_SIZE)] = isPreview ? grid[(int)(state->endPos.y / CELL_SIZE)][(int)(state->endPos.x / CELL_SIZE)] : 1; // Update grid cell
    DrawRectangleRec((Rectangle){state->endPos.x - CELL_SIZE / 2.0f, state->endPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
}

void drawGrid(DrawingState *state) {
  // Calculate the visible area based on the zoom level and offset
  int startX = -1 * (int)(state->offset.x / CELL_SIZE / state->zoom);
  int startY = -1 * (int)(state->offset.y / CELL_SIZE / state->zoom);


  int endX = (int)((-1 * state->offset.x) + (int)(GetScreenWidth() / state->zoom / CELL_SIZE)) + 1;
  int endY = (int)((-1 * state->offset.y) + (int)(GetScreenHeight() / state->zoom / CELL_SIZE)) + 1;


  // Clamp the visible area to the grid boundaries
  startX = fmax(startX, 0);
  endX = fmin(endX, GRID_WIDTH - 1 * CELL_SIZE);
  startY = fmax(startY, 0);
  endY = fmin(endY, GRID_HEIGHT - 1 * CELL_SIZE);

  // Draw only the visible cells
  for (int y = startY; y <= endY; y++) {
    for (int x = startX; x <= endX; x++) {
      Rectangle cellRect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
      if (grid[y][x]) {
          DrawRectangleRec(cellRect, WHITE); // Draw filled cell
      } else {
        if (state->zoom > 0.5) {
          
          // DrawPixel(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2, LIGHTGRAY); // Draw a single point
        }
      }
    }
  }
}

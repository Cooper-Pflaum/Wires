#include "grid.h"
#include <math.h> // Include math.h for fabs
#include <stdio.h>

int grid[GRID_HEIGHT][GRID_WIDTH] = { 0 }; // Initialize grid with all cells empty

v2 SnapToGrid(Vector2 pos) {
  return (v2){ (int)(pos.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f, (int)(pos.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f };
}

void drawWire(v2 startPos, v2 endPos, bool drawHorizontalFirst, bool isPreview) {
  v2 currentPos = startPos;
  Color wireColor = isPreview ? (Color){255,255,255, 128 } : BLACK; // Slightly transparent color for preview

  if (drawHorizontalFirst) {
    while (currentPos.x != endPos.x) {
      grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
      DrawRectangleRec((Rectangle){ currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE }, wireColor);
      currentPos.x += (endPos.x > currentPos.x) ? CELL_SIZE : -CELL_SIZE;
    }

    while (currentPos.y != endPos.y) {
      grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
      DrawRectangleRec((Rectangle){ currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE }, wireColor);
      currentPos.y += (endPos.y > currentPos.y) ? CELL_SIZE : -CELL_SIZE;
    }
  } else {
    while (currentPos.y != endPos.y) {
      grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
      DrawRectangleRec((Rectangle){ currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE }, wireColor);
      currentPos.y += (endPos.y > currentPos.y) ? CELL_SIZE : -CELL_SIZE;
    }

    while (currentPos.x != endPos.x) {
      grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] = isPreview ? grid[(int)(currentPos.y / CELL_SIZE)][(int)(currentPos.x / CELL_SIZE)] : 1; // Update grid cell
      DrawRectangleRec((Rectangle){ currentPos.x - CELL_SIZE / 2.0f, currentPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE }, wireColor);
      currentPos.x += (endPos.x > currentPos.x) ? CELL_SIZE : -CELL_SIZE;
    }
  }

  // Draw the last cell where the mouse is currently at
  grid[(int)(endPos.y / CELL_SIZE)][(int)(endPos.x / CELL_SIZE)] = isPreview ? grid[(int)(endPos.y / CELL_SIZE)][(int)(endPos.x / CELL_SIZE)] : 1; // Update grid cell
  DrawRectangleRec((Rectangle){ endPos.x - CELL_SIZE / 2.0f, endPos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE }, wireColor);
}
//
// void drawGrid(float zoom, Vector2 offset) {
//   // Calculate the visible area based on the zoom level and offset
//   int startX = (int)((offset.x - GetScreenWidth() / (2.0f * zoom)) / CELL_SIZE);
//   int endX = (int)((offset.x + GetScreenWidth() / (2.0f * zoom)) / CELL_SIZE);
//   int startY = (int)((offset.y - GetScreenHeight() / (2.0f * zoom)) / CELL_SIZE);
//   int endY = (int)((offset.y + GetScreenHeight() / (2.0f * zoom)) / CELL_SIZE);
//
//   // Clamp the visible area to the grid boundaries
//   startX = fmax(startX, 0);
//   endX = fmin(endX, GRID_WIDTH - 1);
//   startY = fmax(startY, 0);
//   endY = fmin(endY, GRID_HEIGHT - 1);
//
//   // Draw only the visible cells
//   for (int y = startY; y <= endY; y++) {
//     for (int x = startX; x <= endX; x++) {
//       Rectangle cellRect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
//       if (grid[y][x]) {
//         DrawRectangleRec(cellRect, WHITE); // Draw filled cell
//       } else {
//         DrawRectangleRec(cellRect, GRAY); // Draw empty cell outline
//       }
//     }
//   }
// }
//

void drawGrid(float zoom, Vector2 offset) {
  // Calculate the visible area based on the zoom level and offset

  offset.x = (int)(offset.x / CELL_SIZE);
  offset.y = (int)(offset.y / CELL_SIZE);


  int startX = (int)((offset.x - GetScreenWidth()  / (2.0f * zoom)));
  int endX =   (int)((offset.x + GetScreenWidth()  / (2.0f * zoom)));
  int startY = (int)((offset.y - GetScreenHeight() / (2.0f * zoom)) / CELL_SIZE);
  int endY =   (int)((offset.y + GetScreenHeight() / (2.0f * zoom)) / CELL_SIZE);

  // Clamp the visible area to the grid boundaries
  startX = fmax(startX, 0);
  endX = fmin(endX, GRID_WIDTH - 1);
  startY = fmax(startY, 0);
  endY = fmin(endY, GRID_HEIGHT - 1);

  // printf("startX: %d\n", startX);
  // printf("startY: %d\n", startY);
  // printf("endX: %d\n", endX);
  // printf("endY: %d\n", endY);
  // printf("Offset X: %f\nOffset Y: %f\n", offset.x, offset.y);
  // Draw only the visible cells
  for (int y = startY; y <= endY; y++) {
    for (int x = startX; x <= endX; x++) {
      Rectangle cellRect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
      if (grid[y][x]) {
        DrawRectangleRec(cellRect, WHITE); // Draw filled cell
      } else {
        // DrawRectangleLinesEx(cellRect, 1, GRAY); // Draw empty cell outline
      }
    }
  }
}

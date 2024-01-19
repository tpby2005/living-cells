#include <stdio.h>
#include <raylib.h>
#include <unistd.h>

#define SIZE 800

enum cell_state
{
    DEAD,
    ALIVE
};

enum cell_event
{
    STAY,
    BIRTH,
    DEATH
};

enum cell_state current_cell = DEAD;
enum cell_state next_cell = DEAD;
int neighbor_count = 0;

enum cell_event determine_event(enum cell_state current_cell, int neighbor_count)
{
    if (current_cell == DEAD && neighbor_count == 3)
    {
        return BIRTH;
    }
    else if (current_cell == ALIVE && (neighbor_count == 2 || neighbor_count == 3))
    {
        return STAY;
    }
    else
    {
        return DEATH;
    }
}

enum cell_state handle_transition(enum cell_state current_cell, enum cell_event event)
{
    switch (event)
    {
    case STAY:
        return current_cell;
    case BIRTH:
        return ALIVE;
    case DEATH:
        return DEAD;
    }

    return DEAD;
}

enum cell_state grid[SIZE][SIZE];
enum cell_state next_grid[SIZE][SIZE];

int count_neighbors(enum cell_state grid[SIZE][SIZE], int i, int j)
{
    int count = 0;
    if (i > 0 && j > 0 && grid[i - 1][j - 1] == ALIVE)
    {
        count++;
    }
    if (i > 0 && grid[i - 1][j] == ALIVE)
    {
        count++;
    }
    if (i > 0 && j < SIZE - 1 && grid[i - 1][j + 1] == ALIVE)
    {
        count++;
    }
    if (j > 0 && grid[i][j - 1] == ALIVE)
    {
        count++;
    }
    if (j < SIZE - 1 && grid[i][j + 1] == ALIVE)
    {
        count++;
    }
    if (i < SIZE - 1 && j > 0 && grid[i + 1][j - 1] == ALIVE)
    {
        count++;
    }
    if (i < SIZE - 1 && grid[i + 1][j] == ALIVE)
    {
        count++;
    }
    if (i < SIZE - 1 && j < SIZE - 1 && grid[i + 1][j + 1] == ALIVE)
    {
        count++;
    }
    return count;
}

void game_of_life()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int neighbor_count = count_neighbors(grid, i, j);
            enum cell_event event = determine_event(grid[i][j], neighbor_count);
            next_grid[i][j] = handle_transition(grid[i][j], event);
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = next_grid[i][j];
        }
    }
}

void display()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == ALIVE)
            {
                DrawRectangle(i * 10, j * 10, 10, 10, BLACK);
            }
        }
    }
    EndDrawing();
}

int main(void)
{
    InitWindow(SIZE, SIZE, "Game of Life");
    SetTargetFPS(60);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = DEAD;
        }
    }

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int mouse_x = GetMouseX() / 10;
            int mouse_y = GetMouseY() / 10;

            if (mouse_x >= 0 && mouse_x < SIZE && mouse_y >= 0 && mouse_y < SIZE)
            {
                grid[mouse_x][mouse_y] = grid[mouse_x][mouse_y] == ALIVE ? DEAD : ALIVE;
            }
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            break;
        }

        if (IsKeyPressed(KEY_R))
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    grid[i][j] = GetRandomValue(0, 1);
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (grid[i][j] == ALIVE)
                {
                    DrawRectangle(i * 10, j * 10, 10, 10, BLACK);
                }
            }
        }
        EndDrawing();
    }

    while (!WindowShouldClose())
    {
        game_of_life();
        display();
        usleep(10000);
    }

    return 0;
}
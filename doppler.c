#include <stdio.h>
#include <raylib.h>

#define WIDTH 1200
#define HEIGHT 600
Vector2 CENTER = {WIDTH/2, HEIGHT/2};

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Doppler Simulator");

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(CENTER, 100, WHITE);
        EndDrawing();
    }
    return 0;
}

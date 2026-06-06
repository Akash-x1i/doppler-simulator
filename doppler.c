#include <stdio.h>
#include <raylib.h>

#define WIDTH 1200       // Initial width of window
#define HEIGHT 600       // Initial height of window
#define DELTA 5          // Velocity of OBJ1
#define DELTAD 10        // Doppler Drift Distance
#define OBJ1_RADIUS 40   // size (half) of the OBJ1 
#define DELTA_RADIUS 40  // Diff b/w two waves
#define OBJ1_RANGE 430   // Maximum Radius of a wave for OBJ1

// The remainder when OBJ1_RANGE divided by DELTA_RADIUS should be more than DELTA_RADIUS/2
// to propogate the waves outward, that means waves propgate inward
// when remainder is less than DELTA_RADIUS/2. and stay static when totally divisible or remainder is half of DELTA_RADIUS.

Vector2 OBJCoords = {WIDTH/2, HEIGHT/2};
Vector2 WaveEpicenter = {WIDTH/2, HEIGHT/2};
float WAVE_RADIUS = 45;

void drawCanvas(){
    ClearBackground(BLACK);
    WAVE_RADIUS= (((int)WAVE_RADIUS+DELTA_RADIUS)%OBJ1_RANGE);

    DrawCircleV(OBJCoords, OBJ1_RADIUS, WHITE);
    DrawCircleLinesV(WaveEpicenter, WAVE_RADIUS, PURPLE);
}


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Doppler Simulator");

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        drawCanvas();

        // Keyboard Controls:
        
        if (IsKeyDown(KEY_DOWN))
        {
            OBJCoords.y = OBJCoords.y + DELTA;      // obj moves forward
            WaveEpicenter.y = OBJCoords.y - DELTAD;   // wave drift backward
        }
        
        if (IsKeyDown(KEY_UP))
        {
            OBJCoords.y = OBJCoords.y - DELTA;
            WaveEpicenter.y = OBJCoords.y + DELTAD;
            
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            OBJCoords.x = OBJCoords.x + DELTA;
            WaveEpicenter.x = OBJCoords.x - DELTAD;
            
        }
        if (IsKeyDown(KEY_LEFT))
        {
            OBJCoords.x = OBJCoords.x - DELTA;
            WaveEpicenter.x = OBJCoords.x + DELTAD;
            
        }

        // reset wave drift 

        if(IsKeyReleased(KEY_DOWN) | IsKeyReleased(KEY_UP)){
            WaveEpicenter.y = OBJCoords.y;
        }
        if (IsKeyReleased(KEY_LEFT) | IsKeyReleased(KEY_RIGHT)){
            WaveEpicenter.x = OBJCoords.x;
        }
        

        drawCanvas();
        EndDrawing();
    }
    return 0;
}

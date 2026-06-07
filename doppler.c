#include <stdio.h>
#include <raylib.h>

#define WIDTH 1200       // Initial width of window
#define HEIGHT 600       // Initial height of window
#define DELTA 0.5f          // Velocity of OBJ1
#define DELTAD 10        // Doppler Drift Distance
#define MAX_WAVE 1000
#define OBJ1_RADIUS 10   // size (half) of the OBJ1 
#define FREQUENCY 1      // Diff b/w two wavesArr
#define FRAME_RATE 60
#define WAVELENGTH 10

#define BACKGROUND BLACK

Vector2 OBJCoords = {WIDTH/2, HEIGHT/2};

typedef struct Waves
{
    int x;
    int y;
    float z;

} Waves;

Waves WavesArr[MAX_WAVE];

int WaveCount = 0;
int currentWave = 0;

void newWave(){
    if(WaveCount < MAX_WAVE){
        WaveCount++;
    }
    currentWave = currentWave%WaveCount;
    WavesArr[currentWave] = (Waves){OBJCoords.x, OBJCoords.y, 0.0f};
    currentWave++;
}

void drawWave(){
    for(int i=0; i<WaveCount; i++){
        DrawCircleLines(WavesArr[i].x, WavesArr[i].y, WavesArr[i].z, PURPLE);
    }
}

void propagateWaves(float dt){
    int i;
    for ( i = 0; i < WaveCount; i++)
    {
        WavesArr[i].z += 1 ;
    }
    
}


void drawObj(){
    DrawCircleV(OBJCoords, OBJ1_RADIUS, WHITE);
}


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Doppler Simulator");

    SetTargetFPS(FRAME_RATE);
    float Interval = 0;
    while(!WindowShouldClose()){
        BeginDrawing();
        float dt = GetFrameTime();
        Interval += dt; 
        if(Interval > 0.16){
            newWave();
            Interval = 0;
        }
        
        
        ClearBackground(BLACK);

        // Keyboard Controls:
        
        if (IsKeyDown(KEY_DOWN))
        {
            OBJCoords.y = OBJCoords.y + DELTA;      // obj moves forward
        }
        if (IsKeyDown(KEY_UP))
        {
            OBJCoords.y = OBJCoords.y - DELTA;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            OBJCoords.x = OBJCoords.x + DELTA;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            OBJCoords.x = OBJCoords.x - DELTA;
        }
        
        propagateWaves(dt);
        drawWave();
        drawObj();


        EndDrawing();
    }
    return 0;
}

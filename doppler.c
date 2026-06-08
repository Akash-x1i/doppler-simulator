#include <stdio.h>
#include <raylib.h>

#define MAX_WAVE 50
#define OBJ1_RADIUS 10                // size (half) of the OBJ1 
#define WAVE_SPEED 343                // speed of sound mtr/sec approx      
#define SCALE 0.01f                    // Speed Scaling Factor    
#define FRAME_RATE 60.00f
#define MACH = (WAVE_SPEED * SCALE)  // MACH 1 Speed
#define BACKGROUND BLACK

float Frequency = 5.00f;
float ObjSpeed =  1.0f;               // Speed of Obj in Mach

int Height = 600;                    // Initial Height of window
int Width = 1200;                    // Initial Width of window

Vector2 OBJCoords = {600, 300};
Vector2 LegendPosition = {420, 1060};
Rectangle Legend = {1050, 450, 100, 100};

typedef struct Waves
{
    int x;
    int y;
    float z;
} Waves;

Waves WavesArr[MAX_WAVE];

int WaveCount = 0;
int currentWave = 0;

void getWindowSize(){
    Width = GetScreenWidth();
    Height = GetScreenHeight();
}

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
        WavesArr[i].z += WAVE_SPEED * SCALE;
    }   
}


void drawObj(){
    DrawCircleV(OBJCoords, OBJ1_RADIUS, WHITE);
}


void drawLegend(){
    Legend = (Rectangle){Width-200, Height-160, 180, 140};
    DrawRectangleRounded(Legend, 0.3, 1, WHITE);
    LegendPosition = (Vector2){Width-180, Height-140};
}

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(Width, Height, "Doppler Simulator");
    Font RobotoMono = LoadFont("assets/RobotoMono-Regular.ttf");
    SetTargetFPS(FRAME_RATE);
    float Interval = 0;
    while(!WindowShouldClose()){
        getWindowSize();
        BeginDrawing();
        float dt = GetFrameTime();
        float ObjSpeedWave = (FRAME_RATE/Frequency)*dt;
        Interval += dt; 
        if(Interval > ObjSpeedWave){
            newWave();
            Interval = 0;
        }
        
        
        ClearBackground(BLACK);

        // Keyboard Controls:

        if((IsKeyDown(KEY_LEFT_SHIFT) | IsKeyDown(KEY_RIGHT_SHIFT))){           // change speed of obj
            if (IsKeyPressed(KEY_DOWN))
            {
                if(ObjSpeed>0.0f) ObjSpeed -= 0.1f;
            }
            if (IsKeyPressed(KEY_UP))
            {
                ObjSpeed += 0.1f;

            }
        }
        else if((IsKeyDown(KEY_LEFT_CONTROL) | IsKeyDown(KEY_RIGHT_CONTROL))){   // change frquency
            if (IsKeyPressed(KEY_DOWN))
            {
                if(Frequency > 0)Frequency--;
            }
            if (IsKeyPressed(KEY_UP))
            {
                Frequency++;
            }
        }else{                                                                    // Move Object
            if (IsKeyDown(KEY_DOWN))
            {
                OBJCoords.y = OBJCoords.y + (ObjSpeed * WAVE_SPEED * SCALE);      
            }
            if (IsKeyDown(KEY_UP))
            {
                OBJCoords.y = OBJCoords.y - (ObjSpeed * WAVE_SPEED * SCALE);
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                OBJCoords.x = OBJCoords.x + (ObjSpeed * WAVE_SPEED * SCALE);      
            }
            if (IsKeyDown(KEY_LEFT))
            {
                OBJCoords.x = OBJCoords.x - (ObjSpeed * WAVE_SPEED * SCALE);
            }
        }
        
        
        propagateWaves(dt);
        drawWave();
        drawObj();
        drawLegend();
        DrawTextEx(RobotoMono,
            TextFormat("Frequency: %.2f\nWave Speed: %i\nScaling Factor: %.2f\nObj Speed: Mach %.2f\nFPS: %.f\nPress I for Help",
            Frequency, WAVE_SPEED, SCALE, ObjSpeed, FRAME_RATE), 
            LegendPosition, 15, 0, BLACK
        );
        EndDrawing();
    }
    UnloadFont(RobotoMono);
    CloseWindow();
    return 0;
}




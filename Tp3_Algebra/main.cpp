#include "raylib.h"


int main(void)
{
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Camera camera = { 0 };
    camera.position = Vector3{ 0.0f, 5.0f, 20.0f };
    camera.target = Vector3{ 0.0f, 5.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

   
    Model dice = LoadModel("../res/3x3x3.obj");
    
    SetTargetFPS(60);         
   
    while (!WindowShouldClose())    
    {
       
        /*if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;*/
       
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

        BeginMode3D(camera);

        DrawGrid(20, 1);

        DrawModel(dice, {0,0,0}, 5, RED);
        

        EndMode3D();

        EndDrawing();
       
    }

   
    CloseWindow(); 
    
    return 0;
}

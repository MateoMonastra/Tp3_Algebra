#include "raylib.h"

struct Entity {
    Model model;
    Vector3 position;
};

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

   
    Model poliedro = LoadModel("../res/poliedro1.obj");
    
    SetTargetFPS(60);         
   
    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

        BeginMode3D(camera);

        DrawGrid(20, 5);

        //DrawModel(poliedro, {0, 0, 0}, 2, RED);

        //DrawBoundingBox(box, ORANGE);
       
        for (int i = 0; i < poliedro.meshes[0].vertexCount; i += 3) {
            float x = poliedro.meshes[0].vertices[i];
            float y = poliedro.meshes[0].vertices[i + 1];
            float z = poliedro.meshes[0].vertices[i + 2];
            DrawSphere({x, y, z}, 0.05f, RED);
        }

        EndMode3D();

        EndDrawing();
       
    }

   
    CloseWindow(); 
    
    return 0;
}

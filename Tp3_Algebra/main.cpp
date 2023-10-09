#include "raylib.h"

struct Entity {
    Model model;
    Vector3 position;
};

int main(void)
{
   
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Camera camera = { 0 };
    camera.position = Vector3{ 0.0f, 5.0f, 20.0f };
    camera.target = Vector3{ 0.0f, 5.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

   
    Entity poliedro;
    poliedro.model = LoadModel("../res/poliedro1.obj");
    poliedro.position = { 2, 0, 0 };
    
    SetTargetFPS(60);         
   
    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

        BeginMode3D(camera);

        DrawGrid(20, 5);

        DrawModel(poliedro.model, poliedro.position, 1, RAYWHITE);
       
        Vector3 lastVertex;

        for (int i = 0; i < poliedro.model.meshes[0].vertexCount * 3; i += 3) {
            Vector3 currentVertex;
            currentVertex.x = poliedro.model.meshes[0].normals[i] + poliedro.position.x;
            currentVertex.y = poliedro.model.meshes[0].normals[i + 1] + poliedro.position.y;
            currentVertex.z = poliedro.model.meshes[0].normals[i + 2] + poliedro.position.z;
            DrawSphere({currentVertex.x, currentVertex.y, currentVertex.z}, 0.1f, RED);
            currentVertex.x = poliedro.model.meshes[0].vertices[i] + poliedro.position.x;
            currentVertex.y = poliedro.model.meshes[0].vertices[i + 1] + poliedro.position.y;
            currentVertex.z = poliedro.model.meshes[0].vertices[i + 2] + poliedro.position.z;
            DrawSphere({currentVertex.x, currentVertex.y, currentVertex.z}, 0.1, GREEN);
            if (i > 1) {
                DrawLine3D(currentVertex, lastVertex, GREEN);
            }
            lastVertex = currentVertex;
        }

        EndMode3D();

        EndDrawing();
       
    }

   
    CloseWindow(); 
    
    return 0;
}

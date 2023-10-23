#include "raylib.h"

#include <iostream>
#include <vector>

using namespace std;


struct Entity 
{
    Model model;
    Vector3 position;
};




void DrawVertex(Entity entity);
void ManageInput(Entity& poliedro);


int main(void)
{
   
    const int screenWidth = 1280;
    const int screenHeight = 720;

    vector<Vector3> grid;

    InitWindow(screenWidth, screenHeight, "Algebra TP3");

    Camera camera = { 0 };
    camera.position = Vector3{ 0.0f, 5.0f, 20.0f };
    camera.target = Vector3{ 0.0f, 5.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

   
    Entity poliedro;
    poliedro.model = LoadModel("../res/poliedro1.obj");
    poliedro.position = { 2, 0, 0 };

    Entity poliedro2;
    poliedro2.model = LoadModel("../res/poliedro1.obj");
    poliedro2.position = { 2, 0, 0 };
    
    SetTargetFPS(60);         
   
    


    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        ManageInput(poliedro);

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawGrid(200, 0.2f);

        DrawModel(poliedro.model, poliedro.position, 1, RAYWHITE);
        DrawModel(poliedro2.model, poliedro2.position, 1, YELLOW);
       
        DrawVertex(poliedro);
        DrawVertex(poliedro2);
       

        EndMode3D();

        EndDrawing();
       
    }
 
    CloseWindow(); 
    
    return 0;
}

void DrawVertex(Entity entity)
{
    Vector3 lastVertex;

    for (int i = 0; i < entity.model.meshes[0].vertexCount * 3; i += 3) {
        Vector3 currentVertex;
        currentVertex.x = entity.model.meshes[0].normals[i] + entity.position.x;
        currentVertex.y = entity.model.meshes[0].normals[i + 1] + entity.position.y;
        currentVertex.z = entity.model.meshes[0].normals[i + 2] + entity.position.z;
        DrawSphere({ currentVertex.x, currentVertex.y, currentVertex.z }, 0.1f, RED);
        currentVertex.x = entity.model.meshes[0].vertices[i] + entity.position.x;
        currentVertex.y = entity.model.meshes[0].vertices[i + 1] + entity.position.y;
        currentVertex.z = entity.model.meshes[0].vertices[i + 2] + entity.position.z;
        DrawSphere({ currentVertex.x, currentVertex.y, currentVertex.z }, 0.1, GREEN);
        if (i > 1) {
            DrawLine3D(currentVertex, lastVertex, GREEN);
        }
        lastVertex = currentVertex;
    }
}


bool isPointInsideModel(const Vector3& point, const Entity& entity) 
{
    Vector3 pointToModel;
    pointToModel.x = entity.position.x - point.x;
    pointToModel.y = entity.position.y - point.y;
    pointToModel.z = entity.position.z - point.z;

    bool insideModel = true;

    for (int i = 0; i < entity.model.meshes[0].vertexCount * 3; i+=3) 
    {
        Vector3 normal;
        normal.x = entity.model.meshes[0].normals[i] + entity.position.x;
        normal.y = entity.model.meshes[0].normals[i + 1] + entity.position.y;
        normal.z = entity.model.meshes[0].normals[i + 2] + entity.position.z;

        float dotProduct = pointToModel.x * normal.x + pointToModel.y * normal.y + pointToModel.z * normal.z;

        if (dotProduct < 0) 
        {
            insideModel = false;
            break;
        }
    }

    return insideModel;
}


void ManageInput(Entity& poliedro)
{
    if (IsKeyDown(KEY_RIGHT)) poliedro.position.x += 0.1f;
    if (IsKeyDown(KEY_LEFT)) poliedro.position.x -= 0.1f;
    if (IsKeyDown(KEY_UP)) poliedro.position.z -= 0.1f;
    if (IsKeyDown(KEY_DOWN)) poliedro.position.z += 0.1f;
    if (IsKeyDown(KEY_RIGHT_CONTROL)) poliedro.position.y -= 0.1f;
    if (IsKeyDown(KEY_RIGHT_SHIFT)) poliedro.position.y += 0.1f;
}


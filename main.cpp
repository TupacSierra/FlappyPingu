#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "FlappyPingu");

    Vector2 ballPosition = { (float)screenWidth - 700 , (float)screenHeight / 2 };
    const float ballRadius = 50.0f;

    Rectangle tube;
    tube.x = static_cast<float> (GetScreenWidth());
    tube.y = static_cast<float>(GetScreenHeight()) / 2 - 25;
    tube.width = 75;
    tube.height = 200;

    Vector2 tubePosition = { tube.x,tube.y };

    const float speed = 250.0f;

    bool collided = false;


    while (!WindowShouldClose())    
    {
      
      
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 120.0f * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 120.0f * GetFrameTime();
       

        tube.x -= speed * GetFrameTime();

        if (tube.x + tube.width < 0)
        {

            tube.x = static_cast<float>(GetScreenWidth());
            tube.y = static_cast<float>(GetRandomValue(0, GetScreenHeight() - 50));

        }

        collided = CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, tube);
       
       
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("version 0.1 flappypingu", 10, 430, 10, DARKGRAY);

        DrawCircleV(ballPosition, 50, MAROON);

        DrawRectangleRec(tube, BLUE);

        DrawText("DONT TOUCH THE BLUE RECTAGLE", screenWidth / 2, 10, 20, BLACK);

        if (collided)
        {
            DrawText("You lose", 10, 10, 20, RED);
        }

        EndDrawing();
        
    }

    
    CloseWindow();     
    

    return 0;
}

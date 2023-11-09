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


    const float gravity = 500.0f;
    const float jumpSpeed = 200.0f;

   
    float ballVelocityY = 0.0f;

    bool collided = false;

    while (!WindowShouldClose())    
    {
     
        const float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE) && ballPosition.y > ballRadius)
        {
            ballVelocityY = -jumpSpeed;
        }

        ballPosition.y += ballVelocityY * deltaTime;
        ballVelocityY += gravity * deltaTime;
        

        tube.x -= speed * GetFrameTime();

        if (tube.x + tube.width < 0)
        {

            tube.x = static_cast<float>(GetScreenWidth());
            tube.y = static_cast<float>(GetRandomValue(0, GetScreenHeight() - 50));

        }


        collided = CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, tube);
       

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Version 0.1 Flappy_Pingu", 10, 435, 15,BLACK);

        DrawCircleV(ballPosition, ballRadius, MAROON);

        DrawRectangleRec(tube, BLUE);

        DrawText("DONT TOUCH THE BLUE RECTAGLE", screenWidth / 2, 10, 20, BLACK);

        if (collided)
        {
            DrawText("You lose", 10, 10, 35, RED);
        }

        EndDrawing();
        
    }

    
    CloseWindow();     
    

    return 0;
}

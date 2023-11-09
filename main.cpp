#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "FlappyPingu");

    Vector2 ballPosition = { (float)screenWidth - 700 , (float)screenHeight / 2 };
    const float ballRadius = 50.0f;

    Rectangle upperTube{ (float)screenWidth,0.0f ,75.0f ,0.0f};
    Rectangle lowerTube{ (float)screenWidth ,0.0f ,75.0f ,0.0f };


    upperTube.width = lowerTube.width = 95;


    const float tubeSpeed = 400.0f;
    const float gravity = 650.0f;
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
        
        upperTube.x = lowerTube.x -= tubeSpeed * deltaTime;


        if (upperTube.x + upperTube.width < 0)
        {

            upperTube.x = lowerTube.x = static_cast <float>(GetScreenWidth());
            float tubePosition = static_cast<float>(GetRandomValue(150, GetScreenHeight() - 200));
            float gapHeight = 75.0f;
            float tubeHeight = static_cast<float>(GetScreenHeight()) - tubePosition + gapHeight;
            upperTube.height = tubePosition - gapHeight;
            lowerTube.y = tubePosition + gapHeight;
            lowerTube.height = tubeHeight;

        }

        collided = CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, upperTube) ||
                   CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, lowerTube);
       

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Version 0.1 Flappy_Pingu", 10, 435, 15,BLACK);

        DrawCircleV(ballPosition, ballRadius, MAROON);

        DrawRectangleRec(upperTube, BLUE);
        DrawRectangleRec(lowerTube, BLUE);


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

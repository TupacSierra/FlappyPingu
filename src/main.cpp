#include "raylib.h"

int main(void)
{
    const int screenWidth = 750;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "FlappyPingu");



    Texture2D background = LoadTexture("res/layers/sky.png");
    Texture2D background2 = LoadTexture("res/layers/cloud_lonely.png");
    Texture2D background3 = LoadTexture("res/layers/clouds_bg.png");
    Texture2D midground = LoadTexture("res/layers/glacial_mountains_lightened.png");
    Texture2D midground2 = LoadTexture("res/layers/clouds_mg_2.png");
    Texture2D foreground = LoadTexture("res/layers/clouds_mg_1_lightened.png");


    float scrollingBack = 0.0f;
    float scrollingBack2 = 0.0f;
    float scrollingBack3 = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingMid2 = 0.0f;
    float scrollingFore = 0.0f;


    Vector2 ballPosition = { (float)screenWidth - 600 , (float)screenHeight / 2 };
    const float ballRadius = 40.0f;

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
            float gapHeight = 60.0f;
            float tubeHeight = static_cast<float>(GetScreenHeight()) - tubePosition + gapHeight;
            upperTube.height = tubePosition - gapHeight;
            lowerTube.y = tubePosition + gapHeight;
            lowerTube.height = tubeHeight;
    
        }


        collided = CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, upperTube) ||
                   CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, lowerTube);
      


   

        scrollingBack -= 0.1f * deltaTime;
        scrollingBack2 -= 20.0f * deltaTime;
        scrollingBack3 -= 35.0f * deltaTime;
        scrollingMid -= 70.0f * deltaTime;
        scrollingMid2 -= 85.0f * deltaTime;
        scrollingFore -= 130.0f * deltaTime;

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingBack2 <= -background2.width * 2) scrollingBack2 = 0;
        if (scrollingBack3 <= -background3.width * 2) scrollingBack3 = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
        if (scrollingMid2 <= -midground2.width * 2) scrollingMid2 = 0;
        if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;




        BeginDrawing();

        ClearBackground(GetColor(0x052c46ff));

        DrawTextureEx(background, { scrollingBack , 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, { background.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(background2, { scrollingBack2 , 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background2, { background2.width * 2 + scrollingBack2, 20 }, 0.0f, 2.0f, WHITE);
       
       DrawTextureEx(background3, { scrollingBack3 , 20 }, 0.0f, 2.0f, WHITE);
       DrawTextureEx(background3, { background3.width * 2 + scrollingBack3, 20 }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(midground,  { scrollingMid, 40 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground, { midground.width * 2 + scrollingMid, 40 }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(midground2, { scrollingMid2, 40 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground2, { midground2.width * 2 + scrollingMid2, 40 }, 0.0f, 2.0f, WHITE);


        DrawCircleV(ballPosition, ballRadius, MAROON);

        DrawRectangleRec(upperTube, BLUE);
        DrawRectangleRec(lowerTube, BLUE);

        DrawTextureEx(foreground, { scrollingFore, 50 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreground, { foreground.width * 2 + scrollingFore, 50 }, 0.0f, 2.0f, WHITE);


        DrawText("Version 0.1 Flappy_Pingu", 10, 435, 15,BLACK);
     
   
        DrawText("DONT TOUCH THE BLUE RECTAGLE", screenWidth / 2, 10, 20, BLACK);

        if (collided)
        {
            DrawText("You lose", 10, 10, 35, RED);
        }

        EndDrawing();
        
    }

    UnloadTexture(background);  
    UnloadTexture(midground);  
    UnloadTexture(foreground);


    CloseWindow();     
    

    return 0;
}

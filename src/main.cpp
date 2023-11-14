#include "raylib.h"

enum GameState {
    MENU,
    PLAY,
    CREDITS,
    EXIT,
    GAME_OVER
};



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

    Rectangle upperTube1 = { (float)screenWidth, 0.0f, 95.0f, 0.0f };
    Rectangle lowerTube1 = { (float)screenWidth, 0.0f, 95.0f, 0.0f };

    Rectangle upperTube2 = { (float)screenWidth + screenWidth / 2, 0.0f, 95.0f, 0.0f };
    Rectangle lowerTube2 = { (float)screenWidth + screenWidth / 2, 0.0f, 95.0f, 0.0f };

    upperTube1.width = lowerTube1.width = upperTube2.width = lowerTube2.width = 95;

    const float tubeSpeed = 400.0f;
    const float gravity = 650.0f;
    const float jumpSpeed = 200.0f;

    float ballVelocityY = 0.0f;

    bool collided = false;

   

    GameState gameState = MENU;

    while (!WindowShouldClose())
    {
        switch (gameState)
        {
        case MENU:
            if (IsKeyPressed(KEY_P)) {
                gameState = PLAY;
            }
            else if (IsKeyPressed(KEY_C)) {
                gameState = CREDITS;
            }
            else if (IsKeyPressed(KEY_ESCAPE)) {
                gameState = EXIT;
            }
            break;

    
        case PLAY:

          
            if (ballPosition.y > screenHeight || collided) {
                gameState = GAME_OVER;
            }

            if (IsKeyPressed(KEY_SPACE) && ballPosition.y > ballRadius) {
                ballVelocityY = -jumpSpeed;
            }

            ballPosition.y += ballVelocityY * GetFrameTime();
            ballVelocityY += gravity * GetFrameTime();

            upperTube1.x = lowerTube1.x -= tubeSpeed * GetFrameTime();
            upperTube2.x = lowerTube2.x -= tubeSpeed * GetFrameTime();

            if (upperTube2.x + upperTube2.width <= 0) {
                upperTube2.x = lowerTube2.x = static_cast<float>(GetScreenWidth());
                float tubePosition = static_cast<float>(GetRandomValue(150, GetScreenHeight() - 200));
                float gapHeight = static_cast<float>(GetRandomValue(60, 70));
                float tubeHeight = static_cast<float>(GetScreenHeight()) - tubePosition + gapHeight;
                upperTube2.height = tubePosition - gapHeight;
                lowerTube2.y = tubePosition + gapHeight;
                lowerTube2.height = tubeHeight;

            }

            if (upperTube1.x + upperTube1.width <= 0) {
                upperTube1.x = lowerTube1.x = static_cast<float>(GetScreenWidth());
                float tubePosition = static_cast<float>(GetRandomValue(150, GetScreenHeight() - 200));
                float gapHeight = static_cast<float>(GetRandomValue(60, 70));
                float tubeHeight = static_cast<float>(GetScreenHeight()) - tubePosition + gapHeight;
                upperTube1.height = tubePosition - gapHeight;
                lowerTube1.y = tubePosition + gapHeight;
                lowerTube1.height = tubeHeight;
            }

            collided = CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, upperTube1) ||
                CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, lowerTube1) ||
                CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, upperTube2) ||
                CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, lowerTube2);

            break;

        case CREDITS:

            if (IsKeyPressed(KEY_B)) {
                gameState = MENU;
            }
            break;

        
        case GAME_OVER:
            if (IsKeyDown(KEY_R))
            {
               
                ballPosition = { (float)screenWidth - 600, (float)screenHeight / 2 };
                ballVelocityY = 0.0f;
                collided = false;

              
                upperTube1.x = lowerTube1.x = static_cast<float>(GetScreenWidth());
                upperTube2.x = lowerTube2.x = static_cast<float>(GetScreenWidth()) + screenWidth / 2;

                float tubePosition1 = static_cast<float>(GetRandomValue(150, GetScreenHeight() - 200));
                float gapHeight1 = static_cast<float>(GetRandomValue(60, 70));
                float tubeHeight1 = static_cast<float>(GetScreenHeight()) - tubePosition1 + gapHeight1;
                upperTube1.height = tubePosition1 - gapHeight1;
                lowerTube1.y = tubePosition1 + gapHeight1;
                lowerTube1.height = tubeHeight1;

                float tubePosition2 = static_cast<float>(GetRandomValue(150, GetScreenHeight() - 200));
                float gapHeight2 = static_cast<float>(GetRandomValue(60, 70));
                float tubeHeight2 = static_cast<float>(GetScreenHeight()) - tubePosition2 + gapHeight2;
                upperTube2.height = tubePosition2 - gapHeight2;
                lowerTube2.y = tubePosition2 + gapHeight2;
                lowerTube2.height = tubeHeight2;

                scrollingBack = scrollingBack2 = scrollingBack3 = scrollingMid = scrollingMid2 = scrollingFore = 0.0f;

                gameState = PLAY;
            }
            break;
        }

        scrollingBack -= 0.1f * GetFrameTime();
        scrollingBack2 -= 20.0f * GetFrameTime();
        scrollingBack3 -= 35.0f * GetFrameTime();
        scrollingMid -= 70.0f * GetFrameTime();
        scrollingMid2 -= 85.0f * GetFrameTime();
        scrollingFore -= 130.0f * GetFrameTime();

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

        DrawTextureEx(midground, { scrollingMid, 40 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground, { midground.width * 2 + scrollingMid, 40 }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(midground2, { scrollingMid2, 40 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground2, { midground2.width * 2 + scrollingMid2, 40 }, 0.0f, 2.0f, WHITE);

        DrawCircleV(ballPosition, ballRadius, MAROON);

        DrawRectangleRec(upperTube1, BLUE);
        DrawRectangleRec(lowerTube1, BLUE);

        DrawRectangleRec(upperTube2, BLUE);
        DrawRectangleRec(lowerTube2, BLUE);

        DrawTextureEx(foreground, { scrollingFore, 50 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreground, { foreground.width * 2 + scrollingFore, 50 }, 0.0f, 2.0f, WHITE);


        switch (gameState)
        {
        case MENU:
            DrawText("Press P to Play", screenWidth / 2 - 70, screenHeight / 2 - 20, 20, WHITE);
            DrawText("Press C for Credits", screenWidth / 2 - 90, screenHeight / 2 + 20, 20, WHITE);
            DrawText("Press ESC to Exit", screenWidth / 2 - 80, screenHeight / 2 + 60, 20, WHITE);

            DrawText("Version 0.2 Flappy_Pingu", 10, 435, 15, BLACK);

            DrawText("Flappy Pingu", screenWidth / 2 - 120, screenHeight / 2 - 80, 40, WHITE);
            break;

        case PLAY:

            break;

        case CREDITS:
            DrawText("Game Code by Tupac Sierra", screenWidth / 2 - 70, screenHeight / 2 - 20, 20, WHITE);
            DrawText("Art background by @vnitti_art ", screenWidth / 2 - 90, screenHeight / 2 + 20, 20, WHITE);
            DrawText("Press B to go back menu", screenWidth / 2 - 60, screenHeight / 2 + 60, 20, WHITE);
            break;

        case EXIT:

            break;
        
         case GAME_OVER:
             ClearBackground(GetColor(0x052c46ff));

             DrawText("You lose", screenWidth / 2 - 80, screenHeight / 2 - 20, 35, RED);
             DrawText("Press R to replay", screenWidth / 2 - 100, screenHeight / 2 + 20, 20, WHITE); 

             break;
             }
        

        EndDrawing();
    }


    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();

    return 0;
}
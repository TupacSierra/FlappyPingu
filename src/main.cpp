#include "raylib.h"

const int screenWidth = 750;
const int screenHeight = 450;


const char* backgroundPath = "res/layers/sky.png";
const char* playerPath = "res/player.png";
const char* background2Path = "res/layers/cloud_lonely.png";
const char* background3Path = "res/layers/clouds_bg.png";
const char* midgroundPath = "res/layers/glacial_mountains_lightened.png";
const char* midground2Path = "res/layers/clouds_mg_2.png";
const char* foregroundPath = "res/layers/clouds_mg_1_lightened.png";


const float scrollingBackSpeed = 0.1f;
const float scrollingBack2Speed = 20.0f;
const float scrollingBack3Speed = 35.0f;
const float scrollingMidSpeed = 70.0f;
const float scrollingMid2Speed = 85.0f;
const float scrollingForeSpeed = 130.0f;

const float gravity = 650.0f;
const float jumpSpeed = 200.0f;
const float tubeSpeed = 400.0f;

const float tubeWidth = 95.0f;
const float minGapHeight = 60.0f;
const float maxGapHeight = 70.0f;

const float ballRadius = 40.0f;
const Vector2 initialBallPosition = { (float)screenWidth - 600, (float)screenHeight / 2 };

const int tubeSpawnDistance = screenWidth / 2;

int score = 0;

int main(void)
{
	InitWindow(screenWidth, screenHeight, "FlappyPingu");


	Texture2D player = LoadTexture(playerPath);
	Texture2D background = LoadTexture(backgroundPath);
	Texture2D background2 = LoadTexture(background2Path);
	Texture2D background3 = LoadTexture(background3Path);
	Texture2D midground = LoadTexture(midgroundPath);
	Texture2D midground2 = LoadTexture(midground2Path);
	Texture2D foreground = LoadTexture(foregroundPath);


	float scrollingBack = 0.0f;
	float scrollingBack2 = 0.0f;
	float scrollingBack3 = 0.0f;
	float scrollingMid = 0.0f;
	float scrollingMid2 = 0.0f;
	float scrollingFore = 0.0f;


	Vector2 ballPosition = initialBallPosition;
	float ballVelocityY = 0.0f;

	Rectangle upperTube1 = { (float)screenWidth, 0.0f, tubeWidth, 0.0f };
	Rectangle lowerTube1 = { (float)screenWidth, 0.0f, tubeWidth, 0.0f };

	Rectangle upperTube2 = { (float)screenWidth + tubeSpawnDistance, 0.0f, tubeWidth, 0.0f };
	Rectangle lowerTube2 = { (float)screenWidth + tubeSpawnDistance, 0.0f, tubeWidth, 0.0f };


	upperTube1.x = lowerTube1.x = static_cast<float>(GetScreenWidth());
	upperTube2.x = lowerTube2.x = static_cast<float>(GetScreenWidth()) + tubeSpawnDistance;

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


	upperTube1.width = lowerTube1.width = upperTube2.width = lowerTube2.width = tubeWidth;

	bool scoredForTube1 = false;
	bool scoredForTube2 = false;

	bool collided = false;
	Rectangle playerSource = { 0,0,(float)player.width / 3,(float)player.height };
	Rectangle playerDestination = { ballPosition.x,ballPosition.y,(float)player.width / 3 * 5, (float)player.height * 5 };
	Vector2 origin = { playerDestination.width / 2, playerDestination.height / 2 };

	float playerAnimationTime = 0.0f;
	enum GameState {
		MENU,
		PLAY,
		CREDITS,
		EXIT,
		GAME_OVER,
		HOW_TO_PLAY
	};

	GameState gameState = MENU;

	while (!WindowShouldClose())
	{
		playerAnimationTime += GetFrameTime();

		if (playerAnimationTime > 0.3f)
		{

			playerSource.x += playerSource.width;
			if (playerSource.x >= player.width)
			{
				playerSource.x = 0;
			}
			playerAnimationTime = 0.0f;
		}


		switch (gameState)
		{

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


				scoredForTube2 = false;

			}

			if (upperTube1.x + upperTube1.width <= 0) {
				upperTube1.x = lowerTube1.x = static_cast<float>(GetScreenWidth());

				scoredForTube1 = false;

			}

			if (!collided) {

				if (ballPosition.x > upperTube1.x + upperTube1.width && !scoredForTube1) {
					score++;
					scoredForTube1 = true;
				}

				if (ballPosition.x > upperTube2.x + upperTube2.width && !scoredForTube2) {
					score++;
					scoredForTube2 = true;
				}
			}

			collided = CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, upperTube1) ||
				CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, lowerTube1) ||
				CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, upperTube2) ||
				CheckCollisionCircleRec(Vector2{ ballPosition.x, ballPosition.y }, ballRadius, lowerTube2);

			playerDestination.x = ballPosition.x;
			playerDestination.y = ballPosition.y;

			break;


		case MENU:
			if (IsKeyPressed(KEY_P)) {
				gameState = PLAY;
			}
			else if (IsKeyPressed(KEY_C)) {
				gameState = CREDITS;
			}
			else if (IsKeyPressed(KEY_H)) {
				gameState = HOW_TO_PLAY;
			}
			else if (IsKeyPressed(KEY_ESCAPE)) {
				gameState = EXIT;
			}
			break;

		case HOW_TO_PLAY:

			if (IsKeyPressed(KEY_B)) {
				gameState = MENU;
			}
			break;


		case CREDITS:

			if (IsKeyPressed(KEY_B)) {
				gameState = MENU;
			}
			break;


		case GAME_OVER:

			if (IsKeyDown(KEY_R))
			{

				scoredForTube1 = false;
				scoredForTube2 = false;

				ballPosition = { (float)screenWidth - 600, (float)screenHeight / 2 };
				ballVelocityY = 0.0f;
				collided = false;


				upperTube1.x = lowerTube1.x = static_cast<float>(GetScreenWidth());
				upperTube2.x = lowerTube2.x = static_cast<float>(GetScreenWidth()) + screenWidth / 2;


				scrollingBack = scrollingBack2 = scrollingBack3 = scrollingMid = scrollingMid2 = scrollingFore = 0.0f;

				 score = 0;

				gameState = PLAY;
			}

			if (IsKeyDown(KEY_B)) {

				gameState = MENU;

				scoredForTube1 = false;
				scoredForTube2 = false;

				scrollingBack = scrollingBack2 = scrollingBack3 = scrollingMid = scrollingMid2 = scrollingFore = 0.0f;

				ballPosition = { (float)screenWidth - 600, (float)screenHeight / 2 };
				ballVelocityY = 0.0f;
				collided = false;


				upperTube1.x = lowerTube1.x = static_cast<float>(GetScreenWidth());
				upperTube2.x = lowerTube2.x = static_cast<float>(GetScreenWidth()) + screenWidth / 2;

			

	

				 score = 0;
			}
			break;


		}

		scrollingBack -= scrollingBackSpeed * GetFrameTime();
		scrollingBack2 -= scrollingBack2Speed * GetFrameTime();
		scrollingBack3 -= scrollingBack3Speed * GetFrameTime();
		scrollingMid -= scrollingMidSpeed * GetFrameTime();
		scrollingMid2 -= scrollingMid2Speed * GetFrameTime();
		scrollingFore -= scrollingForeSpeed * GetFrameTime();


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

		DrawTexturePro(player, playerSource, playerDestination, origin, 0, WHITE);

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
			DrawText("Press H for How To Play", screenWidth / 2 - 110, screenHeight / 2 + 60, 20, WHITE);
			DrawText("Press ESC to Exit", screenWidth / 2 - 80, screenHeight / 2 + 100, 20, WHITE);

			DrawText("Version 0.2 Flappy_Pingu", 10, 435, 15, BLACK);

			DrawText("Flappy Pingu", screenWidth / 2 - 120, screenHeight / 2 - 80, 40, WHITE);
			break;

		case PLAY:
			DrawText(TextFormat("%d", score), screenWidth / 2 - 45 , screenHeight / 2 - 200 , 120, WHITE);
			break;

		case CREDITS:
			DrawText("Game Code by Tupac Sierra", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, WHITE);
			DrawText("Art background by @vnitti_art ", screenWidth / 2 - 125, screenHeight / 2 + 20, 20, WHITE);
			DrawText("Press B to go back to the main menu.", screenWidth / 2 - 160, screenHeight / 2 + 60, 20, WHITE);
			break;

		case HOW_TO_PLAY:
			DrawText("How To Play", screenWidth / 2 - 70, screenHeight / 2 - 80, 30, WHITE);
			DrawText("Press SPACE to make the penguin fly", screenWidth / 2 - 150, screenHeight / 2 - 20, 20, WHITE);
			DrawText("Avoid the pipes and try to stay alive!", screenWidth / 2 - 150, screenHeight / 2 + 20, 20, WHITE);
			DrawText("Press B to go back to the main menu.", screenWidth / 2 - 150, screenHeight / 2 + 60, 20, WHITE);

			break;
		case EXIT:

			break;

		case GAME_OVER:
			ClearBackground(GetColor(0x052c46ff));

			DrawText("You lose", screenWidth / 2 - 80, screenHeight / 2 - 20, 35, RED);
			DrawText("Press R to replay", screenWidth / 2 - 100, screenHeight / 2 + 20, 20, WHITE);
			DrawText(TextFormat("Your score is: %d", score), screenWidth / 2 - 100, screenHeight / 2 + 40, 20, WHITE);
			DrawText("Press B to go back to the menu", screenWidth / 2 - 160, screenHeight / 2 + 60, 20, WHITE);

			break;


		}


		EndDrawing();
	}


	UnloadTexture(background);
	UnloadTexture(midground);
	UnloadTexture(foreground);
	UnloadTexture(player);

	CloseWindow();

	return 0;
}


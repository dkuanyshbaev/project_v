#include "raylib.h"
#include <stdlib.h>
#include "rcamera.h"

#define MAX_COLUMNS 20

typedef enum Screen { LOGO = 0, PLAY, INFO } Screen;

int main() {
	// Initialization
    const int screenWidth = 1440;
    const int screenHeight = 900;

    Screen currentScreen = LOGO;
    Vector2 objectPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    // Disable KEY_ESCAPE to close window, X-button still works
    //SetExitKey(KEY_NULL);
    // Flag to request window to exit
    //bool exitWindowRequested = false;
    // Flag to set window to exit
    //bool exitWindow = false;

    Texture2D sprite;
    // Sound sound;
    // Music music;

    InitWindow(screenWidth, screenHeight, "Project V");
    ToggleFullscreen();
    //InitAudioDevice();
    // -------------------------------------------------------------------------
    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;

    // Generates some random columns
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }

    DisableCursor();                    // Limit cursor to relative movement inside the window
    // -------------------------------------------------------------------------
    SetTargetFPS(60);
    sprite = LoadTexture("res/img/texture.png");
    // sound = LoadSound("res/snd/sound.ogg");
    // music = LoadMusicStream("res/mus/music.mp3");
    //PlayMusicStream(music);

	// Main loop
    while (!WindowShouldClose()) {
    //while (!exitWindow) {
        // Update
    	//if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

    	//if (exitWindowRequested) {
    		//// A request for close window has been issued, we can save data before closing
    		//// or just show a message asking for confirmation
    		//if (IsKeyPressed(KEY_Y)) exitWindow = true;
    		//else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
    	//}

        switch(currentScreen) {
        	case LOGO:{
        		if (IsKeyPressed(KEY_ENTER)) {
        			currentScreen = PLAY;
        		}
        	} break;
        	case PLAY:{
        		//if (IsKeyPressed(KEY_ENTER)) {
        			//currentScreen = INFO;
        		//}
        	} break;
        	case INFO:{
        		if (IsKeyPressed(KEY_ENTER)) {
        			currentScreen = PLAY;
        		}
        	} break;
        	default: break;
        }

        /* if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L)) objectPosition.x += 8.0f; */
        /* if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H)) objectPosition.x -= 8.0f; */
        /* if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_K)) objectPosition.y -= 8.0f; */
        /* if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_J)) objectPosition.y += 8.0f; */

        //UpdateMusicStream(music);

        if (IsKeyPressed(KEY_ENTER) &&
            (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
            int display = GetCurrentMonitor();
            if (IsWindowFullscreen()) {
                SetWindowSize(screenWidth, screenHeight);
            } else {
                SetWindowSize(GetMonitorWidth(display),
                              GetMonitorHeight(display));
            }
            ToggleFullscreen();
        }

        if (IsKeyPressed(KEY_SPACE)) {
            // PlaySound(sound);
    		currentScreen = INFO;
        }


        // -------------------------------------------------------------------------
        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advance camera controls, it's reecommended to compute camera movement manually
        UpdateCamera(&camera, cameraMode);                  // Update camera
        // -------------------------------------------------------------------------


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);


        //if (exitWindowRequested) {
			//DrawRectangle(0, 100, screenWidth, 200, BLACK);
            //DrawText("exit? [y/n]", 40, 180, 30, WHITE);
        //}

        //DrawTexture(sprite, 0, 0, RAYWHITE);
        switch(currentScreen) {
        	case LOGO:{
        		DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
        		/* DrawText("welcome. press enter", 240, 350, 42, DARKGRAY); */
        		DrawText("49: The Maze", 240, 350, 42, DARKGRAY);
        	} break;
        	case PLAY:{
        		/* DrawCircleV(objectPosition, 24, BLACK); */
    // -------------------------------------------------------------------------
        BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, DARKGRAY); // Draw ground
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLACK);     // Draw a blue wall
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLACK);      // Draw a green wall
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, BLACK);      // Draw a yellow wall

                // Draw some cubes around
                for (int i = 0; i < MAX_COLUMNS - 12; i++)
                {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                }

                // Draw player cube
                if (cameraMode == CAMERA_THIRD_PERSON)
                {
                    DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
                    DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
                }

            EndMode3D();
    // -------------------------------------------------------------------------
        	} break;
        	case INFO:{
        		DrawText("important info. press enter", 240, 350, 42, DARKGRAY);
        	} break;
        	default: break;
        }
        EndDrawing();
    }

	// De-Initialization
    //StopMusicStream(music);
    //CloseAudioDevice();
    CloseWindow();

    return EXIT_SUCCESS;
}

#include "raylib.h"
#include <stdlib.h>

typedef enum Screen { LOGO = 0, PLAY, INFO } Screen;

int main() {
	// Initialization
    const int screenWidth = 1440;
    const int screenHeight = 900;
    Screen currentScreen = LOGO;
    Vector2 objectPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    // Disable KEY_ESCAPE to close window, X-button still works
    SetExitKey(KEY_NULL);
    // Flag to request window to exit
    bool exitWindowRequested = false;
    // Flag to set window to exit
    bool exitWindow = false;

    Texture2D sprite;
    // Sound sound;
    // Music music;

    InitWindow(screenWidth, screenHeight, "Project V");
    InitAudioDevice();
    SetTargetFPS(60);
    sprite = LoadTexture("res/img/texture.png");
    // sound = LoadSound("res/snd/sound.ogg");
    // music = LoadMusicStream("res/mus/music.mp3");
    //PlayMusicStream(music);

	// Main loop
    //while (!WindowShouldClose()) {
    while (!exitWindow) {
        // Update
    	if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

    	if (exitWindowRequested) {
    		// A request for close window has been issued, we can save data before closing
    		// or just show a message asking for confirmation
    		if (IsKeyPressed(KEY_Y)) exitWindow = true;
    		else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
    	}

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

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L)) objectPosition.x += 20.0f;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H)) objectPosition.x -= 20.0f;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_K)) objectPosition.y -= 20.0f;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_J)) objectPosition.y += 20.0f;

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

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (exitWindowRequested) {
			DrawRectangle(0, 100, screenWidth, 200, BLACK);
            DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
        } else DrawText("Try to close the window to get confirmation message!", 120, 200, 20, LIGHTGRAY);

        //DrawTexture(sprite, 0, 0, RAYWHITE);
        switch(currentScreen) {
        	case LOGO:{
        		DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
        		DrawText("welcome. press enter", 240, 350, 42, DARKGRAY);
        	} break;
        	case PLAY:{
        		DrawCircleV(objectPosition, 24, BLACK);
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

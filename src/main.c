#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

    Texture2D sprite;
    // Sound sound;
    Music music;

    InitWindow(screenWidth, screenHeight, "Project V");
    InitAudioDevice();
    SetTargetFPS(60);
    sprite = LoadTexture("res/texture.png");
    // sound = LoadSound("file_name.ogg");
    music = LoadMusicStream("res/music.mp3");
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        // Update
        UpdateMusicStream(music);
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
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(sprite, 0, 0, RAYWHITE);
        DrawText("Hello..", 240, 350, 42, DARKGRAY);
        EndDrawing();
    }

    StopMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return EXIT_SUCCESS;
}

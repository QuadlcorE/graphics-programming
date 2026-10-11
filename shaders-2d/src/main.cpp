/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

constexpr auto SCREEN_WIDTH = 540;
constexpr auto SCREEN_HEIGHT = 810;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shader 2D");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture background = LoadTexture("images/a.gif");

	Shader shader = LoadShader(0, "shaders/wavy.fs");
	
	int timeLoc = GetShaderLocation(shader, "time");

	SetTargetFPS(60);	
	//-------------------------------------------------------------------------------
	
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update 
		float time = (float)GetTime();
		SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
		
		// Set New shader to be used

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		const int texture_x = SCREEN_WIDTH / 2 - background.width / 2;
		const int texture_y = SCREEN_HEIGHT / 2 - background.height / 2;

		const int hello_text_x = SCREEN_WIDTH / 2 - MeasureText("Shader 2D", 20) / 2;
		const int hello_text_y = texture_y + background.height + 10;

		BeginShaderMode(shader);
			DrawTexture(background, texture_x, texture_y, WHITE);
		EndShaderMode();

		// draw some text using the default font
		DrawText("Shader 2D", hello_text_x, hello_text_y, 20, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(background);
	UnloadShader(shader);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

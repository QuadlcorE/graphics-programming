#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 600;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Shaders");

	// Camera Definitions
	Camera camera = { 0 };
	camera.position = Vector3{ 500.0f, 500.0f, 50.0f }; // Camera position
	camera.target = Vector3{ 0.0f, 12.0f, 0.0f}; 		// Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f }; 			// Camera up Vector  (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load Model 
	Model model = LoadModel("models/cyberpunk-bike/source/neo_tokyo.obj");
	Texture2D texture = LoadTexture("models/cyberpunk-bike/textures/neo_NeoTokyoBike_color.png");
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

	Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model world position

	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update 
		// ----------------------------------------------------------------------------------------
		UpdateCamera(&camera, CAMERA_ORBITAL);

		// Draw 
		// ----------------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);

				DrawModel(model, position, 1.0f, WHITE);

			EndMode3D();

			DrawText(" This actually worked ", 10, 10, 20, GRAY);
		EndDrawing();
	}

	// De-Initialization
	// -------------------------------------------------------------------------------------------
	UnloadModel(model);
	UnloadTexture(texture);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

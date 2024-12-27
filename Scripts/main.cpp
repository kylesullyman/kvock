#include "raylib.h"
#include "rcamera.h"
#include "Headers/CameraController.h"
#include "unused /PlayerController.h"
#include "Headers/Player.h"
#include "Headers/InputHandler.h"

#define MAX_COLUMNS 20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "kvock");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera3D camera = {0};
    camera.position = (Vector3) {0.0f, 2.0f, 4.0f};    // Camera position
    camera.target = (Vector3) {0.0f, 2.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    // initialize cameraController class with the main camera
    // initialize playerModel
    CameraController cameraController(camera);
    // initialize inputHandler
    Player player(cameraController);
    InputHandler inputHandler(player);
    // initialize the player object witht he camera
    
    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        inputHandler.Update();
        player.Update();


        camera.position = player.getPosition();
        camera.target = player.target;

        UpdateCameraPro(&camera,
                        (Vector3){
                                0.0f,
                                0.0f,
                                0.0f
        },
                        (Vector3){
                                GetMouseDelta().x * 0.05f,
                                GetMouseDelta().y * 0.05f,
                                0.0f
        },
        0.0f);
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawPlane((Vector3) {0.0f, 0.0f, 0.0f}, (Vector2) {32.0f, 32.0f}, LIGHTGRAY); // Draw ground
        DrawCube((Vector3) {-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
        DrawCube((Vector3) {16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
        DrawCube((Vector3) {0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
        DrawBoundingBox(player.boundingBox, WHITE);

        // Draw player cube
        if (cameraController.cameraMode == CAMERA_THIRD_PERSON) {
            DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
            DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
        }

        EndMode3D();

        // Draw info boxes
        DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(5, 5, 330, 100, BLUE);

        DrawText("Camera controls:", 15, 15, 10, BLACK);
        DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, BLACK);
        DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);
        DrawText("- Camera mode keys: 1, 2, 3, 4", 15, 60, 10, BLACK);
        DrawText("- Zoom keys: num-plus, num-minus or mouse scroll", 15, 75, 10, BLACK);
        DrawText("- Camera projection key: P", 15, 90, 10, BLACK);

        DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(600, 5, 195, 100, BLUE);

        DrawText("Camera status:", 610, 15, 10, BLACK);
        DrawText(TextFormat("- Mode: %s", (cameraController.cameraMode == CAMERA_FREE) ? "FREE" :
                                          (cameraController.cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                          (cameraController.cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                          (cameraController.cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
        DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"),
                 610, 45, 10, BLACK);
        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y,
                            camera.position.z), 610, 60, 10, BLACK);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z),
                 610, 75, 10, BLACK);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10,
                 BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
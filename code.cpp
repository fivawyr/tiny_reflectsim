#include <raylib.h>
#include <cstdint>

typedef int32_t i32;
typedef float f32;
typedef double f64;

constexpr i32 WIDTH{900};
constexpr i32 HEIGHT{600};  

int main() {
   
    InitWindow(WIDTH, HEIGHT, "Reflection Simulation");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        Vector2 mouse_pos = GetMousePosition();
        ClearBackground(BLACK);
        DrawRectangleV(mouse_pos, (Vector2){10, 10}, WHITE);


        BeginDrawing();
        EndDrawing();
    }
    return 0;

}

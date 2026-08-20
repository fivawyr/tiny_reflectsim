#include <raylib.h>
#include <cstdint>

typedef int32_t i32;
typedef float f32;
typedef double f64;

constexpr i32 WIDTH{900};
constexpr i32 HEIGHT{600};  

struct Particle {
    i32 x, y, vx, vy;
};

struct Particle particles;

void MoveWave(f32 dt) {
    particles.x += particles.vx * dt;
    particles.y += particles.vy * dt;
}

void InitWave(Vector2 origin) {
    // init particles in different directions 
    particles.x = origin.x; 
    particles.y = origin.y; 
    particles.vx = 1; 
    particles.vy = 1; 


}

void DrawWave() {
    DrawRectangle(particles.x, particles.y, PARTICLE_SIZE, PARTICLE_SIZE, BLUE)
}

int main() {
   
    InitWindow(WIDTH, HEIGHT, "Reflection Simulation");
    SetTargetFPS(60);
    InitWave();

    while (!WindowShouldClose()) {

        Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();
        MoveWave();
        ClearBackground(BLACK);
        DrawRectangleV(mouse_pos, (Vector2){10, 10}, WHITE);
        DrawWave();
        EndDrawing();
    }
    return 0;

}

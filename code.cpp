#include <raylib.h>
#include <cstdint>

typedef int32_t i32;
typedef float f32;
typedef double f64;

constexpr i32 WIDTH{900};
constexpr i32 HEIGHT{600};  
constexpr i32 WAVE_SPEED{200};
constexpr i32 PARTICLE_SIZE{20};

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
    particles.vx = WAVE_SPEED;
    particles.vy = WAVE_SPEED;

}

void DrawWave() {
    DrawRectangle(particles.x, particles.y, PARTICLE_SIZE, PARTICLE_SIZE, WHITE);
}

int main() {
   
    InitWindow(WIDTH, HEIGHT, "Reflection Simulation");
    SetTargetFPS(60);

    bool wave_emitted = false;
    f32 interval {0};

    while (!WindowShouldClose()) {

        f32 dt = GetFrameTime();
        interval += dt;

        Vector2 mouse_pos = GetMousePosition();

        if (!wave_emitted && mouse_pos.x > 0 && mouse_pos.y > 0) {
            InitWave(mouse_pos);
            wave_emitted = true;
        }

        BeginDrawing();
        MoveWave(GetFrameTime());
        ClearBackground(BLACK);
        DrawRectangleV(mouse_pos, (Vector2){10, 10}, WHITE);
        DrawWave();
        EndDrawing();
    }
    return 0;

}

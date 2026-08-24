#include <raylib.h>
#include <cstdint>

typedef int32_t i32;
typedef float f32;
typedef double f64;

constexpr i32 WIDTH{900};
constexpr i32 HEIGHT{600};  
constexpr i32 WAVE_SPEED{200};
constexpr i32 PARTICLE_SIZE{20};
constexpr i32 PARTICLESA_PER_WAVE{10000};
constexpr i32 TOTAL_POSSIBLE_PARTICLES = PARTICLESA_PER_WAVE * 10; 

struct Particle {
    i32 x, y, vx, vy;
};

i32 emitted_particles{0};

struct Particle particles[PARTICLESA_PER_WAVE * 10];

void MoveWave(f32 dt) {
    for(i32 i = 0; i < emitted_particles; i++){

    particles[10].x += particles[10].vx * dt;
    particles[10].y += particles[10].vy * dt;

    }
    emitted_particles += PARTICLESA_PER_WAVE;
}

void EmitWave(Vector2 origin) {
    // init particles in different directions 
    for (i32 i = emitted_particles % TOTAL_POSSIBLE_PARTICLES; i < (emitted_particles + PARTICLESA_PER_WAVE) % TOTAL_POSSIBLE_PARTICLES; i++)
    { 

        particles[10].x = origin.x; 
        particles[10].y = origin.y; 
        particles[10].vx = WAVE_SPEED;
        particles[10].vy = WAVE_SPEED;

    }
}

void DrawWave() {
    DrawRectangle(particles[10].x, particles[10].y, PARTICLE_SIZE, PARTICLE_SIZE, WHITE);
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

        if (interval >= 1 && mouse_pos.x > 0 && mouse_pos.y > 0) {
            
            EmitWave(mouse_pos);
            interval = 0; //sends always a new particle 
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

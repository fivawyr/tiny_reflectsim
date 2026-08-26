#include <raylib.h>
#include <cstdint>
#include <cmath>

typedef int32_t i32;
typedef float f32;

constexpr i32 WIDTH{900};
constexpr i32 HEIGHT{600};
constexpr f32 WAVE_SPEED{200.0f};
constexpr f32 MAX_RADIUS{1200.0f};
constexpr i32 MAX_WAVES{32};
constexpr f32 EMIT_INTERVAL{1.0f}; 

struct Wave_Object
{
    Vector2 origin;
    f32 radius;
    bool active;
};

Wave_Object waves[MAX_WAVES];
i32 wave_count = 0;

Color WaveColor(f32 t) 
{

    Color hot = {255, 255, 255, 255}; 
    Color mid = {80, 200, 255, 255}; 
    Color cold = {20, 40, 120, 255}; 
    Color a, b;
    f32 local_t;
    if (t < 0.5f) {
        a = hot; b = mid;
        local_t = t / 0.5f;
    } else {
        a = mid; b = cold;
        local_t = (t - 0.5f) / 0.5f;
    }

    Color result;
    result.r = (unsigned char)(a.r + (b.r - a.r) * local_t);
    result.g = (unsigned char)(a.g + (b.g - a.g) * local_t);
    result.b = (unsigned char)(a.b + (b.b - a.b) * local_t);
    result.a = 255;
    return result;
}

void EmitWave(Vector2 origin) 
{
    i32 idx = wave_count % MAX_WAVES;
    waves[idx].origin = origin;
    waves[idx].radius = 0.0f;
    waves[idx].active = true;
    wave_count++;
}

void UpdateWaves(f32 dt) 
{
    for (i32 i = 0; i < MAX_WAVES; i++) {
        if (!waves[i].active) continue;
        waves[i].radius += WAVE_SPEED * dt;
        if (waves[i].radius > MAX_RADIUS) {
            waves[i].active = false;
        }
    }
}

void DrawWaves() 
{
    for (i32 i = 0; i < MAX_WAVES; i++) 
    {
        if (!waves[i].active) continue;
        f32 t = waves[i].radius / MAX_RADIUS; 
        f32 fade = 1.0f - t; 
        Color base_color = WaveColor(t);
        Color outer_color = Fade(base_color, fade);
        Color inner_color = Fade(base_color, fade * 0.5f);
        f32 thickness = 2.5f + sinf(waves[i].radius * 0.05f) * 1.2f;
        DrawRing(waves[i].origin, waves[i].radius - thickness, waves[i].radius, 0, 360, 64, outer_color);
        f32 inner_radius = waves[i].radius * 0.85f;
        DrawRing(waves[i].origin, inner_radius - thickness * 0.6f, inner_radius, 0, 360, 64, inner_color);
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Reflection Simulation");
    SetTargetFPS(60);
    f32 interval{0};

    while (!WindowShouldClose()) {
        f32 dt = GetFrameTime();
        interval += dt;
        Vector2 mouse_pos = GetMousePosition();

        if (interval >= EMIT_INTERVAL) {
            EmitWave(mouse_pos);
            interval = 0;
        }

        UpdateWaves(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawWaves();
        DrawCircleV(mouse_pos, 5, WHITE);
        EndDrawing();
    }

    return 0;
}

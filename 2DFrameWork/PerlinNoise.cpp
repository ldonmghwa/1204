#include "framework.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::PerlinNoise(int _x, int _y) {
    x = _x;
    y = _y;
}

float PerlinNoise::GetPerlinNoise(float x, float y)
{
    float result = 0.0f;

    Vector2 grads[4];
    Vector2 vertices[4];
    Vector2 dist[4];
    float influence[4];

    Vector2 myPosition(x, y);

    vertices[0] = Vector2(static_cast<int>(x), static_cast<int>(y)); // left down
    vertices[1] = Vector2(static_cast<int>(x) + 1, static_cast<int>(y)); // right down
    vertices[2] = Vector2(static_cast<int>(x), static_cast<int>(y) + 1); // left up
    vertices[3] = Vector2(static_cast<int>(x) + 1, static_cast<int>(y) + 1); // right up

    for (int i = 0; i < 4; i++) {
        grads[i] = GetRandomGradientByCoordinate(vertices[i]);
        dist[i] = myPosition - vertices[i];
        influence[i] = DotProduct(Vector2(grads[i].x, grads[i].y), Vector2(dist[i].x, dist[i].y));
    }

    float lerp1 = Interpolation(influence[0], influence[1], x - static_cast<int>(x));
    float lerp2 = Interpolation(influence[2], influence[3], x - static_cast<int>(x));

    result = Interpolation(lerp1, lerp2, y - static_cast<int>(y));

    return result;
}

float PerlinNoise::Interpolation(float a, float b, float step)
{
    float easeStep = 6 * std::pow(step, 5) - 15 * std::pow(step, 4) + 10 * std::pow(step, 3);
    return a + (b - a) * easeStep;
}

Vector2 PerlinNoise::GetRandomGradientByCoordinate(Vector2 position)
{
    // Seed-based random number generation
    std::srand(static_cast<unsigned int>(std::sin(DotProduct(position, Vector2(12.9898f, 78.233f))) * 43758.5453f) % 2147483647);
    return Vector2(static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f, static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f);
}

float PerlinNoise::DotProduct(Vector2 vector1, Vector2 vector2)
{
    vector1.Normalize();
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

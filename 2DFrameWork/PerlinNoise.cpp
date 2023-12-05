#include "framework.h"

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::~PerlinNoise()
{
}

void PerlinNoise::Update()
{
}

void PerlinNoise::Perlin(float _x, float _y)
{
	Vector2 vertices[4];
	Vector2 grad[4];
	Vector2 dist[4];
	Vector2 position = Vector2(_x, _y);
	float dot[4];
	
	vertices[0] = Vector2((int)_x, (int)_y);
	vertices[1] = Vector2((int)_x, (int)_y + 1);
	vertices[2] = Vector2((int)_x + 1, (int)_y);
	vertices[3] = Vector2((int)_x + 1, (int)_y + 1);

	for (int i = 0; i < 4; i++) {
		dist[i] = position - vertices[i];
		grad[i] = Vector2(vertices[i].x + RANDOM->Float(-100, 100), vertices[i].y + RANDOM->Float(-100, 100))
			- vertices[i];
		grad[i].Normalize();
		//dot[i] = dist[i].x * grad[i].x + dist[i].y + grad[i].y;
		dot[i] = dist[i].Dot(grad[i]);
		cout << dot[i] << endl;
	}

}

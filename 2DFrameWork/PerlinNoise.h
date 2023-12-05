#pragma once
class PerlinNoise
{
private:
	float x, y;
public:
	PerlinNoise();
	~PerlinNoise();
	
	void Update();
	void Perlin(float _x, float _y);
};


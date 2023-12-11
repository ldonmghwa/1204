#include "stdafx.h"
#include "ONEDPerlinNoise.h"

ONEDPerlinNoise::ONEDPerlinNoise()
{    // Initialize permutation table (p)
	p.resize(512);
	iota(p.begin(), p.end(), 0);
	std::random_shuffle(p.begin(), p.end());
}

double ONEDPerlinNoise::noise(double x) const
{
	int X = static_cast<int>(std::floor(x)) & 255;
	x -= std::floor(x);
	double u = fade(x);
	return lerp(u, grad(p[X], x), grad(p[X + 1], x - 1));
}

double ONEDPerlinNoise::fade(double t) const
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double ONEDPerlinNoise::lerp(double t, double a, double b) const
{
	return a + t * (b - a);
}

double ONEDPerlinNoise::grad(int hash, double x) const
{
	int h = hash & 15;
	double grad = 1 + (h & 7);  // Gradient value 1-8
	if (h & 8) {
		grad = -grad;
	}
	return (grad * x);
}

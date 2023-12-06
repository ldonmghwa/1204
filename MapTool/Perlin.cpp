#include "stdafx.h"
#include "Perlin.h"

Perlin::Perlin()
{    // Initialize permutation table (p)
	p.resize(512);
	iota(p.begin(), p.end(), 0);
	std::random_shuffle(p.begin(), p.end());
	for (auto it = p.begin(); it != p.end(); it++)
		cout << (*it) << " ";
	cout << endl;
	p.insert(p.end(), p.begin(), p.end());  // To avoid index wrapping
	for (auto it = p.begin(); it != p.end(); it++)
		cout << (*it) << " ";
	cout << endl;
}

double Perlin::noise(double x) const
{
	int X = static_cast<int>(std::floor(x)) & 255;
	x -= std::floor(x);
	double u = fade(x);
	return lerp(u, grad(p[X], x), grad(p[X + 1], x - 1));
}

double Perlin::fade(double t) const
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double t, double a, double b) const
{
	return a + t * (b - a);
}

double Perlin::grad(int hash, double x) const
{
	int h = hash & 15;
	double grad = 1 + (h & 7);  // Gradient value 1-8
	if (h & 8) {
		grad = -grad;
	}
	return (grad * x);
}

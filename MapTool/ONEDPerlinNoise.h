#pragma once
class ONEDPerlinNoise
{
public:
    ONEDPerlinNoise();

    double noise(double x) const;

private:
    std::vector<int> p;

    double fade(double t) const;
    double lerp(double t, double a, double b) const;
    double grad(int hash, double x) const;
};


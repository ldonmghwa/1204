#pragma once
class PerlinNoise2
{
private:
    int width;
    int height;

    int Number_Of_Octaves;
    float persistence;

    int seed1;
    int seed2;
    int seed3;
    double seed4;

    float Noise1(int x, int y);
    float SmoothNoise_1(float x, float y);
    float InterpolatedNoise_1(float x, float y);
    float PerlinNoise_2D(float x, float y, int Number_Of_Octaves, float persistence);

public:
    PerlinNoise2();
    PerlinNoise2(
        int _width,
        int _height, 
        int _Number_Of_Octaves,
        float _persistence,
        int _seed1,
        int _seed2,
        int _seed3,
        double _seed4);

    void SaveHeightmapAsPNG();
};
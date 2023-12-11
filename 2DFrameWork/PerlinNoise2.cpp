#include "framework.h"

PerlinNoise2::PerlinNoise2()
{
    width = 512;
    height = 512;
    Number_Of_Octaves = 5;
    persistence = 0.5f;
    seed1 = 15731;
    seed2 = 789221;
    seed3 = 1376312589;
    seed4 = 1073741824.0;
}
PerlinNoise2::PerlinNoise2(
    int _width,
    int _height, 
    int _Number_Of_Octaves,
    float _persistence,
    int _seed1, 
    int _seed2, 
    int _seed3, 
    double _seed4)
{
    width = _width;
    height = _height;
    Number_Of_Octaves = _Number_Of_Octaves;
    persistence = _persistence;
    seed1 = _seed1;
    seed2 = _seed2;
    seed3 = _seed3;
    /*if (_seed4 >= 100000000 and _seed4 < 10000000000) seed4 = _seed4;
    else seed4 = 1073741824.0;*/
    seed4 = _seed4;
}

float PerlinNoise2::Noise1(int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
    float retur = static_cast<float>(1.0 - (static_cast<double>((n * (n * n * seed1 + seed2) + seed3) & 0x7fffffff) / seed4));
    return retur;

}


float PerlinNoise2::SmoothNoise_1(float x, float y)
{
	float corners = (Noise1(x - 1, y - 1) + Noise1(x + 1, y - 1) + Noise1(x - 1, y + 1) + Noise1(x + 1, y + 1)) / 16.0f;
	float sides = (Noise1(x - 1, y) + Noise1(x + 1, y) + Noise1(x, y - 1) + Noise1(x, y + 1)) / 8.0f;
	float center = Noise1(x, y) / 4.0f;
	return corners + sides + center;
}

float PerlinNoise2::InterpolatedNoise_1(float x, float y)
{
    int integer_X = static_cast<int>(x);
    float fractional_X = x - integer_X;

    int integer_Y = static_cast<int>(y);
    float fractional_Y = y - integer_Y;

    float v1 = SmoothNoise_1(integer_X, integer_Y);
    float v2 = SmoothNoise_1(integer_X + 1, integer_Y);
    float v3 = SmoothNoise_1(integer_X, integer_Y + 1);
    float v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1);

    float i1 = (1 - fractional_X) * v1 + fractional_X * v2;
    float i2 = (1 - fractional_X) * v3 + fractional_X * v4;

    return (1 - fractional_Y) * i1 + fractional_Y * i2;
}

float PerlinNoise2::PerlinNoise_2D(float x, float y, int Number_Of_Octaves, float persistence)
{
    float total = 0.0f;
    int n = Number_Of_Octaves - 1;

    for (int i = 0; i <= n; ++i) {
        float frequency = static_cast<float>(pow(2, i));
        float amplitude = static_cast<float>(pow(persistence, i));
        total += InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;
    }

    return total;
}

void PerlinNoise2::SaveHeightmapAsPNG()
{
    string filename = "../Contents/HeightMap/perlin_noise_"
        + to_string(Number_Of_Octaves) +
        "_" + to_string(persistence) +
        "_" + to_string(seed1) +
        "_" + to_string(seed2) +
        "_" + to_string(seed3) +
        "_" + to_string(seed4) +
        "_" + to_string(width) + "x" + to_string(height) + ".png";
    std::vector<unsigned char> image;
    image.resize(width * height * 4); // RGBA format

    float scaleX = 0.1f;
    float scaleY = 0.1f;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float perlinValue = PerlinNoise_2D(x * scaleX, y * scaleY, Number_Of_Octaves, persistence);
            unsigned char color = static_cast<unsigned char>((perlinValue + 1.0f) * 0.5f * 255.0f);
            int index = 4 * (y * width + x);
            image[index] = color;
            image[index + 1] = color;
            image[index + 2] = color;
            image[index + 3] = 255; // Alpha channel
        }
    }

    if (lodepng::encode(filename.c_str(), image.data(), width, height) != 0) {
        std::cerr << "Error saving PNG file." << std::endl;
    }
    else {
        std::cout << "Heightmap saved as " << filename << std::endl;
    }
}

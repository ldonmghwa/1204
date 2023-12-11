class PerlinNoise {
public:
    PerlinNoise();
    PerlinNoise(int _x, int _y);
    float GetPerlinNoise(float x, float y);
    float Interpolation(float a, float b, float step);
    Vector2 GetRandomGradientByCoordinate(Vector2 position);
    float DotProduct(Vector2 vector1, Vector2 vector2);
private:
    int x, y;
};
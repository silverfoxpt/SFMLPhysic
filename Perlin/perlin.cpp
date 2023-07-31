#include "perlin.h"

PerlinNoise::PerlinNoise() {
    permutation = std::vector<int>(256);
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), std::default_random_engine());
    permutation.insert(permutation.end(), permutation.begin(), permutation.end());
}

double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : (h == 12 || h == 14) ? x : 0;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

double PerlinNoise::grad1D(int hash, double x) {
    int h = hash & 15;
    double grad = 1.0 + (h & 7); // Gradient value between 1 and 8
    if (h & 8) {
        grad = -grad; // Randomly invert the gradient to get both positive and negative values
    }
    return grad * x;
}

double PerlinNoise::noise(double x, double y) {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    x -= std::floor(x);
    y -= std::floor(y);
    double u = fade(x);
    double v = fade(y);
    int A = permutation[X] + Y;
    int AA = permutation[A];
    int AB = permutation[A + 1];
    int B = permutation[X + 1] + Y;
    int BA = permutation[B];
    int BB = permutation[B + 1];
    return lerp(v, lerp(u, grad(permutation[AA], x, y), grad(permutation[BA], x - 1, y)),
                   lerp(u, grad(permutation[AB], x, y - 1), grad(permutation[BB], x - 1, y - 1)));
}

double PerlinNoise::noise1D(double x) {
    // Add the time parameter to the x coordinate
    //x += time;

    int X = static_cast<int>(std::floor(x)) & 255;
    x -= std::floor(x);
    double u = fade(x);
    int A = permutation[X];
    int B = permutation[X + 1];
    return lerp(u, grad1D(permutation[A], x), grad1D(permutation[B], x - 1));
}
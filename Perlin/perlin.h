#ifndef H_PERLINNOISE
#define H_PERLINNOISE

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class PerlinNoise {
private:
    std::vector<int> permutation;
public:
    PerlinNoise();
    double noise(double x, double y);
private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y);
};

#endif
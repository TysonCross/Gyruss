#ifndef PERLINNOISE_LIBRARY_H
#define PERLINNOISE_LIBRARY_H


#include <vector>
#include <cmath> // M_PI is accessible
#include <numeric>
#include <random>

class PerlinNoise
{
    std::vector<int> permutationVector;

public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    double noise(double x, double y = 0.f, double z = 0.f);

private:
    double smootherStep(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y = 0.f, double z = 0.f);
};

#endif
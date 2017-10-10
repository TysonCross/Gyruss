/////////////////////////////////////////////////////////////////////
/// \brief   Perlin Noise Class
///
/// A widely used method (first proposed by Ken Perlin in 1984) to interpolate
/// between a set of random values, producing smoothly varying noise.
///
/// Based on https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
/// with code from git@github.com:sol-prog/Perlin_Noise.git
/// Which is based on Ken Perlin's original Improved Perlin Noise java code,
/// found at http://cs.nyu.edu/~perlin/noise/
/////////////////////////////////////////////////////////////////////

#ifndef PERLINNOISE_LIBRARY_H
#define PERLINNOISE_LIBRARY_H

#include <vector>
#include <cmath> // M_PI is accessible
#include <numeric>
#include <random>
#include <algorithm>

////////////////////////////////////////////////////////////
/// \brief Ken Perlin's Improved noise method
/// \see http://cs.nyu.edu/~perlin/noise/
////////////////////////////////////////////////////////////
class PerlinNoise
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor for the PerlinNoise (uses a default set of
    /// explicit reference values, from Perlin 1984.
    ////////////////////////////////////////////////////////////
    PerlinNoise();

    ////////////////////////////////////////////////////////////
    /// \brief Custom seeded constructor for the PerlinNoise (uses the default random engine
    /// to shuffle an ordered set of integers from 0-255)
    /// \param seed The seed for the random engine
    /// (if psuedo-random, then produces a repeatable sequence of values)
    ////////////////////////////////////////////////////////////
    PerlinNoise(unsigned int seed);

    ////////////////////////////////////////////////////////////
    /// \brief Chooses a point inside a unit cube,
    /// and calculating the gradients from the corner of the cube to this point.
    /// The corner values of the cube are then hashed, and used to
    /// blend the calculated gradients.
    ///
    /// \param x Input for x coordinate
    /// \param y Input for y coordinate (optional)
    /// \param z Input for z coordinate (optional)
    /// \return A float value between 0 and 1, which varyies smoothly around 0.5f
    ////////////////////////////////////////////////////////////
    double noise(double x, double y = 0.f, double z = 0.f);

private:
    ////////////////////////////////////////////////////////////
    /// \brief Smooths the input, producing an eased in and out value from 0 to 1 over time
    ///
    ///  f(t) = 6t^5 - 15t^4 + 10t^3
    ///
    /// \param t The input value (treated as time)
    /// \see https://en.wikipedia.org/wiki/Smoothstep
    ////////////////////////////////////////////////////////////
    double smootherStep(double t);

    ////////////////////////////////////////////////////////////
    /// \brief Interpolates the input, using cosine interpolation
    ///
    /// \param t How fast to interpolate between the values
    /// \param a The value to interpolate from
    /// \param b The value to interpolate to
    /// \return The interpolated value
    /// \see http://paulbourke.net/miscellaneous/interpolation/
    ////////////////////////////////////////////////////////////
    double lerp(double t, double a, double b);

    ////////////////////////////////////////////////////////////
    /// \brief Converts lower 4 bits of hash into 12 gradient directions
    ////////////////////////////////////////////////////////////
    double grad(int hash, double x, double y = 0.f, double z = 0.f);

    ////////////////////////////////////////////////////////////
    /// \brief The permutation vector, consisting of 256 unique integer values
    ////////////////////////////////////////////////////////////
    std::vector<int> permutationVector;

};

#endif
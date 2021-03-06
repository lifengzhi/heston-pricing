/*
 * Generates paths of a d-dimensional Brownian motion with unitary volatility, over [0 ; T].
*/

#include <array>
#include <vector>
#include <random>

#include "Trajectory.hpp"

template <unsigned Dimension>
class Brownian : public Trajectory<Dimension> {

public:
    // Constructor for non uniform time steps
    Brownian(std::function<double(unsigned)> const & gamma, unsigned n) : Trajectory<Dimension>(gamma, n), G(0, 1) { };

    // Returns the values of a newly generated path
    std::vector<std::array<double, Dimension>> & operator()(std::mt19937_64 & gen) {
        for (unsigned i = 1; i < this->values.size(); ++i) {
            for (unsigned k = 1; k < Dimension; ++k) {
                this->values[i][k] = this->values[i - 1][k] + std::sqrt(this->times[i] - this->times[i - 1]) * G(gen);
            }
        }
        return this->values;
    };

protected:
    std::normal_distribution<> G;
};

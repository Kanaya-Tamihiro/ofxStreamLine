#include "Option.hpp"

void Option::randomSeed() {
    seed[0] = ((double)std::rand()/RAND_MAX)*(xrange[1] - xrange[0]) + xrange[0];
    seed[1] = ((double)std::rand()/RAND_MAX)*(yrange[1] - yrange[0]) + yrange[0];
}

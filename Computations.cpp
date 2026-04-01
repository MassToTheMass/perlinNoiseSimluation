#include <vector>

namespace Calculations {

    double getDotProduct(std::vector<double> vec1, std::vector<double> vec2) {
        double dotProduct = 0.0;
        for (double i = 0; i < vec1.size(); ++i) {
            dotProduct += vec1[i] * vec2[i];
        }
        return dotProduct;

    }

    double lerp(double a, double b, double t) {
        return a + t * (b - a);
    }

    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }
}


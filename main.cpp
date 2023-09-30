/*
 * Desc:
 * Contributing team members:Marcos
 * Date:
 */
// now prototype for uniform distribution:
//std::vector<std::pair<int, double>>histGenUniDist(double mean, double stdDev, int numSamples, int numBins, double binWidth);
//hist2 = histGenUniDist(2.0, 10.0, 10000, 22, 0.1);
//std::vector<std::pair<double, int>> hist2;
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

// other files included

//function prototypes

//declare a function prototype to generate a histogram of random numbers that follow a normal distribution.
//requires the following parameters:
std::vector<std::pair<int, int>>histGenNormalDist(double mean, double stdDev, int numSamples, int numBins, double binWidth);
//returns a vector of pairs, each pair contains the center of a bin and the corresponding frequency.

int main() {
    // declare a vector of pairs to store the histogram:
    std::vector<std::pair<int, int>> hist;
    hist = histGenNormalDist(0.5, 1, 20000, 10, 1);

    //declare a vector of double int pairs to store histogram

    // Find the maximum frequency to scale the histogram
    int maxFrequency = 0;
    for (const auto& bin : hist) {
        if (bin.second > maxFrequency) {
            maxFrequency = bin.second;
        }
    }

    // Display the histogram with asterisks
    for (const auto& bin : hist) {
        std::cout << "Center: " << bin.first << " | Frequency: " << bin.second << " | ";

        // Scale the frequency to fit within a reasonable width
        int scaledFrequency = static_cast<int>(50.0 * bin.second / maxFrequency);

        // Print asterisks based on the scaled frequency
        for (int i = 0; i < scaledFrequency; ++i) {
            std::cout << "*";
        }

        std::cout << std::endl;
    }


    return 0;
}


std::vector<std::pair<int, int>>histGenNormalDist(double mean, double stdDev, int numSamples, int numBins, double binWidth)
{
    // set up the cpp environment to generate random numbers that follow a normal distribution
    // 1. declare a random number generation engine
    std::random_device rd{};
    std::mt19937 gen {rd()};
    // 2. specify the distribution using mean and standard deviation
    std::normal_distribution<> norm(mean, stdDev);
    // declare a vector of pairs to store the histogram.
    std::vector<std::pair<int, int>> hist;
    // initialize the above histogram vector using the user specified numBins and binWidth
    for (int i = 0; i < numBins; ++i)
    {
        int center = static_cast<int>(mean - (numBins / 2) * binWidth + i * binWidth);
        hist.emplace_back(center, 0);
    }
    // generate numSamples random numbers and fill the histogram vector.
    for (int i = 0; i < numSamples; ++i)
    {
        double randNum = round(norm(gen));

        auto pos = std::find_if(hist.begin(), hist.end(),
                                [randNum](const std::pair<int, int>& p){return p.first == randNum;});

        if (pos != hist.end()) {

            pos -> second++;

        }
    }
    return hist;

}

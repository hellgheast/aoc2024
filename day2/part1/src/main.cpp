#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


/**
 * @brief Parse 
 * 
 * @param line raw line to parse
 * @return int -1 in case of error, 0 if the line is not safe, 1 if the line is safe
 */
int parseLineReports(std::string line) {

    std::stringstream ss{line};
    std::string value;
    std::vector<int> reportNumber{};
    
    // Using : https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings
    // Parse the space separated string to get all the numbers
    while(std::getline(ss,value,' ')) {
        reportNumber.push_back(std::stoi(value));
    }

    std::cout << "Number of element in the line " << reportNumber.size() << "\n";

    // If we get less than two elements
    if (reportNumber.size() < 2 ) {
        std::cerr << "Array too small to parse.. BREAK \n";
        return -1;
    }

    // Check if line is safe
    bool increasingSerie = false;
    int absDiff = 0;

    for (size_t i = 0; i < reportNumber.size() - 1; i++) {
        // To check:
        // TODO part 2: put the valid condition inside a function
        // TODO part 2: Strategy : remove the first element when you have an invalid serie and rewind the complete serie
        if(i == 0) {

            absDiff = std::abs(reportNumber[0] - reportNumber[1]);
            if(absDiff < 1 || absDiff > 3) {
                std::cout << "Line not safe \n";
                return 0;
            }
            // Increasing or decreasing serie
            if (reportNumber[0] < reportNumber[1] ) {
                increasingSerie = true;
            }
        } else {

            // Absolute difference : between 1 and 3, more or less is invalid
            absDiff = std::abs(reportNumber[i] - reportNumber[i+1]);
            if(absDiff < 1 || absDiff > 3) {
                std::cout << "Line not safe \n";
                return 0;
            }
            // Serie is increasing but decrease at a point increasing or decreasing
            if(increasingSerie == true && reportNumber[i] > reportNumber[i+1]) {
                return 0;
            }
            if(increasingSerie == false && reportNumber[i] < reportNumber[i+1]) {
                return 0;
            }
        }
    }
    // If we passed all the analysis we return 1
    std::cout << line << "is safe !\n";
    return 1;

}

int computeSimiliarity(int value, std::vector<int> &vecref) {
    
    int count = std::count(vecref.begin(),vecref.end(),value);
    const int similarity = count*value;
    return similarity;
}


int main()
{
    std::cout << "Hello again Ismail\n";

    std::ifstream inf{"../input/input"};

    if (!inf.is_open()) {
        std::cerr << "Unable to open AOC input\n";
        return -1;
    }
    
    // We read the file and 
    std::string line {};
    int totalSafeReports = 0;
    int result = 0;
    while (std::getline(inf,line)) {
        std::cout << "Line is " << line << "\n";
        result = parseLineReports(line);
        if(result < 0 ) {
            std::cerr << "Error during parsing abort\n";
            inf.close();
            return -1;
        }
        totalSafeReports += result;
    }
    inf.close();

    std::cout << "total safe report is " << totalSafeReports << "\n";

    return 0;
}


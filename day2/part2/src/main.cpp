#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


bool safeNumbers(int a,int b) {

    int absDiff = std::abs(a - b);
    // Absolute difference : between 1 and 3, more or less is invalid
    if(absDiff < 1 || absDiff > 3) {
        return false;
    }
    return true;
}


bool lineIsSafe(bool increasingSerie,size_t index,const std::vector<int>& reportNumber) {

    if(index > (reportNumber.size() - 1)) {
        std::cerr << "Invalid index access !";
        return false;
    }

    if(!safeNumbers(reportNumber[index],reportNumber[index+1])) {
        return false;
    }
    // Serie is increasing but decrease at a point increasing or decreasing
    if(increasingSerie == true && reportNumber[index] > reportNumber[index+1]) {
        return false;
    }

    if(increasingSerie == false && reportNumber[index] < reportNumber[index+1]) {
        return false;
    }
    return true;
}

bool checkReportSafe(size_t& invalidIndex,const std::vector<int>& reportNumber) {
    bool isSafe = false;
    bool increasingSerie = false;

    for (size_t i = 0; i < reportNumber.size() - 1; i++) {
    // To check:
    // TODO part 2: put the valid condition inside a function
    // TODO part 2: Strategy : remove the first element when you have an invalid serie and rewind the complete serie
    if(i == 0) {
        
        // Increasing or decreasing serie
        if (reportNumber[0] < reportNumber[1] ) {
            increasingSerie = true;
        }

        if(!safeNumbers(reportNumber[0],reportNumber[1])) {
            invalidIndex = i;
            std::cout << "Line not safe \n";
            return false;
        }

    } else {

        if(!lineIsSafe(increasingSerie,i,reportNumber)) {
            std::cout << "Line not safe \n";
            invalidIndex = i;
            return false;
        }
    }
    }
    // If we passed all the analysis we return 1
    std::cout << "Line is safe !\n";
    return true;
}

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
    bool result = false;
    size_t invalidIndex = 0;

    result = checkReportSafe(invalidIndex,reportNumber);
    if(result) {
        return 1;
    }

    // If the initial report is not safe, we remove one number and see if it works
    for (size_t numberTrials = 0; numberTrials < reportNumber.size() - 1 ; numberTrials++) {
        std::vector<int> workingNumber(reportNumber);
        workingNumber.erase(workingNumber.begin()+numberTrials);
        
        // create working copy
        result = checkReportSafe(invalidIndex,workingNumber);
        // if any invalid number,
        if(result) {
            return 1;
        }
    }
    
    // If all trials failed,
    return 0;


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


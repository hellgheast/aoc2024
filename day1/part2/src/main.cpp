#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>


int computeDistance(int a, int b) {
    int difference = a-b;
    return abs(difference);
}

int computeSimiliarity(int value, std::vector<int> &vecref) {
    
    int count = std::count(vecref.begin(),vecref.end(),value);
    const int similarity = count*value;
    return similarity;
}

int main()
{
    std::cout << "Hello again Ismail for part 2 of day 1\n";

    std::ifstream inf{"../input/input"};

    if (!inf.is_open()) {
        std::cerr << "Unable to open AOC input\n";
        return -1;
    }
    
    //std::string_view strv = std::string_view(line);
    //strv.substr(strv.find(" "));
    // We read the file and 
    std::string line {};
    int a,b;
    std::vector<int> leftList{};
    std::vector<int> rightList{};
    while (std::getline(inf,line)) {
        std::cout << "Line is " << line << "\n";
        a = std::stoi(line.substr(0,line.find(" ")));
        b = std::stoi(line.substr(line.find(" ")));
        // std::cout << "A is " << a << " and B is " << b << "\n";
        leftList.push_back(a);
        rightList.push_back(b);
    }
    inf.close();
    // We sort them, for quick search reason
    std::sort(leftList.begin(),leftList.end());
    std::sort(rightList.begin(),rightList.end());
    std::cout << "leftList of size: " << leftList.size() << " and rightList of size: " << rightList.size() << "\n"; 

    int totalSimilarity = 0;
    for(size_t i = 0; i< leftList.size(); i++) {
        totalSimilarity += computeSimiliarity(leftList.at(i),rightList);
    }

    std::cout << "total similarity is " << totalSimilarity << "\n";

    return 0;
}


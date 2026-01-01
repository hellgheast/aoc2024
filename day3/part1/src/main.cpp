#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <format>

bool safeNumbers(int a,int b) {

    int absDiff = std::abs(a - b);
    // Absolute difference : between 1 and 3, more or less is invalid
    if(absDiff < 1 || absDiff > 3) {
        return false;
    }
    return true;
}

template <typename T>
void printVector(const std::vector<T>& vec)
{
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i + 1 < vec.size())
            std::cout << ", ";
    }
    std::cout << "]\n";
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
    for (size_t numberTrials = 0; numberTrials < reportNumber.size() ; numberTrials++) {
        std::vector<int> workingNumber(reportNumber);
        workingNumber.erase(workingNumber.begin()+static_cast<std::ptrdiff_t>(numberTrials));
        
        // create working copy
        result = checkReportSafe(invalidIndex,workingNumber);
        // if any invalid number,
        if(result) {
            std::cout << "Line ";
            printVector(workingNumber);
            std::cout << " is safe";
            return 1;
        }
    }
    
    // If all trials failed,
    return 0;


}

int computeSimiliarity(int value, std::vector<int> &vecref) {
    
    std::vector<int>::difference_type countDiff = (int)std::count(vecref.begin(),vecref.end(),(long int)value);
    // convert to actual number, we could check the overflow
    int count = static_cast<int>(countDiff);
    const int similarity = count*value;
    return similarity;
}

std::string peek_n(std::istream& in, std::size_t n) {
    std::streampos pos = in.tellg();
    std::string buf;
    std::streamsize actualSize = (std::streamsize)n;
    buf.resize(n);

    in.read(&buf[0], actualSize);
    std::streamsize actually_read = in.gcount();

    in.clear();      // clear flags in case of EOF
    in.seekg(pos);   // restore position

    buf.resize((size_t)actually_read);
    return buf;
}


int peekFindChar(std::istream& in, char charToFind) {
    
    std::string peekStr{peek_n(in,64)};
    size_t found = peekStr.find_first_of(charToFind,0);
    if (found != std::string::npos) {
        return (int)found;
    }

#if 0
    for (size_t idx = 0; peekStr.size();idx++) {
        if(peekStr[idx] == charToFind) {
            return (int) idx;
        }
    }
#endif
    return -1;
}



int64_t parseMulOperation(std::string mulOp) {
    int64_t x=0,y=0,res=0;
    if(mulOp.starts_with("ul(")) {

        size_t openIdx = mulOp.find_first_of('(',0);
        size_t commaIdx = mulOp.find_first_of(',',0);
        size_t closeIdx = mulOp.find_first_of(')',0);
        std::string xString = mulOp.substr(openIdx + 1,commaIdx - openIdx - 1);
        std::string yString = mulOp.substr(commaIdx + 1,closeIdx - commaIdx - 1);
        std::cout << "XSTR " << xString  << " YSTR " << yString << " MULOP " << mulOp << std::endl;
        try {
            x = std::stol(xString,nullptr);
            y = std::stol(yString,nullptr);
            res = x * y;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception happened" << e.what() << '\n';
            return -1;
        }
        
        std::cout << std::format("x: {:d} y: {:d} res: {:d}",x,y,res) << std::endl;
        return res;
    }
    
    // If it failed we return -1
    return -1;
}

int64_t parseValidOperation(char toParse,std::ifstream& inf) {
    (void) inf;
    std::cout << "\'" << toParse << "\'," << std::format("{:#x}",(int)toParse) << std::endl;
    std::string peekStr{};
    std::string expectedMulOp{};
    
    switch (toParse)
    {
        case 'm':
            /* code */
            peekStr = peek_n(inf,4); // Expected str : ul(first digit
            std::cout << "Peeked str " << peekStr << std::endl;
            // If we find the beginning of the good pattern, we proceed to find also the number and we compute
            if (peekStr[0] == 'u' && peekStr[1] == 'l' && peekStr[2] == '(') {
                if (std::isdigit(peekStr[3])) {
                    std::cout << "found digit " << peekStr[3] << std::endl;
                    // Look for closing parenthese and process (only (x,y) without space is valid) 
                    int commaIdx = peekFindChar(inf,',');
                    int closeParenIdx = peekFindChar(inf,')');
                    if (closeParenIdx > commaIdx && commaIdx > 0 && closeParenIdx > 0) {
                        closeParenIdx += 1; // The + 1 is to also get the closing parenthese
                        peekStr = peek_n(inf,(size_t)closeParenIdx); 
                        // We now have a buffer with ul(something,something)
                        std::cout << "Peeked pot operation " << peekStr << std::endl;
                        int64_t result = parseMulOperation(peekStr);
                        return result;
                    }
                } 
            } 
            // ONce succesfully parsed we advance the if stream to avoid to parse it again
            break;

        default:
            break;
    }

    return 1;
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
    int64_t totalMulOperations = 0;
    int64_t result = 0;
    char c;
    while (inf >> std::noskipws >> c) {
        result = parseValidOperation(c,inf);
        if(result < 0 ) {
            std::cerr << "Error during parsing abort\n";
            inf.close();
            return -1;
        }
        totalMulOperations += result;
    }
    inf.close();

    std::cout << "total safe multipliy operation is " << totalMulOperations << "\n";

    return 0;
}


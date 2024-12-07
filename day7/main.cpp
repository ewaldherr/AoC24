#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

void readGridToVector(const std::string& filename, std::vector<std::vector<int64_t>>& grid) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Trim leading/trailing spaces
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        if (line.empty()) continue; // Skip empty lines

        // Find the colon
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) {
            std::cerr << "Warning: Line missing colon, skipping: " << line << std::endl;
            continue;
        }

        // Extract the first integer (before the colon)
        std::string firstPart = line.substr(0, colonPos);
        int64_t firstNumber = std::stoll(firstPart);

        // Extract the part after the colon
        std::string numbersPart = line.substr(colonPos + 1);

        // Parse the integers after the colon
        std::istringstream numbersStream(numbersPart);
        std::vector<int64_t> row;
        row.push_back(firstNumber); // Add the first number to the row
        int64_t num;
        while (numbersStream >> num) {
            row.push_back(num);
        }

        // Add the row to the grid
        grid.push_back(row);
    }

    file.close();
}

int64_t concat(int64_t a, int64_t b) 
{ 
    std::string s1 = std::to_string(a); 
    std::string s2 = std::to_string(b); 
    std::string s = s1 + s2; 
    int64_t c = std::stoll(s); 
    return c; 
} 

bool DFS(std::vector<int64_t>& vec, int64_t goal, int64_t currentVal, int pos){
    if(pos == vec.size()){
        if(goal == currentVal){
            return true;
        }
        return false;
    } else{
        
        return (DFS(vec, goal, currentVal + vec[pos], pos + 1) || DFS(vec, goal, currentVal * vec[pos], pos + 1)
        || DFS(vec, goal, concat(currentVal,vec[pos]), pos + 1));
    }
}

int64_t getSum(std::vector<std::vector<int64_t>>& grid){
    int64_t sum = 0;
    for(auto vec: grid){
        if(DFS(vec, vec[0], vec[1], 2)){
            sum += vec[0];
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<int64_t>> grid;
    readGridToVector(argv[1], grid);
    std::cout << "The result is " << getSum(grid) << std::endl;
}
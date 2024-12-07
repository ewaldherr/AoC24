#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

void readGridToVector(const std::string& filename, std::vector<std::vector<int>>& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream iss(line);
        std::vector<int> row;
        for (int c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    file.close();
}

bool DFS(std::vector<int>& vec, int goal, int currentVal, int pos){
    if(pos == vec.size()){
        if(goal == currentVal){
            return true;
        }
        return false;
    } else{
        return (DFS(vec, goal, currentVal + vec[pos], pos + 1) || DFS(vec, goal, currentVal * vec[pos], pos + 1));
    }
}

int getSum(std::vector<std::vector<int>>& grid){
    int sum = 0;
    for(auto vec: grid){
        if(DFS(vec, vec[0], vec[1], 2)){
            sum += vec[0];
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<int>> grid;
    readGridToVector(argv[1], grid);
    std::cout << "The result is " << getSum(grid) << std::endl;
}
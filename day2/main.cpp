#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void readGridToVector(const std::string& filename, std::vector<std::vector<int>>& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        grid.push_back(row);
    }

    file.close();
}

int checkDecreasingLine(std::vector<int>& vec, int errors){
    for(int i = 0; i + 1 < vec.size(); ++i){
        int diff = vec[i] - vec[i+1];
        if(diff > 3 || diff < 1){
            errors++;
            if(errors > 1){
                return 0;
            } else{
                std::vector<int> copy = vec;
                copy.erase(copy.begin()+i);
                vec.erase(vec.begin()+i+1);
                int cascade = checkDecreasingLine(vec,1) + checkDecreasingLine(copy,1);
                if(cascade > 0){
                    return 1;
                } else{
                    return 0;
                }
            }
        }
    }
    return 1;
}

int checkIncreasingLine(std::vector<int>& vec, int errors){
    for(int i = 0; i + 1 < vec.size(); ++i){
        int diff = vec[i+1] - vec[i];
        if(diff > 3 || diff < 1){
            errors++;
            if(errors > 1){
                return 0;
            } else{
                std::vector<int> copy = vec;
                copy.erase(copy.begin()+i);
                vec.erase(vec.begin()+i+1);
                int cascade = checkIncreasingLine(vec,1) + checkIncreasingLine(copy,1);
                if(cascade > 0){
                    return 1;
                } else{
                    return 0;
                }
            }
        }
    }
    return 1;
}

int GetValidLines(std::vector<std::vector<int>>& grid){
    int sum = 0;
    for(auto vec: grid){
        std::vector<int> copy = vec;
        sum += checkIncreasingLine(vec, 0);
        sum += checkDecreasingLine(copy, 0);
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<int>> grid;
    readGridToVector(argv[1], grid);
    std::cout << "The result is " << GetValidLines(grid) << std::endl;
}
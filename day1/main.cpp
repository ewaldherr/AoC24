#include <algorithm>
#include <functional>
#include <iostream>
#include <string_view>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

void readFileToVectors(const std::string& filename, std::vector<std::string>& left, std::vector<std::string>& right) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string leftEntry, rightEntry;
        if (iss >> leftEntry >> rightEntry) {
            left.push_back(leftEntry);
            right.push_back(rightEntry);
        } else {
            std::cerr << "Malformed line: " << line << std::endl;
        }
    }

    file.close();
}

int getDiff(std::vector<std::string>& left, std::vector<std::string>& right){
    int sum = 0;
    std::make_heap(left.begin(), left.end());
    std::make_heap(right.begin(), right.end());

    for(int i = 0; i < left.size(); ++i){
        sum += std::abs(std::pop_heap(left.begin(), left.end()) - std::pop_heap(right.begin(), right.end()));
    }

    return sum;
}

int main(int argc, char** argv){
    std::vector<int> left;
    std::vector<int> right;
    readFileToVectors(argc[1], left, right);
    std::cout << "The result is" << getDiff(left, right) << std::endl;
}
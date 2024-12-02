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

void readFileToVectors(const std::string& filename, std::vector<int>& left, std::vector<int>& right) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int leftEntry, rightEntry;
        if (iss >> leftEntry >> rightEntry) {
            left.push_back(leftEntry);
            right.push_back(rightEntry);
        } else {
            std::cerr << "Malformed line: " << line << std::endl;
        }
    }

    file.close();
}

int getDiff(std::vector<int>& left, std::vector<int>& right){
    int sum = 0;
    std::make_heap(left.begin(), left.end());
    std::make_heap(right.begin(), right.end());

    int size = left.size();
    for(int i = 0; i < size; ++i){
        std::pop_heap(left.begin(), left.end());
        std::pop_heap(right.begin(), right.end());
        sum += std::abs(left.back() - right.back() );
        left.pop_back();
        right.pop_back();
    }

    return sum;
}

int getSim(int n, std::vector<int>& right){
    int sim = 0;
    for(int i = 0; i < right.size(); ++i){
        if(right[i] == n){
            sim++;
        }
    }
    return n * sim;
}

int getSimilarityScore(std::vector<int>& left, std::vector<int>& right){
    int sum = 0;
    for(int i = 0; i < left.size(); ++i){
        sum += getSim(left[i],right);
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<int> left;
    std::vector<int> right;
    readFileToVectors(argv[1], left, right);
    std::cout << "The result is " << getSimilarityScore(left, right) << std::endl;
}
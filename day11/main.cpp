#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void readGridToVector(const std::string& filename, std::vector<int64_t>& vec) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int64_t value;
        while (iss >> value) {
            vec.push_back(value);
        }
    }

    file.close();
}

void printVec(std::vector<int64_t>& vec){
    for(int64_t entry: vec){
        std::cout << entry << " ";
    }
    std::cout << std::endl;
}

void performBlink(std::vector<int64_t>& vec){
    for(int i = 0; i < vec.size(); ++i){
        int64_t entry = vec[i];
        if(entry == 0){
            vec[i] = 1;
        } else{
            std::string s = std::to_string(entry);
            if(s.length()%2 == 0){
                std::string firstHalf = s.substr(0, s.length()/2);
                std::string secondHalf = s.substr(s.length()/2);
                vec[i] = std::stoll(firstHalf);
                auto iter = vec.begin();
                iter += i + 1;
                vec.insert(iter, std::stoll(secondHalf));
                i++;
            } else{
                vec[i] *= 2024;
            }
        }
    }
}

int64_t rec(int value, int blinks){
    if()
}

void performBlinks(std::vector<int64_t>& vec, int blinks){
    for(int i = 0; i < blinks; ++i){
        performBlink(vec);
        std::cout << i+1 << " " << vec.size()<<std::endl;
    }
}

int main(int argc, char** argv){
    std::vector<int64_t> vec;
    readGridToVector(argv[1], vec);
    printVec(vec);
    std::vector<int64_t> test;
    test.push_back(0);
    performBlinks(test, 75);
    std::cout << "The result is " << vec.size() << std::endl;
}
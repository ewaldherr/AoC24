#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

void readSections(std::string filename, std::vector<std::vector<int>>& gridSection, std::multimap<int,int>& multimapSection){
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    std::string line;
    bool isSecondSection = false;

    // Process input line by line
    while (std::getline(file, line)) {
        // Trim leading/trailing spaces
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        // Skip empty lines
        if (line.empty()) {
            isSecondSection = true;
            continue;
        }

        if (!isSecondSection) {
            // First section: Parse "key|value"
            std::replace(line.begin(), line.end(), '|', ' '); // Replace '|' with space
            std::istringstream lineStream(line);
            int key, value;
            lineStream >> value >> key;
            multimapSection.insert({key, value});
        } else {
            // Second section: Parse comma-separated integers
            std::replace(line.begin(), line.end(), ',', ' '); // Replace ',' with space
            std::istringstream lineStream(line);
            std::vector<int> row;
            int num;
            while (lineStream >> num) {
                row.push_back(num);
            }
            gridSection.push_back(row);
        }
    }

    file.close();
}

int checkLine(std::vector<int>& vec, std::multimap<int,int>& rules){
    for(int i = 0; i < vec.size(); ++i){
        for(int j = i + 1; j < vec.size(); j++){
            auto range = rules.equal_range(vec[i]);
            auto start = range.first;
            auto end = range.second;
            for(start;start!=end;++start){
                auto [k,v] = *start;
                if(v == vec[j]){
                    return 0;
                }
            }
        }
    }
    return vec[vec.size()/2];
}

int correctLine(std::vector<int>& vec, std::multimap<int,int>& rules){
    for(int i = 0; i < vec.size(); ++i){
        for(int j = i + 1; j < vec.size(); j++){
            auto range = rules.equal_range(vec[i]);
            auto start = range.first;
            auto end = range.second;
            for(start;start!=end;++start){
                auto [k,v] = *start;
                if(v == vec[j]){
                    std::swap(vec[i],vec[j]);
                }
            }
        }
    }
    return vec[vec.size()/2];
}

int correctLines(std::multimap<int,int>& rules, std::vector<std::vector<int>>& incorrectLines){
    int sum = 0;
    for(auto vec: incorrectLines){
        sum += correctLine(vec, rules);
    }
    return sum;
}

int checkGrid(std::vector<std::vector<int>>& grid, std::multimap<int,int>& rules, std::vector<std::vector<int>>& incorrectLines){
    int sum = 0;
    for(auto vec: grid){
        int current = checkLine(vec, rules);
        if(current == 0){
            incorrectLines.push_back(vec);
        }
        sum += current;
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> incorrectLines;
    std::multimap<int,int> rules;
    readSections(argv[1], grid, rules);
    std::cout << "The result for part 1 is " << checkGrid(grid, rules, incorrectLines) << std::endl;
    std::cout << "The result for part 1 is " << correctLines(rules, incorrectLines) << std::endl;
}
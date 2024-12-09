#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void readGridToVector(const std::string& filename,std::vector<int>& vec) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Read the entire line
    file.close();

    // Process each character in the line
    for (char ch : line) {
        if (std::isdigit(ch)) { // Check if the character is a digit
            digits.push_back(ch - '0'); // Convert the character to an integer and store it
        } else {
            std::cerr << "Warning: Non-digit character encountered and ignored: " << ch << std::endl;
        }
    }
}

void moveEntries(std::vector<int>& vec){
    auto left = vec.begin();
    auto right = vec.end();
    right --;
    while(left!=right){
        while(*left != -1){
            left ++;
        }
        while(*left == -1){
            if(*right == -1){
                right--;
                vec.pop_back();
            } else{
                *left = *right;
                left++;
                if(left == right){
                    vec.pop_back();
                    return;
                }
                right--;
                vec.pop_back();
            }
        }
    }
}

void parseVec(std::vector<int>& vec){
    std::vector<int> parsed;
    for(int i = 0; i < vec.size(); ++i){
        if(i%2 == 0){
            for(int j = 0; j < vec[i]; ++j){
                parsed.push_back(i/2);
            }
        } else {
            for(int j = 0; j < vec[i]; ++j){
                parsed.push_back(-1);
            }
        }
    }
    vec = parsed;
}

int getChecksum(std::vector<int>& vec){
    int sum = 0;
    for(int i = 0;i < vec.size();++i){
        sum += i * vec[i];
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<int> vec;
    readGridToVector(argv[1], vec);
    std::cout << "The result is " << getChecksum(vec) << std::endl;
}
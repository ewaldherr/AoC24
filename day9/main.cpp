#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void readGridToVector(const std::string& filename,std::vector<int>& vec) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    std::string line;
    std::getline(file, line); // Read the entire line
    file.close();

    // Process each character in the line
    for (char ch : line) {
        if (std::isdigit(ch)) { // Check if the character is a digit
            vec.push_back(ch - '0'); // Convert the character to an integer and store it
        } else {
            std::cerr << "Warning: Non-digit character encountered and ignored: " << ch << std::endl;
        }
    }
}

void printVec(std::vector<int>& vec){
    for(int entry: vec){
        std::cout << entry << " ";
    }
    std::cout << std::endl;
}

void moveFiles(std::vector<int>& vec){
    auto right = vec.end();
    right --;
    int current = *right;
    while(current>0){
        while(*right != current){
            right --;
        }
        std::cout << current << std::endl;

        int fileSize = 0;
        while(*right == current){
            fileSize ++;
            right --;
        }
        auto left = vec.begin();
        while(*left!= current){
            bool ret = false;
            while(*left != -1){
                left ++;
                if(*left == current){
                    ret = true;
                }
            }
            if(left == right || ret){
                break;
            }
            int spaceSize = 0;
            while(*left == -1){
                spaceSize++;
                left++;
            }
            if(spaceSize>=fileSize){
                left--;
                right++;
                while(*left == -1){
                    left--;
                }
                left++;
                while(*right == current){
                    *left = current;
                    *right = -1;
                    left++;
                    right++; 
                }
                right--;
                break;
            }
        }
        current--;
    }
}

void moveEntries(std::vector<int>& vec){
    auto left = vec.begin();
    auto right = vec.end();
    right --;
    while(left!=right){
        while(*left != -1){
            left ++;
            if(left == right){
                return;
            }
        }
        while(*left == -1){
            if(*right == -1){
                right--;
                if(left == right){
                    vec.pop_back();
                    return;
                }
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

int64_t getChecksum(std::vector<int>& vec){
    int64_t sum = 0;
    for(int i = 0;i < vec.size();++i){
        if(vec[i]== -1){
            continue;
        } else{
            sum += i * vec[i];
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<int> vec;
    readGridToVector(argv[1], vec);
    parseVec(vec);
    std::cout << "Parsed vec" << std::endl;
    moveFiles(vec);
    printVec(vec);
    std::cout << "Moved entries" << std::endl;
    std::cout << "The result is " << getChecksum(vec) << std::endl;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void readGridToVector(const std::string& filename, std::vector<std::vector<char>>& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<char> row;
        char value;
        while (iss >> value) {
            row.push_back(value);
        }
        grid.push_back(row);
    }

    file.close();
}

bool isDigit(char c){
    int i = c - '0';
    return (i > -1 && i < 10);
}

int multiply(int a1, int a2, int a3, int b1, int b2, int b3){
    return a1*100*b1*100+a1*100*b2*10+a1*100*b3+a2*10*b1*100+a2*10*b2*10+a2*10*b3+a3*b1*100+a3*b2*10+a3*b3;
}

int checkPosition(std::vector<char> & vec, int pos){
    if(vec[pos] == 'u' && vec[pos+1] == 'l' && vec[pos+2] == '('){
        int a1, a2, a3, b1, b2, b3;
        if(!isDigit(vec[pos+3])){
            return 0;
        } else {
            a1 = vec[pos+3] - '0';
        }
        if(!isDigit(vec[pos+4])){
            if(vec[pos+4] != ','){
                return 0;
            }
            //first number is 1 digit long
            if(!isDigit(vec[pos+5])){
            return 0;
            } else {
                b1 = vec[pos+5] - '0';;
            }
            if(!isDigit(vec[pos+6])){
                if(vec[pos+6] != ')'){
                    return 0;
                }
                //second number is 1 digit long 
                return multiply(0,0,a1,0,0,b1);
            } else{
                a2 = vec[pos+6] - '0';;
            }
            if(!isDigit(vec[pos+7])){
                if(vec[pos+7] != ')'){
                    return 0;
                }
                //second number is 2 digits long
                return multiply(0,0,a1,0,b1,b2);
            } else{
                b3 = std::atoi(vec[pos+7]);
            } 
            if(vec[pos+8]!= ')'){
                return 0;
            }
            return multiply(0,0,a1,b1,b2,b3);
        } else{
            a2 = vec[pos+4] - '0';
        }
        if(!isDigit(vec[pos+5])){
            if(vec[pos+5] != ','){
                return 0;
            }
            //first number is 2 digits long
            if(!isDigit(vec[pos+6])){
            return 0;
            } else {
                b1 = vec[pos+6] - '0';
            }
            if(!isDigit(vec[pos+7])){
                if(vec[pos+7] != ')'){
                    return 0;
                }
                //second number is 1 digit long 
                return multiply(0,a1,a2,0,0,b1);
            } else{
                a2 = vec[pos+7] - '0';
            }
            if(!isDigit(vec[pos+8])){
                if(vec[pos+8] != ')'){
                    return 0;
                }
                //second number is 2 digits long
                return multiply(0,a1,a2,0,b1,b2);
            } else{
                b3 = vec[pos+8] - '0';
            } 
            if(vec[pos+9]!= ')'){
                return 0;
            }
            return multiply(0,a1,a2,b1,b2,b3);
        } else{
            a3 = vec[pos+5] - '0';
        }
        if(vec[pos+6]!= ','){
            return 0;
        } 
        //first number is 3 digits long
        if(!isDigit(vec[pos+7])){
            return 0;
        } else {
            b1 = vec[pos+7] - '0';
        }
        if(!isDigit(vec[pos+4])){
            if(vec[pos+4] != ')'){
                return 0;
            }
            //second number is 1 digit long 
            return multiply(a1,a2,a3,0,0,b1);
        } else{
            b2 = vec[pos+8] - '0';
        }
        if(!isDigit(vec[pos+5])){
            if(vec[pos+5] != ')'){
                return 0;
            }
            //second number is 2 digits long
            return multiply(a1,a2,a3,0,b1,b2);
        } else{
            b3 = vec[pos+9] - '0';
        } 
        if(vec[pos+10]!= ')'){
            return 0;
        }
        return multiply(a1,a2,a3,b1,b2,b3);  
    }
    return 0;
}

int calcLine(std::vector<char> & vec){
    int sum = 0;
    for(i = 0; i < vec.size();++i){
        if(vec[i] == 'm'){
            sum += checkPosition(vec, i + 1);
        }
    }
}

int main(int argc, char** argv){
    std::vector<std::vector<char>> grid;
    readGridToVector(argv[1], grid);
    int sum = 0;
    for(auto vec: grid){
        sum += calcLine(vec);
    }
    std::cout << "The result is " << sum << std::endl;
}
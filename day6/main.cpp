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
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    file.close();
}

std::pair<int,int> getStartingPos(std::vector<std::vector<char>>& grid){
    for(int i = 0; i< grid.size();++i){
        for(int j = 0; j < grid[0].size();++j){
            if(grid[i][j] == '^'){
                grid[i][j] = 'X';
                return std::make_pair(i,j);
            }
        }
    }
}

void checkPath(std::vector<std::vector<char>>& grid){
    int posI, posJ;
    std::pair<int,int> startPos = getStartingPos(grid);
    posI = startPos.first;
    posJ = startPos.second;
    bool inBounds = true;

    while(inBounds){
        if(inBounds){
            while(grid[posI - 1][posJ] != '#'){
                grid[posI][posJ] = 'X';
                posI--;
                if(posI == 0){
                    inBounds = false;
                    break;
                }
            }
            grid[posI][posJ] = 'X';
        }
        if(inBounds){
            while(grid[posI][posJ + 1] != '#'){
                grid[posI][posJ] = 'X';
                posJ++;
                if(posJ == grid[0].size() - 1){
                    inBounds = false;
                    break;
                }
            }
            grid[posI][posJ] = 'X';
        }
        if(inBounds){
            while(grid[posI + 1][posJ] != '#'){
                grid[posI][posJ] = 'X';
                posI++;
                if(posI == grid.size()-1){
                    inBounds = false;
                    break;
                }
            }
            grid[posI][posJ] = 'X';
        }
        if(inBounds){
            while(grid[posI][posJ - 1] != '#'){
                grid[posI][posJ] = 'X';
                posJ--;
                if(posJ == 0){
                    inBounds = false;
                    break;
                }
            }
            grid[posI][posJ] = 'X';
        }
    }
}

int countPathSize(std::vector<std::vector<char>>& grid){
    int sum = 0;
    for(auto vec : grid){
        for(auto entry: vec){
            if(entry == 'X'){
                sum++;
            }
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<char>> grid;
    readGridToVector(argv[1], grid);
    checkPath(grid);
    std::cout << "The result is " << countPathSize(grid) << std::endl;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>

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

void printGrid(std::vector<std::vector<char>>& grid){
    for(auto vec : grid){
        for(auto entry: vec){
            std::cout << entry;
        }
        std::cout << std::endl;
    }
}

int checkClockwise(std::vector<std::vector<char>>& grid, int i, int j){
    int currentJ = j + 1;
    int currentI = i + 1;
    int sum = 0;
    for(currentJ;currentJ < grid[0].size();++currentJ){
        if(grid[i][currentJ]=='+'){
            for(currentI;currentI < grid.size();++currentI){
                if(grid[currentI][currentJ]=='+' && (grid[currentI][j] == 'X' || grid[currentI][j] == '+')){
                    sum++;
                } else if(grid[currentI][currentJ]=='#'){
                    break;
                }
            }
        } else if(grid[i][currentJ]=='#'){
            break;
        }
    }
    return sum;
}

int checkCounterClockwise(std::vector<std::vector<char>>& grid, int i, int j){
    int currentJ = j + 1;
    int currentI = i + 1;
    int sum = 0;
    for(currentI;currentI < grid[0].size();++currentI){
        if(grid[currentI][j]=='+'){
            for(currentJ;currentJ < grid.size();++currentJ){
                if(grid[currentI][currentJ]=='+' && (grid[i][currentJ] == 'X' || grid[i][currentJ] == '+')){
                    sum++;
                } else if(grid[currentI][currentJ]=='#'){
                    break;
                }
            }
        } else if(grid[currentI][j]=='#'){
            break;
        }
    }
    return sum;
}

int checkOpposite(std::vector<std::vector<char>>& grid, int i, int j){
    int currentJ = j + 1;
    int currentI = i + 1;
    int sum = 0;
    for(currentJ;currentJ < grid[0].size();++currentJ){
        if(grid[i][currentJ]=='+'){
            for(currentI;currentI < grid.size();++currentI){
                if(grid[currentI][j]=='+' && (grid[currentI][currentJ] == 'X' || grid[currentI][currentJ] == '+')){
                    sum++;
                } else if(grid[currentI][j]=='#'){
                    break;
                }
            }
        } else if(grid[i][currentJ]=='#'){
            break;
        }
    }
    return sum;
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

int checkPath(std::vector<std::vector<char>>& grid){
    int posI, posJ;
    std::pair<int,int> startPos = getStartingPos(grid);
    posI = startPos.first;
    posJ = startPos.second;
    bool inBounds = true;

    auto start_time = std::chrono::steady_clock::now();
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    start_time = std::chrono::steady_clock::now();
    while(inBounds && duration < 1000){
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
        end_time = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }
    if(duration < 1000){
        return 0;
    } else{
        return 1;
    }
}

int findLoops(std::vector<std::vector<char>>& grid){
    std::vector<std::vector<char>> initialGrid = grid;
    int sum = 0;
    for(int i = 0; i< grid.size();++i){
        for(int j = 0; j < grid[0].size();++j){
            if(grid[i][j]== '.'){
                grid[i][j]= '#';
                sum += checkPath(grid);
                grid = initialGrid;
                std::cout << sum << std::endl;
            }
        }
    }
    return sum;
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
    std::cout << "The result is " << findLoops(grid) << std::endl;
}
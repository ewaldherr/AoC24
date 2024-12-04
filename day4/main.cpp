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

int checkPosition(std::vector<std::vector<char>>& grid, int i, int j, int i_incr, int j_incr){
    if(grid[i+i_incr][j+j_incr] == 'M' && grid[i+2*i_incr][j+2*j_incr] == 'A' && grid[i+3*i_incr][j+3*j_incr] == 'S'){
        return 1;
    }
    return 0;
}

int checkGrid(std::vector<std::vector<char>>& grid){
    int sum = 0;
    for(int i=0; i < grid.size();++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j] == 'X'){
                if(grid.size() > i + 3 && grid[0].size() > j + 3){
                    sum += checkPosition(grid, i, j, 1, 1);
                }
                if(grid[0].size() > j + 3){
                    sum += checkPosition(grid, i, j, 0, 1);
                }
                if(grid.size() > i + 3){
                    sum += checkPosition(grid, i, j, 1, 0);
                }
                if(-1 < i - 3 && -1 < j + 3){
                    sum += checkPosition(grid, i, j, -1, -1);
                }
                if(-1 < i - 3){
                    sum += checkPosition(grid, i, j, -1, 0);
                }
                if(-1 < j + 3){
                    sum += checkPosition(grid, i, j, 0, -1);
                }
                if(grid.size() > i + 3 && -1 < j - 3){
                    sum += checkPosition(grid, i, j, 1, -1);
                }
                if(grid[0].size() > j + 3 && -1 < i - 3){
                    sum += checkPosition(grid, i, j, -1, 1);
                }
            }
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<char>> grid;
    readGridToVector(argv[1], grid);
    std::cout << "The result is " << checkGrid(grid) << std::endl;
}
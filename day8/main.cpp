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

void printGrid(std::vector<std::vector<char>>& grid){
    for(auto vec : grid){
        for(auto entry: vec){
            std::cout << entry;
        }
        std::cout << std::endl;
    }
}

int countAntinodes(std::vector<std::vector<char>>& antinodes){
    int sum = 0;
    for(auto vec : antinodes){
        for(auto entry: vec){
            if(entry == '#'){
                sum++;
            }
        }
    }
    return sum;
}

void setAntinodes(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& antinodes, int i, int a){
    int initialI = i;
    int initialJ = a;
    if(a + 1 < grid[0].size()){
        a++;
    } else if(i + 1 < grid.size()){
        i++; 
        a = 0;
    } 
    for(i; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j]==grid[initialI][initialJ]){
                if(i>initialI||j>initialJ){
                    int iDiff = i - initialI;
                    int jDiff = j - initialJ;
                    if(i + iDiff < grid.size()&& j + jDiff < grid[0].size() && i + iDiff > -1 && j + jDiff > -1){
                        antinodes[i+iDiff][j+jDiff] = '#';
                    }
                    if(initialI - iDiff < grid.size()&& initialJ - jDiff < grid[0].size()&& initialI + iDiff > -1 && initialJ + jDiff > -1){
                        antinodes[initialI-iDiff][initialJ-jDiff] = '#';
                    }
                }
            }
        }
    }
}

void findAntinodes(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& antinodes){
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j]!= '.'){
                setAntinodes(grid, antinodes, i, j);
            }
        }
    }
}

int main(int argc, char** argv){
    std::vector<std::vector<char>> grid;
    readGridToVector(argv[1], grid);
    std::vector<std::vector<char>> antinodes = grid;
    findAntinodes(grid, antinodes);
    std::cout << "The result is " << countAntinodes(antinodes) << std::endl;
}
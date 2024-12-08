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

int setAntinodes(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& antinodes, int i, int a){
    int sum = 0;
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
                    bool changes = true;
                    int iters = 0;
                    while(changes){
                        changes = false;
                        if(i + iters*iDiff < grid.size()&& j + iters*jDiff < grid[0].size() && i + iters*iDiff > -1 && j + iters*jDiff > -1){
                            antinodes[i+iters*iDiff][j+iters*jDiff] = '#';
                            sum++;
                            changes = true;
                        }
                        if(initialI - iters*iDiff < grid.size()&& initialJ - iters*jDiff < grid[0].size()&& initialI + iters*iDiff > -1 && initialJ + iters*jDiff > -1){
                            antinodes[initialI-iters*iDiff][initialJ-iters*jDiff] = '#';
                            sum++;
                            changes = true;
                        }
                        iters++;
                    }
                }
            }
        }
    }
    return sum;
}

int findAntinodes(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& antinodes){
    int sum = 0;
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            if(grid[i][j]!= '.'){
                sum += setAntinodes(grid, antinodes, i, j);
            }
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<char>> grid;
    readGridToVector(argv[1], grid);
    printGrid(grid);
    std::vector<std::vector<char>> antinodes = grid;
    std::cout << findAntinodes(grid, antinodes) << std::endl;
    printGrid(antinodes);
    std::cout << "The result is " << countAntinodes(antinodes) << std::endl;
}
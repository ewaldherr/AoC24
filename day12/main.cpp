#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <utility>

void readGridToVector(const std::string& filename, std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row;
        std::vector<bool> rowV;
        for (char ch : line) {
            row.push_back(ch);
            rowV.push_back(false);
        }
        if (!row.empty()) {
            grid.push_back(row);
            visited.push_back(rowV);
        }
    }

    file.close();
}

int checkTrailhead(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, int posI, int posJ){
    int area = 1;
    int perimeter = 0;
    std::queue<std::pair<int,int>> queue;
    char plant = grid[posI][posJ];
    visited[posI][posJ] = true;
    //std::vector<std::pair<int,int>> vec;
    queue.push(std::make_pair(posI,posJ));
    while(!queue.empty()){
        auto current = queue.front();
        queue.pop();
        int i = std::get<0>(current);
        int j = std::get<1>(current);
        if(i > 0){
            if(grid[i-1][j] == plant && !visited[i-1][j]){
                queue.push(std::make_pair(i-1,j));
                visited[i-1][j] = true;
                area++;
            } else if(grid[i-1][j] != plant){
                perimeter++;
            }           
        } else{
            perimeter++;
        }
        if(i < grid.size()-1){
            if(grid[i+1][j] == plant && !visited[i+1][j]){
                queue.push(std::make_pair(i+1,j));
                visited[i+1][j] = true;
                area++;
            } else if(grid[i+1][j] != plant){
                perimeter++;
            }
        } else{
            perimeter++;
        }
        if(j > 0){
            if(grid[i][j-1] == plant && !visited[i][j-1]){
                queue.push(std::make_pair(i,j-1));
                visited[i][j-1] = true;
                area++;
            } else if(grid[i][j-1] != plant){
                perimeter++;
            }
        } else{
            perimeter++;
        }
        if(j < grid[0].size()){
            if(grid[i][j+1] == plant && !visited[i][j+1]){
                queue.push(std::make_pair(i,j+1));
                visited[i][j+1] = true;
                area++;
            } else if(grid[i][j+1] != plant){
                perimeter++;
            }
        } else{
            perimeter++;
        }
    }
    std::cout << area << " " << perimeter << " " << area* perimeter <<" "<< plant << std::endl;
    return area*perimeter;
}

int checkTrailheads(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited){
    int sum = 0;
    for(int i = 0; i < grid.size();++i){
        for(int j= 0; j< grid[0].size(); ++j){
            if(!visited[i][j]){
                sum += checkTrailhead(grid, visited, i, j);
            }
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<bool>> visited;
    readGridToVector(argv[1], grid, visited);
    std::cout << "Grid established" << std::endl;
    std::cout << "The result is " << checkTrailheads(grid, visited) << std::endl;
}
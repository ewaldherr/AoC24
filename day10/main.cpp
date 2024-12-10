#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <utility>

void readGridToVector(const std::string& filename, std::vector<std::vector<int>>& grid) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) { // Process each line
        std::vector<int> row;

        // Process each character in the line
        for (char ch : line) {
            if (std::isdigit(ch)) { // Check if the character is a digit
                row.push_back(ch - '0'); // Convert the character to an integer and store it
            } else {
                std::cerr << "Warning: Non-digit character encountered and ignored: " << ch << std::endl;
            }
        }

        if (!row.empty()) {
            grid.push_back(row); // Add the row to the grid
        }
    }

    file.close();
}

int checkTrailhead(std::vector<std::vector<int>>& grid, int posI, int posJ){
    int sum = 0;
    std::queue<std::tuple<int,int,int>> queue;
    //std::vector<std::pair<int,int>> vec;
    queue.push(std::make_tuple(posI,posJ,0));
    while(!queue.empty()){
        auto current = queue.front();
        queue.pop();
        int i = std::get<0>(current);
        int j = std::get<1>(current);
        int level = std::get<2>(current);
        if(level == 9){
            //bool found = false;
            //for(auto entry: vec){
            //    if(entry.first == i && entry.second == j){
            //        found = true;
            //    }
            //}
            //if(!found){
                sum++;
            //    vec.push_back(std::make_pair(i,j));
            //}
        }
        if(i > 0){
            if(grid[i-1][j] == level + 1){
                queue.push(std::make_tuple(i-1,j,level+1));
            }            
        }
        if(i < grid.size()-1){
            if(grid[i+1][j] == level + 1){
                queue.push(std::make_tuple(i+1,j,level+1));
            }
        }
        if(j > 0){
            if(grid[i][j-1] == level + 1){
                queue.push(std::make_tuple(i,j-1,level+1));
            }
        }
        if(j < grid[0].size()){
            if(grid[i][j+1] == level + 1){
                queue.push(std::make_tuple(i,j+1,level+1));
            }
        }
    }
    return sum;
}

int checkTrailheads(std::vector<std::vector<int>>& grid){
    int sum = 0;
    for(int i = 0; i < grid.size();++i){
        for(int j= 0; j< grid[0].size(); ++j){
            if(grid[i][j]==0){
                sum += checkTrailhead(grid, i, j);
            }
        }
    }
    return sum;
}

int main(int argc, char** argv){
    std::vector<std::vector<int>> grid;
    readGridToVector(argv[1], grid);
    std::cout << "The result is " << checkTrailheads(grid) << std::endl;
}
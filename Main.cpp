#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

const int WIDTH = 10;
const int HEIGHT = 10;

enum Cell {
    WALL,
    PATH,
    VISITED
};

struct Position {
    int x, y;
};

void initializeMaze(std::vector<std::vector<Cell>>& maze) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            maze[i][j] = WALL;
        }
    }
}

void generateMaze(std::vector<std::vector<Cell>>& maze, int startX, int startY) {
    std::stack<Position> stack;
    stack.push({startX, startY});
    maze[startY][startX] = PATH;

    std::srand(std::time(0));

    while (!stack.empty()) {
        Position current = stack.top();
        stack.pop();

        std::vector<Position> neighbors;

        if (current.x > 1 && maze[current.y][current.x - 2] == WALL) {
            neighbors.push_back({current.x - 2, current.y});
        }
        if (current.x < WIDTH - 2 && maze[current.y][current.x + 2] == WALL) {
            neighbors.push_back({current.x + 2, current.y});
        }
        if (current.y > 1 && maze[current.y - 2][current.x] == WALL) {
            neighbors.push_back({current.x, current.y - 2});
        }
        if (current.y < HEIGHT - 2 && maze[current.y + 2][current.x] == WALL) {
            neighbors.push_back({current.x, current.y + 2});
        }

        if (!neighbors.empty()) {
            stack.push(current);

            Position next = neighbors[std::rand() % neighbors.size()];

            maze[(current.y + next.y) / 2][(current.x + next.x) / 2] = PATH;
            maze[next.y][next.x] = PATH;

            stack.push(next);
        }
    }
}

void printMaze(const std::vector<std::vector<Cell>>& maze) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (maze[i][j] == WALL) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<Cell>> maze(HEIGHT, std::vector<Cell>(WIDTH));
    initializeMaze(maze);
    generateMaze(maze, 1, 1);
    printMaze(maze);

    return 0;
}
#include "npc.h"
#include "bomb.h"
#include <ctime>
#include <QDebug>
#include <vector>
#include <set>
using namespace std;
const int N = 20;
int getPos(int x, int y);
int checkPosition(int** m, int x, int y);
bool* search(int** m, int x, int y, bool setBomb);
int nextStep(int** m, int x, int y);
void resetVisited();
bool dfs(int** m, std::vector<int>& path, int x, int y, int target);

bool visited[N * N + 1]{ false };
int depth = 0;

int map[N][N]{ {EMPTY, EMPTY, EMPTY, WALL},
              {BRICK, WALL, BRICK, WALL},
              {WALL, WALL, EMPTY, EMPTY},
              {WALL, OUT, EMPTY, EMPTY} };


int getPos(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N) {
        return -1;
    }
    return x * N + y;
}

int checkPosition(int** m, int x, int y) {
    if (getPos(x, y) != -1) {
        return *((int*)m + getPos(x, y));
    }
    return -1;
}

bool* search(int** m, int x, int y, bool ignore) {
    int directions[4];
    directions[0] = checkPosition(m, x - 1, y); // UP
    directions[1] = checkPosition(m, x + 1, y); // DOWN
    directions[2] = checkPosition(m, x, y - 1); // LEFT
    directions[3] = checkPosition(m, x, y + 1); // RIGHT

    bool* directionsCanMove = new bool[4];

    for (int i = 0; i < 4; i++) {
        if (directions[i] == -1 || directions[i] == WALL) {
            directionsCanMove[i] = false;
        }
        else {
            directionsCanMove[i] = true;
        }
        if (!ignore && (directions[i] == BRICK || directions[i] == OCCUPIED || directions[i] == BOMB)) {
            directionsCanMove[i] = false;
        }
    }
    return directionsCanMove;
}

void resetVisited() {
    for (int i = 0; i <= N * N; i += 1) {
        visited[i] = false;
    }
}

bool dfs(int** m, std::vector<int>& path, int x, int y, int target) {
    if (checkPosition(m, x, y) == target) {
        return true;
    }
    visited[getPos(x, y)] = true;
    bool* directionsCanMove = search(m, x, y, true);
    bool find = false;
    for (int i = 0; i < 4; i++) {
        if (directionsCanMove[i]) {
            path.push_back(i);
            if (i == 0 && !visited[getPos(x - 1, y)]) {
                find = dfs(m, path, x - 1, y, target);
            }
            else if (i == 1 && !visited[getPos(x + 1, y)]) {
                find = dfs(m, path, x + 1, y, target);
            }
            else if (i == 2 && !visited[getPos(x, y - 1)]) {
                find = dfs(m, path, x, y - 1, target);
            }
            else if (i == 3 && !visited[getPos(x, y + 1)]) {
                find = dfs(m, path, x, y + 1, target);
            }
            if (find) {
                return true;
            }
            path.pop_back();
        }
    }
    return false;
}

void setBomb(int** m, int x, int y) {
   // *((int*)m + getPos(x, y)) = BOMB;
}

int nextStep(int** m, int x, int y) {
    bool* canMove = search(m, x, y, false);
    std::vector<int> pathToBomb;
    bool findBomb = dfs(m, pathToBomb, x, y, BOMB);
    resetVisited();
    // Go away if near bomb
    if (findBomb && pathToBomb.size() == 1) {
        for (int i = 0; i < 4; i += 1) {
            if (canMove[i] && i != pathToBomb[0]) {
                return i;
            }
        }
    }

    std::vector<int> pathToOut;
    bool findOut = dfs(m, pathToOut, x, y, OUT);
    resetVisited();
    std::vector<int> pathToPlayer;
    bool findPlayer = dfs(m, pathToPlayer, x, y, OCCUPIED);
    resetVisited();
    std::vector<int> path;
    if (findOut && findPlayer) {
        if (pathToOut.size() < pathToPlayer.size()) {
            path = pathToOut;
        }
        else {
            path = pathToPlayer;
        }
    }
    // Set bomb if near player
    if (pathToPlayer.size() == 1) {
        setBomb(m, x, y);
        for (int i = 0; i < 4; i += 1) {
            if (canMove[i] && i != pathToPlayer[0]) {
                return i;
            }
        }
    }

    for (int i = 0; i < 4; i += 1) {
        if (findOut && findPlayer && canMove[i] && i == path[0]) {
            return i;
        }
    }

    for (int i = 0; i < 4; i += 1) {
        if (findOut && canMove[i] && i == pathToOut[0]) {
            return i;
        }
    }

    setBomb(m, x, y);

    for (int i = 0; i < 4; i += 1) {
        if (canMove[i]) {
            return i;
        }
    }

    return -1;
}

//void printMap() {
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            std::cout << *((int*)map + getPos(i, j)) << ' ';
//        }
//        std::cout << std::endl;
//    }
//}

npc::npc(int HP_in, int id_in, int role_in, int location_x_in, int location_y_in):
    Character (HP_in, id_in, role_in, location_x_in, location_y_in)
{

}

void npc::automove(int** map){
    qsrand(time(NULL)+this->Get_id());
    int direction = int(qrand()) % 4;
    Move(direction, map, 20, 20);
    //Move(nextStep(map, Get_locationx(), Get_locationy()), map, 20, 20);
    //qDebug() << map[Get_locationy()][Get_locationx()-1] << map[Get_locationy()-1][Get_locationx()] << map[Get_locationy()+1][Get_locationx()] << map[Get_locationy()][Get_locationx()+1];
}

void npc::skill(){

}


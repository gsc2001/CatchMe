//
// Created by gurkirat on 26/03/21.
//

#include "maze.h"

#include "resource_manager.h"
#include <iostream>
#include <vector>
#include "globals.h"

Maze::Maze(int m, int n) {

    this->M = m;
    this->N = n;
    this->maze = new char *[M];
    this->directions = new Movement *[M * N];
    for (int i = 0; i < M; i++) {
        this->maze[i] = new char[N];

    }
    for (int i = 0; i < M * N; i++)
        this->directions[i] = new Movement[M * N];



    // TODO: remove get from generator
    char temp_maze[][10] = {
            "#S#######",
            "#       #",
            "#2# #1# #",
            "# # #   #",
            "# # ### #",
            "#I      #",
            "##### ###",
            "#       #",
            "#######E#",
    };

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            maze[i][j] = temp_maze[i][j];
    }
    this->wall_size = glm::vec2(SCREEN_WIDTH / N, SCREEN_HEIGHT / M);
}

void Maze::Init() {

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == '#') {
                this->walls.emplace_back(glm::vec2(j * wall_size.x, i * wall_size.y), this->wall_size,
                                         ResourceManager::GetTexture("wall"));
            } else if (maze[i][j] == 'S')
                this->start_pos = glm::vec2(j, i);
            else if (maze[i][j] == 'E')
                this->end_pos = glm::vec2(j, i);
            else if (maze[i][j] == 'I')
                this->imposter_pos = glm::vec2(j, i);
            else if (maze[i][j] == '1') {
                this->vap_task = new GameObject(glm::vec2(j * wall_size.x, i * wall_size.y), this->wall_size,
                                                ResourceManager::GetTexture("vapour_task"));
            } else if (maze[i][j] == '2') {
                this->pow_task = new GameObject(glm::vec2(j * wall_size.x, i * wall_size.y), this->wall_size,
                                                ResourceManager::GetTexture("powerup_task"));

            } else {
                this->free_spaces.emplace_back(j, i);
            }
        }
    }
    this->ComputeShortestPaths();
}


void Maze::Draw(SpriteRenderer &renderer) {
    for (auto &wall : this->walls) {
        wall.Draw(renderer);
    }
    this->vap_task->Draw(renderer);
    this->pow_task->Draw(renderer);

}

glm::vec2 Maze::GetWallSize() {
    return this->wall_size;
}

glm::vec2 Maze::GetStart() {
    return wall_size * start_pos + wall_size / 4.0f;
}

glm::vec2 Maze::GetEnd() {
    return wall_size * end_pos + wall_size / 4.0f;
}

glm::vec2 Maze::GetImposterPos() {
    return wall_size * imposter_pos + wall_size / 4.0f;
}

int Maze::getIdx(int i, int j) {
    return i * MAZE_WIDTH + j;
}

void Maze::ComputeShortestPaths() {
    // index of i, j = N * i + j
    std::vector<std::vector<int>> distances(M * N, std::vector<int>(M * N, INT_MAX));
    std::vector<std::vector<int>> parents(M * N, std::vector<int>(M * N, -1));
    std::vector<std::pair<int, int>> adj;
    adj.emplace_back(-1, 0);
    adj.emplace_back(1, 0);
    adj.emplace_back(0, 1);
    adj.emplace_back(0, -1);
    for (int s = 0; s < M * N; s++) {
        int s_j = s % N, s_i = s / N;
        if (maze[s_i][s_j] == '#') {
            continue;
        }
        std::vector<bool> u(M * N, false);
        distances[s][s] = 0;

        // dijkstra for source s
        for (int indd = 0; indd < M * N; indd++) {
//            int d_j = indd % N, d_i = indd / N;
//            if (maze[d_i][d_j] == '#') {
//                continue;
//            }
            int v = -1;
            for (int j = 0; j < M * N; j++) {
                if (!u[j] && (v == -1 || distances[s][j] < distances[s][v])) {
                    v = j;
                }
            }
            if (distances[s][v] == INT_MAX)
                break;
            u[v] = true;
            for (auto edge:adj) {
                int new_i = v / N + edge.first;
                int new_j = v % N + edge.second;
                if (new_i < 0 || new_i >= M || new_j < 0 || new_j >= N || maze[new_i][new_j] == '#') {
                    continue;
                }
                int to = getIdx(new_i, new_j);
                if (distances[s][v] + 1 < distances[s][to]) {
                    distances[s][to] = distances[s][v] + 1;
                    parents[s][to] = v;
                }
            }
        }


        for (int d = 0; d < M * N; d++) {
            if (maze[d / N][d % N] == '#') {
                continue;
            }
            std::vector<int> path;
            for (int v = d; v != s; v = parents[s][v]) {
                if (v == -1) {
                    path.clear();
                    break;
                }
                path.push_back(v);
            }
            if (path.empty()) {
                this->directions[s][d] = STOP;
                continue;
            }
            auto last = path[path.size() - 1];
            int last_i = last / N, last_j = last % N;
            if (last_i == s_i + 1)
                this->directions[s][d] = DOWN;
            else if (last_i == s_i - 1)
                this->directions[s][d] = UP;
            else if (last_j == s_j + 1)
                this->directions[s][d] = RIGHT;
            else if (last_j == s_j - 1)
                this->directions[s][d] = LEFT;
            else {
                // shouldn't have come here some error
#ifdef DEBUG
                std::cout << "Djikstra wrong for " << s << "\n";
                std::cout << last << "\n";
                exit(1);
#endif
            }

        }
    }
#ifdef DEBUG
    for (int i = 0; i < M * N; i++) {
        if (maze[i / N][i % N] == '#') {
            continue;
        }
        std::cout << "\n\n\n";
        std::cout << "For s" << i << "\n";
        for (int j = 0; j < M * N; j++) {
            if (maze[j / N][j % N] == '#') {
                continue;
            }
            std::cout << j << "-> " << directions[i][j] << "\n";
        }
        std::cout << "\n\n\n";
    }
#endif

}
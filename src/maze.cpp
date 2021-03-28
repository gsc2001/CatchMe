//
// Created by gurkirat on 26/03/21.
//

#include "maze.h"

#include "resource_manager.h"
#include <iostream>
#include "globals.h"

Maze::Maze(int m, int n) {

    this->M = 2 * m + 1;
    this->N = 2 * n + 1;
    this->maze = new char *[M];
    for (int i = 0; i < M; i++)
        maze[i] = new char[N];


    // TODO: remove get from generator
    char temp_maze[][10] = {
            "# #######",
            "#     # #",
            "### # # #",
            "# # #   #",
            "# # ### #",
            "#   #   #",
            "##### ###",
            "#       #",
            "####### #",
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
                this->walls.emplace_back(glm::vec2(j * wall_size.x, i * wall_size.y), this->wall_size, glm::vec3(1.0f),
                                         ResourceManager::GetTexture("wall"));
            }

        }
    }


}


void Maze::Draw(SpriteRenderer &renderer) {
    for (auto &wall : this->walls) {
        wall.Draw(renderer);
    }

}

//
// Created by gurkirat on 26/03/21.
//

#ifndef CATCHME_MAZE_H
#define CATCHME_MAZE_H

#include "game_object.h"
#include <vector>
#include "globals.h"


class Maze {
private:
    int M, N;
    char **maze;
    glm::vec2 wall_size;
    glm::vec2 start_pos, end_pos, imposter_pos;
public:

    Maze(int m, int n);

    void Init();

    std::vector<GameObject> walls;
    std::vector<glm::vec2> free_spaces;
    // direction[i][j] -> direction to take if imposter at i and player at j
    Movement **directions;
    GameObject *pow_task = nullptr, *vap_task = nullptr;


    void Load(const char *file);

    void Draw(SpriteRenderer &renderer);

    void Generate(int m, int n);

    glm::vec2 GetStart();

    glm::vec2 GetEnd();

    glm::vec2 GetWallSize();

    void ComputeShortestPaths();

    glm::vec2 GetImposterPos();

    static int getIdx(int i, int j);


};


#endif //CATCHME_MAZE_H

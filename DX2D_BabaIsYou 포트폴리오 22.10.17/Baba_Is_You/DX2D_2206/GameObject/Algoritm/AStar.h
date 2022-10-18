#pragma once

//A*
class AStar
{
public:
    AStar(class GameTileMap * map);
    ~AStar();

    void Render();

    int FindCloseNode(Vector2 pos);

    void GetPath(IN int start, IN int end, OUT vector<Vector2> & path);

private:
    void SetEdge(UINT width);

    void Reset();

    float GetManhattanDistance(int start, int end);
    float GetDiagonalManhattanDistance(int start, int end);

    void Extend(int center, int end);
    int GetMinNode();

private:
    vector<Node *> nodes;
    //vector<int> openNodes;
    Heap * heap;
};
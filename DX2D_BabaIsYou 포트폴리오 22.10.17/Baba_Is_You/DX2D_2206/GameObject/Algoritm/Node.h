#pragma once

class Node
{
public:
    friend class AStar;

    enum State
    {
        NONE, OPEN, CLOSED, USING, OBSTACLE
    };    

    struct Edge
    {
        int index;
        float cost;
        LineCollider * line;

        Edge(Vector2 start, Vector2 end)
        {
            line = new LineCollider(start, end);
            line->SetColor(1, 1, 0);
        }
        ~Edge()
        {
            delete line;
        }
    };

public:
    Node(Vector2 pos, int index);
    ~Node();

    void Render();

    void AddEdge(Node * node);

    void SetState(State state) { this->state = state; }
    float GetCost() { return f; }

private:
    Vector2 pos;

    int index = 0;
    int via = -1;

    //Cost
    float f = 0, g = 0, h = 0;
    //F : 최종코스트 -> G + H
    //G : 시작점->노드까지의 거리
    //H : 노드에서 부터 목적지까의 추정 가중치

    State state = NONE;

    vector<Edge *> edges;

    Collider * collider;
};
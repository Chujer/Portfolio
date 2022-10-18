#include "Framework.h"

AStar::AStar(GameTileMap * map)
{
    map->GetNodes(nodes);
    SetEdge(map->GetWidth());

    heap = new Heap();
}

AStar::~AStar()
{
    for (Node * node : nodes)
        delete node;

    delete heap;
}

void AStar::Render()
{
    for (Node * node : nodes)
        node->Render();
}

int AStar::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX;

    int index = -1;

    for (UINT i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue;

        float distance = Vector2::Distance(pos, nodes[i]->pos);

        if (minDist > distance)
        {
            minDist = distance;
            index = i;
        }
    }

    return index;
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector2> & path)
{
    Reset();
    path.clear();

    //1. 시작노드 초기화하고 오픈노드에 추가
    float G = 0;
    float H = GetDiagonalManhattanDistance(start, end);

    nodes[start]->f = G + H;
    nodes[start]->g = G;
    nodes[start]->h = H;    
    nodes[start]->via = start;
    nodes[start]->state = Node::OPEN;

    //openNodes.push_back(start);
    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::CLOSED)
    {
        //if (openNodes.empty())
        if(heap->Empty())
            return;

        //2. 오픈노드 중에서 효율이 가장 좋은 노드 찾기
        int curIndex = GetMinNode();
        //3. 찾은 노드와 연결된 노드의 정보 갱신후 오픈노드에 추가하기
        Extend(curIndex, end);
        //4. 확장된 노드 닫기
        nodes[curIndex]->state = Node::CLOSED;
    }

    //5. 백트렉킹
    int curIndex = end;

    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::USING;
        path.push_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via;
    }

    path.push_back(nodes[start]->pos);
}

void AStar::SetEdge(UINT width)
{
    for (UINT i = 0; i < nodes.size(); i++)
    {
        if (i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }        

        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width]);
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if ((i % width != width - 1) && (i < nodes.size() - width))
        {
            nodes[i]->AddEdge(nodes[i + 1 + width]);
            nodes[i + 1 + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != 0 )
        {
            nodes[i]->AddEdge(nodes[i + width - 1]);
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }
}

void AStar::Reset()
{
    for (Node * node : nodes)
    {
        if (node->state != Node::OBSTACLE)
            node->state = Node::NONE;
    }

    //openNodes.clear();
    heap->Clear();
}

float AStar::GetManhattanDistance(int start, int end)
{
    Vector2 startPos = nodes[start]->pos;
    Vector2 endPos = nodes[end]->pos;

    Vector2  temp = endPos - startPos;

    return abs(temp.x) + abs(temp.y);
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    Vector2 startPos = nodes[start]->pos;
    Vector2 endPos = nodes[end]->pos;

    Vector2  temp = endPos - startPos;

    float x = abs(temp.x);
    float y = abs(temp.y);

    float minSize = min(x, y);
    float maxSize = max(x, y);

    return (maxSize - minSize) + sqrt(minSize * minSize * 2);
}

void AStar::Extend(int center, int end)
{
    for (Node::Edge * edge : nodes[center]->edges)
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED)
            continue;
        if (nodes[index]->state == Node::OBSTACLE)
            continue;

        float G = nodes[center]->g + edge->cost;
        float H = GetDiagonalManhattanDistance(index, end);
        float F = G + H;

        if (nodes[index]->state == Node::OPEN)
        {
            if (F < nodes[index]->f)
            {
                nodes[index]->g = G;
                nodes[index]->f = F;
                nodes[index]->via = center;
            }
        }
        else if (nodes[index]->state == Node::NONE)
        {
            nodes[index]->g = G;
            nodes[index]->h = H;
            nodes[index]->f = F;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;

            //openNodes.push_back(index);
            heap->Insert(nodes[index]);
        }
    }
}

int AStar::GetMinNode()
{
    /*
    int openIndex = 0;
    int nodeIndex = openNodes[openIndex];
    float minF = nodes[nodeIndex]->f;

    for (UINT i = 1; i < openNodes.size(); i++)
    {
        nodeIndex = openNodes[i];
        if (nodes[nodeIndex]->f < minF)
        {
            minF = nodes[nodeIndex]->f;
            openIndex = i;
        }
    }

    nodeIndex = openNodes[openIndex];

    openNodes.erase(openNodes.begin() + openIndex);

    return nodeIndex;
    */

    return heap->DeleteRoot()->index;
}

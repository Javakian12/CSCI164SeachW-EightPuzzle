#include <bitset>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
#define N 3
int node_num = 0;
int choiceOf;
map<string, bool>mp;
bool isSolved = false;
int goalx[N + 10] = { 0 }, goalY[N + 10] = { 0 };
int searchNodes[15], solutionNodes[15];
int track1[999999];
int track2[999999];
int iterate = 0;

int calcMisplaced(int mat[N][N], int goal[N][N]);

struct Node
{

    Node* parent;
    int mat[N][N];
    int x, y;
    int level;
    int misplaced;
    int manhattanDistance;
};

Node* newNode(int mat[N][N], int x, int y, int newX,
    int newY, int level, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    malloc(sizeof(node->parent) * 5);
    malloc(sizeof node->mat * 5);

    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->level = level;
    node->x = newX;
    node->y = newY;

    return node;
}
Node* newNodeH(int mat[N][N], int x, int y, int newX,
    int newY, int level, int misplaced, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->level = level;
    node->x = newX;
    node->y = newY;
    node->misplaced = misplaced;

    return node;
}
Node* newNodeA(int mat[N][N], int x, int y, int newX,
    int newY, int level, int misplaced, int manhattan, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->level = level;
    node->x = newX;
    node->y = newY;
    node->misplaced = misplaced;
    node->manhattanDistance = manhattan;

    return node;
}

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };


int isSafe(int x, int y)
{
    return (x >= 0 && x < N&& y >= 0 && y < N);
}

int printMatrix(int mat[N][N], int algo, ofstream& myfile)
{
    solutionNodes[algo]++;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] == 0) {
                if (track1[iterate] == NULL) {
                    track1[iterate] = i;
                    track2[iterate] = j;
                    if ((track1 != nullptr) && (track2 != nullptr) && (iterate != 0)) {
                        if (track1[iterate] < track1[iterate - 1]) {
                            cout << "U";
                            iterate++;
                        }
                        else if (track1[iterate] > track1[iterate - 1]) {
                            cout << "D";
                            iterate++;
                        }
                        else if (track2[iterate] < track2[iterate - 1]) {
                            cout << "L";
                            iterate++;
                        }
                        else if (track2[iterate] > track2[iterate - 1]) {
                            cout << "R";
                            iterate++;
                        }
                        else {
                            //didn't move
                            iterate++;
                        }
                    }
                    else {
                        iterate++;
                    }
                }
            }
        }

    }
    return 0;
}

bool moveLeft(int x)
{
    if (x > 0) return true;
    return false;
}
bool moveRight(int x)
{
    if (x < N - 1) return true;
    return false;
}
bool moveUp(int x)
{
    if (x > 0) return true;
    return false;
}
bool moveDown(int x)
{
    if (x < N - 1) return true;
    return false;
}

void printPath(Node* root, int algo, ofstream& myfile)
{
    if (root == NULL)
        return;

    printPath(root->parent, algo, myfile);

    printMatrix(root->mat, algo, myfile);

}

string getMatString(int mat[N][N])
{
    string s = "";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s.append(to_string(mat[i][j]));
        }
    }
    return s;
}

bool compareMat(int mat1[N][N], int mat2[N][N])
{
    int flg = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                flg = 1;

            }
        }
    }
    if (flg == 1) return false;
    return true;
}

int calcMisplaced(int mat[N][N], int goal[N][N])
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] != goal[i][j])
            {
                cnt++;
            }
        }
    }
    return cnt;
}
struct comp2
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->misplaced) > (rhs->misplaced);
    }
};


void BFS(int initial[N][N], int x, int y,
    int goal[N][N])
{
    queue<Node*>q;
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    q.push(root);
    while (!q.empty())
    {
        Node* curr = q.front();

        mp[getMatString(curr->mat)] = true;
        q.pop();
        if (compareMat(curr->mat, goal))
        {
            ofstream myfile;
            myfile.open("bfs.txt");
            cout << "\nCall Count:" << searchNodes[1] << endl;
            cout << "Path found: ";
            printPath(curr, 1, myfile);
            myfile.close();
            return;
        }
        if (moveLeft(curr->y))
        {
            Node* new_node = newNode(curr->mat, curr->x, curr->y, curr->x, (curr->y) - 1, curr->level + 1, curr);
            if (!mp[getMatString(new_node->mat)])
            {
                q.push(new_node);
                searchNodes[1]++;
            }

        }
        if (moveRight(curr->y))
        {
            Node* new_node = newNode(curr->mat, curr->x, curr->y, curr->x, (curr->y) + 1, curr->level + 1, curr);
            if (!mp[getMatString(new_node->mat)])
            {
                q.push(new_node);
                searchNodes[1]++;
            }
        }
        if (moveUp(curr->x))
        {
            Node* new_node = newNode(curr->mat, curr->x, curr->y, (curr->x) - 1, curr->y, curr->level + 1, curr);
            if (!mp[getMatString(new_node->mat)])
            {
                q.push(new_node);
                searchNodes[1]++;
            }
        }
        if (moveDown(curr->x))
        {
            Node* new_node = newNode(curr->mat, curr->x, curr->y, (curr->x) + 1, curr->y, curr->level + 1, curr);
            if (!mp[getMatString(new_node->mat)])
            {
                q.push(new_node);
                searchNodes[1]++;
            }
        }
    }

}
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->level) > (rhs->level);
    }
};

int calcManhattanDist(int mat[N][N])
{
    int manhatt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] != 0)
            {
                manhatt += abs(i - goalx[mat[i][j]]) + abs(j - goalY[mat[i][j]]);
            }
        }
    }
    return manhatt;
}
void setGoalposition(int goal[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            goalx[goal[i][j]] = i;
            goalY[goal[i][j]] = j;
        }
    }
}
struct comp3
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->level + lhs->manhattanDistance) > (rhs->level + rhs->manhattanDistance);
    }
};
void AstarSearch(int initial[N][N], int x, int y,
    int goal[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp3> pq;
    Node* root = newNodeA(initial, x, y, x, y, 0, calcMisplaced(initial, goal), calcManhattanDist(initial), NULL);
    pq.push(root);
    setGoalposition(goal);
    while (!pq.empty())
    {
        Node* curr = pq.top();
        

        mp[getMatString(curr->mat)] = true;
        pq.pop();
        if (compareMat(curr->mat, goal))
        {
            ofstream myfile;
            myfile.open("a*.txt");
            cout << "\nCall Count:" << searchNodes[6] << endl;
            cout << "Path Found: ";
            printPath(curr, 6, myfile);
            myfile.close();
            return;
        }
        if (moveLeft(curr->y))
        {
            Node* new_node = newNodeA(curr->mat, curr->x, curr->y, curr->x, (curr->y) - 1, curr->level + 1, 0, 0, curr);
            new_node->manhattanDistance = calcManhattanDist(new_node->mat);
            new_node->misplaced = calcMisplaced(new_node->mat, goal);
            if (!mp[getMatString(new_node->mat)])
            {

                pq.push(new_node);
                searchNodes[6]++;

            }
        }
        if (moveRight(curr->y))
        {
            Node* new_node = newNodeA(curr->mat, curr->x, curr->y, curr->x, (curr->y) + 1, curr->level + 1, 0, 0, curr);
            new_node->manhattanDistance = calcManhattanDist(new_node->mat);
            new_node->misplaced = calcMisplaced(new_node->mat, goal);
            if (!mp[getMatString(new_node->mat)])
            {
                pq.push(new_node);
                searchNodes[6]++;

            }
        }
        if (moveUp(curr->x))
        {
            Node* new_node = newNodeA(curr->mat, curr->x, curr->y, (curr->x) - 1, curr->y, curr->level + 1, 0, 0, curr);
            new_node->manhattanDistance = calcManhattanDist(new_node->mat);
            new_node->misplaced = calcMisplaced(new_node->mat, goal);
            if (!mp[getMatString(new_node->mat)])
            {
                pq.push(new_node);
                searchNodes[6]++;

            }
        }
        if (moveDown(curr->x))
        {
            Node* new_node = newNodeA(curr->mat, curr->x, curr->y, (curr->x) + 1, curr->y, curr->level + 1, 0, 0, curr);
            new_node->manhattanDistance = calcManhattanDist(new_node->mat);
            new_node->misplaced = calcMisplaced(new_node->mat, goal);
            if (!mp[getMatString(new_node->mat)])
            {
                pq.push(new_node);
                searchNodes[6]++;

            }
        }
    }

}
void IDAStar(int initial[N][N], int x, int y,
    int goal[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp3> fp;
    Node* root = newNodeA(initial, x, y, x, y, 0, calcMisplaced(initial, goal), calcManhattanDist(initial), NULL);
    setGoalposition(goal);
    fp.push(root);
    while (!fp.empty())
    {
        Node* curr = fp.top();


        mp[getMatString(curr->mat)] = true;
        fp.pop();
        if (compareMat(curr->mat, goal))
        {
            ofstream myfile;
            myfile.open("IDAStar.txt");
            cout << "\nCall Count:" << searchNodes[6] << endl;
            cout << "Path Found: ";
            printPath(curr, 6, myfile);
            myfile.close();
            return;
        }
        if (moveLeft(curr->y))
        {
            Node* newNode = newNodeA(curr->mat, curr->x, curr->y, curr->x, (curr->y) - 1, curr->level + 1, 0, 0, curr);
            newNode->misplaced = calcMisplaced(newNode->mat, goal);
            newNode->manhattanDistance = calcManhattanDist(newNode->mat);
            if (!mp[getMatString(newNode->mat)])
            {

                fp.push(newNode);
                searchNodes[6]++;

            }
        }
        if (moveRight(curr->y))
        {
            Node* newNode = newNodeA(curr->mat, curr->x, curr->y, curr->x, (curr->y) + 1, curr->level + 1, 0, 0, curr);
            newNode->misplaced = calcMisplaced(newNode->mat, goal);
            newNode->manhattanDistance = calcManhattanDist(newNode->mat);
            if (!mp[getMatString(newNode->mat)])
            {
                fp.push(newNode);
                searchNodes[6]++;

            }
        }
        if (moveUp(curr->x))
        {
            Node* newNode = newNodeA(curr->mat, curr->x, curr->y, (curr->x) - 1, curr->y, curr->level + 1, 0, 0, curr);
            newNode->misplaced = calcMisplaced(newNode->mat, goal);
            newNode->manhattanDistance = calcManhattanDist(newNode->mat);
            if (!mp[getMatString(newNode->mat)])
            {
                fp.push(newNode);
                searchNodes[6]++;

            }
        }
        if (moveDown(curr->x))
        {
            Node* newNode = newNodeA(curr->mat, curr->x, curr->y, (curr->x) + 1, curr->y, curr->level + 1, 0, 0, curr);
            newNode->misplaced = calcMisplaced(newNode->mat, goal);
            newNode->manhattanDistance = calcManhattanDist(newNode->mat);
            if (!mp[getMatString(newNode->mat)])
            {
                fp.push(newNode);
                searchNodes[6]++;

            }
        }
    }

}
bool dfs_sltn = false;
void DFS(int inital[N][N], int x, int y, int level, Node* parent, int goal[N][N], int limit)
{
    Node* root = newNode(inital, x, y, x, y, level, parent);
    if (dfs_sltn) return;

    searchNodes[3]++;
    

    mp[getMatString(root->mat)] = true;
    if (compareMat(root->mat, goal))
    {
        ofstream myfile;
        myfile.open("dls.txt");
        cout << "Call Count:" << searchNodes[3] << endl;
        printPath(root, 3, myfile);
        dfs_sltn = true;
        myfile.close();
        return;
    }
    if (limit == 0)
    {

        return;
    }

    if (moveLeft(root->y))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, root->x, (root->y) - 1, root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
            //if (!offlinemode) cout << "Exploring action: Left" << endl;
            DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);
        }
    }
    if (moveRight(root->y))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, root->x, (root->y) + 1, root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
            //if (!offlinemode) cout << "Exploring action: Right" << endl;
            DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);

        }
    }
    if (moveUp(root->x))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, (root->x) - 1, (root->y), root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
           // if (!offlinemode) cout << "Exploring action: Up" << endl;
            DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);

        }
    }
    if (moveDown(root->x))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, (root->x) + 1, (root->y), root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
           // if (!offlinemode) cout << "Exploring action: Down" << endl;
            DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);

        }
    }

}
void IDS_DFS(int inital[N][N], int x, int y, int level, Node* parent, int goal[N][N], int limit)
{
    Node* root = newNode(inital, x, y, x, y, level, parent);
    if (dfs_sltn) return;

    searchNodes[4]++;
    

    mp[getMatString(root->mat)] = true;
    if (compareMat(root->mat, goal))
    {
        ofstream myfile;
        myfile.open("ids.txt");
        cout << "\nCall Count:" << searchNodes[4] << endl;
        cout << "Path Found: " << endl;
        printPath(root, 4, myfile);
        dfs_sltn = true;
        myfile.close();
        return;
    }
    if (limit == 0)
    {

        return;
    }

    if (moveLeft(root->y))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, root->x, (root->y) - 1, root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
            IDS_DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);
        }
    }
    if (moveRight(root->y))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, root->x, (root->y) + 1, root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
            IDS_DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);

        }
    }
    if (moveUp(root->x))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, (root->x) - 1, (root->y), root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
            IDS_DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);

        }
    }
    if (moveDown(root->x))
    {
        Node* new_node = newNode(root->mat, root->x, root->y, (root->x) + 1, (root->y), root->level + 1, root);
        if (!mp[getMatString(new_node->mat)] && !dfs_sltn)
        {
            IDS_DFS(new_node->mat, new_node->x, new_node->y, new_node->level, root, goal, limit - 1);

        }
    }

}

void IDS(int inital[N][N], int x, int y, int level, Node* parent, int goal[N][N], int limit)
{
    for (int i = 0; i <= limit; i++)
    {
        if (dfs_sltn)
        {
            return;
        }

        IDS_DFS(inital, x, y, 0, NULL, goal, i);

        mp.clear();
    }
}

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
#define N 4
int node_num = 0;
int choiceOf;
map<string, bool>mp;
int goalx[N + 10] = { 0 }, goalY[N + 10] = { 0 };
int searchNodes[15], solutionNodes[15];
int track1[999999];
int track2[999999];
int iterate = 0;

int main()
{
    string initialSEight[3][3]{
        {"1", "6", "0"},
        {"2", "7", "3"},
        {"4", "8", "5"}
    };
    int initialEight[3][3] =
    {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };

    int goalEight[3][3]{
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    string goalSEight[3][3] =
    {
        {"1", "2", "3"},
        {"4", "5", "6"},
        {"7", "8", "0"}
    };
    int x = 1, y = 0;
    int choice, mode;
    int n;
    while (1)
    {
        cout << "This is the 3 tile driver. Pick a mode:" << endl;
        cout << "Choose Mode:" << endl << "1.Traverse Mode (No move sequence Input)" << endl << "2.Traverse Mode (Move Sequence Input)" << "\n3.Exit" << endl;
        cin >> mode;
        if (mode == 1)
        {
#undef N
#define N 3




            string s;
            int val;
            cout << "Enter Initial State:" << endl;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    // cin >> s;
                    // initialSSixT[i][j] = s;
                    s = initialSEight[i][j];
                    if (s == "A")
                        val = 10;
                    else if (s == "B")
                        val = 11;
                    else if (s == "C")
                        val = 12;
                    else if (s == "D")
                        val = 13;
                    else if (s == "E")
                        val = 14;
                    else if (s == "F")
                        val = 15;
                    else
                        val = stoi(s);

                    initialEight[i][j] = val;

                    if (initialEight[i][j] == 0)
                    {
                        x = i, y = j;
                    }
                }
            }
            cout << "Enter Goal State:" << endl;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    //cin >> goalSSixT[i][j];
                    s = goalSEight[i][j];

                    if (s == "A")
                        val = 10;
                    else if (s == "B")
                        val = 11;
                    else if (s == "C")
                        val = 12;
                    else if (s == "D")
                        val = 13;
                    else if (s == "E")
                        val = 14;
                    else if (s == "F")
                        val = 15;
                    else
                        val = stoi(s);

                    goalEight[i][j] = val;

                }
            }
        }
        else if (mode == 2) {
#undef N
#define N 3
            int val;
            string s;
            cout << "Enter Initial State:" << endl;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    // cin >> s;
                    // initialSSixT[i][j] = s;
                    s = initialSEight[i][j];
                    if (s == "A")
                        val = 10;
                    else if (s == "B")
                        val = 11;
                    else if (s == "C")
                        val = 12;
                    else if (s == "D")
                        val = 13;
                    else if (s == "E")
                        val = 14;
                    else if (s == "F")
                        val = 15;
                    else
                        val = stoi(s);

                    initialEight[i][j] = val;

                    if (initialEight[i][j] == 0)
                    {
                        x = i, y = j;
                    }
                }
            }
            cout << "Enter Goal State:" << endl;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    //cin >> goalSSixT[i][j];
                    s = goalSEight[i][j];

                    if (s == "A")
                        val = 10;
                    else if (s == "B")
                        val = 11;
                    else if (s == "C")
                        val = 12;
                    else if (s == "D")
                        val = 13;
                    else if (s == "E")
                        val = 14;
                    else if (s == "F")
                        val = 15;
                    else
                        val = stoi(s);

                    goalEight[i][j] = val;

                }
            }

            cout << "Enter input move sequence: " << endl;
            string t;
            int temp;
            cin >> t;
            char* moves = new char[999];
            for (int x = 0; x < t.size(); x++) {
                moves[x] = t.at(x);
            }
            for (int v = 0; v < t.size(); v++) {
                if (moves[v] == 'l') {
                    for (int o = 0; o < 3; o++) {
                        for (int q = 0; q < 3; q++) {
                            if (initialEight[o][q] == 0) {
                                if (q == 0) {
                                    cout << "Cant move left, empty tile is leftmost" << endl;
                                }
                                else {
                                    temp = initialEight[o][q];
                                    initialEight[o][q] = initialEight[o][q - 1];
                                    initialEight[o][q - 1] = temp;
                                }
                            }
                        }
                    }
                }
                else if (moves[v] == 'r') {
                    for (int o = 0; o < 3; o++) {
                        for (int q = 0; q < 3; q++) {
                            if (initialEight[o][q] == 0) {
                                if (q == 3) {
                                    cout << "Cant move right, empty tile is rightmost" << endl;
                                }
                                else {
                                    temp = initialEight[o][q];
                                    initialEight[o][q] = initialEight[o][q + 1];
                                    initialEight[o][q + 1] = temp;
                                }
                            }
                        }
                    }
                }
                else if (moves[v] == 'd') {
                    for (int o = 0; o < 3; o++) {
                        for (int q = 0; q < 3; q++) {
                            if (initialEight[o][q] == 0) {
                                if (o == 3) {
                                    cout << "Cant move down, empty tile is at the bottom" << endl;
                                }
                                else {
                                    temp = initialEight[o][q];
                                    initialEight[o][q] = initialEight[o + 1][q];
                                    initialEight[o + 1][q] = temp;
                                }
                            }
                        }
                    }
                }
                else if (moves[v] == 'u') {
                    for (int o = 0; o < 3; o++) {
                        for (int q = 0; q < 3; q++) {
                            if (initialEight[o][q] == 0) {
                                if (o == 0) {
                                    cout << "Cant move up, empty tile is at the top" << endl;
                                }
                                else {
                                    temp = initialEight[o][q];
                                    initialEight[o][q] = initialEight[o - 1][q];
                                    initialEight[o - 1][q] = temp;
                                }
                            }
                        }
                    }
                }
            }
            delete[] moves;
            string useless;
            cout << "Printing out modified array... (Letters are translated to numbers)" << endl;
            for (int o = 0; o < 3; o++) {
                for (int q = 0; q < 3; q++) {
                    cout << initialEight[o][q];
                    if (q + 1 < 3) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
        else if (mode == 3) {
            break;
        }
        else
        {
            cout << "Enter a right mode" << endl;
        }
        cout << "Enter your choice:" << endl << "1. Run BFS" << endl << "2. Run DFS" << endl << "3. Run IDS" << endl << "4. Run A*" << endl << "5. Run IDA*" << endl << "6. Run all" << endl << "7. Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            mp.clear();
            clock_t start = clock();
            BFS(initialEight, x, y, goalEight);
            double  runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
            cout << "\nTotal Nodes-->" << searchNodes[choice] << endl << "Solution Nodes-->" << solutionNodes[choice] << endl << endl;
            cout << "Elapsed Times " << runtime << " seconds\n\n\n" << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
        }
        else if (choice == 2)
        {

            mp.clear();
            dfs_sltn = false;
            clock_t start = clock();
            DFS(initialEight, x, y, 0, NULL, goalEight, 40);
            double  runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
            cout << "\nTotal Nodes-->" << searchNodes[choice+1] << endl << "Solution Nodes-->" << solutionNodes[choice+1] << endl << endl;
            cout << "Elapsed Times " << runtime << " seconds\n\n\n" << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }

        }
        else if (choice == 3)
        {
            mp.clear();
            dfs_sltn = false;
            clock_t start = clock();
            IDS(initialEight, x, y, 0, NULL, goalEight, 40);
            double  runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
            cout << "\nTotal Nodes-->" << searchNodes[choice+1] << endl << "Solution Nodes-->" << solutionNodes[choice+1] << endl << endl;
            cout << "Elapsed Times " << runtime << " seconds\n\n\n" << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
        }
        else if (choice == 4)
        {
            mp.clear();
            clock_t start = clock();
            AstarSearch(initialEight, x, y, goalEight);
            double  runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
            cout << "\nTotal Nodes-->" << searchNodes[choice+2] << endl << "Solution Nodes-->" << solutionNodes[choice+2] << endl << endl;
            cout << "Elapsed Times " << runtime << " seconds\n\n\n" << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
        }
        else if (choice == 5) {
            mp.clear();
            clock_t start = clock();
            IDAStar(initialEight, x, y, goalEight);
            double  runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
            cout << "\nTotal Nodes-->" << searchNodes[choice+1] << endl << "Solution Nodes-->" << solutionNodes[choice+1] << endl << endl;
            cout << "Elapsed Times " << runtime << " seconds\n\n\n" << endl;
        }
        else if (choice == 6)
        {
            cout << "Running BFS" << endl << endl;
            mp.clear();
            BFS(initialEight, x, y, goalEight);
            cout << "\nTotal Nodes-->" << searchNodes[1] << endl << "Solution Nodes-->" << solutionNodes[1] << endl << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
            for (int i = 0; i < 8; i++) {
                solutionNodes[i] = 0;
                searchNodes[i] = 0;
            }

            cout << "Running DFS" << endl << endl;
            mp.clear();
            dfs_sltn = false;
            DFS(initialEight, x, y, 0, NULL, goalEight, 40);
            cout << "\nTotal Nodes-->" << searchNodes[3] << endl << "Solution Nodes-->" << solutionNodes[3] << endl << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
            for (int i = 0; i < 8; i++) {
                solutionNodes[i] = 0;
                searchNodes[i] = 0;
            }

            cout << "Running IDS" << endl << endl;
            mp.clear();
            dfs_sltn = false;
            IDS(initialEight, x, y, 0, NULL, goalEight, 40);
            cout << "\nTotal Nodes-->" << searchNodes[4] << endl << "Solution Nodes-->" << solutionNodes[4] << endl << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
            for (int i = 0; i < 8; i++) {
                solutionNodes[i] = 0;
                searchNodes[i] = 0;
            }


            cout << "Running A*" << endl << endl;
            mp.clear();
            AstarSearch(initialEight, x, y, goalEight);
            cout << "\nTotal Nodes-->" << searchNodes[6] << endl << "Solution Nodes-->" << solutionNodes[6] << endl << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
            for (int i = 0; i < 8; i++) {
                solutionNodes[i] = 0;
                searchNodes[i] = 0;
            }

            cout << "Running IDA*" << endl << endl;
            mp.clear();
            clock_t start = clock();
            IDAStar(initialEight, x, y, goalEight);
            double  runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
            cout << "\nTotal Nodes-->" << searchNodes[choice] << endl << "Solution Nodes-->" << solutionNodes[choice] << endl << endl;
            cout << "Elapsed Times " << runtime << " seconds\n\n\n" << endl;
            iterate = 0;
            for (int i = 0; i < 999999; i++) {
                track1[i] = NULL;
                track2[i] = NULL;
            }
            for (int i = 0; i < 8; i++) {
                solutionNodes[i] = 0;
                searchNodes[i] = 0;
            }


        }
        if (choice == 7) {
            break;
        }
        else
        {
            cout << "Please enter right option" << endl;


        }

        for (int i = 0; i < N + 5; i++)
        {
            searchNodes[i] = 0;
            solutionNodes[i] = 0;
        }

    }
    return 0;
}

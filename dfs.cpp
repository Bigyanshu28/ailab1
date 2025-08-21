#include<iostream>
#include<stack>
using namespace std;

const int goal[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
const int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
const char dirChar[] = {'U','D','L','R'};
const int factorial[] = {1,1,2,6,24,120,720,5040,40320};

struct Node {
    int state[3][3];
    Node* parent;
    string path;
};

bool visited[362880] = {false};

int getRank(const int s[3][3]) {  
    int f[9], r = 0;
    for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
        f[i*3+j] = s[i][j];
    
    for (int i=0; i<9; i++) {
        int c = 0;
        for (int j=i+1; j<9; j++)
            if (f[j] < f[i]) c++;
        r += c * factorial[8-i];
    }
    return r;
}

void printSolution(Node* n) {
    if (!n) return;
    printSolution(n->parent);
    static int step = 0;
    cout << "Step " << step++ << ":\n";
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) 
            cout << n->state[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void DFS(int start[3][3]) {
    stack<Node*> s;
    Node* root = new Node();
    for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
        root->state[i][j] = start[i][j];
    root->parent = 0;
    root->path = "";
    
    s.push(root);
    visited[getRank(start)] = true;
    
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        
        if (getRank(current->state) == getRank(goal)) {
            cout << "Solution found in " << current->path.size() << " moves: " << current->path << "\n\n";
            printSolution(current);
            return;
        }
        
        int x, y;
        for (x=0; x<3; x++) {
            bool found = false;
            for (y=0; y<3; y++)
                if (current->state[x][y] == 0) {
                    found = true;
                    break;
                }
            if (found) break;
        }
        
        for (int i=0; i<4; i++) {
            int nx = x+dx[i], ny = y+dy[i];
            if (nx<0 || nx>2 || ny<0 || ny>2) continue;
            
            Node* child = new Node();
            for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                child->state[i][j] = current->state[i][j];
            
            child->state[x][y] = child->state[nx][ny];
            child->state[nx][ny] = 0;
            
            int cr = getRank(child->state);
            if (!visited[cr]) {
                visited[cr] = true;
                child->parent = current;
                child->path = current->path + dirChar[i];
                s.push(child);
            }
            else delete child;
        }
    }
    cout << "No solution found.\n";
}

int main() {
    int start[3][3] = {{1,0,3},{4,2,6},{7,5,8}};
    DFS(start);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

char color[81];
char grid[9][9];
vector<int> g[81];
int backtracks;

bool dfs(int u) {
    if (u == 82) return true;
    if (color[u] != '.') return dfs(u+1);
    //checking which color to paint this node with
    for (char c='1';c<='9';c++) {
        bool check=true;
        //checking if this color is already used in the adj nodes
        for (int v : g[u]) {
            if (color[v]==c) {
                //if at all the color is used already
                //mark check as false and break out of the loop
                check=false;
                break;
            }
        }
        //if check is true, it means, we can
        //color this node with c temporarily
        if (check) {
            color[u]=c;
            //checking if 'c' results in a solved sudoku
            if (dfs(u+1)) return true;
            //if the control is passed on to here
            //it means, 'c' is not the correct color
            //as the result was not a solved sudoku
            //so we backtrack to here again, color c back to '.'
            //ans check next color, until the sudoku is solved
            color[u]='.';
            backtracks++;
        }
    }
    return false;
}

int main() {
    for (int i=0;i<81;i++) {
        color[i]='.';
    }
    cout<<"Input un-solved sudoku\n";
    for (int i=0;i<9;i++) {
        for (int j=0;j<9;j++) {
            cin>>grid[i][j];
            if (grid[i][j] != '.') {
                int idx=9*i+j;
                color[idx]=grid[i][j];
            }
        }
    }
    cout<<"\n" <<"Solved Sudoku: \n";
    clock_t start=clock();
    for (int i=0;i<9;i++) {
        for (int j=0;j<9;j++) {
            //vis:- to make sure there are no repetitions in the adjacent nodes
            unordered_map<int,bool> vis;
            int u=9*i+j;
            int x=(i/3)*3;
            int y=(j/3)*3;
            //nodes in same block
            for (int k=x;k<x+3;k++) {
                for (int l=y;l<y+3;l++) {
                    if (k==i && l==j) continue;
                    int v=9*k+l;
                    if (vis.count(v) == 0) {
                        g[u].push_back(v);
                        vis[v]=true;
                    }
                }
            }
            //nodes in same column
            for (int k=0;k<9;k++) {
                if (k==i) continue;
                int v=k*9+j;
                if (vis.count(v) == 0) {
                    g[u].push_back(v);
                    vis[v]=true;
                }
            }
            //nodes in same row
            for (int l=0;l<9;l++) {
                if (l==j) continue;
                int v=i*9+l;
                if (vis.count(v) == 0) {
                    g[u].push_back(v);
                    vis[v]=true;
                }
            }
        }
    }
    dfs(0);
    for (int i=0;i<9;i++) {
        for (int j=0;j<9;j++) {
            cout<<color[i*9+j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\nNumber of backtracks: "<<backtracks<<"\n";
    //colors:- set to count unique number of colors used
    //it lies in [1,9]
    set<char> colors;
    for (int i=0;i<9;i++) {
        for (int j=0;j<9;j++) {
            if (grid[i][j] == '.') {
                colors.insert(color[i*9+j]);
            }
        }
    }
    cout<<"\nNumber of colors: "<<(int)colors.size()<<"\n";
    clock_t stop=clock();
    cout<<"\nRun time:- "<<(stop-start)/(double)CLOCKS_PER_SEC<<" sec\n";
    return 0;
}
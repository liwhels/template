#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<queue>
using namespace std;
//二分图判定
//https://labuladong.gitee.io/algo/2/20/49/

class bipatitle{
private:
    bool ok = true;//是否是二分图
    vector<bool> color;
    vector<bool> visited;
public:
    bool isBipartite(vector<vector<int>>& graph){
        int len = graph.size();
        color.assign(len,false);
        visited.assign(len,false);
        for(int i=0li<len;i++){
            if(visited[i]) continue;
            traverse(graph,i);
            //bfs(graph,i);
        }


        return ok;
    }


    //DFS遍历
    void traverse(vector<vector<int>>& graph,int v){
        if(!ok) return;
        visited[v] = true;
        for(int w:graph[v]){
            if(!visited[w]){
                // 相邻节点 w 没有被访问过
                // 那么应该给节点 w 涂上和节点 v 不同的颜色
                color[w]=!color[v];
                //继续遍历
                traverse(graph,w);
            }else{
                // 相邻节点 w 已经被访问过
                // 根据 v 和 w 的颜色判断是否是二分图
                if(color[v]==color[w]){
                    ok = false;
                }
            }
        }

    }


    //bfs
    void bfs(vector<vector<int>>& graph,int v){
        queue<int> q;
        q.push(v);
        visited[v] = true;
        while(!q.empty){
            int node = q.front();
            q.pop();
            for(int w :graph[v]){
                if(visited[w]){
                    if(color[w]==color[v]){
                        ok = false;
                        break;
                    }
                }else{
                    visited[w]=true;
                    color[w]=!color[v];
                    q.push(w);
                }
            }
        }
    }
};

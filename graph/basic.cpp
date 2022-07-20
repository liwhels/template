#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
//DFS版本
//环检测算法
class Cycle{
public:
vector<bool> onPath;//visited 记录蛇经过过的格子，而 onPath 仅仅记录蛇身。
vector<bool> visited;
bool hasCycle = false;
public://numCourse节点数量 prerequisites邻接表
    bool canFinish(int numCourse,vector<vector<int>>&prerequisites){
        visited.assign(numCourse,false);
        onPath.assign(numCourse,false);
        for(int i=0;i<numCourse;i++){
            if(visited[i]) continue;
            traverse(i,prerequisites);
        }

        return hasCycle;
    }

    void traverse(int node,vector<vector<int>>&prerequisites){
        if(onPath[node]){
            hasCycle = true;
        }
        if(visited[node]||hasCycle){
            return ;
        }

        visited[node] = true;
        onPath[node] = true;
        for(auto t:prerequisites[node]){
            traverse(t,prerequisites);
        }
        onPath[node] = false;
    }

};

//拓扑排序 如果一个图是有向无环图可以进行拓扑排序
//DFS

class sortDfs{
public:
vector<bool> onPath;//visited 记录蛇经过过的格子，而 onPath 仅仅记录蛇身。
vector<bool> visited;
vector<int> postOrder;
bool hasCycle = false;
public://numCourse节点数量 prerequisites邻接表
    vector<int> findOrder(int numCourse,vector<vector<int>>&prerequisites){
        visited.assign(numCourse,false);
        onPath.assign(numCourse,false);
        for(int i=0;i<numCourse;i++){
            if(visited[i]) continue;
            traverse(i,prerequisites);
        }

        if(hasCycle) return [];
        reverse(postOrder.begin(),postOrder.end());
        return postOrder;
    }

    void traverse(int node,vector<vector<int>>&prerequisites){
        if(onPath[node]){
            hasCycle = true;
        }
        if(visited[node]||hasCycle){
            return ;
        }

        visited[node] = true;
        onPath[node] = true;
        for(auto t:prerequisites[node]){
            traverse(t,prerequisites);
        }

        //后续遍历位置
        postOrder.push_back(node);
        onPath[node] = false;
    }

};

//bfs版本
//通过节点的入读信息来进行遍历
class Bfs{
public:
    bool canFinishBfs(int numCourse,vector<vector<int>>& prerequisites){
        vector<int> inDegree(numCourse,0);//节点的入度信息
        for(int i=0;i<numCourse;i++){
            for(auto to:prerequisites[i]){
                inDegree[to]++;
            }
        }
        queue<int> q;
        for(int i=0;i<numCourse;i++){
            if(inDegree[i]==0){
                //0入度的点进入队列
                q.push(i);
            }
        }
        int count=0;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            count++;
            for(int next:prerequisites[node]){
                inDegree[next]--;
                if(inDegree[next]==0){
                    q.push(next);
                }
            }
        }

        return count==numCourse;//如果遍历完了，则没有成环
        
    }
};


//拓扑排序
class sortBfs{
public:
    vector<int> sortDegree(int numCourse,vector<vector<int>>& prerequisites){
        vector<int> inDegree(numCourse,0);//节点的入度信息
        for(int i=0;i<numCourse;i++){
            for(auto to:prerequisites[i]){
                inDegree[to]++;
            }
        }
        queue<int> q;
        for(int i=0;i<numCourse;i++){
            if(inDegree[i]==0){
                //0入度的点进入队列
                q.push(i);
            }
        }
        int count=0;
        vector<int> res;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            res.push_back(node);//弹出顺序即为拓扑排序结果
            count++;
            for(int next:prerequisites[node]){
                inDegree[next]--;
                if(inDegree[next]==0){
                    q.push(next);
                }
            }
        }

        if(count==numCourse){//如果遍历完了，则没有成环
            return [];
        }


        return res;
        
    }
};
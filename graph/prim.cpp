#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<queue>
using namespace std;
class Prim{

private:
    vector<bool> inMST;//记录是否在最小生成树的一部分
    int weight_sum = 0;
    vector<vector<vector<int>>> graph;
    struct node{
        int y;
        int distance;
        node(int b,int c){
            y = b;
            distance = c;
        }

        bool operator<(const node& a)const{
            return distance>a.distance;//小根堆
        }

    };
    priority_queue<node> que;

public:
    Prim(vector<vector<vector<int>>> &graph){
        this->graph = graph;
        int n = graph.size();
        inMST.resize(n,false);
        //从节点零开始分割
        inMST[0]=true;
        cout<<0<<" ";
        cut(0);

        while(!que.empty()){
            node edge = que.top();
            que.pop();
            int to = edge.y;
            cout<<to<<" ";
            int weight = edge.distance;
            if(!inMST[to]){
                weight_sum+=weight;
                inMST[to]=true;
                cut(to);
            }
        }
        cout<<endl;
    }

    void cut(int s){
        for(vector<int> edge:graph[s]){
            int to = edge[0];
            if(!inMST[to]){
                que.emplace(edge[0],edge[1]);
            }
        }
    }

    int weightSum(){
        return weight_sum;
    }

    bool allConnected(){
        for(int i=0;i<inMST.size();i++){
            if(!inMST[i]) return false;
        }

        return true;
    }

};

class Solution{
private:
   vector<vector<vector<int>>> graph;

public:
    //graph 邻接表
    int miniCost(int n,vector<vector<int>>& connections){
        buildGraph(n,connections);
        Prim prim(graph);
        if(!prim.allConnected()){
            return -1;
        }

        return prim.weightSum();

    }


    void buildGraph(int n,vector<vector<int>>& connections){
        graph.resize(n);
        for(vector<int>& connection:connections){
            int from = connection[0]-1;
            int to = connection[1]-1;
            int weight = connection[2];
            graph[from].push_back({to,weight});
            graph[to].push_back({from,weight});
        }
    }

   
};

int main(){
    Solution s;
    int N =3;
    vector<vector<int>> connections = {{1,2,5},{1,3,6},{2,3,1}};
    int weight_sum = s.miniCost(N,connections);
    cout<<weight_sum<<endl;


    return 0;

}
#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<queue>
using namespace std;


class Solution {
    struct node{
        int x;
        int dis;
        node(int a,int b){
            x = a;
            dis = b;
        }

        bool operator<(const node& a) const{
            return dis>a.dis;
        }
    };
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<vector<int>>> graph(n+1);
        for(vector<int> time:times){
            int from = time[0];
            int to = time[1];
            int weight =time[2];
            graph[from].push_back({to,weight});
        } 
        vector<int> dis(n+1);
        dis = dijkstra(k,graph,n);
        int res = 0;
        for(int i=1;i<=n;i++){ 
            if(dis[i]==INT_MAX){
                return -1;
            }

            res = max(res,dis[i]);
        }

        return res;
    }


    vector<int> dijkstra(int start,vector<vector<vector<int>>>& graph,int n){
        vector<int> disall(n+1,INT_MAX);
        disall[start]=0;
        priority_queue<node>  que;
        que.emplace(start,0);
        while(!que.empty()){
            node curnode = que.top();
            que.pop();
            int curnodeid = curnode.x;
            int dis = curnode.dis;
            if(dis>disall[curnodeid]){
                continue;
            } 
            for(vector<int> neighbor:graph[curnodeid]){
                int nextid = neighbor[0];
                int weight = neighbor[1];
                int distance = weight+disall[curnodeid];

                if(distance<disall[nextid]){
                    disall[nextid]=distance;
                    que.emplace(nextid,distance);
                }
            }   
        }

        return disall;
    }
};

int main(){
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n =4;
    int k =2;


    Solution s;
    int time = s.networkDelayTime(times,n,k);
    cout<<time<<endl;


    return time;
}
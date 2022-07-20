#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//插并集初始化每个节点父节点为自己，主要操作有合并，找父亲节点，（在找父亲节点的过程中进行路径压缩），
class UF{
private:
    int count;
    vector<int> parent;
public:

//初始化
    UF(int n){
        this->count = n;
        this->parent.resize(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }

//合并
    void Union(int p,int q){
        int rootp = find(p);
        int rootq = find(q);
        if(rootp==rootq){
            return ;
        }

        parent[rootq]=rootp;

        count--;

    }
//找父节点+路径压缩
    int find(int x){
        if(parent[x]!=x){
            parent[x]=find(parent[x]);
        }

        return parent[x];
    }
//判断两个节点是否相连
    bool connected(int p,int q){
        int rootp = find(p);
        int rootq = find(q);
        return rootp==rootq;
    }
//返回森林数量
    int Count(){
        return count;
    }


};

int main(){
    int N = 3;
    vector<vector<int>> connections = {{1,2,5},{1,3,6},{2,3,1}};
    UF uf(N+1);
    sort(connections.begin(),connections.end(),[](const vector<int>&a,const vector<int>& b){
        return a[2]<b[2];
    });
    int weight = 0;
    for(auto edge:connections){
        int a = edge[0];
        int b = edge[1];
        if(!uf.connected(a,b)){//检查两个节点是否在同一棵数中
            uf.Union(a,b);
            weight+=edge[2];
        }
    }
    int ans = uf.Count()==2?weight:-1;

    cout<<ans<<endl;

    return 0;
}
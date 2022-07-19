#include<iostream>
#include<vector>
//基于区间重叠对区间进行加减的更新操作
//https://leetcode.cn/problems/my-calendar-ii/
class MyCalendarTwo {
struct Node{
        Node* left;
        Node* right;
        int val;
        int add;
        Node(){
            val = 0;
            add = 0;
            left = nullptr;
            right = nullptr;
        }
    };
public:
    Node *root;
    int N = (int)1e9;
    MyCalendarTwo() {
        root = new Node();
    }
    bool book(int start, int end) {
        if(query(root,0,N,start,end-1)==2) return false;
        update(root,0,N,start,end-1,1);

        return true;
    }

    void update(Node* node,int start,int end,int l,int r,int val){
        if(l<=start && end<=r){
            node->val += val;
            node->add += val;

            return ;
        }
        int mid = (start+end)>>1;
        pushDown(node);
        if(l<=mid) update(node->left,start,mid,l,r,val);
        if(r>mid) update(node->right,mid+1,end,l,r,val);
        pushUp(node);
    }

    int query(Node* node,int start,int end,int l,int r){
        if(l<=start && r>=end) return node->val;
        int mid = (start+end)>>1,ans= 0;
        pushDown(node);
        if(l<=mid) ans = query(node->left,start,mid,l,r);
        if(r>mid) ans = max(ans,query(node->right,mid+1,end,l,r));

        return ans;
    }

    void pushUp(Node* node){
        node->val = max(node->left->val,node->right->val);
    }
    void pushDown(Node* node){
        if(node->left==nullptr) node->left = new Node();
        if(node->right==nullptr) node->right= new Node();
        node->left->val += node->add;
        node->right->val += node->add;

        node->left->add +=node->add;
        node->right->add += node->add;

        node->add = 0;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
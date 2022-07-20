#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

void process(vector<int>& nums){
    stack<int> s;
    //入栈
    s.push(0);
    for(int i=0;i<nums.size();i++){
        //维持栈的单调性(单调递减，那么出栈条件为栈头元素小于等于当前元素)
        while(!s.empty()&&nums[s.top()]<=nums[i]){
            int index = s.top();
            //做相应的处理
            s.pop();
        }

        //入栈
        s.push(i);
    }

    //返回答案
    return ;
}
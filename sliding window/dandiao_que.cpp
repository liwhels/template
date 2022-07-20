#include<iostream>
#include<vector>
#include<deque>
using namespace std;
https://leetcode.cn/problems/sliding-window-maximum/
/*
    滑动窗口最大值。(把元素下标存入队列中)
    1、队头出队，当队头元素滑出窗口时，队头元素出队
    2、队尾入队，
        1、直接入队：如果新元素小于队尾元素，直接入队
        2、先删后插：如果新元素大于等于队尾元素，删除队尾元素，直到队尾元素大于新元素，然后插入元素
    一直维持着队头对应的元素为当前窗口的最大元素
    时间复杂度为O(N)
*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int>  index;
        vector<int> res;
        for(int i=0;i<nums.size();i++){
            //对头出队
            if(!index.empty()&&i-index.front()>k-1) index.pop_front();

            while(!index.empty()&&nums[i]>=nums[index.back()]) index.pop_back();

            index.push_back(i);
            if(i>=k-1) res.push_back(nums[index.front()]);            
        }

        return res;
    }
};

/*
    滑动窗口+单调队列两。(把元素下标存入队列中)保持区间内数组有序(自然想到单调队列)
    https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
    ji窗口可以被nums[i]分为两部分，一部分为大于nums[i],一部分小于nums[i],因此可以维护两个单调队列，常数时间内获得目前窗口内的最大
    值和最小值，然后更新j
*/

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> Max,Min;
        int len = nums.size();
        int res=0;
        for(int i=0,j=0;i<len;i++){
            while(!Max.empty()&&nums[Max.back()]<=nums[i]){
                Max.pop_back();
            }
            while(!Min.empty()&&nums[Min.back()]>=nums[i]){
                Min.pop_back();
            }
            Min.push_back(i);
            Max.push_back(i);
            while(!Min.empty()&&!Max.empty()&&abs(nums[Max.front()]-nums[Min.front()])>limit){
                j++;
                if(Max.front()<j) Max.pop_front();
                if(Min.front()<j) Min.pop_front();
            }

            res = max(res,i-j+1);

        }
        return res;
    }
};
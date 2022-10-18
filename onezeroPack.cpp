#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <utility>
using namespace std;
int get_maxv(vector<int>& w,vector<int>& v,int W)
{
    // args:w表示每件物品的重量，v表示每件物品的价值，W表示背包的重量
    int dp[W+1]={0};
    for(int i=1;i<=w.size();i++)
    {
        for(int j=W;j>=w[i-1];j--)
        {
            dp[j]=(dp[j]>dp[j-w[i-1]]+v[i-1]?dp[j]:dp[j-w[i-1]]+v[i-1]);
        }
    }
    return dp[W];
}
int get_maxv1(vector<int>& w,vector<int>& v,int W)
{
    vector<vector<int>> dp(w.size()+1,vector<int>(W+1,0));
    for(int i=1;i<=w.size();i++)
    {
        for(int j=0;j<=W;j++)
        {
            if(j<w[i-1])
            {
                dp[i][j]=dp[i-1][j];
            }
            else{
                dp[i][j]=(dp[i-1][j]>dp[i-1][j-w[i-1]]+v[i-1]?dp[i-1][j]:dp[i-1][j-w[i-1]]+v[i-1]);
            }
        }
    }
    int start=W;
    for(int k=w.size();k>=1;k--)
    {
        if(dp[k][start]!=dp[k-1][start])
        {
            cout<<k<<" is selected!"<<endl;
            start=start-w[k-1];
        }
        if(start==0)
            break;
    }
    // for(int i=0;i<dp.size();i++){
    //     for(const auto& num: dp[i])
    //     {
    //         cout<<num<<" ";
    //     }
    //     cout<<endl;
    // }
    return dp[w.size()][W];
}
int main()
{
    vector<int> w={2,2,6,5,4};
    vector<int> v={6,3,5,4,6};
    int W=15;
    int res=get_maxv(w,v,W);
    cout<<res<<endl;
    int res1=get_maxv1(w,v,W);
    cout<<res1<<endl;
    return 0;
}
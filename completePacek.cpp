#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <utility>
using namespace std;

int get_max(vector<int> w,vector<int> v,int W)
{
    // args: w代表每件物品的重量，v代表每件物品的价值，W代表背包容量
    vector<vector<int>> dp(w.size()+1,vector<int>(W+1,0));
    for(int i=1;i<=w.size();i++)
    {
        for(int j=0;j<=W;j++)
        {
            if(j<w[i-1])
                dp[i][j]=dp[i-1][j];
            else
            {
                dp[i][j]=max(dp[i-1][j],dp[i][j-w[i-1]]+v[i-1]);
            }
        }
    }
    return dp[w.size()][W];
}
int get_max1(vector<int> w,vector<int> v,int W)
{
    vector<int> dp(W+1,0);
    for(int i=1;i<=w.size();i++)
    {
        for(int j=w[i-1];j<=W;j++)
        {
            dp[j]=max(dp[j],dp[j-w[i-1]]+v[i-1]);
        }
    }
    return dp[W];
}

int main()
{
     vector<int> w={2,2,6,5,4};
    vector<int> v={6,3,5,4,6};
    int W=10;
    int res=get_max(w,v,W);
    cout<<res<<endl;
    int res1=get_max1(w,v,W);
    cout<<res1<<endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <utility>
using namespace std;

//解决01背包问题
//状态转移方程：F[i][v]=max(F[i-1][v],F[i-1][v-C_i]+W_i
// 优化空间复杂度: F[v]=max(F[v],F[v-C_i]+W_i) v:W----->C_i
int V=15;   //设置背包重量
int N=5;    //设置物品件数
void ZeroOnePack(vector<int>& F, int C_i, int W_i)
{
    //args: F代表动态规划数组，用来存储状态；C_i表示当前物品的容积，W_i表示当前物品的价值
    for(int i=V;i>=C_i;i--)
    {
        F[i]=max(F[i],F[i-C_i]+W_i);
    }
}

int get_zeroonepack(vector<int> v, vector<int> w)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        ZeroOnePack(F, v[i-1], w[i-1]);
    }
    return F[V];
}

// 解决完全背包问题，物件种类是N,每个类别有无数件
//状态转移方程：F[i][v]=max(F[i-1][v],F[i-1][v-k*C_i]+k*W_i
// 优化空间复杂度: F[v]=max(F[v],F[v-k*C_i]+k*W_i) v:W----->C_i

// 改进状态转移方程，优化时间复杂度
// F[i][v]=max(F[i-1][v],F[i][v-C_i]+W_i
// 优化空间复杂度: F[v]=max(F[v],F[v-C_i]+W_i) v:C_i--------->W
void CompletePack(vector<int>& F, int C_i, int W_i)
{
    //args: F代表动态规划数组，用来存储状态；C_i表示当前物品的容积，W_i表示当前物品的价值
    for(int i=C_i;i<=V;i++)
    {
        F[i]=max(F[i],F[i-C_i]+W_i);
    }
}
int get_CompletePack(vector<int> v, vector<int> w)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        CompletePack(F, v[i-1], w[i-1]);
    }
    return F[V];
}
// 转化为01背包问题, 将第i件物品的每一个个体看作一个件，个体即种类。
int get_CompletePack_onezero(vector<int> v, vector<int> w)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        for(int j=1;j<=V/v[i-1];j++)
        {
            ZeroOnePack(F, v[i-1], w[i-1]);
        }
    }
    return F[V];
}

// 转化为01背包问题, 将第i件物品的每一个个体看作一个件，个体即种类。（采用二进制编码的思想，优化时间复杂度)
int get_CompletePack_onezero1(vector<int> v, vector<int> w)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        int k=1;
        int M=V/v[i-1]; //每件物品的数量上限
        while(k<M)
        {
            ZeroOnePack(F, k*v[i-1], k*w[i-1]);
            M=M-k;
            k=2*k;
        }
        ZeroOnePack(F, M*v[i-1], M*w[i-1]);
    }
    return F[V];
}

// 解决多层背包问题
// 转化为01背包问题
int get_ManyLevelPack(vector<int> v, vector<int> w, vector<int> m)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        for(int j=1;j<=min(V/v[i-1],m[i-1]);j++)
        {
            ZeroOnePack(F, v[i-1], w[i-1]);
        }
    }
    return F[V];
}
int get_ManyLevelPack1(vector<int> v, vector<int> w, vector<int> m)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        int k=1;
        int M=min(V/v[i-1],m[i-1]);
        while(k<M)
        {
            ZeroOnePack(F, k*v[i-1], k*w[i-1]);
            M=M-k;
            k=2*k;
        }
        ZeroOnePack(F, M*v[i-1], M*w[i-1]);
    }
    return F[V];
}

//解决混合背包问题
void zeroone_complete(vector<int>& F, int C_i, int W_i, int flag)
{
    // args: F表示状态数组，C_i表示物品的容积，W_i表示物品的价值，flag表示是否是01背包：0表示01背包，1表示完全背包
    if(!flag)
    {
        ZeroOnePack(F, C_i, W_i);
    }
    else
    {
        CompletePack(F, C_i, W_i);
    }
}
int get_zeroone_complete(vector<int> v, vector<int> w, vector<int> Flag)
{
    vector<int> F[V+1];
    for(int i=1;i<=v.size();i++)
    {
        zeroone_complete(F, v[i-1], w[i-1], Flag[i-1]);
    }
    return F[V];
}

// 解决三种混合背包问题
void three_pack(vector<int>& F, int C_i, int W_i, int M_i, int flag)
{
    if(!flag)
    {
        ZeroOnePack(F, C_i, W_i);   //01背包
    }
    else if(flag==1)
    {
        CompletePack(F, C_i, W_i);  //完全背包
    }
    else
    {   // 多层背包
        int k=1;
        int M=min(V/C_i,M_i);
        while(k<M)
        {
            ZeroOnePack(F, k*C_i, k*W_i);
            M=M-k;
            k=2*k;
        }
        ZeroOnePack(F, M*C_i, M*W_i);
    }
}

int get_three_pack(vector<int> v, vector<int> w, vector<int> m, vector<int> Flag)
{
    vector<int> F(V+1);
    for(int i=1;i<=v.size();i++)
    {
        three_pack(F, v[i-1], w[i-1], m[i-1], Flag[i-1])
    }
    return F[V];
}
// 解决二维背包问题，对每件物品增加了除容积外的另一项损失
// 增加一个维度

int main()
{
    vector<int> v={2,2,6,5,4};
    vector<int> w={6,3,5,4,6};
    vector<int> m={1,2,2,3,1};
    int res=get_ManyLevelPack(v, w, m);
    cout<<res<<endl;
    int res1=get_ManyLevelPack1(v, w, m);
    cout<<res1<<endl;
    return 0;
}
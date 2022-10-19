#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <utility>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <string.h>
using namespace std;

//设置背包容量
//  分组背包问题
//  定义：有k个组，每个组里的物件只能选一个，损失上限V, 每个物品的损失为v, 价值w，求最大价值
//  动态转移方程dp[i][j]=max(dp[i-1][j],dp[i-1][j-v_i_k]+w_i_k) 其中，v_i_k表示第i组的第k个物品
//  优化空间复杂度dp[j]=max(dp[j],dp[j-v_i_k]+w_i_k) j：V---->0

int get_GroupPack(int V, const vector<vector<int>>& v, const vector<vector<int>>& w)
{
    vector<int> dp(V+1,0);
    //cout<<w[1][1]<<endl;
    for(int i=1;i<=v.size();i++)
    {
        for(int j=V;j>=0;j--)
        {
            int max_v=dp[j];
            for(int k=0;k<v[i-1].size();k++)
            {
                if(j>=v[i-1][k])
                {
                    max_v=max(max_v,w[i-1][k]+dp[j-v[i-1][k]]);
                }
                    
            }
            dp[j]=max_v;
            //cout<<max_v<<endl;
        }
    }
    return dp[V];
}
// 有依赖背包问题：NOIP2006提高组 - 金明的预算方案
// 问题链接：https://blog.csdn.net/njuptACMcxk/article/details/105518551
// 输入格式
// 输入文件的第1行，为两个正整数，用一个空格隔开：N m，其中N表示总钱数，m为希望购买物品的个数。

// 从第2行到第m+1行，第j行给出了编号为j-1的物品的基本数据，每行有3个非负整数v p q，其中v表示该物品的价格，p表示该物品的重要度（1~5），q表示该物品是主件还是附件。

// 如果q=0，表示该物品为主件，如果q>0，表示该物品为附件，q是所属主件的编号。

void input()
{
    cout<<"****金明的预算方案****"<<endl;
    cout<<"请输入总钱数和希望购买物品的个数"<<endl;
    int N,m;
    cin>>N>>m;
    vector<int> v,p,q;
    for(int i=0;i<m;i++)
    {
        int v_i,p_i,q_i;
        cout<<"请输入第"<<i+1<<"件商品的价格、重要度、主件or附件"<<endl;
        cin>>v_i>>p_i>>q_i;
        v.push_back(v_i);
        p.push_back(p_i);
        q.push_back(q_i);
    }
    string sstr = "G:\\c++_projects\\compare_three_for\\data.txt";//定义文件路径
    
    ofstream fout(sstr);
    fout<<N<<" "<<m<<endl;
    for(int i=0;i<v.size();i++)
    {
        fout<<v[i]<<" "<<p[i]<<" "<<q[i]<<endl;
    }
}
// 每个主件最多有两个附件，共有4种状态: 只有主件；主件+附件1；主件+附件2；主件+附件1+附件2，将每个主件与对应的附件组合成一个组
// 组1：主件1；主件1+附件1；主件1+附件2；主件1+附件1+附件2；组2：主件2；主件2+附件1；主件2+附件2；主件2+附件1+附件2；...
//每组内只能选择一个，可以选择多组；分组背包问题
// 数据预处理：分组：
pair<vector<vector<int>>,vector<vector<int>>> divide_group(int m, const vector<int>& v, const vector<int>& p, const vector<int>& q)
{
    unordered_map<int,vector<int>> my_map;
    for(int i=0;i<m;i++)
    {
        if(q[i]==0)
        {
            my_map[i+1].push_back(i+1);
        }
        else
        {
            my_map[q[i]].push_back(i+1);
        }
    }
    vector<vector<int>> v1(my_map.size()),w1(my_map.size());
    int j=0;
    //cout<<my_map.size()<<endl;
    for(auto iter=my_map.begin();iter!=my_map.end();iter++)
    {
        for(const auto& num:iter->second)
        {
            cout<<num<<" ";
        }
        cout<<endl;
        
        v1[j].push_back(v[iter->first-1]);
        w1[j].push_back(v[iter->first-1]*p[iter->first-1]);
        
        
        if(iter->second.size()==2)
        {
            if(iter->second[0]==iter->first)
            {
                v1[j].push_back(v[iter->second[1]-1]+v[iter->first-1]);
                w1[j].push_back(v[iter->second[1]-1]*p[iter->second[1]-1]+v[iter->first-1]*p[iter->first-1]);
            }
            else
            {
                v1[j].push_back(v[iter->second[0]-1]+v[iter->first-1]);
                w1[j].push_back(v[iter->second[0]-1]*p[iter->second[0]-1]+v[iter->first-1]*p[iter->first-1]);
            }
        }
        if(iter->second.size()==3)
        {
            if(iter->second[0]==iter->first)
            {
                v1[j].push_back(v[iter->second[1]-1]+v[iter->first-1]);
                v1[j].push_back(v[iter->second[2]-1]+v[iter->first-1]);
                v1[j].push_back(v[iter->second[1]-1]+v[iter->second[2]-1]+v[iter->first-1]);
                w1[j].push_back(v[iter->second[1]-1]*p[iter->second[1]-1]+v[iter->first-1]*p[iter->first-1]);
                w1[j].push_back(v[iter->second[2]-1]*p[iter->second[2]-1]+v[iter->first-1]*p[iter->first-1]);
                w1[j].push_back(v[iter->second[1]-1]*p[iter->second[1]-1]+v[iter->second[2]-1]*p[iter->second[2]-1]+v[iter->first-1]*p[iter->first-1]);
            }
            else if(iter->second[1]==iter->first)
            {
                v1[j].push_back(v[iter->second[0]-1]+v[iter->first-1]);
                v1[j].push_back(v[iter->second[2]-1]+v[iter->first-1]);
                v1[j].push_back(v[iter->second[0]-1]+v[iter->second[2]-1]+v[iter->first-1]);
                w1[j].push_back(v[iter->second[0]-1]*p[iter->second[0]-1]+v[iter->first-1]*p[iter->first-1]);
                w1[j].push_back(v[iter->second[2]-1]*p[iter->second[2]-1]+v[iter->first-1]*p[iter->first-1]);
                w1[j].push_back(v[iter->second[0]-1]*p[iter->second[0]-1]+v[iter->second[2]-1]*p[iter->second[2]-1]+v[iter->first-1]*p[iter->first-1]);
            }
            else if(iter->second[2]==iter->first)
            {
                v1[j].push_back(v[iter->second[0]-1]+v[iter->first-1]);
                v1[j].push_back(v[iter->second[1]-1]+v[iter->first-1]);
                v1[j].push_back(v[iter->second[0]-1]+v[iter->second[1]-1]+v[iter->first-1]);
                w1[j].push_back(v[iter->second[0]-1]*p[iter->second[0]-1]+v[iter->first-1]*p[iter->first-1]);
                w1[j].push_back(v[iter->second[1]-1]*p[iter->second[1]-1]+v[iter->first-1]*p[iter->first-1]);
                w1[j].push_back(v[iter->second[0]-1]*p[iter->second[0]-1]+v[iter->second[1]-1]*p[iter->second[1]-1]+v[iter->first-1]*p[iter->first-1]);
            }
        }
        j++;
    }
    pair<vector<vector<int>>,vector<vector<int>>> res(v1,w1);
    return res; 
}

pair<vector<vector<int>>,vector<vector<int>>> readTxt(string file)
{
    ifstream infile; 
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

    string s;
    vector<int> v,p,q;
    int N,m;
    int row=0;
    while(getline(infile,s))
    {
        cout<<s<<endl;
        row++;
        if(row==1)
        {
            int i=0;
            int counter=0;
            while(i<s.size())
            {
                int sum=0;
                while(s[i]>='0'&&s[i]<='9')
                {
                    sum=sum*10+s[i]-'0';
                    i++;
                }
                while(s[i]==' '&&i<s.size())
                {
                    i++;
                }
                counter++;
                if(counter==1)
                    N=sum;
                else if(counter==2)
                    m=sum;
            }
        }
        else{
            int i=0;
            int counter=0;
            while(i<s.size())
            {
                int sum=0;
                while(s[i]>='0'&&s[i]<='9')
                {
                    sum=sum*10+s[i]-'0';
                    i++;
                }
                while(s[i]==' '&&i<s.size())
                {
                    i++;
                }
                counter++;
                if(counter==1)
                    v.push_back(sum);
                else if(counter==2)
                    p.push_back(sum);
                else
                    q.push_back(sum);
            }
        }
        
    }
    //cout<<endl;
    // for(int i=0;i<v.size();i++)
    // {
    //     cout<<v[i]<<" ";
    // }
    // cout<<endl;
    infile.close();             //关闭文件输入流 
    pair<vector<vector<int>>,vector<vector<int>>> data=divide_group(m,v,p,q);
    return data;
}
int read_N(string file)
{
    ifstream infile; 
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

    string s;
    vector<int> v,p,q;
    int N,m;
    int row=0;
    while(getline(infile,s))
    {
        cout<<s<<endl;
        row++;
        if(row==1)
        {
            int i=0;
            int counter=0;
            while(i<s.size())
            {
                int sum=0;
                while(s[i]>='0'&&s[i]<='9')
                {
                    sum=sum*10+s[i]-'0';
                    i++;
                }
                while(s[i]==' '&&i<s.size())
                {
                    i++;
                }
                counter++;
                if(counter==1)
                    N=sum;
                else if(counter==2)
                    m=sum;
            }
            break;
        }
        else{
            int i=0;
            int counter=0;
            while(i<s.size())
            {
                int sum=0;
                while(s[i]>='0'&&s[i]<='9')
                {
                    sum=sum*10+s[i]-'0';
                    i++;
                }
                while(s[i]==' '&&i<s.size())
                {
                    i++;
                }
                counter++;
                if(counter==1)
                    v.push_back(sum);
                else if(counter==2)
                    p.push_back(sum);
                else
                    q.push_back(sum);
            }
        }
        
    }
    //cout<<endl;
    // for(int i=0;i<v.size();i++)
    // {
    //     cout<<v[i]<<" ";
    // }
    // cout<<endl;
    infile.close();             //关闭文件输入流 
    return N;
}
// 使用分组背包问题求解：
int get_result()
{
    pair<vector<vector<int>>,vector<vector<int>>> data=readTxt("G:\\c++_projects\\compare_three_for\\data.txt");
    // for(int i=0;i<data.second.size();i++)
    // {
    //     for(int j=0;j<data.second[i].size();j++)
    //     {
    //         cout<<data.second[i][j]<<" ";

    //     }
    //     cout<<endl;
    // }
    int V=read_N("G:\\c++_projects\\compare_three_for\\data.txt");
    int res=get_GroupPack(V,data.first,data.second);
    cout<<"最大价值："<<res<<endl;
    return res;
}
int main()
{
    input();
    int res=get_result();
    return 0;
}
#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <utility>
using namespace std;

class pack_problem
{
    private:
    int V;  //背包容积
    vector<int> w;  //物品价值
    vector<int> v;  //物品重量
    vector<int> s;  //物品数量
    public:
    pack_problem()
    {
        V=0;
        w={0};
        v={0};
        s={0};
    }
    void input()
    {
        w.clear();
        v.clear();
        s.clear();
        int V_1,w1,v1,s1,n;
        cout<<"please input V:"<<endl;
        cin>>V_1;
        V=V_1;
        cout<<"please input the nums of object:"<<endl;
        cin>>n;
        while(n)
        {
            cout<<"please input w:"<<endl;
            cin>>w1;
            cout<<"please input v"<<endl;
            cin>>v1;
            cout<<"please input s"<<endl;
            cin>>s1;
            w.push_back(w1);
            v.push_back(v1);
            s.push_back(s1);
            n--;
        }
        cout<<"the input action is finished!"<<endl;
    }
    void display()
    {
        cout<<"V:"<<V<<endl;
        cout<<"v:"<<endl;
        for(const auto& num: v)
        {
            cout<<num<<" ";
        }
        cout<<endl;
        cout<<"w:"<<endl;
        for(const auto& num: w)
        {
            cout<<num<<" ";
        }
        cout<<endl;
        cout<<"s:"<<endl;
        for(const auto& num: s)
        {
            cout<<num<<" ";
        }
        cout<<endl;
    }
    int  out_V()
    {
        return V;
    }
    vector<int> out_v()
    {
        return v;
    }
    vector<int> out_w()
    {
        return w;
    }
    vector<int> out_s()
    {
        return s;
    }
};

int get_max(vector<int> w,vector<int> v,vector<int> s,int V)
{
    vector<vector<int>> dp(w.size()+1,vector<int>(V+1,0));
    for(int i=1;i<=w.size();i++)
    {
        for(int j=0;j<=V;j++)
        {
            
            int max_v=0;
            for(int k=0;k<=min(V/v[i-1],s[i-1]);k++)
            {
                if(j<k*v[i-1])
                {
                    max_v=dp[i-1][j];
                    break;
                }
                else
                {
                    if(dp[i-1][j-k*v[i-1]]+k*w[i-1]>max_v)
                    {
                        max_v=dp[i-1][j-k*v[i-1]]+k*w[i-1];
                    }

                }

            }
            dp[i][j]=max_v;
            
        }
    }
    return dp[w.size()][V];
}
int main()
{
    pack_problem my_pack;
    my_pack.input();
    my_pack.display();
    int res=get_max(my_pack.out_w(),my_pack.out_v(),my_pack.out_s(),my_pack.out_V());
    cout<<res<<endl;
    return 0;
}
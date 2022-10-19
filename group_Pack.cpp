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

//���ñ�������
//  ���鱳������
//  ���壺��k���飬ÿ����������ֻ��ѡһ������ʧ����V, ÿ����Ʒ����ʧΪv, ��ֵw��������ֵ
//  ��̬ת�Ʒ���dp[i][j]=max(dp[i-1][j],dp[i-1][j-v_i_k]+w_i_k) ���У�v_i_k��ʾ��i��ĵ�k����Ʒ
//  �Ż��ռ临�Ӷ�dp[j]=max(dp[j],dp[j-v_i_k]+w_i_k) j��V---->0

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
// �������������⣺NOIP2006����� - ������Ԥ�㷽��
// �������ӣ�https://blog.csdn.net/njuptACMcxk/article/details/105518551
// �����ʽ
// �����ļ��ĵ�1�У�Ϊ��������������һ���ո������N m������N��ʾ��Ǯ����mΪϣ��������Ʒ�ĸ�����

// �ӵ�2�е���m+1�У���j�и����˱��Ϊj-1����Ʒ�Ļ������ݣ�ÿ����3���Ǹ�����v p q������v��ʾ����Ʒ�ļ۸�p��ʾ����Ʒ����Ҫ�ȣ�1~5����q��ʾ����Ʒ���������Ǹ�����

// ���q=0����ʾ����ƷΪ���������q>0����ʾ����ƷΪ������q�����������ı�š�

void input()
{
    cout<<"****������Ԥ�㷽��****"<<endl;
    cout<<"��������Ǯ����ϣ��������Ʒ�ĸ���"<<endl;
    int N,m;
    cin>>N>>m;
    vector<int> v,p,q;
    for(int i=0;i<m;i++)
    {
        int v_i,p_i,q_i;
        cout<<"�������"<<i+1<<"����Ʒ�ļ۸���Ҫ�ȡ�����or����"<<endl;
        cin>>v_i>>p_i>>q_i;
        v.push_back(v_i);
        p.push_back(p_i);
        q.push_back(q_i);
    }
    string sstr = "G:\\c++_projects\\compare_three_for\\data.txt";//�����ļ�·��
    
    ofstream fout(sstr);
    fout<<N<<" "<<m<<endl;
    for(int i=0;i<v.size();i++)
    {
        fout<<v[i]<<" "<<p[i]<<" "<<q[i]<<endl;
    }
}
// ÿ�������������������������4��״̬: ֻ������������+����1������+����2������+����1+����2����ÿ���������Ӧ�ĸ�����ϳ�һ����
// ��1������1������1+����1������1+����2������1+����1+����2����2������2������2+����1������2+����2������2+����1+����2��...
//ÿ����ֻ��ѡ��һ��������ѡ����飻���鱳������
// ����Ԥ�������飺
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
    infile.open(file.data());   //���ļ����������ļ��������� 
    assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

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
    infile.close();             //�ر��ļ������� 
    pair<vector<vector<int>>,vector<vector<int>>> data=divide_group(m,v,p,q);
    return data;
}
int read_N(string file)
{
    ifstream infile; 
    infile.open(file.data());   //���ļ����������ļ��������� 
    assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

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
    infile.close();             //�ر��ļ������� 
    return N;
}
// ʹ�÷��鱳��������⣺
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
    cout<<"����ֵ��"<<res<<endl;
    return res;
}
int main()
{
    input();
    int res=get_result();
    return 0;
}
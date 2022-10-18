#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;
unordered_set<int> my_hash;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
unordered_map<int,Node*> my_map;
// 采用递归遍历无向图
void digui(Node* root)
{
    if(my_hash.find(root->val)==my_hash.end())
    {
        my_hash.emplace(root->val);
        cout<<root->val<<endl;
    }
    int cnt=0;
    int key=root->neighbors.size();
    if(key)
    {
        for(const auto& p: root->neighbors)
        {
            if(my_hash.find(p->val)==my_hash.end())
            {
                my_hash.emplace(p->val);
                cout<<p->val<<endl;
                digui(p);
            }
            else
            {
                cnt++;
            }
        }
        if(cnt==key)
            return;
    }
}
// 定义一个深度拷贝构造函数

void cloneGraph(Node* node) {
    if(my_map.find(node->val)==my_map.end())
    {
        Node* cp=new Node(node->val);
        my_map.emplace(pair<int,Node*>(node->val,cp));
    }
        
    int n=node->neighbors.size();
    int cnt=0;
    if(n)
    {
        for(int i=0;i<n;i++)
        {
            Node* cur=node->neighbors[i];
            int num=cur->val;
            if(my_map.find(num)==my_map.end())
            {
                Node* cp1=new Node(num);
                my_map.emplace(pair<int,Node*>(num,cp1));
                Node* cp1_root=my_map.find(node->val)->second;
                cp1_root->neighbors.push_back(cp1);
                cloneGraph(cur);
            }
            else
            {
                Node* cp1=my_map.find(num)->second;
                Node* cp1_root=my_map.find(node->val)->second;
                cp1_root->neighbors.push_back(cp1);
                cnt++;
            }
        }
        if(cnt==n)
            return;
    }
}
Node* returnclone(Node* node) {
    Node* cp=new Node(1);
    my_map.emplace(pair<int,Node*>(1,cp));
    cloneGraph(node);
    return cp;
}
int main() {
    // 构造图
    Node* root=new Node(1);
    Node* a=new Node(2);
    Node* b=new Node(3);
    Node* c=new Node(4);
    Node* d=new Node(5);
    root->neighbors=vector<Node*>({a,b,d});
    a->neighbors=vector<Node*>({root,c,d});
    b->neighbors=vector<Node*>({root,c,d});
    c->neighbors=vector<Node*>({a,b,d});
    d->neighbors=vector<Node*>({root,a,b,c});
    digui(root);    //输出图的值
    Node* res=returnclone(root);
    my_hash.clear();
    digui(res);
    //cout<<my_hash.size()<<endl;
    return 0;

}
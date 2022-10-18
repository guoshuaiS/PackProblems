#include <iostream>
#include <vector>
#include <stdio.h>
#include "time.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList(Node* head) {
    // 哈希表统计每个结点的random,键为结点，值为标签
    unordered_map<Node*,int> map1;
    Node* cur=head;
    int i=-1;
    while(cur)
    {
        i++;
        map1[cur]=i;
        cur=cur->next;
    }
    int hash[i+1];
    cur=head;
    int count=0;
    while(cur)
    {
        if(cur->random==nullptr)
            hash[count]=-1;
        else
            hash[count]=map1[cur->random];
        count++;
        cur=cur->next;
    }
    // 将链表逆置
    Node* prev=nullptr;
    cur=head;
    while(cur)
    {
        Node* temp=cur->next;
        cur->next=prev;
        prev=cur;
        cur=temp;
    }
    // 此时prev是逆置后的头节点
    cur=prev;
    Node* nextnode=nullptr;
    while(cur)
    {
        Node* clonenode=new Node(cur->val);
        clonenode->next=nextnode;
        nextnode=clonenode;
        cur=cur->next;
    }
    // 此时clonenode和nextnode均是复制后的头结点
    // 下面补全random指针
    unordered_map<int,Node*> map2;
    cur=nextnode;
    int count1=-1;
    while(cur)
    {
        count1++;
        map2[count1]=cur;
        cur=cur->next;
    }
    cur=nextnode;
    int j=0;
    while(cur)
    {
        if(hash[j]!=-1)
        {
            cur->random=map2[hash[j]];
        }
        cur=cur->next;
        j++;
    }
    return nextnode;
}
Node* copy1RandomList(Node* head) {
    // 哈希表统计每个结点的random,键为结点，值为标签
    unordered_map<Node*,int> map1;
    Node* cur=head;
    int i=-1;
    while(cur)
    {
        i++;
        map1[cur]=i;
        cur=cur->next;
    }
    int hash[i+1];
    cur=head;
    int count=0;
    while(cur)
    {
        if(cur->random==nullptr)
            hash[count]=-1;
        else
            hash[count]=map1[cur->random];
        count++;
        cur=cur->next;
    }
    // 拷贝成逆置链表
    Node* prev=nullptr;
    cur=head;
    while(cur)
    {
        Node* clonenode=new Node(cur->val);
        clonenode->next=prev;
        prev=clonenode;
        cur=cur->next;
    }
    // 此时prev是拷贝逆置后的头节点(拷贝后的尾结点),接下来逆置
    cur=prev;
    Node* prevnode=nullptr;
    while(cur)
    {
        Node* temp=cur->next;
        cur->next=prevnode;
        prevnode=cur;
        cur=temp;
    }// prevnode是copy链表的头节点
    // 下面补全random指针
    unordered_map<int,Node*> map2;
    cur=prevnode;
    int count1=-1;
    while(cur)
    {
        count1++;
        map2[count1]=cur;
        cur=cur->next;
    }
    cur=prevnode;
    int j=0;
    while(cur)
    {
        if(hash[j]!=-1)
        {
            cur->random=map2[hash[j]];
        }
        cur=cur->next;
        j++;
    }
    return prevnode;
}
void readList(Node* head)
{
    Node* cur=head;
    while(cur)
    {
        cout<<cur->val<<endl;
        cur=cur->next;
    }
}
int main() {
    Node* head=new Node(2);
    Node* node1=new Node(1);
    Node* node2=new Node(1);
    Node* node3=new Node(4);
    Node* node4=new Node(0);
    head->next=node1;
    head->random=node3;
    node1->next=node2;
    node1->random=head;
    node2->next=node3;
    node3->next=node4;
    node4->random=node3;
    readList(head);
    Node* copyhead=copy1RandomList(head);
    readList(copyhead);
    readList(head);
    return 0;
}
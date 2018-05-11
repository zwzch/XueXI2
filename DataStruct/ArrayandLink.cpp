//
// Created by zw on 18-3-10.
//
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include "iostream"
using  namespace std;
struct Node{
    int  Data;
    struct Node* next;
};

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

    }
};
Node * createNode(int data){
    Node * node = NULL;
    node = (Node *) malloc(sizeof(Node));
    if(node == NULL){
        printf("malloc fair!\n");
    }
    memset(node,0,sizeof(Node));
    node->next  = NULL;
    node->Data = data;
    return node;
}
int AddNode(Node * pnode, int Data){
    while (pnode->next!=NULL){
        pnode = pnode->next;
    }
    Node * newNode = createNode(Data);
    pnode->next = newNode;
    return 0;
}
int  display(Node * pnode){
    while (1){
        cout<<pnode->Data <<endl;
        if(pnode->next==NULL){
            break;
        }
        pnode = pnode->next;
    }
    return 0;
}
Node * Transfer1(Node * pnode){
    if (pnode==NULL) return NULL;
    else if(pnode->next == NULL)
        return pnode;
    Node *node = Transfer1(pnode->next);
    if (node !=NULL ){
        node->next = node;
        pnode->next = NULL;
    }
    return pnode;
}
Node * Transfer2(Node * pnode){
    Node * ret = NULL;
    Node * p = NULL;
    Node * pr = NULL;
    p = pnode;
    while(p){
        pr = p->next;
        p->next = ret;
        //反向移动指针
        ret = p;
        p = pr;
    }
    return ret;















//        Node *  head = (Node *) malloc(sizeof(Node));
//        head->Data = 0;
//        head->next = pnode;
//        Node * p;
//        Node *q;
//        Node *pr;
//        p = head->next;
//        q = NULL;
//        head->next = NULL;
//        while(p){
//            pr = p->next;
//            p->next = q;
//            q = p;
//            p = pr;
//        }
//
//        return q;
}
int DelNode(Node * pnode, int data){
    while (pnode->next!=NULL){
        if (pnode->next->Data == data){
            Node * tmp = pnode->next;
            pnode->next = pnode->next->next;
            free(tmp);
        }
        pnode = pnode->next;
    }
    return 0;
}
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{

}



int ArrayAndLinked(){
//    int arr[] = {1,2,3,4,5};
//    int arr2[5];
//    arr2[0]=12;
//    for (int i = 0; i < 5; ++i) {
//        cout<<arr2[i]<<endl;
//    }
//    int  data = 99;
//
//    Node * pnode = createNode(data);
////    cout<<pnode->Data<<endl;
//
//    AddNode(pnode,100);
//    AddNode(pnode,101);
////    DelNode(pnode,100);
//    display(pnode);
//
//    display(Transfer2(pnode));
////    free(pnode);
//    return 0;
}




struct ListNode{
    int val;
    ListNode * next;
    ListNode(int x): val(x),next(NULL){};
};

struct RandomListNode{
    int  label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL),random(NULL){}
};
RandomListNode * copyRandomList(RandomListNode *head){
    //复制随机链表 需要两个映射关系  map和vector
    std::map<RandomListNode*,int >nodemap;
    std::vector<RandomListNode *> nodevec;
    RandomListNode *ptr = head;
    int  i = 0;
    while (ptr){
        nodevec.push_back(new RandomListNode(ptr->label));
        nodemap[ptr] = i;
        ptr = ptr->next;
        i++;
    }
    nodevec.push_back(0);
    ptr=head;
    i=0;
    while (ptr){
        nodevec[i]->next = nodevec[i+1];
        if (ptr->random){
            int  id = nodemap[ptr->random];
            nodevec[i]->random = nodevec[id];
        }
        ptr = ptr->next;
        i++;
    }
    return nodevec[0];
}

ListNode * mergeTwoLists(ListNode * l1,ListNode * l2){
    //合并两个链表
    ListNode  temp_head(0);
    ListNode *pre = &temp_head;
    while (l1 && l2){
        if (l1->val < l2->val){
            pre->next = l1;
            l1 = l1->next;
        } else{
            pre->next = l2;
            l2 = l2->next;
        }
        pre = pre->next;
    }
    if (l1){
        pre->next=l1;
    }
    if (l2){
        pre->next = l2;
    }
}
ListNode * mergeKLists(std::vector<ListNode *> &lists){
    //合并多个链表 分治法

//    if (lists.size() == 0){
//        return NULL;
//    }
//    if (lists.size() == 1){
//        return lists[1];
//    }
//    if (lists.size() ==2){
//        return  mergeTwoLists(Lists[0],);
//    }
}


//链表逆置嗷
ListNode * reverseList(ListNode * head){
    //就地逆置
    ListNode * newHead = NULL;
    ListNode *Next = NULL;
    while (head) {
        Next = head->next;
        //next保存下一个值
        head->next = newHead;
        //新链表头插法
        newHead  = head;
        //新链表指向头
        head = Next;
        //旧链表下移
    }
    return newHead;
}
ListNode * reverseList2(ListNode *head){
    //头插法
    ListNode *temp_head = (ListNode *) malloc(sizeof (ListNode *));
    while  (head){
        ListNode *Next = head->next;
        head->next = temp_head->next;
        temp_head->next = head;
        head = Next;
    }
    return temp_head->next;
}
ListNode * detectCycle(ListNode *head){
    //set求环
    std::set<ListNode *> node_set;
    while (head){
        if (node_set.find(head)!=node_set.end()){
            return head;
        }
        node_set.insert(head);
        head = head->next;
    }
    return NULL;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    ListNode *fast = pHead;
    ListNode *slow = pHead;
    ListNode *meet = NULL;//相遇的结点
    while (fast){
        slow = slow->next;
        fast = fast->next;
        if (!fast){//如果走一步到了没有环的尾部
            return NULL;
        }
        fast = fast->next;
        if (fast==slow){
            meet = fast;
            break;
        }
    }
    if (meet == NULL){
        return  NULL;
    }

    //两边互相走 来寻找环的开始
    while (pHead && meet){
        if (meet==pHead)
            return pHead;
        pHead = pHead->next;
        meet = meet->next;
    }
    return NULL;

}
ListNode * detectCycle2(ListNode *head){
    //快慢指针求环 时间复杂度 线性时间复杂度
    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *meet = NULL;//相遇的结点
    while (fast){
        slow = slow->next;
        fast = fast->next;
        if (!fast){//如果走一步到了没有环的尾部
            return NULL;
        }
        fast = fast->next;
        if (fast==slow){
            meet = fast;
            break;
        }
    }
    if (meet == NULL){
        return  NULL;
    }

    //两边互相走 来寻找环的开始
    while (head && meet){
        if (meet==head)
            return head;
        head = head->next;
        meet = meet->next;
    }
    return NULL;
}




//ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB){
//
//}
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){

    //寻找交叉结点 空间复杂度On
    std::set<ListNode *>  node_set;
    while (headA){
        node_set.insert(headA);
        headA = headA->next;
    }
    while (headB){
        if (node_set.find(headB)!=node_set.end()){
            return headB;
        }
        headB=headB->next;
    }
    return NULL;
}


ListNode * resverseBtween(ListNode* head, int m , int n){
    //中间逆置
    int  count = 1;
    ListNode * pre_ListNode;
    ListNode * cur_ListNode;
    pre_ListNode = NULL;
    cur_ListNode = head;
    while (count!=m){
        count++;
        pre_ListNode = cur_ListNode;
        cur_ListNode = cur_ListNode->next;
    }
//    cout<<cur_ListNode->val<<endl;
    ListNode * newHead = NULL;
    ListNode * modifyHead = cur_ListNode;
    ListNode *Next = NULL;
    int  i =0;
    int  len = n-m+1;
    for  (;i<len;i++){
        count++;
        Next = cur_ListNode->next;
        //next保存下一个值
        cur_ListNode->next = newHead;
        //新链表头插法
        newHead = cur_ListNode;
        //新链表指向头
        cur_ListNode = Next;
        //旧链表下移
    }


    modifyHead->next = Next;

    //如果从一开始逆置
    if (pre_ListNode) {
        pre_ListNode->next = newHead;
    } else{
        head = newHead;
    }
    return head ;
}

ListNode * partition(ListNode * head, int x){
    //partation函数
    ListNode * start = head;
    ListNode * Low = (ListNode *) malloc(sizeof(ListNode * ));
    ListNode * LowPtr = Low;
    ListNode * High = (ListNode *) malloc(sizeof(ListNode * ));
    ListNode * HighPtr = High;
    while (head){
        if (head->val>=x){
            HighPtr->next = head;
            HighPtr = HighPtr->next;
//            HighPtr->next = NULL;
        } else{
            LowPtr->next = head;
            LowPtr = LowPtr->next;
//            LowPtr->next = NULL;
        }
        head = head->next;
    }
    LowPtr->next = High->next;
    HighPtr->next = NULL;
    return Low->next;
}
ListNode* deleteDuplication(ListNode* pHead)
{
//    std::map<int ,ListNode *> map1;
    ListNode * ptr = pHead;
    std::vector<int > val_vector ;
    std::vector<ListNode *>  list_vector;

    while (ptr){
//        if (map1.)
//        map1.insert(pair<int, ListNode *>(ptr->val, ptr));
        if(list_vector.empty() && val_vector.empty()){
            list_vector.push_back(ptr);
            val_vector.push_back(ptr->val);
            ptr=ptr->next;
            continue;

        } else if (val_vector.back()==ptr->val)
        {
                    val_vector.pop_back();
                    list_vector.pop_back();
        } else{
            val_vector.push_back(ptr->val);
            list_vector.push_back(ptr);
        }
//        cout<<val_vector.back()<<endl;
        ptr=ptr->next;
    }
    ListNode * head = list_vector[0];
    ListNode * pptr = head;
    for (size_t i = 0; i < list_vector.size(); i++) {
        pptr->next = list_vector.at(i);
        pptr = pptr->next;
//        cout << val_vector.at(i) << endl;
    }
    return head;
//    std::map<int ,ListNode *>::iterator iter;
//    for(iter = map1.begin(); iter != map1.end(); iter++)

//        cout<<iter->first<<' '<<iter->second<<endl;
}
int  ListTest(){
    ListNode a(1);
    ListNode b(2);
//    b.val=10;
    ListNode c(3);
//    c.val = 30;
    ListNode d(3);
//    d.val = 44;
    ListNode e(4);
//    e.val = 23;
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = NULL;
    ListNode *head = &a;
head =     deleteDuplication(head);
//    head =  partition(head,30);
////   head=  resverseBtween(head,1,30);
    while (head){
        cout<<head->val<<endl;
        head = head->next;
    }
    return 0;
}

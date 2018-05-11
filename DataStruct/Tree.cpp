//
// Created by zw on 18-3-23.
//

# include "iostream"
using namespace std;
typedef struct BinaryTreeNode
{
    int data;
    struct BinaryTreeNode *Left;
    struct BinaryTreeNode *Right;
}Node;


Node* createBinaryTree()
{
    Node *p;
    int ch;
    cin>>ch;
    if(ch == 0)     //如果到了叶子节点，接下来的左、右子树分别赋值为0
    {
        p = NULL;
    }
    else
    {
        p = (Node*)malloc(sizeof(Node));
        p->data = ch;
        p->Left  = createBinaryTree();  //递归创建左子树
        p->Right = createBinaryTree();  //递归创建右子树
    }
    return p;
}
void preOrderTraverse(Node* root){
    if (root){
        cout<<root->data<<' ';
        preOrderTraverse(root->Left);
        preOrderTraverse(root->Right);
    }
}
void inOrderTraverse(Node* root)
{
    if( root )
    {
        inOrderTraverse(root->Left);
        cout<<root->data<<' ';
        inOrderTraverse(root->Right);
    }
}

void lastOrderTraverse(Node* root)
{
    if( root )
    {
        lastOrderTraverse(root->Left);
        lastOrderTraverse(root->Right);
        cout<<root->data<<' ';
    }
}

int Nodenum (Node * root){
    if (root == NULL)
    {
        return 0;
    } else {
        return 1 + Nodenum(root->Left)+Nodenum(root->Right);
    }
}
int Leafnum(Node* root)
{
    if(!root)
    {
        return 0;
    }
    else if(  (root->Left == NULL) && (root->Right == NULL) )
    {
        return 1;
    }
    else
    {
        return  (Leafnum(root->Left) + Leafnum(root->Right)) ;
    }
}




void TreeTest(){
//    Node * root = createBinaryTree();
//    cout<<"先根："<<" ";
//    preOrderTraverse(root);
//    cout<<endl;
//    cout<<"中根："<<" ";
//    inOrderTraverse(root);
//    cout<<endl;
//    cout<<"后根："<<" ";
//    lastOrderTraverse(root);
//    cout<<endl;
//    cout<<"结点个数"<<Nodenum(root)<<endl;
//    cout<<"叶子结点个数"<<Leafnum(root)<<endl;
}
/*
B-树：
    多路搜索树，每个结点存储M/2到M个关键字，非叶子结点存储指向关键

    字范围的子结点；

    所有关键字在整颗树中出现，且只出现一次，非叶子结点可以命中；
B+树：
    在B-树基础上，为叶子结点增加链表指针，所有关键字都在叶子结点

    中出现，非叶子结点作为叶子结点的索引；B+树总是到叶子结点才命中；
B*树：
    在B+树基础上，为非叶子结点也增加链表指针，将结点的最低利用率

    从1/2提高到2/3；*/
/*
一个m阶的B+树具有如下几个特征：

1.有k个子树的中间节点包含有k个元素（B树中是k-1个元素），每个元素不保存数据，只用来索引，所有数据都保存在叶子节点。

2.所有的叶子结点中包含了全部元素的信息，及指向含这些元素记录的指针，且叶子结点本身依关键字的大小自小而大顺序链接。

3.所有的中间节点元素都同时存在于子节点，在子节点元素中是最大（或最小）元素。

4.data域之间用指针相连

5.1.b+树io次数更少 2.查询性能稳定 3.范围查询简便
 B+树的特征：

1.有k个子树的中间节点包含有k个元素（B树中是k-1个元素），每个元素不保存数据，只用来索引，所有数据都保存在叶子节点。

2.所有的叶子结点中包含了全部元素的信息，及指向含这些元素记录的指针，且叶子结点本身依关键字的大小自小而大顺序链接。

3.所有的中间节点元素都同时存在于子节点，在子节点元素中是最大（或最小）元素。

B+树的优势：

1.单一节点存储更多的元素，使得查询的IO次数更少。

2.所有查询都要查找到叶子节点，查询性能稳定。

3.所有叶子节点形成有序链表，便于范围查询。
 */
/*
 * AVL树
 * 一棵AVL树有如下必要条件：

    条件一：它必须是二叉查找树。
    条件二：每个节点的左子树和右子树的高度差至多为1。

    总结：四种失衡调整
    类型 	使用情形
    单左旋 	在左子树插入左孩子节点，使得平衡因子绝对值由1增至2
    单右旋 	在右子树插入右孩子节点，使得平衡因子绝对值由1增至2
    先左旋后右旋 	在左子树插入右孩子节点，使得平衡因子绝对值由1增至2
    先右旋后左旋 	在右子树插入左孩子节点，使得平衡因子绝对值由1增至2


    删除节点也可能导致AVL树的失衡，实际上删除节点和插入节点是一种互逆的操作：
    删除右子树的节点导致AVL树失衡时，相当于在左子树插入节点导致AVL树失衡，即情况情况二或情况四。
    删除左子树的节点导致AVL树失衡时，相当于在右子树插入节点导致AVL树失衡，即情况情况一或情况三。
    另外，AVL树也是一棵二叉排序树，因此在删除节点时也要维护二叉排序树的性质。


    红黑树
    红黑树需要满足的五条性质：
    性质一：节点是红色或者是黑色；
    在树里面的节点不是红色的就是黑色的，没有其他颜色，要不怎么叫红黑树呢，是吧。
    性质二：根节点是黑色；
    根节点总是黑色的。它不能为红。
    性质三：每个叶节点（NIL或空节点）是黑色；
    这个可能有点理解困难，可以看图：
    性质四：每个红色节点的两个子节点都是黑色的（也就是说不存在两个连续的红色节点）；
    就是连续的两个节点不能是连续的红色，连续的两个节点的意思就是父节点与子节点不能是连续的红色
    性质五：从任一节点到其没个叶节点的所有路径都包含相同数目的黑色节点；


    红黑树是一种常用的平衡二叉搜索树，单次的查找、插入、删除的复杂度都是lg(n)，这些操作的复杂度都不会恶化；
    红黑树的定义；红黑树结点数与树高的约束：lg(n+1) >= h/2，及其证明；STL中的map和set是用红黑树实现的，以及它们的用法

 *
 * */

#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}

int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    int l,r;
    if(node==0) return 0;
    l=getSize(node->left);
    r=getSize(node->right);
    return (l+r+1) ;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    struct treeNode * t ;
    t=root;
    int depth=0;//write your codes here
    if(node==0) return -1;
    else if(root->item == node->item ) return 0;
    while(t->item != node->item)
    {
        if(t->item > node->item)
            t= t->left;
        else
            t= t->right;
        depth++;
    }
    return depth;
}

int calcDepth(int item)//return depth of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeDepth(node);
}

struct treeNode* findSuccessor(struct treeNode * node, int item)
{
    //go to right child, and then all left children
    struct treeNode * succ, * t;
    if( node->right != 0 )
    {
        succ = node->right ;
        while( succ->left!=0 )
            succ = succ->left ;
        return succ ;
    }
    else
    {
    //search the item, during searching, track the successor
        succ = 0 ;
        t = root ;
        while( t!= 0 )
        {
            if (node->item == t->item ) return succ ;
            else if (node->item < t->item )
            {
                succ = t ;
                t = t->left ;
            }
            else t = t->right ;
        }
        return 0 ;
    }
}

int deleteItem(struct treeNode * node, int item)
{
    struct treeNode * succ, * t;
    if(node==0) return FALSE_VALUE;
    else if(root->item==item && root->left==0 && root->right==0)
    {
        root=0;
        return TRUE_VALUE;
    }
    else if(node->left->item==item)
    {
        if(node->left->left==0&&node->left->right==0)  node->left=0;
        else if(node->left->left==0&&node->left->right!=0)  node->left=node->left->right;
        else if(node->left->left!=0&&node->left->right==0)  node->left=node->left->left;
        else
        {
            //succ=findSuccessor(node->left,node->left->item);
            succ=findSuccessor(root,node->left->item);
            t->item=node->left->item;
            node->left->item=succ->item;
            succ->item=t->item;
            //deleteItem(node,item);
        }
        return TRUE_VALUE;
    }
    else if(node->right->item==item)
    {
        if(node->right->left==0&&node->right->right==0)  node->right=0;
        else if(node->right->left==0&&node->right->right!=0)  node->right=node->right->right;
        else if(node->right->left!=0&&node->right->right==0) node->right=node->right->left;
        else
        {
            //succ=findSuccessor(node->right,node->right->item);
            succ=findSuccessor(root,node->right->item);
            t->item=node->right->item;
            node->right->item=succ->item;
            succ->item=t->item;
            //deleteItem(node,item);
        }
        return TRUE_VALUE;
    }
    int t1;
    if(node->item > item ) t1=deleteItem(node->left,item);
    else
        t1=deleteItem(node->right,item);
    return t1;
}



int getMinItem() //returns the minimum item in the tree
{
    int min;
    struct treeNode * node ;
    node = root ;
    while(node->left != 0)
    {
        node=node->left;
        min=node->item;
    }
    return min ;

}

int getMaxItem() //returns the maximum item in the tree
{
    int max;
    struct treeNode * node ;
    node = root ;
    while(node->right != 0)
    {   node=node->right;
        max=node->item;
    }
    return max ;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    int num,l,r;
    if(node==0) return 0;
    l=rangeSearch(node->left , leftBound, rightBound);
    r=rangeSearch(node->right,leftBound,rightBound);
    if(node->item >= leftBound && node->item <= rightBound)   return l+r+1;
    else return l+r;
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.   8. Size     9. Node Depth   10.Item Depth\n");
        printf("11. Maximum item. 12. Minimum item.     13.Range Search     14.Delete Item  \n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch==8)
        {
            printf( "CURRENT SIZE IS: %d\n",getSize(root));
        }
        else if(ch==9)
        {
            int depth = calcNodeDepth(root->right->left);
            printf("Depth of tree = %d\n", depth);
        }
        else if(ch==10)
        {
            int item;
            scanf("%d", &item);
            int depth = calcDepth(item);
            printf("Depth of %d = %d\n", item, depth);
        }
        else if(ch==11)
        {
            printf("The Maximum Number is: %d\n",getMaxItem());
        }
        else if(ch==12)
        {
            printf("The Minimum Number is: %d\n",getMinItem());
        }
        else if(ch==13)
        {
            int leftBound , rightBound ;
            printf("leftBound=");
            scanf("%d",&leftBound);
            printf("\nrightBound=");
            scanf("%d",&rightBound);
            printf("\nThe Number of Elements is: %d\n",rangeSearch(root,leftBound,rightBound));
        }
        else if(ch==14)
        {
            int item;
            scanf("%d", &item);
            int res = deleteItem(root, item);
            if(res) printf("The Item is Deleted...\n");
            else printf("Not found.\n");
        }
    }

}

// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 
#include "avltree.h"
// An AVL tree node 

bool inUse(struct treeNode *N){
    return inUse;
}

int getEnd(struct treeNode *N)
{
    return (N->size)+(N->startPoint);
}

int getStart(struct treeNode *N)
{
    return N->startPoint;
}

int getSize(struct treeNode *N)
{
    return N->size;
}
// A utility function to get the height of the tree 
int height(struct treeNode *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given size and 
    NULL left and right pointers. */
struct treeNode* newNode(int size) 
{ 
    struct treeNode* node = (struct treeNode*) 
                        malloc(sizeof(struct treeNode)); 
    node->size   = size; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct treeNode *rightRotate(struct treeNode *y) 
{ 
    struct treeNode *x = y->left; 
    struct treeNode *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 
    x->height = max(height(x->left), 
                    height(x->right)) + 1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct treeNode *leftRotate(struct treeNode *x) 
{ 
    struct treeNode *y = x->right; 
    struct treeNode *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left),    
                    height(x->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(struct treeNode *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a size in the subtree rooted 
// with node and returns the new root of the subtree. 
struct treeNode* insert(struct treeNode* node, int size) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(size)); 
  
    if (size < node->size) 
        node->left  = insert(node->left, size); 
    else if (size > node->size) 
        node->right = insert(node->right, size); 
    else // Equal sizes are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                        height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && size < node->left->size) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && size > node->right->size) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && size > node->left->size) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && size < node->right->size) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
struct treeNode * minValueNode(struct treeNode* node)
{
    struct treeNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node with given size
// from subtree with given root. It returns root of
// the modified subtree.
struct treeNode* deleteNode(struct treeNode* root, int size)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the size to be deleted is smaller than the
    // root's size, then it lies in left subtree
    if ( size < root->size )
        root->left = deleteNode(root->left, size);
 
    // If the size to be deleted is greater than the
    // root's size, then it lies in right subtree
    else if( size > root->size )
        root->right = deleteNode(root->right, size);
 
    // if size is same as root's size, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct treeNode *temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct treeNode* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            root->size = temp->size;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->size);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
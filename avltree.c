// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 
#include "avltree.h"
// An AVL tree node 

int getEnd(struct Node *N)
{
    return (N->size)+(N->start);
}

int getStart(struct Node *N)
{
    return N->start;
}

int getSize(struct Node *N)
{
    return N->size;
}
// A utility function to get the height of the tree 
int height(struct Node *N) 
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
struct Node* newNode(int size,int start) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->size   = size; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->start  = start;
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
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
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
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
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a size in the subtree rooted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, int size,int start) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(size,start)); 
  
    if (size < node->size) 
        node->left  = insert(node->left, size,start); 
    else if (size > node->size) 
        node->right = insert(node->right, size,start); 
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
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node with given size
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, int size)
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
            struct Node *temp = root->left ? root->left :
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
            struct Node* temp = minValueNode(root->right);
 
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
// Function to find the best fit node for a specific job
//return such node
struct Node* bestFit(struct Node* root, int size){
    struct Node* bfn=(root);
    helperBF(root, size, bfn);
    if(((bfn->size)-size)<0){
        return NULL;
    }{
        return bfn;
    }
}

void* helperBF(struct Node* root, int size,struct Node* bFn){
    int bF=((bFn->size)-size);
    int nF=((root->size)-size);
    if(abs(nF)<abs(bF)){
        bF=nF;
        bFn=root;
    }
    if(bF<0){
        //if difference is negative need more space so iterate right
        if((root->right)){
            helperBF(root->right, size, bFn);
        }else{
            return NULL;
        }
    }
    //if difference is positive get as close to 0 as possible
    if((root->left)){
        helperBF(root->left, size,bFn);
    }else{
        return NULL;
    }
}
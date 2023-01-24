/*This program is written by: Nithya Munagala 
The reason of program is to create a binary search tree based off of users input */

//libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leak_detector_c.h"

#define MAXLEN 30
FILE * output;

//struct for item node
  typedef struct item_Node
{
  char name[MAXLEN];
  int count;
  struct item_Node *left, *right;
}item_Node;

//struct for treeName
typedef struct treeNameNode
{
  char treeName[MAXLEN];
  struct treeNameNode *left, *right;
  item_Node *theTree;
}treeNameNode;

//function protoypes
//functions for treeNameNode struct 
treeNameNode *createTreeNameNode(char *treeName);
treeNameNode* insertTreeNameNode(treeNameNode *root, treeNameNode *node);
treeNameNode *buildNree(int val);
treeNameNode *searchNameNode(treeNameNode *root, char name[MAXLEN]);

//functions for item_Node struct 
item_Node *createitem_Node(char *Itemname, int node);
item_Node *insertitem_Node(item_Node *root, item_Node *node);
item_Node* minVal(item_Node *root);
item_Node* parentFunction(item_Node *root, item_Node *node);
item_Node *findNode(item_Node *root, char *node);
item_Node *deleteNode(item_Node *root, char *name);

//int prototype functions 
int countBefore(item_Node *root, char *name);
int hasOnlyLeftChild(item_Node *root);
int hasOnlyRightChild(item_Node *root);
int isLeaf(item_Node *root);
int countAll(item_Node *root);
int rightAdd(item_Node *root);
int leftAdd(item_Node *root);
int searchTree(item_Node *root, char *name);

//void prototype functions 
void valOfTrees(treeNameNode *root, int val);
void inOrder(treeNameNode *root);
void traverseSubTrees(item_Node *root);
void traverseInTraverse(treeNameNode *root);
void freeitem_Node(item_Node *root);
void freeNree(treeNameNode *root);
void itemBefore(treeNameNode *root, char *name, char *node);
void delete(treeNameNode *root, char *node, char *name);
void count(treeNameNode *root, char *name);
void calcRightHeight(treeNameNode *root, char *firstTreeName);
void search(treeNameNode *root, char *name, char *node);
void reduce(treeNameNode *root, int val, char *node, char *name);
void outputFunc(treeNameNode *root, int values);
void runFunc();


treeNameNode *createTreeNameNode(char *treeName)
{
  //creates room for new tree nodes and string copies new pointer
  treeNameNode *newNode;
  newNode = malloc(sizeof(treeNameNode));
  strcpy((*newNode).treeName, treeName);
  // left equal to then right equal to NULL
  (*newNode).left = NULL;
  (*newNode).right = NULL;

  //returns node to pointer
  return newNode;
}

//suppose to be left then right but idk
//inserts names into trees
treeNameNode* insertTreeNameNode(treeNameNode *root, treeNameNode *node) {
  //if root is empty / NULL then return node
  if (root == NULL){
	return node;
  }
  //else element should go in right first
  else {

	if (strcmp(root->treeName, node->treeName) < 0) {
  	//first the right subtree to insert the node
  	if (root->right != NULL)
    	root->right = insertTreeNameNode(root->right, node);
    	//then the node directly to right
  	else
    	root->right = node;
	}
	//otherwise element should insert to left
	else {
  	// left subtree to insert the node.
  	if (root->left != NULL)
    	root->left = insertTreeNameNode(root->left, node);
    	//places node directly into left of root
  	else
    	root->left = node;
	}
	//returns root pointer of new tree
	return root;
  }
}

//builds tree to take input
treeNameNode *buildNree(int val)
{
  //variable declaration
  int j;
  //creates root
  treeNameNode *root;
  // makes node
  treeNameNode *Node;
  char treename[MAXLEN];
  // set root to NULL until built
  root = NULL;
  // loop through values. and takes input of tree then set functions to variables
  for (j = 0; j < val; j++)
  {

	scanf("%s", treename);

	Node = createTreeNameNode(treename);
	root = insertTreeNameNode(root, Node);
  }
  // return what we created.
  return root;
}

// finds the node with root and name
treeNameNode *searchNameNode(treeNameNode *root, char name[MAXLEN])
{
  // if root is empty then it is equal to NULL, if not create new variable to store function.
  if (root == NULL)
	return NULL;
  treeNameNode *newNode;
//if both strings of root greater than 0 return left side
  if (strcmp((*root).treeName, name) == 0)
  {
	return root;
  }

  else if (strcmp((*root).treeName, name) > 0)
  {
	newNode = searchNameNode((*root).left, name);
  }
	//if it isnt greater than return side to right
  else
	//else return root
	newNode = searchNameNode((*root).right, name);
  return newNode;
}


item_Node *createitem_Node(char *Itemname, int node)
{
	//makes space for new item node and then string copied to new pointer
  item_Node *newNode;
  newNode = malloc(sizeof(treeNameNode));
  strcpy((*newNode).name, Itemname);

  //pointer set to = to node
  (*newNode).count = node;
  //left and right = to null and returns node to pointer
  (*newNode).left = NULL;
  (*newNode).right = NULL;
  return newNode;
}

//second part of insert function
item_Node *insertitem_Node(item_Node *root, item_Node *node)
{
  //if root is null then insert into empty tree
  if (root == NULL)
  {
	return node;
  }
  // otherwise elements should be inserted to the right
  else {

	if (strcmp(root->name, node->name) < 0)
	//if not right subtree can be inserted into node
	{
  	if (root->right != NULL)
  	{
    	root->right = insertitem_Node(root->right, node);
  	}
  	 
    	//places node into the right of root
  	else
  	{
    	root->right = node;
  	}
	}
  	// otherwise should be inserted into left
	else {
  	//left subtree to insert node
  	if (root->left != NULL)
    	root->left = insertitem_Node(root->left, node);
  	 
    	//places node directly into left root
  	else
  	{
    	root->left = node;
  	}
	}
	//returns root pointer of updated tree
	return root;
  }
}

//Returns pointers to the node by storing a min value in the tree root. Will not work however with an empty tree
item_Node* minVal(item_Node *root) {
  //stores root at min value
  if (root->left == NULL)
  {
	return root;
  }
	//left subtree stores min value
  else
  {
	return minVal(root->left);
  }
}

item_Node* parentFunction(item_Node *root, item_Node *node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
	return NULL;
  // The root is the direct parent of node.
  if ((*root).left == node || (*root).right == node)
	return root;
  // Look for node's parent in the left side of the tree.
  if (strcmp((*node).name, (*root).name) > 0)
  {
    //returns node parent to the right side 
	return parentFunction((*root).right, node);
  }
    //if node and root name is less than 0
  else if (strcmp((*node).name, (*root).name) < 0)
    //returns left of root 
	return parentFunction((*root).left, node);
  //return NULL is equal
  return NULL;
}


//finds node
item_Node *findNode(item_Node *root, char *node)
{
  //if root is null
  if (root == NULL)
  {
    //return null
	return NULL;
  }
    //if name is empty
  else
	if (strcmp((*root).name, node) == 0)
	{
    //return nothing
  	return root;
	}
  //if name is less than 0
	if (strcmp(node, (*root).name) < 0)
    //find node to the left side
  	return findNode((*root).left, node);
    //if name is greater than 0
	else if (strcmp(node, (*root).name) > 0)
    //find node on the right side 
  	return findNode((*root).right, node);
	else
  	return root;
}



item_Node *deleteNode(item_Node *root, char *name)
{
  // initailize variables
  item_Node *node;
  item_Node *Secondnode;
  item_Node *node3;
  char arr[MAXLEN];

  node = findNode(root, name);
  // set the parent variable in the parent function
  item_Node *parent = parentFunction(root, node);
  if (isLeaf(node))
  {
	// if parent is NULL frees the root and returns empty
	if (parent == NULL)
	{
  	free(root);
  	return NULL;
	}
// if name is greater than 0 then left is NULL
	if (strcmp(name, (*parent).name) > 0)
	{
  	free((*parent).left);
  	// the left will be NULL
  	(*parent).left = NULL;
	}
  	//otherwise  frees right and makes it NULL
    else
  {
    free((*parent).right);
  	(*parent).right = NULL;
	}
	strcpy((*node).name, "");
	return root;
  }
  // if it only has a left child
  if (hasOnlyLeftChild(node))
  {
	// if the root parent is empty
	if (parent == NULL)
	{
  	// sets the left into node, then frees node and returns
  	node3 = (*node).left;
  	free(node);
  	return node3;
	}
   
	// if variable name is greater than 0 then node is assigned to left parent
	if (strcmp(name, (*parent).name) > 0)
	{
  	node3 = (*parent).left;
  	(*parent).left = (*parent).left->left;

  	//frees node
  	free(node3);
	}

  	//sets node equal to right of the parent
	else
	{
  	node3 = (*parent).right;
  	(*parent).right = (*parent).right->left;
  	//frees the node
  	free(node3);
	}
	//string copies the return root
	strcpy((*node).name, "");
	return root;
  }

  //if node has a right child
  if (hasOnlyRightChild(node))
  {
	//if parent is empty then frees node and returns other node
	if (parent == NULL)
	{
  	node3 = (*node).right;
  	free(node);
  	return node3;
	}

	//if parents name is greater than 0 then assigns it to the left
	if (strcmp(name, (*parent).name) > 0)
	{
  	node3 = (*parent).left;
  	(*parent).left = (*parent).left->right;
  	//frees node
  	free(node3);
	}
	else
	{
  	//repeats actions with right side
  	node3 = (*parent).right;
  	(*parent).right = (*parent).right->right;
  	//frees right side
  	free(node3);
	}
	return root;
  }

  Secondnode = minVal((*node).right);
  //string copies the array in nodes name
  strcpy(arr, (*Secondnode).name);
  deleteNode(root, arr);
  //prints name to string copy and return re initalized function
  strcpy((*node).name, "");
  (*node).count = 0;
  return root;
}


//check
//count previous to tree function
int countBefore(item_Node *root, char *name)
{
  //if root is empty return 0
  if (root == NULL)
  {
	return 0;
  }

  //if root is equal to 0 then return 1
  if (strcmp((*root).name, name) == 0)
  {
	return 1;
  }
   
  //if root is greater than 0 return 1 + root of left
  else if (strcmp((*root).name, name) > 0)
  {
	return 1 + countBefore((*root).left, name);
  }
   
  else
  {
	// repeats same steps to right side
	return 1 + countBefore((*root).right, name);
  }
}


//checks if node has left children but no right children
int hasOnlyLeftChild(item_Node *root) {
  return ((*root).left != NULL && (*root).right == NULL);
}
//checks if node has right children but no left children
int hasOnlyRightChild(item_Node *root) {
  return ((*root).left == NULL && (*root).right != NULL);
}
//checks if node is leaf node
int isLeaf(item_Node *root) {
  return ((*root).left == NULL && (*root).right == NULL);
}


//counts nodes
int countAll(item_Node *root)
{
  //if root isnt null then return count left and right
  if (root != NULL)
  {
	return (*root).count + countAll((*root).left) + countAll((*root).right);
  }
   
  //if root is null then returns 0
  else
	return 0;
}


//functions to add node to left and right on binary tree
int rightAdd(item_Node *root)
{
  // set initial value to 0
  int r;
  r = 0;
  
  // while the right root isnt NULL, increment right and store root of right at original
  while ((*root).right != NULL)
  {
	r = r + 1;
	root = (*root).right;
  }
  if ((*root).left != NULL)
  {
	while ((*root).left != NULL)
	{
  	r =  r + 1;
  	root = (*root).left;
	}
  }
  //otherwise returns right
  return r;
}

//adds node to left of tree
int leftAdd(item_Node *root)
{
  //variable declaration
  int l;
  l = 0;
  //if ((*root).right && (*root).left == NULL)
// {
   // return l;
// }
  //while left isnt equal to null increment left and store root of at original
  while ((*root).left != NULL)
  {
	l =  l + 1;
	root = (*root).left;
  }
  if ((*root).right != NULL)
  {
	while ((*root).right != NULL)
	{
  	l = l + 1;
  	root = (*root).right;
	}
  }
  //returns left
  return l;
}

int searchTree(item_Node *root, char *name)
{
  //if the root is equal to NULL, return 0
  if (root == NULL)
  {
	return 0;
  }
  //if the name is greater than 0 then return the count
  if (strcmp((*root).name, name) > 0)
  {
	return searchTree((*root).left, name);
  }
  else if (strcmp((*root).name, name) < 0)
  {
	return searchTree((*root).right, name);
  }
	//if 0 is greater recursively call right
  else
  {
	//otherwise return root count
	return (*root).count;
  }
}

void valOfTrees(treeNameNode *root, int val)
{
//variable declaration
  int name;
  int j;
  char N[MAXLEN];
  item_Node *Firstnode;
  treeNameNode *Secondnode;
  char Q[MAXLEN];

  for (j = 0; j < val; j++)
  {
    //scans in variables 
	scanf("%s %s %d", N, Q, &name);

	Firstnode = createitem_Node(Q, name);
	Secondnode = searchNameNode(root, N);
	(*Secondnode).theTree = insertitem_Node((*Secondnode).theTree, Firstnode);
  }
}


//checks if function is inorder
void inOrder(treeNameNode *root)
{
  //if root is null, return
  if (root == NULL)
  {
	return;
  }
  //checks left side, root, then the right side
  inOrder((*root).left);
  //print statement and recursive
  printf("%s ", (*root).treeName);
  fprintf(output, "%s ", root->treeName);
  //calls right recursively
  inOrder((*root).right);
}

//tree traversal
void traverseSubTrees(item_Node *root) {
//if root is null then return
  if (root == NULL)
  {
	return;
  }
//checks left, prints, then right
  traverseSubTrees((*root).left);
  printf("%s ", (*root).name);
  fprintf(output, "%s ", (*root).name);
  traverseSubTrees((*root).right);
}


// traversal function for tree names
void traverseInTraverse(treeNameNode *root)
{
  //if root is null
  if (root == NULL)
  {
    //then return
	return;
  }
  //if not tranverses left, to root, then right 
  traverseInTraverse((*root).left);
  printf("\n===%s===\n", (*root).treeName);
  fprintf(output, "\n===%s===\n", (*root).treeName);
  traverseSubTrees((*root).theTree);
  traverseInTraverse((*root).right);
}

//freeTree function
void freeitem_Node(item_Node *root)
{
  //if root is empty then return
  if (root == NULL)
  {
	return;
  }
  //frees up left root, right root and node root
  freeitem_Node((*root).left);
  freeitem_Node((*root).right);
  printf("test");
  free(root);

}
//
void freeNree(treeNameNode *root)
{
//if root is null then
  if (root == NULL)
  {
    //returns
	return;
  }
  //frees left, right, and tree and root
  freeNree((*root).left);
  freeNree((*root).right);
  freeitem_Node((*root).theTree);
  freeNree(root);
}

//prints items
void itemBefore(treeNameNode *root, char *name, char *node)
{
  //holds function in 2 variables
  treeNameNode *t;
  int key;
  //then sets them equal to functions
  t = searchNameNode(root, name);
  key = countBefore((*t).theTree, node);
  //prints out items before
	printf("\nitem before %s: %d", node, key + 1);
  //file output
  fprintf(output, "\nitem before %s: %d", node, key + 1);
}


//Delete an entire tree
void delete(treeNameNode *root, char *node, char *name)
{
  treeNameNode *t;
  t = searchNameNode(root, name);

  //if name isnt NULL
  if (t != NULL)
  {
    //deletes name from tree
	(*t).theTree = deleteNode((*t).theTree, node);
    //prints that name is deleted from tree
	printf("\n%s deleted from %s", node, name);
    //file output
	fprintf(output, "\n%s deleted from %s", node, name);
  }

    //if balances takes root, checks left and right and compares
  else
  {
    //print statement that name doesnt exist
	printf("\n%s does not exist", name);
        //file output statement that name doesnt exist
	fprintf(output,"\n%s does not exist", name);

  }
}

// function counts nodes
void count(treeNameNode *root, char *name)
{
  // variable declaration
  treeNameNode *t;
  int tres;
  t = searchNameNode(root, name);

  //if t isnt null then it stores the count node in new variables
  if (t != NULL)
  {

	tres = countAll((*t).theTree);
	//prints if its not equal to NULL
	printf("\n%s count %d", name, tres);
	fprintf(output,"\n%s count %d", name, tres);
  }
	//otherwise prints if its not NULL
  else
  {
	printf("\n%s does not exist", name);
	fprintf(output, "\n%s does not exist", name);
  }
}


//height balance  calculation
void calcRightHeight(treeNameNode *root, char *firstTreeName)
{
  //variable declaration
  treeNameNode *t;
  int l;
  int r;
  int h;
  t = searchNameNode(root, firstTreeName);

  //if the left is null then make it equal to -1
  if ((*t).theTree->left == NULL)
  {
	l = -1;
  }
  //if right is null then make it equal to -1
  if ((*t).theTree->right == NULL)
  {
	r = -1;
  }
  //if left isnt then calculate tree subtree
  if ((*t).theTree->left != NULL)
  {
	l = leftAdd((*t).theTree->left);
  }
  //if left isnt then calculate tree subtree
  if ((*t).theTree->right != NULL)
  {
	r = rightAdd((*t).theTree->right);
  }
  //height balance calculation
  h = abs(r - l);
  //prints height balance
  printf("\n%s: left height %d, right height %d, difference %d, %s", firstTreeName, l, r, h, h == 0 ? "balanced" : "not balanced");
  fprintf(output, "\n%s: left height %d, right height %d, difference %d, %s", firstTreeName, l, r, h, h == 0 ? "balanced" : "not balanced");

}

void search(treeNameNode *root, char *name, char *node)
{
  //variable declaration
  treeNameNode *t;
  t = searchNameNode(root, name);
  int val;
  //if t is null, name doesnt exist
  if (t == NULL)
  {
	printf("\n%s does not exist", name);
	fprintf(output, "\n%s does not exist", name);
  }
  else
  {
	//places function in integer variable
	val = searchTree((*t).theTree, node);
	//if val is 0 then it is not found
	if (val == 0)
	{
  	printf("\n%s not found in %s", node, name);
  	fprintf(output,"\n%s not found in %s", node, name);
	}
  	//if val is less than or greater then printed it is found
	else
	{
  	printf("\n%d %s found in %s", val, node, name);
  	fprintf(output,"\n%d %s found in %s", val, node, name);
	}
  }
}

//checks and prints reduced chars
void reduce(treeNameNode *root, int val, char *node, char *name)
{
  //variable declaration
  treeNameNode *t1;
  item_Node *t2;
  t1 = searchNameNode(root, name);
  //if t1 isnt null then it is stored in t2
  if (t1 != NULL)
  {
	t2 = findNode((*t1).theTree, node);
	//decrements by val then prints reduced val
	(*t2).count = (*t2).count - val;
	printf("\n%s reduced", node);
	fprintf(output,"\n%s reduced", node);
   
	//if count is less or equal to 0 then deletes the node
	if ((*t2).count <= 0)
	{
  	deleteNode((*t1).theTree, node);
	}
   
  }
}

//deletes entire tree
void deleteTreeName(treeNameNode *root, char *name)
{
  treeNameNode *treeNode;
  //creates a string copy of node to struct
  treeNode = searchNameNode(root, name);
  strcpy((*treeNode).treeName, "");
  //set the node equal to null then free the node
  treeNode = NULL;
  //freeNree(treeNode);
  free(treeNode);
  //print deleted statement
  printf("\n%s deleted", name);
  fprintf(output,"\n%s deleted", name);
}

void outputFunc(treeNameNode *root, int values)
{
  //variable declaration
  int node;
  char name[MAXLEN];
  char tree[MAXLEN];
  char Firstnode[MAXLEN];
  int Secondnode;
  for (node = 0; node < values; node++)
  {
    //scans val of test cases
    scanf("%s", name);
    
    //scans to see if anything is 0
    if (strcmp(name, "search") == 0 || strcmp(name, "item_before") == 0 || strcmp(name, "delete") == 0)
    {
      scanf("%s %s", tree, Firstnode);
	  }
	  else if (strcmp(name, "reduce") == 0)
	  {
  	  scanf("%s %s %d", tree, Firstnode, &Secondnode);
	  }
	  else if (strcmp(name, "height_balance") == 0 || strcmp(name, "count") == 0 || strcmp(name, "delete_name") == 0)
	  {
  	  scanf("%s", tree);
	  }

//does function intended from word
	//induces delete function
	if (strcmp(name, "delete") == 0)
	{
  	delete(root, Firstnode, tree);
	}
	 
  	//induces height balance
	else if (strcmp(name, "height_balance") == 0)
	{
  	calcRightHeight(root, tree);
	}
	 
	 
	//induces reduced function
	else if (strcmp(name, "reduce") == 0)
	{
  	reduce(root, Secondnode, Firstnode,tree);
	}
	 
  	//induced delete name function
	else if (strcmp(name, "delete_name") == 0)
	{
  	deleteTreeName(root, tree);
	}
	 
  	//induces node count function
	else if (strcmp(name, "count") == 0)
	{
   	count(root, tree);
	}
	 
  	//induces finding node function
	else if (strcmp(name, "search") == 0)
	{
  	search(root, tree, Firstnode);
	}
	 
  	//induces item printing function
	else if (strcmp(name, "item_before") == 0)
	{
  	itemBefore(root, tree, Firstnode);
	}
  }
}

//function to run outputs
void runFunc() {
  //variable declaration
  int node;
  int Firstnode;
  int Secondnode;
  treeNameNode *tree;
  output = fopen("out.txt", "w");

  //scans in all inputs for tree nodes
  scanf("%d %d %d", &node, &Firstnode, &Secondnode);
  tree = buildNree(node);
  valOfTrees(tree, Firstnode);
  inOrder(tree);
  traverseInTraverse(tree);
  outputFunc(tree, Secondnode);

  //prints new line for every output
  printf("\n");
  //check
  fprintf(output, "\n");
  fclose(output);
}

//main function to execute program
int main() {
  atexit(report_mem_leak);
  runFunc();
  return 0;
}

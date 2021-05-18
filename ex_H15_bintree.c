#include <stdio.h>
#include <stdlib.h>

//Implementation of Aufgabe H15, binary search tree find value a<=x<=b

struct node {
	int key;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct bin_tree {
	struct node *root;
};

struct node *new_node(int val)
{
	struct node *new = malloc(sizeof(struct node));
	new->key = val;
	new->parent = NULL;
	new->right = NULL;
	new->left = NULL;

	return new;
}

struct bin_tree *new_bin_tree()
{
	struct bin_tree *new = malloc(sizeof(struct bin_tree));
	new->root = NULL;

	return new;
}

void left_rotate(struct bin_tree *tree, struct node *x)
{
	struct node *y = x->right;
	x->right = y->left;
	if(y->left!= NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x == tree->root) {
		tree->root = y;
	}
	else if(x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}
void right_rotate(struct bin_tree *tree, struct node *x)
{
	struct node *y = x->left;
	x->left = y->right;
	if(y->right != NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x == tree->root) {
		tree->root = y;
	}
	else if(x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

void splay(struct bin_tree *tree, struct node *node)
{
	while(node != tree->root) {
		if(node->parent == tree->root) {
			if(node == node->parent->left)
				right_rotate(tree, node->parent);
			else
				left_rotate(tree, node->parent);
		}
		else {
			struct node *p = node->parent;
			struct node *g = p->parent; //grandparent

			if(node->parent->left == node && p->parent->left == p) {
				right_rotate(tree, g);
				right_rotate(tree, p);
			}
			else if(node->parent->right == node && p->parent->right == p) {
				left_rotate(tree, g);
				left_rotate(tree, p);
			}
			else if(node->parent->right == node && p->parent->left == p) {
				left_rotate(tree, p);
				right_rotate(tree, g);
			}
			else if(node->parent->left == node && p->parent->right == p) {
				right_rotate(tree, p);
				left_rotate(tree, g);
			}
		}
	}
}

struct node *search(struct bin_tree *tree, struct node *node, int val)
{
	if (val == node->key) {
		splay(tree, node);
		return node;
	}
	else if(val < node->key && node->left != NULL)
		return search(tree, node->left, val);
	else if(val > node->key && node->right != NULL)
		return search(tree, node->right, val);
	else
		splay(tree, node);
		return NULL;
}

//----------------------------------------------------------

void insert(struct bin_tree *t, struct node *n) {
struct node *y = NULL;
struct node *temp = t->root;
while(temp != NULL) {
  y = temp;
  if(n->key < temp->key)
    temp = temp->left;
  else
    temp = temp->right;
}
n->parent = y;

if(y == NULL) //newly added node is root
  t->root = n;
else if(n->key < y->key)
  y->left = n;
else
  y->right = n;

}

void inorder(struct bin_tree *t,struct node *n)
{
if(n != NULL) {
  inorder(t, n->left);
  printf("%d\n", n->key);
  inorder(t, n->right);
}
}

//----------------------------------------------------------

void print_range(struct bin_tree *tree, int a, int b)
{

	struct node *node = tree->root;
	struct node *tmp_parent;

	//left wing
	while(!(node->left == NULL && node->right == NULL)) {
		if(a < node->key && node->left != NULL) {
			node = node->left;
			printf("l");
		}
		else if(a > node->key) {
			printf("r");
			struct bin_tree *main_left = malloc(sizeof(struct bin_tree));
			main_left->root = node;

			if (node->parent != NULL)
				tmp_parent = node->parent;
			else tmp_parent = node;
			search(main_left, node, a);
			if (node == tree->root)
				tree->root = main_left->root;
			
			node = main_left->root;
			tmp_parent->left = node;
			node->left = NULL;
			break;
		}
		else {
			node->left = NULL;
			printf("x");
			break;
		}
	}

	node = tree->root;

	//right wing
	while(!(node->left == NULL && node->right == NULL)) {
		if(b > node->key && node->right != NULL) {
			node = node->right;
			printf("R");
		}
		else if(b < node->key) {
			struct bin_tree *main_right = malloc(sizeof(struct bin_tree));
			main_right->root = node;
			tmp_parent = node->parent;
			search(main_right, node, b);
			node = main_right->root;
			tmp_parent->right = node;
			node->right = NULL;
			printf("L");
			break;
		}
		else {
			node->right = NULL;
			printf("X");
			break;
		}
	}

	printf("\n");
	inorder(tree, tree->root);
}


int main() {
struct bin_tree *t = new_bin_tree();

struct node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
a = new_node(50);
b = new_node(20);
c = new_node(30);
d = new_node(100);
e = new_node(90);
f = new_node(40);
g = new_node(25);
h = new_node(60);
i = new_node(70);
j = new_node(80);
k = new_node(150);
l = new_node(110);
m = new_node(120);

insert(t, a);
insert(t, b);
insert(t, c);
insert(t, d);
insert(t, e);
insert(t, f);
insert(t, g);
insert(t, h);
insert(t, i);
insert(t, j);
insert(t, k);
insert(t, l);
insert(t, m);


inorder(t, t->root);

printf("\n");

print_range(t, 1, 140);

return 0;
}
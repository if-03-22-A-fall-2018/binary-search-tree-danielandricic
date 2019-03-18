/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: 2AHIF
 *-----------------------------------------------------------------------------
 * Exercise Number: 
 * File:			bst.cpp
 * Author(s):		Daniel Andricic
 * Due Date:		18.März.2019
 *-----------------------------------------------------------------------------
 * Description:
 *-----------------------------------------------------------------------------
*/

#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include "general.h"
#define LENGTH 50

struct Node
{
    Bst left;
    Bst right;
    int data;
};

/**
*** Initializes the binary search tree. Deletes all existing nodes in the tree
*** @return The number of deleted nodes
*/
Bst new_bst()
{
  Bst tree = (Bst) malloc(sizeof(struct Node));
  tree = 0;
  return tree;
}

void delete_bst(Bst bst)
{
  if(bst == 0)
  {
    return;
  }
  delete_bst(bst->left);
  delete_bst(bst->right);
  sfree(bst);
}

/**
*** @return The depth of the BST
*/
int get_depth(Bst bst)
{
  if(bst == 0)
  {
    return 0;
  }
  int l = get_depth(bst->left) + 1;
  int r = get_depth(bst->right) + 1;
  return  r>l ? r:l; // Wenn r > l ergibt, dann return r; sonst return l;
}

/**
*** Adds a value to the BST
*/
void add(Bst* bst, int value)
{
  Bst &bst2 = *bst;
  if(bst2 == 0)
  {
    bst2 = (Bst)malloc(sizeof(struct Node));
    bst2->data = value;
    bst2->left = 0;
    bst2->right = 0;
  }
  else if(value <= bst2->data)
  {
      add(&bst2->left, value);
  }
  else
  {
      add(&bst2->right,value);
  }
}

/**
*** @return The value of the root element of the BST
*/
int root_value(Bst bst)
{
  return bst==0?0:bst->data; // True = return 0 und False = return bst->data
}

/**
*** @return The left subtree of the BST
*/
Bst left_subtree(Bst root)
{
  return root == 0?0:root->left; // True = return 0 und False = return root->left
}

/**
*** @return The right subtree of the BST
*/
Bst right_subtree(Bst root)
{
  return root == 0?0:root->right; // True = return 0 und False = return root->right
}

/**
*** Traverses the BST depth first by first returning the root, then traversing the left
*** subtree, then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_pre_order(Bst bst, int *elements, int start)
{
  if(bst == 0)
  {
    return 0;
  }

  int counter = 0;
  elements[start] = bst->data;
  counter += traverse_pre_order(bst->left, elements, start + 1);
  counter += traverse_pre_order(bst->right, elements, start + counter + 1);

  return counter + 1;
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then adding the root,
*** then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_in_order(Bst bst, int *elements, int start)
{
  if(bst == 0)
  {
    return 0;
  }

  int counter = 0;
  counter += traverse_in_order(bst->left, elements, start);
  elements[start + counter] = bst->data;
  counter += traverse_in_order(bst->right, elements, start + counter + 1);

  return counter + 1;
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then traversing the right
*** subtree and finally adding the root.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_post_order(Bst bst, int *elements, int start)
{
  if(bst == 0)
  {
    return 0;
  }

  int counter = 0;
  counter += traverse_post_order(bst->left, elements, start);
  counter += traverse_post_order(bst->right, elements, start + counter);
  elements[start + counter] = bst->data;

  return counter + 1;
}

/**
*** Checks whether two trees are equal
*** @param bst1 First bst
*** @param bst2 Second bst
*** @return true if bst1 and bst2 are equal, false otherwise
*/
bool are_equal(Bst bst1, Bst bst2)
{
  if(bst1 == bst2)
  {
    return true;
  }

  if(bst1 != 0 && bst2 != 0)
  {
    int arr1[LENGTH];
    int length = traverse_pre_order(bst1, arr1, 0);
    int arr2[LENGTH];
    int length2 = traverse_pre_order(bst2, arr2, 0);

    if(length == length2)
    {
      bool x = true;
      for (int i = 0; i < length; i++)
      {
        if(arr1[i] != arr2[i])
        {
          x = false;
        }
      }
      return x;
    }
  }
  return false;
}

/**
*** Calculates the longest branch in the tree. If two branches are equally long
*** the left branch is taken.
*** @param bst Bst which longest branch should be found
*** @return A tree where each node has only one child equal to the longest
*** branch of bst
*/
void most_left_longest_branch(Bst bst, Bst* branch)
{
    if(bst == 0)
    {
      return;
    }
    add(branch, bst->data);
    get_depth(bst->left) >= get_depth(bst->right) ? most_left_longest_branch(bst->left, branch):most_left_longest_branch(bst->right, branch);
}

/**
*** Gets the number of non-empty subtrees of a tree
*** @param bst The tree which number of subtrees to get
*** @return The number of non-empty subtrees
*/
int get_number_of_subtrees(Bst bst)
{
  if(bst == 0)
  {
    return - 1;
  }
  return get_number_of_subtrees(bst->left) + 1 + get_number_of_subtrees(bst->right) + 1;
}

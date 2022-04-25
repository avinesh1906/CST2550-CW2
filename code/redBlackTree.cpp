/* 
    redBlackTree.h
    Author: M00776456
    Created: 28/03/22
    Updated: 12/04/22
 */

#include "redBlackTree.h"

RedBlackTree::RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

RedBlackTree::~RedBlackTree(){
    delete TNULL;
}

void RedBlackTree::insert(Vehicle vehicle){
    // creating the node
    NodePtr node = new Node;
    node->parent = nullptr;
    node->key = vehicle.getNumber();
    node->timeIn = vehicle.getTimeIn();
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;
    NodePtr y = nullptr;
    NodePtr x = this->root;
    // Keep looping until reach the leaf (end of the tree)
    while(x != TNULL){
        y = x;
        // compare newKey with root key
        if (node->key < x->key) {
            // traverse through left subtree
            x = x->left;
        } else {
            // traverse through right subtree
            x = x->right;
        }
    }
    node->parent = y;
    // if tree is empty, insert newNode as rootNode
    if (y == nullptr){
        
        root = node;
    // decide where to place it (right or left)
    } else if (node->key < y->key){
        y->left = node;
    } else {
        y->right = node;
    }
    if (node->parent == nullptr){
        node->color = 0;
        return;
    }
    if (node->parent->parent == nullptr){
        return;
    }
    // fix up the BST after insertion
    insertFixUp(node);
}

void RedBlackTree::rightRotation(NodePtr xNode){
    NodePtr yNode = xNode->left;
    xNode->left = yNode->right;
    if (yNode->right != TNULL){
        // assign right subtree of Y to x as parent
        yNode->right->parent = xNode;
    }
    yNode->parent = xNode->parent;
    if(xNode->parent == nullptr){
        // make y as the root node
        this->root = yNode;
    } else if (xNode == xNode->parent->right){
        // make yNode as the right child of xNode
        xNode->parent->right = yNode;
    } else {
        // make yNode as the left child of xNode
        xNode->parent->left = yNode;
    }
    yNode->right = xNode;
    xNode->parent = yNode;
}

void RedBlackTree::leftRotation(NodePtr xNode){
    NodePtr yNode = xNode->right;
    xNode->right = yNode->left;
    if (yNode->left != TNULL) {
        yNode->left->parent = xNode;
    }
    yNode->parent = xNode->parent;
    if (xNode->parent == nullptr) {
        this->root = yNode;
    } else if (xNode == xNode->parent->left) {
        xNode->parent->left = yNode;
    } else {
        xNode->parent->right = yNode;
    }
    yNode->left = xNode;
    xNode->parent = yNode;
}   

int RedBlackTree::deleteNode(std::string key){
    return deleteNodeHelper(this->root, key);
}

NodePtr RedBlackTree::minimum(NodePtr node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

int RedBlackTree::nodePresent(std::string key) {
    return nodePresentHelper(this->root, key);
}

NodePtr RedBlackTree::searchTree(std::string key) {
    return searchTreeHelper(this->root, key);
}

void RedBlackTree::saveTree(std::string filename, std::string date) {
    if (root) {
        saveHelper(this->root, filename, date);
    }
}

void RedBlackTree::saveHelper(NodePtr root, std::string filename, std::string date){
            std::ofstream file;

    file.open(filename, std::ios_base::app);
    if (root != TNULL) {
        file << date << ", " << root->key << ", " << root->timeIn << ",-" << std::endl;
        saveHelper(root->left, filename, date);
        saveHelper(root->right, filename, date);
    }
}

void RedBlackTree::initializeNullNode(NodePtr node, NodePtr parent){
    node->key = "";
    node->parent = parent;
    node->left = nullptr; 
    node->right = nullptr;
    node->color = 0;          
}

void RedBlackTree::insertFixUp(NodePtr node){
    NodePtr uncle;
    // loop while the parent of node is red
    while(node->parent->color == 1){
        // if parent of node is the right child of grandparent
        if(node->parent == node->parent->parent->right){
            uncle = node->parent->parent->left;
            if(uncle->color == 1){
                // recolor
                uncle->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                // assign grandparent to new node
                node = node->parent->parent;
            } else {
                // rotate the parent of node
                if(node == node->parent->left){
                    node = node->parent;
                    rightRotation(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                leftRotation(node->parent->parent);
            }
        // left child of grandparent
        } else {
            uncle = node->parent->parent->right;
            // recolor
            if (uncle->color == 1){
                uncle->color = 0;
                node->parent->color = 0;
                node->parent->parent->color = 1;
                // assign grandparent to new node
                node = node->parent->parent;
            } else {
                // rotate the parent of node
                if (node == node->parent->right){
                    node = node->parent;
                    leftRotation(node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rightRotation(node->parent->parent);
            }
        }
        if(node == root){
            break;
        }
    }
    root->color = 0;
}

void RedBlackTree::transplant(NodePtr node1, NodePtr node2) {
    if (node1->parent == nullptr) {
        root = node2;
    } else if (node1 == node1->parent->left) {
        node1->parent->left = node2;
    } else {
        node1->parent->right = node2;
    }
    node2->parent = node1->parent;
}

void RedBlackTree::deleteFixUp(NodePtr node){
    NodePtr sNode;
    // loop until reach root and color is red
    while (node != root && node->color == 0)
    {
        // check if node is left child of parent
        if(node == node->parent->left){
            sNode = node->parent->right;
            // if right child is RED
            if(sNode->color == 1){
                sNode->color = 0;
                node->parent->color = 1;
                leftRotation(node->parent);
                sNode = node->parent->right;
            }
            // if color of both left and right child is BLACK
            if(sNode->left->color == 0 && sNode->right->color == 0){
                sNode->color = 1;
                node = node->parent;
            } else {
                // if right child is BLACK
                if(sNode->right->color == 0){
                    sNode->left->color = 0;
                    sNode->color = 1;
                    rightRotation(sNode);
                    sNode = node->parent->right;
                }
                sNode->color = node->parent->color;
                node->parent->color = 0;
                sNode->right->color = 0;
                leftRotation(node->parent);
                node = root;
            }
        // right child of parent
        // same as above with right changed to left and vice versa
        }else {
            sNode = node->parent->left;
            if (sNode->color == 1) {
                sNode->color = 0;
                node->parent->color = 1;
                rightRotation(node->parent);
                sNode = node->parent->left;
            }
            if (sNode->right->color == 0 && sNode->right->color == 0) {
                sNode->color = 1;
                node = node->parent;
            } else {
                if (sNode->left->color == 0) {
                    sNode->right->color = 0;
                    sNode->color = 1;
                    leftRotation(sNode);
                    sNode = node->parent->left;
                }
                sNode->color = node->parent->color;
                node->parent->color = 0;
                sNode->left->color = 0;
                rightRotation(node->parent);
                node = root;
            }
        }
    } 
    node->color = 0;
}

int RedBlackTree::deleteNodeHelper(NodePtr root, std::string nodeToDelete){
    NodePtr zNode = TNULL;
    NodePtr xNode, yNode;
    // loop until reach leaf
    while(root != TNULL){
        if(root->key == nodeToDelete){
            zNode = root;
        }
        // Traverse the tree
        if(root->key <= nodeToDelete){
            // go to the right subtree
            root = root->right;
        } else {
            // go to the left subtree
            root = root->left;
        }
    }
    // check if node exits in RBT
    if (zNode == TNULL){
        return 1;
    }
    yNode = zNode;
    int yNode_original_color = yNode->color;
    // check if left subtree of nodeToDelete is null
    if(zNode->left == TNULL){
        xNode = zNode->right;
        transplant(zNode, zNode->right);
    // check if right subtree of nodeToDelete is null
    } else if(zNode->right == TNULL){
        xNode = zNode->left;
        transplant(zNode, zNode->left);
    } else {
        yNode = minimum(zNode->right);
        yNode_original_color = yNode->color;
        xNode = yNode->right;
        // checks if yNode is the child of nodeToDelete
        if(yNode->parent == zNode){
            xNode->parent = yNode;
        } else {
            transplant(yNode, yNode->right);
            yNode->right = zNode->right;
            yNode->right->parent = yNode;
        }
        transplant(zNode, yNode);
        yNode->left = zNode->left;
        yNode->left->parent = yNode;
        yNode->color = zNode->color;
    }
    delete zNode;
    if(yNode_original_color == 0){
        deleteFixUp(xNode);
    }
    return 0;
}

int RedBlackTree::nodePresentHelper(NodePtr root, std::string key) {
    NodePtr zNode = TNULL;
    // loop until reach leaf
    while(root != TNULL){
        if(root->key == key){
            zNode = root;
        }
        // Traverse the tree
        if(root->key <= key){
            // go to the right subtree
            root = root->right;
        } else {
            // go to the left subtree
            root = root->left;
        }
    }
    // check if node exits in RBT
    if (zNode == TNULL){
        return 1;
    }
    return 0;
}

NodePtr RedBlackTree::searchTreeHelper(NodePtr root, std::string key) {
    if (root == TNULL || key == root->key) {
        return root;
    }
    if (key < root->key) {
        return searchTreeHelper(root->left, key);
    }
    return searchTreeHelper(root->right, key);
}
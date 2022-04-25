#ifndef __REDBLACKTREE_H_
#define __REDBLACKTREE_H_
/* 
    redBlackTree.h
    Author: M00776456
    Created: 28/03/22
    Updated: 12/04/22
 */

#include "struct.h"
#include <iostream>
#include <fstream>

typedef Node *NodePtr;

class RedBlackTree {
    private:
        NodePtr root;
        NodePtr TNULL;

    public:
        RedBlackTree();
        
        ~RedBlackTree();

        /* 
            To initialize a null node 
            @param node refers to the node that will be initialize as null. 
            Parent refers to the parent of the null node.
        */
        void initializeNullNode(NodePtr node, NodePtr parent);

        /* 
            Function to prevent violations of RBT after insertion
            @param the inserted node
        */
        void insertFixUp(NodePtr node);
        
        /* 
            To make the parent of the firstNode to point to 
            the secondNode and vice versa
            @param node1 represents the first node and node2 
            represents the secondNode
        */
        void transplant(NodePtr node1, NodePtr node2);

        /* 
            To fix the RBT after deleting a node
            @param the node that contains an extra black
        */
        void deleteFixUp(NodePtr node);

        /* 
            To delete the node from the RBT
            @param root represents the root node and nodeToDelete represents 
            the node to delete 
            @return int
        */
        int deleteNodeHelper(NodePtr root, std::string nodeToDelete);
        
        /* 
            Helper function to search if a specific key is present
            @param root presents the root of the RBT and
            key represents the key to be seached
            @return int
        */
        int nodePresentHelper(NodePtr root, std::string key);

        /* 
            Helper function to extract a specific key if present
            @param root presents the root of the RBT and
            key represents the key to be seached
            @return NodePtr
        */
        NodePtr searchTreeHelper(NodePtr root, std::string key);

        /* 
            Helper functions to aid to save the Red Black Tree's node to the 
            input file
            @param root represents the root of the RBT, filename represents the
            filename inserted in the commond line and date represents the date to
            be inserted when saving to the input file
        */
        void saveHelper(NodePtr root, std::string filename, std::string date);

        /* 
            Insert a node in the RBT when vehicle enters the parking
            @param vehicle stores the details of the vehicle that 
            the node will store
         */
        void insert(Vehicle vehicle);

        /* 
            To rotate the arrangement of the node on the left into the
            arrangements of the right node
            @param the arrangement of the nodet to rotate
         */
        void rightRotation(NodePtr xNode);
        
        /* 
            To rotate the arrangement of the node on the right into the
            arrangements of the left node
            @param the arrangement of the nodet to rotate
         */
        void leftRotation(NodePtr xNode);

        /* 
            To delete a node from RBT when vehicle exits
            @param key represents the key of the node to delete
            @return int
        */
        int deleteNode(std::string key);

        /* 
            To return the minimum node in a subtree
            @param node represents nodeToDelete
            @return NodePtr
        */
        NodePtr minimum(NodePtr node);

        /* 
            To search if a specific key is present in the RBT
            @param key represents the key of node to be searched
            @return int
        */
        int nodePresent(std::string key);
        /* 
            To extract a specific node in the RBT
            @param key represents the key of node to be searched
            @return NodePtr
        */
        NodePtr searchTree(std::string key);

        /* 
            Functions to save data to the file
            @param represents the filename inserted in the command line and
            date represents the date to be added each line when saving
        */
        void saveTree(std::string filename, std::string date);
};

#endif
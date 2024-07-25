#include "HCTree.hpp"
#include "Helper.hpp"
#include <queue>
#include <vector>

// Helper to deconstruct
void deleteAll(HCNode* node) {
        if (!node) { return;}
        
        deleteAll(node->c0);
        deleteAll(node->c1);
        delete node;
}

// Deconstructor 
HCTree::~HCTree() {
    deleteAll(root);
}


/**
* Use the Huffman algorithm to build a Huffman coding tree.
* PRECONDITION: freqs is a vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the input file.
* POSTCONDITION: root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
*/
void HCTree::build(const vector<int>& freqs) {

    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    // Populate min heap
    for (unsigned int i = 0; i < freqs.size(); ++i) {
        if (freqs[i] > 0) {
            HCNode* node = new HCNode(freqs[i], i);
            pq.push(node);
            leaves[i] = node;
        }  
    }

    while (pq.size() > 1) {

        // Pop two lowest elements in priority queue
        HCNode* low_node1 = pq.top();
        pq.pop();
        HCNode* low_node2 = pq.top();
        pq.pop();

        // combine total counts
        int total_freq = low_node1->count + low_node2->count; 
        // create a parent node with popped elements as children 
        HCNode* new_parent = new HCNode(total_freq, 0);

        // Set parent-child relationships
        new_parent->c0 = low_node1;
        new_parent->c1 = low_node2;
        low_node1->p = new_parent;
        low_node2->p = new_parent;

        // Push new parent node onto queue
        pq.push(new_parent);

    }

    // Only one node
    if (pq.size() == 1) {
        root = pq.top();
        pq.pop();
        return;
    }
   
}


/**
* Write to the given FancyOutputStream the sequence of bits coding the given symbol.
* PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
*/
void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const {

    // Find node with given symbol
    HCNode* leaf_node = leaves[symbol];

    // If leaf_node is still nullptr, symbol not found in tree
    if (!leaf_node) {
        return;
    }

    // Traverse up from leaf node to root and store binary 
    vector<int> binary;
    HCNode* current_node = leaf_node;
    while (current_node->p) {  
        HCNode* parent = current_node->p;
        if (parent->c0 == current_node) {
            binary.push_back(0);  
        } else {
            binary.push_back(1);  
        }
        current_node = parent;
    }

    // Write bits to the output stream
    for (int i = binary.size() - 1; i >= 0; --i) {
        out.write_bit(binary[i]);
    }

}

/**
* Return symbol coded in the next sequence of bits from the stream.
* PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
*/
unsigned char HCTree::decode(FancyInputStream & in) const { 
    HCNode* current = root; 

    // Traverse down the tree until a leaf is reached
    while (current->c0 || current->c1) {
        int bit = in.read_bit();  // Read the next bit from the input stream
        if (bit == -1) {
            // Handle error or end of input stream
            return 0;
        }
        if (bit == 0) {
            // Move to the left child 
            current = current->c0;
        } else {
            // Move to the right child 
            current = current->c1;
        }
    }

    // Return the symbol associated with the leaf 
    return current->symbol;
    
}





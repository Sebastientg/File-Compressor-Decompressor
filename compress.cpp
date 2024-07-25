#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    // Check for correct arguments
    if (argc < 3) {
        error("Usage: compress <input_file> <output_file>");
    }

    // Open input file
    FancyInputStream input(argv[1]);


    // Handle empty file
    if (input.filesize() == 0) {
        FancyOutputStream output(argv[2]);
        return 0; 
    }

    // Read bytes and count number of occurrences
    vector<int> freqs(256, 0);
    int numSymbols = 0;

    while (true) {
        int byte = input.read_byte();
        if (byte == -1) {
            break;
        }
        freqs[byte]++;
        if (freqs[byte] == 1) {
            numSymbols++; // Count unique symbols
        }
    }

    // Build the Huffman tree with the given frequencies
    HCTree tree;
    tree.build(freqs);

    // Open output file
    FancyOutputStream output(argv[2]);

    // Write the number of unique symbols
    output.write_int(numSymbols);

    // Write symbol frequencies (optimized)
    for (int i = 0; i < 256; ++i) {
        if (freqs[i] > 0) {
            output.write_byte(i); // Write the symbol
            int freq = freqs[i];
            // Write frequency using 3 bytes
            output.write_byte((freq >> 16) & 0xFF);
            output.write_byte((freq >> 8) & 0xFF);
            output.write_byte(freq & 0xFF);
        }
    }

    // Move back to the beginning of the input file
    input.reset();

    // Encode each byte from the input file using the Huffman coding tree and write to output file
    while (true) {
        int byte = input.read_byte();
        if (byte == -1) {
            break; // End of input file
        }
        tree.encode(byte, output);
    }

    return 0;
}

// vector<int> freqs(256, 0);
    // freqs['a'] = 5;
    // freqs['b'] = 9;
    // freqs['c'] = 12;
    // freqs['d'] = 13;
    // freqs['e'] = 16;
    // freqs['f'] = 45;

    // // Create HCTree instance
    // HCTree tree;

    // // Build the Huffman tree with the given frequencies
    // tree.build(freqs);

    // // Print the tree structure
    // cout << "Huffman Tree Structure:\n";
    // printTree(tree.getRoot());  // Assuming you have a getter for the root

    // return 0;

// Level Order Traversal 
// void printTree(HCNode* root) {
//     if (!root)
//         return;

//     queue<HCNode*> nodeQueue;
//     nodeQueue.push(root);

//     while (!nodeQueue.empty()) {
//         HCNode* current = nodeQueue.front();
//         nodeQueue.pop();

//         cout << "Node (symbol: " << current->symbol << ", count: " << current->count << ")\n";

//         if (current->c0)
//             nodeQueue.push(current->c0);
//         if (current->c1)
//             nodeQueue.push(current->c1);
//     }
// }



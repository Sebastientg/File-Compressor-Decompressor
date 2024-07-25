#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    // Check for correct arguments
    if (argc != 3) {
        error("Usage: uncompress <input_file> <output_file>");
    }

    // Open input file
    FancyInputStream input(argv[1]);

    // Handle empty file
    if (input.filesize() == 0) {
        FancyOutputStream output(argv[2]);
        return 0; 
    }

    // Read the number of unique symbols from the header
    int numSymbols = input.read_int();

    // Read symbol frequencies from the header (optimized)
    vector<int> freqs(256, 0);
    for (int i = 0; i < numSymbols; ++i) {
        unsigned char symbol = input.read_byte();
        int count = (input.read_byte() << 16) | (input.read_byte() << 8) | input.read_byte();
        freqs[symbol] = count;
    }

    // Build Huffman tree with the given frequencies
    HCTree tree;
    tree.build(freqs);

    // Open output file
    FancyOutputStream output(argv[2]);

    // Decode bits from input file into sequence of bytes and write to output file
    int counter = 0;
    for (int freq : freqs) {
        counter += freq;
    }
    while (counter != 0) {
        unsigned char symbol = tree.decode(input);
        output.write_byte(symbol);
        --counter; 
    }

    return 0;
}

#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        error("Usage: uncompress <input_file> <output_file>");
    }

    // Open input file using a custom input stream class
    FancyInputStream input(argv[1]);

    // Handle the case where the input file is empty
    if (input.filesize() == 0) {
        // Open output file using a custom output stream class
        FancyOutputStream output(argv[2]);
        return 0; 
    }

    // Read the number of unique symbols from the input file header
    int numSymbols = input.read_int();

    // Read the symbol frequencies from the input file header in an optimized format
    vector<int> freqs(256, 0);  // Vector to store frequencies of each byte (0-255)
    for (int i = 0; i < numSymbols; ++i) {
        unsigned char symbol = input.read_byte();  // Read the symbol
        // Read the frequency of the symbol using 3 bytes (big-endian format)
        int count = (input.read_byte() << 16) | (input.read_byte() << 8) | input.read_byte();
        freqs[symbol] = count;  // Store the frequency in the vector
    }

    // Build the Huffman tree using the frequencies of each byte
    HCTree tree;
    tree.build(freqs);

    // Open output file for writing the decompressed data
    FancyOutputStream output(argv[2]);

    // Decode bits from the input file into a sequence of bytes and write them to the output file
    int counter = 0;  // Variable to count the total number of bytes to decode
    for (int freq : freqs) {
        counter += freq;  // Sum up the frequencies to get the total number of bytes
    }

    while (counter != 0) {
        unsigned char symbol = tree.decode(input);  // Decode the next symbol using the Huffman tree
        output.write_byte(symbol);  // Write the decoded symbol to the output file
        --counter;  // Decrement the counter
    }

    return 0;  // Return 0 to indicate successful execution
}

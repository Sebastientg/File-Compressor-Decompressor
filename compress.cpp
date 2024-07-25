#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc < 3) {
        error("Usage: compress <input_file> <output_file>");
    }

    // Open input file using a custom input stream class
    FancyInputStream input(argv[1]);

    // Handle the case where the input file is empty
    if (input.filesize() == 0) {
        // Open output file using a custom output stream class
        FancyOutputStream output(argv[2]);
        return 0; 
    }

    // Read bytes from the input file and count the frequency of each byte (symbol)
    vector<int> freqs(256, 0);  // Vector to store frequencies of each byte (0-255)
    int numSymbols = 0;  // Variable to count the number of unique symbols

    while (true) {
        int byte = input.read_byte();  // Read a byte from the input file
        if (byte == -1) {  // Check for end of file
            break;
        }
        freqs[byte]++;  // Increment the frequency count for the read byte
        if (freqs[byte] == 1) {
            numSymbols++;  // Increment unique symbol count if this is the first occurrence
        }
    }

    // Build the Huffman tree using the frequencies of each byte
    HCTree tree;
    tree.build(freqs);

    // Open output file for writing the compressed data
    FancyOutputStream output(argv[2]);

    // Write the number of unique symbols to the output file
    output.write_int(numSymbols);

    // Write the symbol frequencies to the output file in an optimized format
    for (int i = 0; i < 256; ++i) {
        if (freqs[i] > 0) {
            output.write_byte(i);  // Write the symbol
            int freq = freqs[i];
            // Write the frequency using 3 bytes (big-endian format)
            output.write_byte((freq >> 16) & 0xFF);
            output.write_byte((freq >> 8) & 0xFF);
            output.write_byte(freq & 0xFF);
        }
    }

    // Reset the input stream to the beginning of the file
    input.reset();

    // Encode each byte from the input file using the Huffman coding tree and write the encoded bits to the output file
    while (true) {
        int byte = input.read_byte();  // Read a byte from the input file
        if (byte == -1) {  // Check for end of file
            break;  // End of input file
        }
        tree.encode(byte, output);  // Encode the byte and write the encoded bits to the output file
    }

    return 0;  // Return 0 to indicate successful execution
}




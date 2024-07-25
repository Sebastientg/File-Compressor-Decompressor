
# Huffman Compression and Decompression

## Project Description

This project implements Huffman compression and decompression algorithms in C++. The program compresses an input file using Huffman coding, a lossless data compression algorithm, and decompresses it back to its original form.

## File Structure

- example_files/: Directory containing example files for testing.
- .gdbinit: GDB configuration file.
- HCTree.cpp: Source file containing the implementation of the Huffman Coding Tree.
- HCTree.hpp: Header file containing the declarations for the Huffman Coding Tree.
- Helper.cpp: Source file containing helper functions and classes for file handling.
- Helper.hpp: Header file containing the declarations for helper functions and classes.
- Makefile: Makefile for compiling the project.
- README.md: This README file.
- compress.cpp: Source file containing the main function for compressing files.
- refcompress: Reference binary for compressing files.
- refuncompress: Reference binary for decompressing files.
- uncompress.cpp: Source file containing the main function for decompressing files.

# Prerequisites

- C++ compiler (e.g., g++)
- Makefile (optional, for easy compilation)

# Compilation

To compile the project, you can use the following command in the terminal:

```
g++ -o compress compress.cpp HCTree.cpp Helper.cpp
g++ -o uncompress uncompress.cpp HCTree.cpp Helper.cpp
```

Alternatively, if you have a Makefile, simply run:

```
make
```

## Usage

### Compressing a File

To compress a file, run the following command:

```
./compress <input_file> <output_file>
```

- <input_file>: Path to the file you want to compress.
- <output_file>: Path where the compressed file will be saved.

Example:

```
./compress example_files/example.txt compressed.bin
```

### Decompressing a File

To decompress a file, run the following command:

```
./uncompress <input_file> <output_file>
```

- <input_file>: Path to the compressed file.
- <output_file>: Path where the decompressed file will be saved.
  
Example:

```
./uncompress compressed.bin decompressed.txt
```

## Example Workflow

1. Compress a file:

```
./compress example_files/input.txt compressed.bin
```

  This will take example_files/input.txt and create a compressed version named compressed.bin.

2. Decompress the file:

```
./uncompress compressed.bin example_files/output.txt
```

  This will take compressed.bin and restore it to example_files/output.txt, which should be identical to example_files/input.txt.

## Acknowledgments

This project uses a custom implementation of the Huffman Coding Tree (HCTree) and helper functions for file handling.
Special thanks to my CSE 100 Advanced Data Structures Course for the assignment. 

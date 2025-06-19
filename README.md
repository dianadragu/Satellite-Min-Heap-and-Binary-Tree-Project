# Satellites Project

## Overview

This project is organized using header files. In `sateliti.h`, I defined the data structures: a structure for a satellite (which also stores links to left/right child nodes) and a structure for a min-heap. In `sateliti.c`, I implemented helper functions, while the main logic for each requirement is found in `main.c`.

---

## Task 1

**Description:**  
Read the number of satellites, then for each satellite, read its frequency and name. Using the `aloc_init_satelit` function, add each satellite to the heap, increment the size, and restore the min-heap property by sifting up after each insertion.

The main function for this task is also used in other tasks. The root of the created tree is saved, and for the `-c1` option, the `bfs` function is called to print the tree level by level.

**Implementation:**  
- A loop runs until only two elements remain in the min-heap.
- Extract the two smallest satellites, concatenate their names, and sum their frequencies.
- Create a new satellite node with the combined name and frequency, add it to the heap, increment the size, and restore the min-heap property.
- At the end, return the only remaining element in the heap, which is the root of the tree.

**Helper Functions:**
- `aloc_init_satelit`: Allocates and initializes a satellite node with given frequency, name, and child nodes.
- `aloc_heap`: Allocates and initializes a min-heap with a given capacity.
- `comp`: Compares two satellites by frequency, and by name if frequencies are equal.
- `siftDown`: Restores the min-heap property by sifting down from a given index.
- `siftUp`: Restores the min-heap property by sifting up from a given index.
- `extractMin`: Removes and returns the smallest element from the heap.
- `free_arbore`: Recursively frees the memory used by the tree.
- `bfs`: Prints the tree level by level using a queue.

---

## Task 2

**Description:**  
Read the number of binary encodings, then for each encoding, decode it using the tree and print the names of the satellites.

**Implementation:**  
- For each binary string, use a recursive function that traverses the tree according to the bits in the string.
- If a leaf node is reached, print its name and restart from the root for the next part of the string.

---

## Task 3

**Description:**  
For each satellite name given, print the binary code (path) to reach that satellite in the tree.

**Implementation:**  
- For each satellite, use a recursive function that traverses the tree, printing `0` for left and `1` for right.
- The function uses a helper (`valid`) to ensure that the name matches exactly (not as a substring of another name).

**Helper Function:**
- `valid`: Checks if the satellite name matches exactly, not as a substring (e.g., searching for "R1" in "R10R12R5" should not match).

---

## Task 4

**Description:**  
Given a list of satellite names, find their lowest common ancestor (LCA) in the tree.

**Implementation:**  
- Read the number of satellites and the first two names.
- Use the `lca` function to find their common ancestor.
- For each additional satellite, update the ancestor by finding the LCA of the current ancestor and the new satellite.
- At the end, print the name of the final ancestor.

**Helper Function:**
- `lca`: Recursively finds the lowest common ancestor of two nodes in the tree.

---

## File Structure

- `sateliti.h`: Data structure definitions.
- `sateliti.c`: Helper function implementations.
- `main.c`: Main logic and task handling.

---

## Notes

- The code is modular, with clear separation between data structures, helper functions, and main logic.
- All memory allocations are checked, and memory is freed appropriately.
- The project uses standard C libraries and is portable.

---

## Usage

Compile the project using a C compiler (e.g., gcc):

```sh
gcc main.c sateliti.c -o satellites
```

Run with the desired option (e.g., `-c1`, `-c2`, etc.) and input files as required by the assignment.

---

## Author

*Please add your name and contact information here.*

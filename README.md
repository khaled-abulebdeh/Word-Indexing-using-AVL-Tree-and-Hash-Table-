
# Word Indexing (using AVL Tree and Hash Table)

## Overview

This project implements an application for efficiently indexing words found in a text file using an **AVL Tree** and a **Hash Table**.  
The AVL Tree ensures balanced, fast word retrieval and ordering, while the Hash Table allows fast direct access for frequency lookup.

Developed in **C Language**, this project combines concepts of self-balancing binary trees and hashing with collision handling.

---

## Files

| File | Description |
|:-----|:------------|
| `main.c` | Main C source code implementing AVL Tree and Hash Table for word indexing. |
| `input.txt` | Input file containing the text data to be processed (should exist before running). |
| `Project_Description.pdf` | Full project assignment description and requirements. |

---

## Features

- Load text data from an input file.
- Create an AVL Tree where each word is stored along with its frequency.
- Insert or delete a word from the AVL Tree.
- Display words and their frequencies sorted using in-order traversal.
- Create a Hash Table from the AVL Tree.
- Insert or delete a word in the Hash Table.
- Search for a word's frequency directly from the Hash Table.
- Display word statistics:
  - Total number of unique words.
  - Most frequent words.
  - Words with frequency above a user-defined threshold.

---

## Requirements

- C Language (Standard C)
- Knowledge of AVL Trees and Hash Tables
- `input.txt` must exist before running the program.



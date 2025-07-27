````markdown
# 🧠 Lexical Context Functions in C

This repository contains the core C functions for lexical context extraction and analysis. It enables text parsing, frequency analysis, and the creation of a word-context dictionary using custom data structures. These utilities can be useful for basic natural language processing or educational purposes in C programming.

---

## 📁 Files Included

| File         | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `fonction.h` | Header file with structure definitions and function declarations.           |
| `FONCTION.c` | Source file implementing all text-processing and data-manipulation logic.   |

> ✅ Note: These are the only two files included here for simplicity and reusability in other projects. The `main.c` interface is excluded to keep the repository modular and focused.

---

## ⚙️ Features

- Read and parse text from a file
- Tokenize text into words and build a linked list
- Remove duplicates from a word list
- Build context lists for each word (based on next-word order)
- Count occurrences of words or contexts
- Create a dictionary mapping words to their context frequencies
- Sort contexts (ascending or descending by frequency)
- Generate word sequences based on most frequent contexts

---

## 🛠️ How to Use

1. Include the header in your own C file:
   ```c
   #include "fonction.h"
````

2. Compile your program with:

   ```bash
   gcc main.c FONCTION.c -o context-analyzer
   ```

3. Make sure your `main.c` provides:

   * Reading from a text file
   * Calling functions such as `creeListeChaine`, `creationdictionary`, `maxcontexte`, etc.

---

## 🧪 Sample Usage

```c
FILE *f = fopen("text.txt", "r");
char *text = lire(f);                   // Read file content
liste L = creeListeChaine(text);       // Tokenize into words
dictionnaire D = creationdictionary(L); // Create context dictionary
affichagedictionnaire(D);              // Display full dictionary
```

---

## 👥 Authors

* **Ferchichi Manel**
* **Madi Sara**

---

## 📄 License

This project is released for educational and personal use. You may reuse and adapt the code with proper credit.

---

## 💡 Contributions

Suggestions and contributions are welcome! Feel free to open an issue or fork the project to enhance it.

---


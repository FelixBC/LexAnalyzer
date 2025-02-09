# LexAnalyzer

**LexAnalyzer** is a lexical analyzer built using **Flex** and **Qt**. It processes input source code and tokenizes it into meaningful components such as keywords, identifiers, operators, and numbers.

## Features
- Identifies keywords, identifiers, numbers, and operators
- Reads input from user or a file
- Displays tokenized output
- Generates documentation using **Doxygen**

## File Structure
| File/Directory      | Description |
|---------------------|-------------|
| **lexer.l**        | Flex file defining token recognition rules |
| **lex.yy.c**       | Generated C source file from Flex |
| **LexAnalyzer**    | Compiled executable |
| **Doxyfile**       | Configuration file for Doxygen documentation |
| **html/**         | Folder containing generated documentation (HTML) |
| **latex/**        | Folder containing LaTeX documentation |

## Build & Run Instructions
### **1. Building the Lexer**
To compile the lexer, use the following commands:
```bash
flex lexer.l
gcc lex.yy.c -o lexer -lfl
```

### **2. Running the Lexer**
Once compiled, execute the lexer with an input file:
```bash
./lexer < input.txt
```

### **3. Generating Documentation**
To generate the documentation using **Doxygen**:
```bash
doxygen Doxyfile
xdg-open html/index.html
```

## Example Input & Output
**Example Input:** (input.txt)
```
if x = 10
```

**Expected Output:**
```
Keyword: if
Identifier: x
Operator: =
Number: 10
```

## Author
- **FelixBC**

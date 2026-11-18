# C-Line-editor-3rd-Sem-PB

# Line Editor in C

A simple command-line line editor. The user types commands that act on
line numbers, with no GUI.

**Course:** Portfolio Building (B25CS0311), Activity 7

## Team
| Name | Roll No. | GitHub |
|------|----------|--------|
| <Your Name> | <Roll No.> | [@<username>](https://github.com/<username>) |
| <Teammate> | <Roll No.> | [@<username>](https://github.com/<username>) |

## Features implemented
**Core:**
- Insert a line at a given line number
- Delete a line
- Display the document with line numbers
- Save to and load from a `.txt` file

**Bonus:**
- Search for a word or phrase
- Line and word count
- Append a line at the end

## Data structure
A **dynamic array of strings** (`char **lines`) that grows with `realloc`.
It gives direct access to any line by number. The trade-off is that insert
and delete must shift elements, which takes O(n) time. For a small
document this is simple and fast enough.

## How to compile and run
```
gcc -Wall -Wextra editor.c -o editor.exe
.\editor.exe
```
To open an existing file on startup:
```
.\editor.exe notes.txt
```

## Usage
See [HELP.md](HELP.md) for every command with examples.

## Files
- `editor.c` — source code
- `HELP.md` — command reference
- `paper-design.jpg` — hand-written design and core functions
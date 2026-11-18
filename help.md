# Line Editor — Help

A command-line line editor written in C. Type a command at the `>` prompt.
Line numbers start at 1.

## Commands

### Insert a line
`i <n> <text>`
Inserts `<text>` as line `n`, shifting later lines down.
`n` can be from 1 up to (number of lines + 1).
```
> i 1 Hello world
Inserted at line 1.
```

### Append a line
`a <text>`
Adds `<text>` at the end of the document.
```
> a This is the last line
Inserted at line 2.
```

### Delete a line
`d <n>`
Removes line `n`, shifting later lines up.
```
> d 2
Deleted line 2.
```

### Display the document
`p`
Prints every line with its line number.
```
> p
  1 | Hello world
  2 | This is the last line
```

### Save to a file
`s <filename>`
Writes the document to a text file.
```
> s notes.txt
Saved 2 line(s) to 'notes.txt'.
```

### Load from a file
`l <filename>`
Replaces the current document with the contents of the file.
You can also load a file on startup: `editor.exe notes.txt`
```
> l notes.txt
Loaded 2 line(s) from 'notes.txt'.
```

### Search
`f <phrase>`
Shows every line that contains the word or phrase.
```
> f Hello
Found on line 1: Hello world
```

### Count lines and words
`c`
```
> c
Lines: 2, Words: 8
```

### Help
`h` — shows the list of commands.

### Quit
`q` — exits the editor. Unsaved changes are lost, so save first with `s`.

## Error handling
- A line number out of range gives an error message and changes nothing.
- Deleting from an empty document gives an error message.
- Loading a file that does not exist gives an error message.
- An unknown command prints a hint to type `h`.
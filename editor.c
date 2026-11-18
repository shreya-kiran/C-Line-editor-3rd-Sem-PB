/*
 * Simple Line Editor in C
 * Data structure: dynamic array of strings (char **lines + count + capacity)
 * Features: insert, delete, display, save, load, search, word/line count
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

static char **lines = NULL;   /* the document */
static int count = 0;         /* number of lines in use */
static int capacity = 0;      /* allocated slots */

/* Make sure there is room for at least one more line. */
static int ensure_capacity(void) {
    if (count < capacity) return 1;
    int new_cap = (capacity == 0) ? 8 : capacity * 2;
    char **tmp = realloc(lines, new_cap * sizeof(char *));
    if (tmp == NULL) {
        printf("Error: out of memory.\n");
        return 0;
    }
    lines = tmp;
    capacity = new_cap;
    return 1;
}

/* Copy a string onto the heap. */
static char *copy_string(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL) strcpy(p, s);
    return p;
}

/* Insert text so that it becomes line n (1..count+1). */
static void insert_line(int n, const char *text) {
    if (n < 1 || n > count + 1) {
        printf("Error: line number must be between 1 and %d.\n", count + 1);
        return;
    }
    if (!ensure_capacity()) return;
    char *copy = copy_string(text);
    if (copy == NULL) {
        printf("Error: out of memory.\n");
        return;
    }
    for (int i = count; i >= n; i--)      /* shift lines down */
        lines[i] = lines[i - 1];
    lines[n - 1] = copy;
    count++;
    printf("Inserted at line %d.\n", n);
}

/* Delete line n (1..count). */
static void delete_line(int n) {
    if (count == 0) {
        printf("Error: the document is empty.\n");
        return;
    }
    if (n < 1 || n > count) {
        printf("Error: line number must be between 1 and %d.\n", count);
        return;
    }
    free(lines[n - 1]);
    for (int i = n - 1; i < count - 1; i++)   /* shift lines up */
        lines[i] = lines[i + 1];
    count--;
    printf("Deleted line %d.\n", n);
}

/* Print every line with its number. */
static void display(void) {
    if (count == 0) {
        printf("(document is empty)\n");
        return;
    }
    for (int i = 0; i < count; i++)
        printf("%3d | %s\n", i + 1, lines[i]);
}

/* Free all lines and reset the document. */
static void clear_document(void) {
    for (int i = 0; i < count; i++) free(lines[i]);
    count = 0;
}

static void save_file(const char *name) {
    FILE *fp = fopen(name, "w");
    if (fp == NULL) {
        printf("Error: could not open '%s' for writing.\n", name);
        return;
    }
    for (int i = 0; i < count; i++) fprintf(fp, "%s\n", lines[i]);
    fclose(fp);
    printf("Saved %d line(s) to '%s'.\n", count, name);
}

static void load_file(const char *name) {
    FILE *fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error: could not open '%s'.\n", name);
        return;
    }
    clear_document();
    char buf[MAX_INPUT];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (!ensure_capacity()) break;
        char *copy = copy_string(buf);
        if (copy == NULL) break;
        lines[count++] = copy;
    }
    fclose(fp);
    printf("Loaded %d line(s) from '%s'.\n", count, name);
}

/* Bonus: report every line containing the phrase. */
static void search(const char *phrase) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(lines[i], phrase) != NULL) {
            printf("Found on line %d: %s\n", i + 1, lines[i]);
            found++;
        }
    }
    if (found == 0) printf("'%s' not found.\n", phrase);
}

/* Bonus: line and word counts. */
static void stats(void) {
    int words = 0;
    for (int i = 0; i < count; i++) {
        int in_word = 0;
        for (const char *p = lines[i]; *p; p++) {
            if (isspace((unsigned char)*p)) {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                words++;
            }
        }
    }
    printf("Lines: %d, Words: %d\n", count, words);
}

static void print_help(void) {
    printf("Commands:\n");
    printf("  i <n> <text>   insert text as line n\n");
    printf("  a <text>       append text at the end\n");
    printf("  d <n>          delete line n\n");
    printf("  p              print the document\n");
    printf("  s <file>       save to a file\n");
    printf("  l <file>       load from a file\n");
    printf("  f <phrase>     find a word or phrase\n");
    printf("  c              line and word count\n");
    printf("  h              show this help\n");
    printf("  q              quit\n");
}

int main(int argc, char *argv[]) {
    char input[MAX_INPUT];

    if (argc > 1) load_file(argv[1]);   /* optional: editor.exe notes.txt */
    printf("Line Editor - type 'h' for help.\n");

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;   /* EOF */
        input[strcspn(input, "\r\n")] = '\0';

        char cmd = input[0];
        const char *rest = input + 1;
        while (*rest == ' ') rest++;     /* skip spaces after the command */

        if (cmd == '\0') {
            continue;
        } else if (cmd == 'i') {
            char *end;
            long n = strtol(rest, &end, 10);
            if (end == rest) {
                printf("Usage: i <n> <text>\n");
            } else {
                while (*end == ' ') end++;
                insert_line((int)n, end);
            }
        } else if (cmd == 'a') {
            insert_line(count + 1, rest);
        } else if (cmd == 'd') {
            char *end;
            long n = strtol(rest, &end, 10);
            if (end == rest) printf("Usage: d <n>\n");
            else delete_line((int)n);
        } else if (cmd == 'p') {
            display();
        } else if (cmd == 's') {
            if (*rest == '\0') printf("Usage: s <file>\n");
            else save_file(rest);
        } else if (cmd == 'l') {
            if (*rest == '\0') printf("Usage: l <file>\n");
            else load_file(rest);
        } else if (cmd == 'f') {
            if (*rest == '\0') printf("Usage: f <phrase>\n");
            else search(rest);
        } else if (cmd == 'c') {
            stats();
        } else if (cmd == 'h') {
            print_help();
        } else if (cmd == 'q') {
            break;
        } else {
            printf("Unknown command '%c'. Type 'h' for help.\n", cmd);
        }
    }

    clear_document();
    free(lines);
    return 0;
}

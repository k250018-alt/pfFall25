#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 4
#define MAX_LEN 4096

typedef struct {
    char** ln;
    int cnt;
    int cap;
} TxtEd;

TxtEd* createEd();
int insLn(TxtEd* ed, int idx, const char* txt);
int delLn(TxtEd* ed, int idx);
void printAll(const TxtEd* ed);
void freeAll(TxtEd* ed);
int shrink(TxtEd* ed);
int saveFile(const TxtEd* ed, const char* fn);
int loadFile(TxtEd* ed, const char* fn);
char* readLn();


// ------------------------------------------------------------
// Create editor
// ------------------------------------------------------------
TxtEd* createEd() {
    TxtEd* ed = malloc(sizeof(TxtEd));
    if (!ed) {
        fprintf(stderr, "Error: Failed to allocate editor\n");
        return NULL;
    }

    ed->ln = malloc(INIT_CAP * sizeof(char*));
    if (!ed->ln) {
        fprintf(stderr, "Error: Failed to allocate line array\n");
        free(ed);
        return NULL;
    }

    ed->cnt = 0;
    ed->cap = INIT_CAP;

    printf("Editor created\n");
    return ed;
}


// ------------------------------------------------------------
// Corrected insertion function (BUG FIXED)
// ------------------------------------------------------------
int insLn(TxtEd* ed, int idx, const char* txt) {
    if (!ed || !txt) return 0;
    if (idx < 0 || idx > ed->cnt) {
        fprintf(stderr, "Error: Invalid index\n");
        return 0;
    }

    // expand if needed
    if (ed->cnt >= ed->cap) {
        int newCap = ed->cap * 2;
        char** newLn = realloc(ed->ln, newCap * sizeof(char*));
        if (!newLn) {
            fprintf(stderr, "Error: Failed to expand\n");
            return 0;
        }
        ed->ln = newLn;
        ed->cap = newCap;
        printf("Capacity expanded\n");
    }

    // shift lines only once — no rollback needed
    if (idx < ed->cnt) {
        memmove(&ed->ln[idx + 1], &ed->ln[idx], (ed->cnt - idx) * sizeof(char*));
    }

    // allocate new line
    size_t len = strlen(txt);
    char* newStr = malloc(len + 1);
    if (!newStr) {
        fprintf(stderr, "Error: Failed to allocate line\n");
        return 0;
    }

    strcpy(newStr, txt);
    ed->ln[idx] = newStr;

    ed->cnt++;
    return 1;
}


// ------------------------------------------------------------
// Delete a line
// ------------------------------------------------------------
int delLn(TxtEd* ed, int idx) {
    if (!ed) return 0;
    if (idx < 0 || idx >= ed->cnt) {
        fprintf(stderr, "Error: Invalid index\n");
        return 0;
    }

    free(ed->ln[idx]);

    if (idx < ed->cnt - 1) {
        memmove(&ed->ln[idx], &ed->ln[idx + 1], ( ed->cnt - idx - 1 ) * sizeof(char*));
    }

    ed->cnt--;
    printf("Line deleted\n");

    return 1;
}


// ------------------------------------------------------------
// Print all lines
// ------------------------------------------------------------
void printAll(const TxtEd* ed) {
    if (!ed) return;

    printf("\nLines: %d/%d\n", ed->cnt, ed->cap);

    if (ed->cnt == 0) {
        printf("(empty)\n\n");
        return;
    }

    for (int i = 0; i < ed->cnt; i++) {
        printf("%d: %s\n", i, ed->ln[i]);
    }
    printf("\n");
}


// ------------------------------------------------------------
// Shrink array
// ------------------------------------------------------------
int shrink(TxtEd* ed) {
    if (!ed) return 0;

    if (ed->cnt < ed->cap) {
        int newCap = ed->cnt == 0 ? 1 : ed->cnt;
        char** newLn = realloc(ed->ln, newCap * sizeof(char*));

        if (!newLn) {
            fprintf(stderr, "Warning: Failed to shrink\n");
            return 0;
        }

        ed->ln = newLn;
        ed->cap = newCap;

        printf("Memory optimized\n");
        return 1;
    }

    printf("Already optimal\n");
    return 1;
}


// ------------------------------------------------------------
// Save to file
// ------------------------------------------------------------
int saveFile(const TxtEd* ed, const char* fn) {
    if (!ed || !fn) return 0;

    FILE* f = fopen(fn, "w");
    if (!f) {
        fprintf(stderr, "Error: Cannot open file\n");
        return 0;
    }

    for (int i = 0; i < ed->cnt; i++) {
        fprintf(f, "%s\n", ed->ln[i]);
    }

    fclose(f);
    printf("Saved\n");
    return 1;
}


// ------------------------------------------------------------
// Load from file
// ------------------------------------------------------------
int loadFile(TxtEd* ed, const char* fn) {
    if (!ed || !fn) return 0;

    FILE* f = fopen(fn, "r");
    if (!f) {
        fprintf(stderr, "Error: Cannot open file\n");
        return 0;
    }

    // clear old lines
    for (int i = 0; i < ed->cnt; i++) free(ed->ln[i]);
    ed->cnt = 0;

    char buf[MAX_LEN];

    while (fgets(buf, MAX_LEN, f)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';

        if (!insLn(ed, ed->cnt, buf)) {
            fprintf(stderr, "Error: Failed to load line\n");
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    printf("Loaded\n");
    return 1;
}


// ------------------------------------------------------------
// Read a line from stdin
// ------------------------------------------------------------
char* readLn() {
    char buf[MAX_LEN];

    if (!fgets(buf, MAX_LEN, stdin)) return NULL;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    }

    char* s = malloc(len + 1);
    if (!s) {
        fprintf(stderr, "Error: Failed to allocate\n");
        return NULL;
    }

    strcpy(s, buf);
    return s;
}


// ------------------------------------------------------------
// Free everything
// ------------------------------------------------------------
void freeAll(TxtEd* ed) {
    if (!ed) return;

    for (int i = 0; i < ed->cnt; i++)
        free(ed->ln[i]);

    free(ed->ln);
    free(ed);

    printf("Memory freed\n");
}


// ------------------------------------------------------------
// Main program
// ------------------------------------------------------------
int main() {
    printf("Text Editor\n\n");

    TxtEd* ed = createEd();
    if (!ed) return 1;

    int run = 1;

    while (run) {
        printf("1.Insert 2.Delete 3.Print 4.Shrink 5.Save 6.Load 7.Exit\n");
        printf("Choice: ");

        char buf[32];
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        int ch = atoi(buf);

        switch (ch) {

            case 1: {
                printf("Index: ");
                fgets(buf, sizeof(buf), stdin);
                int idx = atoi(buf);

                printf("Text: ");
                char* txt = readLn();
                if (txt) {
                    if (insLn(ed, idx, txt))
                        printf("Inserted\n");
                    free(txt);
                }
                break;
            }

            case 2: {
                printf("Index: ");
                fgets(buf, sizeof(buf), stdin);
                int idx = atoi(buf);

                delLn(ed, idx);
                break;
            }

            case 3:
                printAll(ed);
                break;

            case 4:
                shrink(ed);
                break;

            case 5: {
                printf("Filename: ");
                char* fn = readLn();
                if (fn) {
                    saveFile(ed, fn);
                    free(fn);
                }
                break;
            }

            case 6: {
                printf("Filename: ");
                char* fn = readLn();
                if (fn) {
                    loadFile(ed, fn);
                    free(fn);
                }
                break;
            }

            case 7:
                run = 0;
                printf("Exiting\n");
                break;

            default:
                fprintf(stderr, "Invalid choice\n");
        }
    }

    freeAll(ed);
    return 0;
}

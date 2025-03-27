#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple structs for items and lists
/* self-referential structure */
struct item {
    char name[50]; /* each listNode contains a character */
    struct item *next;/* pointer to next node */
};/* end structure item */ 

struct list {
    char name[50];
    Item *items;
    struct List *next;
};

List *board = NULL;

typedef struct list List;
typedef struct item Item; /* synonym for struct listNode */

//generic file processing code
void loadBoardFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    
    fclose(file);
}


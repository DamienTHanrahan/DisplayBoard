#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple structs for items and lists
/* self-referential structure */
typedef struct item {
    char name[50]; /* each listNode contains a character */
    struct item *next;/* pointer to next node */
}Item;/* end structure item */ 

typedef struct list {
    char name[50];
    Item *items;
    struct list *next;
}List;

List *board = NULL;
    // prototypes
    void displayBoard();
    void loadBoardFromFile(char *filename);
    void addList(char *name);
    List* findList(char *name);
    void addItemToList(List *list, char *itemName);


//generic file processing code
void loadBoardFromFile(char *filename) {
    FILE *file = fopen(filename, "r"); // open for reading
    int lineNum = 0; // Initialize lineNum

    if (!file) {
        printf("Error: could not open file %s\n", filename);
        return;
    }
    else {
        char listName[50], itemName[50];
        char linebreak[50]; 
        while (fgets(linebreak, sizeof(linebreak), file) != NULL) {
            size_t len = strlen(linebreak);
            if (len > 0 && linebreak[len - 1] == '\n') {
                linebreak[len - 1] = '\0'; 
            }
            strcpy (listName, linebreak);
            addList(listName);
            List *list = findList(listName);
            while (fgets(linebreak, sizeof(linebreak), file) != NULL && strcmp(linebreak, "-") != 0) {
                size_t len = strlen(linebreak);
            if (len > 0 && linebreak[len - 1] == '\n') {
                linebreak[len - 1] = '\0'; 
            }
                strcpy (itemName, linebreak);
                addItemToList(list, itemName); 
            }
        }
        
    }
        fclose(file);
}
// displays the loaded file   
void displayBoard() {
    List *current = board;
    if (current == NULL) {
        printf("Board is empty.\n");
        return;
    }
    while (current != NULL) {
        printf("%s:\n", current->name);
        Item *item = current->items;
        while (item != NULL) {
            printf("    %s\n", item->name);
            item = item->next;
        }
        current = current->next;
    }
}





int main() {

    char *WEATHER_FILE_PATH = "weather.txt";
    loadBoardFromFile(WEATHER_FILE_PATH);
    
   int choice;
   while (1) {
       printf("\nMenu:\n");
       printf("1. Display board\n");
       printf("2. Load board from a file\n");
       printf("3. Edit list\n");
       printf("4. Edit Board\n");
       printf("5. Save board to a file\n");
       printf("6. Quit\n");
       printf("Enter your choice: ");
       scanf("%d", &choice);
       getchar();

       if (choice == 6) {
           printf("Bye!\n");
           
           break;
       }

       if (choice == 1) {
           displayBoard();
       } else if (choice == 2) {
           char filename[50];
           printf("Enter filename: ");
           scanf("%s", filename);
           loadBoardFromFile(filename);
       } else if (choice == 3) {
           //editList();
       } else if (choice == 4) {
           //editBoard();
       } else if (choice == 5) {
           //saveBoardToFile();
       } else {
           printf("Invalid choice. Try again.\n");
       }
   }


    return 0;
}

void addItemToList(List *list, char *itemName) {
    Item *newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, itemName);
    newItem->next = list->items;
    list->items = newItem;
}

void addList(char *name) {  
    List *newList = (List*)malloc(sizeof(List));
    strcpy(newList->name, name);
    newList->items = NULL;
    newList->next = board;
    board = newList;
}

List* findList(char *name) {
    List *current = board;
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
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
    void editBoard();
    void loadBoardFromFile(char *filename);
    void addList(char *name);
    List* findList(char *name);
    void addItemToList(List *list, char *itemName);
    void editList(List *list);
    void printItems(List *list);
    Item* findItem(List *list, char *name);
    void editItem(Item *item);
    void deleteItemFromList(List *list, char *name);
    void editListName(char *name);
    void deleteListFromBoard (char *name);
    void printLists();
    void clearBoard();
    


//generic file processing code
void loadBoardFromFile(char *filename) {
    // empty lists
    clearBoard();
    FILE *file = fopen(filename, "r"); // open for reading
    int lineNum = 0; // Initialize lineNum

    if (!file) {
        //error handling
        printf("Error: could not open file %s\n", filename);
        return;
    }
    else {
        char listName[50], itemName[50];
        char linebreak[50]; // copy in the lines and add them using helper functions
        while (fgets(linebreak, sizeof(linebreak), file) != NULL) {
            size_t len = strlen(linebreak);
            if (len > 0 && linebreak[len - 1] == '\n') {
                linebreak[len - 1] = '\0'; 
            }
            strcpy (listName, linebreak);
            addList(listName);
            List *list = board;
            while (fgets(linebreak, sizeof(linebreak), file) != NULL) {
                size_t len = strlen(linebreak);
            if (len > 0 && linebreak[len - 1] == '\n') {
                linebreak[len - 1] = '\0'; 
            }
               if (strcmp(linebreak, "-") == 0) { break;}
               else {

                strcpy (itemName, linebreak);
                addItemToList(list, itemName); 
               }
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
    // load pre defined board
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
           char listName[50];
           printf("Enter the name of the list to edit: ");
           fgets(listName, sizeof(listName), stdin);
           size_t len = strlen(listName);
            if (len > 0 && listName[len - 1] == '\n') {
                listName[len - 1] = '\0'; 
            }
            List *list = findList(listName);
            editList(list); 

           

           
        
        
           //editList();
       } else if (choice == 4) {

        editBoard ();


           //editBoard();
       } else if (choice == 5) {
           //saveBoardToFile();
       } else {
           printf("Invalid choice. Try again.\n");
       }
   }


    return 0;
}
// add item in correct location
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

// search for list
List* findList(char *name) {
    List *current = board;
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
Item* findItem(List *list, char *name) {
    Item *current = list->items;
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
// edit individul list
void editList (List *list) {

    int choice;
    while (1) {
        
        
        printf("\nOptions:\n");
        printf("1. Edit an item\n");
        printf("2. Add a new item\n");
        printf("3. Delete an item\n");
        printf("4. Display list items\n");
        printf("5. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 5) {
            
            break;
        }
        else if (choice == 1) {

            char itemName[50];
                printf("Enter the name of the item to edit: ");
                fgets(itemName, sizeof(itemName), stdin);
                size_t len = strlen(itemName);
                 if (len > 0 && itemName[len - 1] == '\n') {
                     itemName[len - 1] = '\0'; 
                 }
                 Item *newItem = findItem(list, itemName);
                 editItem(newItem); 




        }
        else if (choice == 2) {
            

                char itemName[50];
                printf("Enter the name of the item to add: ");
                fgets(itemName, sizeof(itemName), stdin);
                size_t len = strlen(itemName);
                 if (len > 0 && itemName[len - 1] == '\n') {
                     itemName[len - 1] = '\0'; 
                 }

                 addItemToList(list, itemName);



        }
        else if (choice == 3) {
                char itemName[50];
                printf("Enter the name of the item to delete: ");
                fgets(itemName, sizeof(itemName), stdin);
                size_t len = strlen(itemName);
                 if (len > 0 && itemName[len - 1] == '\n') {
                     itemName[len - 1] = '\0'; 
                 }

                 deleteItemFromList (list, itemName);

        }
        else if (choice == 4) {

            printItems(list);

        }
        

    }




}

void printItems (List *list) {

    printf("The items in your chosen list are:\n");
    Item *current = list->items;
    while (current) {
    printf("%s\n", current->name); 
        current = current->next; 
    }
}

void editItem(Item *item) {
    
    printf("Enter the new name for %s:\n", item->name);
    fgets(item->name, sizeof(item->name), stdin);
                size_t len = strlen(item->name);
                 if (len > 0 && item->name[len - 1] == '\n') {
                     item->name[len - 1] = '\0'; 
                 }
     
                 

}
void deleteItemFromList (List *list, char* name) {

    
    
    Item *current = list->items;
    Item *anteCurrent = NULL; 
    while (current != NULL) {
        if (strcmp (current->name, name) == 0) {

            if (anteCurrent == NULL) {
                list->items = current->next;
            }
            else {
                anteCurrent->next = current->next;
            }

            free (current);
            return;

            


            
            
        } 

        else {
            anteCurrent = current; 
            current = current->next; 
        }
        
    }  

    
    


}
//edit entire board
void editBoard () {

    int choice;

    while (1) {

        
        
        printf("\nOptions:\n");
        printf("1. Edit the name of a list\n");
        printf("2. Add a new list\n");
        printf("3. Delete a list\n");
        printf("4. Display lists\n");
        printf("5. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 5) {
            
            break;
        }
        else if (choice == 1) {

            char listName[50];
                printf("Enter the name of the item to edit: ");
                fgets(listName, sizeof(listName), stdin);
                size_t len = strlen(listName);
                 if (len > 0 && listName[len - 1] == '\n') {
                     listName[len - 1] = '\0'; 
                 }
                
                 editListName(listName);




        }
        else if (choice == 2) {
            

                char listName[50];
                printf("Enter the name of the list to add: ");
                fgets(listName, sizeof(listName), stdin);
                size_t len = strlen(listName);
                 if (len > 0 && listName[len - 1] == '\n') {
                     listName[len - 1] = '\0'; 
                 }

                 addList(listName);



        }
        else if (choice == 3) {
                char listName[50];
                printf("Enter the name of the list to delete: ");
                fgets(listName, sizeof(listName), stdin);
                size_t len = strlen(listName);
                 if (len > 0 && listName[len - 1] == '\n') {
                     listName[len - 1] = '\0'; 
                 }

                 deleteListFromBoard (listName);

        }
        else if (choice == 4) {

            printLists();

        }
        

    }




}

void editListName(char *name) {
    List *current = findList (name); 
    printf("Please enter the new name for the list %s\n", current->name);
    fgets(current->name, sizeof(current->name), stdin);
                size_t len = strlen(current->name);
                 if (len > 0 && current->name[len - 1] == '\n') {
                     current->name[len - 1] = '\0'; 
                 }

}

void deleteListFromBoard (char *name){

    List *current = board;
    List *anteCurrent = NULL; 
    while (current != NULL) {
        if (strcmp (current->name, name) == 0) {

            if (anteCurrent == NULL) {
                board = current->next;
            }
            else {
                anteCurrent->next = current->next;
            }

            free (current);
            return;

            


            
            
        } 

        else {
            anteCurrent = current; 
            current = current->next; 
        }
        
    }

}

void printLists() {
    printf("The lists on this board are:\n");
    List *current = board;
    while (current) {
    printf("%s\n", current->name); 
        current = current->next; 
    }
}
// clear the lists 
void clearBoard() {

    List *current = board;
    List *anteCurrent = NULL;
    
    while (current != NULL) {
         
        Item *currentItem = current->items;
        Item *anteCurrentItem = NULL; 
        while (currentItem != NULL) {
            anteCurrentItem = currentItem;
            currentItem = currentItem->next;
            free (anteCurrentItem); 
        }
        anteCurrent = current;
        current = current->next;
        free (anteCurrent);  
        
        
    }

    board = NULL; 

}


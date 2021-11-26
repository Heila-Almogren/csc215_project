#include <stdio.h>
#include <stdlib.h>
//ff
typedef struct {
    int id;
    char name[20];
    int age;
    char gender;
    char address[7];
} Companion;

typedef struct {
    int yy;
    int mm;
    int dd;
} Date;


// Attendee struct
typedef struct {
    int id;
    char name[20];
    int age;
    char state;
    char address[7];
    char ActivityZone[35];
    int numOfCompanion;
    struct Companion **listOfCompanion;
    float totalFees;
    float balance;
    float activityFee;
    struct Date *date;
} Attendee;


typedef struct {
    char name[35];
    float price;
    Date startDate;
    Date endDate;
    int freePassAge;
    int ageRestriction;

} activity;

struct node {
    Attendee val;
    struct node *next;
};

void readFile(); //Heila Al-Mogren
void showMainMenu(); //Alanoud Al-ashSheikh
void addNewAttendee(); //Alanoud KG
void editRecord();

void editActivity();

void showAttendeeReport();

void showAttendee();

void deleteRecord();

void writeAttendee(char *fileName);

void printList();

// Data structures
void deleteNode(struct node **head, int id);
void printList(struct node * head);
void insertAtEnd(struct node **head, Attendee attendee);
void insertAtBeginning(struct node **head, Attendee attendee);


int main() {

    struct node *registered_head, *prev, *cur;
    registered_head = (struct node *) malloc(sizeof(struct node));


    Attendee registered;
    registered_head->val = registered;

    struct node *singleVisit_head;
    singleVisit_head = (struct node *) malloc(sizeof(struct node));

    // allocate memory for activity list (array)
    activity *ActivitiesList = (activity *) calloc(10, sizeof(activity));

    // read file and fill activity list
    readFile();

    struct node singleVisit;

    return 0;
}

void readFile() {

}

void showMainMenu() {

}

void insertAtBeginning(struct node **head, Attendee attendee) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->val = attendee;
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct node **head, Attendee attendee){
    if (*head == NULL) { //if the list is empty
        *head = (struct node *) malloc(sizeof(struct node));
        (*head)->val = attendee;
        (*head)->next = NULL; }
    else { //if the list has at least one node
        struct node * current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
/* now we can add a new variable */
        current->next = (struct node *)malloc(sizeof(struct node));
        current->next->val = attendee;
        current->next->next = NULL;
    } }


void printList(struct node * head) {
    struct node * current = head;
    while(current != NULL)
    {
        printf("%d->",current->val); // edit this to show the details of attendee
        current = current ->next;
    }
}


void deleteNode(struct node **head, int id) {
    if (*head != NULL) {
        if ((*head)->val.id == id) { //if the deleted node is the first node
            struct node * temp = *head;
            *head = (*head)->next;
            free(temp);
        }
        else {
            struct node *prev = *head;
            struct node *cur = (*head)->next ;
            while (cur != NULL) {
                if (cur->val.id == id) {
                    prev->next = cur->next;
                    free(cur);
                    break; } //exit loop when delete the node
                prev = cur;
                cur = cur ->next;
            } } } }
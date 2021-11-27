#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void printList(struct node *head);

void insertAtEnd(struct node **head, Attendee attendee);

void insertAtBeginning(struct node **head, Attendee attendee);

// Testing methods (to be deleted later)
void test_readFile(activity activities[]);


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


    activity *activities = NULL;
    int nActivities = 0;

    FILE *fp;
    fp = fopen("../Activities.txt", "r");
    char tx[200];
    char name[35];
    double price = 0;
//    Date startDate;
//    Date endDate;
    int freePassAge = 0;
    int ageRestriction = 0;
    char fullDate[50];

    char startDate_dd[33];
    char startDate_mm[33];
    char startDate_yy[33];
    char endDate_dd[33];
    char endDate_mm[33];
    char endDate_yy[33];


    char *eof;
    int line_counter = 0;

    // Skip first two lines
    eof = fgets(tx, 200, fp);
    eof = fgets(tx, 200, fp);

    while (eof) {

        activities = realloc(activities, (nActivities + 1) * sizeof(activity));
        activity ac;

        // Get name
        eof = fgets(tx, 33, fp);
        sscanf(tx, "%[^\\n]s", name);
        // Remove extra space
        char *last = name + strlen(name);
        while (isspace(*--last));
        *(last + 1) = '\0';
        strcpy(ac.name, name);

        // Get Price
        eof = fgets(tx, 18, fp);
        sscanf(tx, "%lf", &price);
        ac.price = price;

        // Get date
        eof = fgets(tx, 32, fp);
        printf("Date: %s\n", tx);
        sscanf(tx, "%s", fullDate);
        printf("Full date is is %s\n", fullDate);
//        2021/11/01-2022/04/01

        sscanf(tx, "%s", fullDate);
        //start date (day)
        strcpy(startDate_dd, tx);

        *(startDate_dd + 4) = '\0';
        sscanf(startDate_dd, "%d", &ac.startDate.dd);

        //start date (month)
        strcpy(startDate_mm, tx + 5);
        *(startDate_mm + 2) = '\0';
        sscanf(startDate_mm, "%d", &ac.startDate.mm);

        //start date (year)
        strcpy(startDate_yy, tx + 8);
        *(startDate_yy + 2) = '\0';
        sscanf(startDate_yy, "%d", &ac.startDate.yy);


        //end date (day)
        strcpy(endDate_dd, tx+11);
        *(endDate_dd + 4) = '\0';
        sscanf(endDate_dd, "%d", &ac.endDate.dd);

        //end date (month)
        strcpy(endDate_mm, tx + 16);
        *(endDate_mm + 2) = '\0';
        sscanf(endDate_mm, "%d", &ac.endDate.mm);

        //end date (year)
        strcpy(endDate_yy, tx + 19);
        *(endDate_yy + 2) = '\0';
        sscanf(endDate_yy, "%d", &ac.endDate.yy);





        // ignore the <
        eof = fgets(tx, 2, fp);
        printf("Ignored sign: %s\n", tx);

        if (strcmp(tx, "-") == 0) {
            freePassAge = -1;
            eof = fgets(tx, 19, fp);
        } else {
            // Get FREEPASS
            eof = fgets(tx, 19, fp);
            printf("Free pass: %s\n", tx);
            sscanf(tx, "%d", &freePassAge);
        }

        // ignore the > or
        eof = fgets(tx, 2, fp);
        printf("Ignored sign: %s\n", tx);

        if (strcmp(tx, "-") == 0) {
            ageRestriction = -1;
            eof = fgets(tx, 20, fp);
        } else {
            // Get minimum age
            eof = fgets(tx, 20, fp);
            printf("Min Age: %s\n", tx);
            sscanf(tx, "%d", &ageRestriction);
        }

        line_counter++;


        ac.freePassAge = freePassAge;
        ac.ageRestriction = ageRestriction;

        *(activities + nActivities) = ac;
        nActivities++;
    };

    fclose(fp);

    test_readFile(activities);
}

void test_readFile(activity activities[]) {

    for (int i = 0; i < 10; i++) {
        printf("%d | Name: %-32s\t Price: %-18lf\t Date:%d/%d/%d-%d/%d/%d \t freePassAge:%d\t ageRestriction: %d\n",
               i + 1,
               activities[i].name,
               activities[i].price,
               activities[i].startDate.dd,
               activities[i].startDate.mm,
               activities[i].startDate.yy,
               activities[i].endDate.dd,
               activities[i].endDate.mm,
               activities[i].endDate.yy,
               activities[i].freePassAge,
               activities[i].ageRestriction
        );

    }
}

void showMainMenu() {

}

void insertAtBeginning(struct node **head, Attendee attendee) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->val = attendee;
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct node **head, Attendee attendee) {
    if (*head == NULL) { //if the list is empty
        *head = (struct node *) malloc(sizeof(struct node));
        (*head)->val = attendee;
        (*head)->next = NULL;
    } else { //if the list has at least one node
        struct node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
/* now we can add a new variable */
        current->next = (struct node *) malloc(sizeof(struct node));
        current->next->val = attendee;
        current->next->next = NULL;
    }
}


void printList(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d->", current->val); // edit this to show the details of attendee
        current = current->next;
    }
}


void deleteNode(struct node **head, int id) {
    if (*head != NULL) {
        if ((*head)->val.id == id) { //if the deleted node is the first node
            struct node *temp = *head;
            *head = (*head)->next;
            free(temp);
        } else {
            struct node *prev = *head;
            struct node *cur = (*head)->next;
            while (cur != NULL) {
                if (cur->val.id == id) {
                    prev->next = cur->next;
                    free(cur);
                    break;
                } //exit loop when delete the node
                prev = cur;
                cur = cur->next;
            }
        }
    }
}
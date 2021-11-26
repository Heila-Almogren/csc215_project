#include <stdio.h>
#include <stdlib.h>

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
    struct Date date[];
} Attendee;


struct activity {
    char name[35];
    float price;
    Date startDate;
    Date endDate;
    int freePassAge;
    int ageRestriction;
};

struct node {
    Attendee val;
    struct node *next;
};

void readFile();


int main() {

    struct node *registered_head;
    registered_head = (struct node *) malloc(sizeof(struct node));
    Attendee registered;
    registered_head->val = registered;

    struct node *singleVisit_head;
    singleVisit_head = (struct node *) malloc(sizeof(struct node));

    // allocate memory for activity list (array)

    // read file and fill activity list
    readFile();

    struct node singleVisit;

    return 0;
}



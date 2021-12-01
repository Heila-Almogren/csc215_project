#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

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

typedef struct {
    Date date;
    int attendeeCounter;
} Day;

// Attendee struct
struct Attendee {
    int id;
    char name[20];
    int age;
    char state;
    char address[7];
    char ActivityZone[35];
    int numOfCompanion;
    Companion *listOfCompanion;
    float totalFees;
    float balance;
    float activityFee;
    Date *date;
    struct Attendee *next;
};


typedef struct {
    char name[35];
    float price;
    Date startDate;
    Date endDate;
    int freePassAge;
    int ageRestriction;
    int nDays;
    Day *days;
} Activity;


void readFile(); //Heila Al-Mogren
void test_readFile(Activity activities[]);

void showMainMenu(); //Alanoud Al-ashSheikh
void addNewAttendee(); //Alanoud KG
void editRecord();

void editActivity();//Heila Al-Mogren

void showAttendeeReport();

void showAttendee();

void deleteRecord();

void writeAttendee(char *fileName);

bool isDateInFuture(char date[]);

void printList();

void getDaysList(Activity *activity, Date firstDate, Date lastDate);

bool isDateValid(char date[]);

bool isDateFormatValid(char date[]);

int compareDates(Date date1, Date date2);

void assignDate(Date *date, char stringDate[]);


struct Attendee *registered = NULL;
struct Attendee *singleVisit = NULL;
struct Attendee *registered_head, *singleVisit_head, *registered_cur, *singleVisit_cur;
Activity *activities = NULL;


int main() {


    // read file and fill Activity list
    readFile();
    getDaysList(activities, activities->startDate, activities->endDate);

    return 0;
}


void addNewAttendee() {
    struct Attendee *temp = (struct Attendee *) malloc(sizeof(struct Attendee));

    printf("Enter The Attende ID:");
    scanf("%d", &temp->id);

    printf("Enter The Attende Name:");
    scanf("%s", temp->name);

    printf("Enter The Attende Age:");
    scanf("%d", &temp->age);

    printf("Enter The Attende Addres as (3 alphabet characters then 3 digits):");
    scanf("%s", temp->address);

    printf("Enter numuer Of Companion:");
    scanf("%d", &temp->numOfCompanion);
    if (temp->numOfCompanion = 0) {
        temp->state = 'V';
        temp->listOfCompanion = NULL;
    } else if (temp->numOfCompanion > 0) {
        temp->state = 'R';

        temp->listOfCompanion = (Companion *) calloc(temp->numOfCompanion, sizeof(Companion));
        Companion Ctemp;
        int i;

        for (i = 0; i < temp->numOfCompanion; i++) {
            // ctemp = NULL ;
            printf("Enter #%d  Companion ID:", (i + 1));
            scanf("%d", &Ctemp.id);

            printf("Enter #%d  Companion Name:", (i + 1));
            scanf("%s", Ctemp.name);

            printf("Enter #%d  Companion Age:", (i + 1));
            scanf("%d", &Ctemp.age);

            printf("Enter The Attende Addres as (3 alphabet characters then 3 digits):", (i + 1));
            scanf("%d", &Ctemp.address);

            *(temp->listOfCompanion + i) = Ctemp;
        }//end loop

    }//end if val.state == 'R'


    printf("Enter the day of your Reservation ");
    scanf("%d", temp->date->dd);
    printf("Enter the month of your Reservation ");
    scanf("%d", temp->date->mm);
    printf("Enter the year of your Reservation ");
    scanf("%d", temp->date->yy);

    char tempActivityZone[35];
    bool ActivityFound = false;

    int j;

    while (!ActivityFound) {
        printf("Enter The ActivityZone:");
        scanf("%s", tempActivityZone);

        for (j = 0; j < 10; j++) {//its better to change 10 with the number of activities
            Activity TempPName = *(activities + j);
            if (strstr(TempPName.name, tempActivityZone) != NULL) { //tempActivityZone.equals( TempPName.name )??
                strcpy (temp->ActivityZone, tempActivityZone);
                temp->activityFee = TempPName.price;
                temp->totalFees =
                        temp->numOfCompanion > 0 ? (temp->activityFee + (temp->numOfCompanion * temp->activityFee))
                                                 : temp->activityFee;
                ActivityFound = true;
                break;
            }
        }
        if (!ActivityFound)
            printf("Sorry This Activity name dose not match any Activity :( .. Try again ");
    }//end will

    //bool enough_amount = true ;
    while (1) {
        printf("Enter The Attende Balance:");
        scanf("%f", &temp->balance);

        if ((temp->balance) < (temp->totalFees))
            printf("Sorry you need to recharge your Balance to To complete the reservation .. Try again ");
        else
            break;
    }


    if (temp->numOfCompanion > 0) { //add the record to the registered linked list
        if (registered_head == NULL) { //if the list is empty
            registered_head = (struct Attendee *) malloc(sizeof(struct Attendee));
            (registered_head) = temp;
            (registered_head)->next = NULL;
        } else { //if the list has at least one node
            registered_cur = registered_head;
            while (registered_cur->next != NULL)
                registered_cur = registered_cur->next;
        }
    } else {//add the record to the singleVisit linked list
        if (singleVisit_head == NULL) { //if the list is empty
            singleVisit_head = (struct Attendee *) malloc(sizeof(struct Attendee));
            (singleVisit_head) = temp;
            (singleVisit_head)->next = NULL;
        } else { //if the list has at least one node
            singleVisit_cur = singleVisit_head;
            while (singleVisit_cur->next != NULL)
                singleVisit_cur = singleVisit_cur->next;
        }
    }


}//end addNewAttendee


void readFile() {


    int nActivities = 0;

    FILE *fp;
    fp = fopen("../Activities.txt", "r");

    if (fp == NULL) {
        printf("Can’t open %s\n", "Activities.txt");
        return;
    }


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

        activities = realloc(activities, (nActivities + 1) * sizeof(Activity));
        Activity ac;

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
        //start date (Year)
        strcpy(startDate_yy, tx);

        *(startDate_yy + 4) = '\0';
        sscanf(startDate_yy, "%d", &ac.startDate.yy);

        //start date (month)
        strcpy(startDate_mm, tx + 5);
        *(startDate_mm + 2) = '\0';
        sscanf(startDate_mm, "%d", &ac.startDate.mm);

        //start date (Day)
        strcpy(startDate_dd, tx + 8);
        *(startDate_dd + 2) = '\0';
        sscanf(startDate_dd, "%d", &ac.startDate.dd);


        //end date (Year)
        strcpy(endDate_yy, tx + 11);
        *(endDate_yy + 4) = '\0';
        sscanf(endDate_yy, "%d", &ac.endDate.yy);

        //end date (month)
        strcpy(endDate_mm, tx + 16);
        *(endDate_mm + 2) = '\0';
        sscanf(endDate_mm, "%d", &ac.endDate.mm);

        //end date (Day)
        strcpy(endDate_dd, tx + 19);
        *(endDate_dd + 2) = '\0';
        sscanf(endDate_dd, "%d", &ac.endDate.dd);





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

void test_readFile(Activity activities[]) {
    int i;
    for (i = 0; i < 10; i++) {
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

int maxDaysDependingOnMonth(int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    } else {
        if (month == 2) { // feb
            return 28;
        } else {
            return 30;
        }
    }
}

void testDaysList(int nDaysDifference, Day *daysList) {

    printf("Testing");
    int i;
//    for(i=0; i<nDaysDifference; i++) {
//        printf("%d | %d/%d/%d\n ",
//        i+1,
//        (daysList + i)->date.yy,
//        (daysList + i)->date.mm,
//        (daysList + i)->date.dd);
//    }

}

void getDaysList(Activity *activity, Date firstDate, Date lastDate) {

    struct tm date1;
    date1.tm_year = firstDate.yy - 1900;
    date1.tm_mon = firstDate.mm - 1;
    date1.tm_mday = firstDate.dd;
    date1.tm_hour = 0;
    date1.tm_min = 0;
    date1.tm_sec = 0;
    // Heila: I used this to solve this problem https://stackoverflow.com/questions/26788470/difftime-returns-strange-value-on-particular-date
    date1.tm_isdst = -1;

    struct tm date2;
    date2.tm_year = lastDate.yy - 1900;
    date2.tm_mon = lastDate.mm - 1;
    date2.tm_mday = lastDate.dd;
    date2.tm_hour = 0;
    date2.tm_min = 0;
    date2.tm_sec = 0;
    date2.tm_isdst = -1;


    printf("Year: %d\t", date1.tm_year + 1900);
    printf("Month: %d\t", date1.tm_mon + 1);
    printf("Day: %d\n", date1.tm_mday);
    printf("Year: %d\t", date2.tm_year + 1900);
    printf("Month: %d\t", date2.tm_mon + 1);
    printf("Day: %d\t", date2.tm_mday);


    int daysDifference = (int)(difftime(mktime(&date2), mktime(&date1))) / 60 / 60 / 24;
    printf("Date Difference = %d Days\n", daysDifference);
    activity->nDays = (int) daysDifference;

//    Day *daysList = (Day *) calloc(daysDifference, sizeof(Day));

//    Date currentDate = firstDate;
//
//    int i;
//    for (i = 0; i < daysDifference; i++) {
//        (daysList + i)->date.yy = currentDate.yy;
//        (daysList + i)->date.mm = currentDate.mm;
//        (daysList + i)->date.dd = currentDate.dd;
//
//        if (currentDate.dd != lastDate.dd || currentDate.mm != lastDate.mm || currentDate.yy != lastDate.yy) {
//            if (currentDate.dd < maxDaysDependingOnMonth(currentDate.mm)) {
//                currentDate.dd++;
//            } else {
//                if (currentDate.mm < 12) {
//                    currentDate.mm++;
//                } else {
//                    currentDate.yy++;
//                }
//            }
//
//        }
//    }
//
//    testDaysList(daysDifference, daysList);
}


void editActivity() {

    /*
     * char name[35];
    float price;
    Date startDate;
    Date endDate;
    int freePassAge;
    int ageRestriction;
     */

    char activity_name[53];
    bool found = false;
    printf("Enter the name of the Activity you want to edit\n> ");
    scanf("%[^\n]s", activity_name);
    int i;
    for (i = 0; i < 10; i++) {
//        printf("%s VS %s\n", activities[i].name, activity_name);
        if (strcmp(activities[i].name, activity_name) == 0) {
            found = true;
            printf("Activity found!\nWhat Do you to edit:\n");
            printf("1. Activity Name\n");
            printf("2. Activity Price\n");
            printf("3. Activity Start Date\n");
            printf("4. Activity End Date\n");
            printf("5. Activity Free Pass Age\n");
            printf("6. Activity Age Restriction\n> ");
            int option;
            bool valid_option;
            do {
                valid_option = true;
                scanf("%d", &option);
                switch (option) {
                    case 1: {
                        char new_name[30];
                        printf("Enter the new name:\n> ");
                        scanf(" %[^\n]s", new_name);
                        strcpy(activities[i].name, new_name);
                        printf("Done! ✨");
                    };
                        break;
                    case 2: {
                        float new_price;
                        printf("Enter the new price:\n> ");
                        scanf(" %f", &new_price);
                        activities[i].price = new_price;
                        printf("Done! ✨");
                    };
                        break;
                    case 3: {
                        bool valid_date = true;
                        printf("Enter the new start date (in the format yyyy/mm/dd):\n> ");
                        char new_startDate[30];
                        do {
                            valid_date = true;
                            scanf(" %[^\n]s", new_startDate);

                            if (!isDateValid(new_startDate)) {
                                valid_date = false;
                                if (!isDateFormatValid(new_startDate)) {
                                    printf("Date format is invalid, please re-enter the date:\n> ");
                                } else {
                                    if (!isDateInFuture(new_startDate)) {
                                        printf("Date is in the past, please re-enter the date:\n> ");
                                    }
                                }
                            }
                        } while (!valid_date);

                        assignDate(&(activities[i].startDate), new_startDate);
                        printf("result: %d/%d/%d", activities[i].startDate.yy, activities[i].startDate.mm,
                               activities[i].startDate.dd);
                        printf("Done! ✨");
                    };
                        break;
                    case 4: {

                        bool valid_date = true;
                        printf("Enter the new end date (in the format yyyy/mm/dd):\n> ");
                        char new_endDate[30];
                        do {
                            valid_date = true;
                            scanf(" %[^\n]s", new_endDate);

                            if (!isDateValid(new_endDate)) {
                                valid_date = false;
                                if (!isDateFormatValid(new_endDate)) {
                                    printf("Date format is invalid, please re-enter the date:\n> ");
                                } else {
                                    if (!isDateInFuture(new_endDate)) {
                                        printf("Date is in the past, please re-enter the date:\n> ");
                                    }
                                }
                            } else {
                                Date dateToCompare;
                                assignDate(&(dateToCompare), new_endDate);
                                if (compareDates(activities[i].startDate, dateToCompare) < 0) {
                                    valid_date = false;
                                    printf("End date is before start date, please re-enter the date:\n> ");
                                }
                            }
                        } while (!valid_date);

                        assignDate(&(activities[i].endDate), new_endDate);
                        printf("result: %d/%d/%d", activities[i].endDate.yy, activities[i].endDate.mm,
                               activities[i].endDate.dd);
                        printf("Done! ✨");

                    };
                        break;
                    case 5: {
                        int new_freePassAge;
                        printf("Enter the new free pass age:\n> ");
                        scanf(" %d", &new_freePassAge);
                        activities[i].freePassAge = new_freePassAge;
                        printf("Done! ✨");
                    };
                        break;
                    case 6: {
                        int new_ageRestriction;
                        printf("Enter the new age restriction:\n> ");
                        scanf(" %d", &new_ageRestriction);
                        activities[i].ageRestriction = new_ageRestriction;
                        printf("Done! ✨");
                    };
                        break;
                    default: {
                        valid_option = false;
                        printf("Invalid option, please retry:\n> ");
                    }
                }
            } while (!valid_option);

        }

    }
    if (!found) {
        printf("Activity not found, add a new Activity");
    }

}

bool isDateValid(char date[]) {
    if (isDateFormatValid(date) && isDateInFuture(date)) {
        return true;
    }
    return false;
}

bool isDateFormatValid(char date[]) {

    char month[3];
    char day[3];

    strncpy(month, date + 5, 2);
    strncpy(day, date + 8, 2);

    int test_month = atoi(month);
    int test_day = atoi(day);

    //test Day
    if (test_day > 30 || test_day < 1) {
        return false;
    }

    //test month
    if (test_month > 12 || test_month < 1) {
        return false;
    }

    if (
            isdigit(date[0]) &&
            isdigit(date[1]) &&
            isdigit(date[2]) &&
            isdigit(date[3]) &&
            date[4] == '/' &&
            isdigit(date[5]) &&
            isdigit(date[6]) &&
            date[7] == '/' &&
            isdigit(date[8]) &&
            isdigit(date[9]) &&
            strlen(date) == 10
            )
        return true;
    return false;
}

int compareDates(Date date1, Date date2) {
    if (date1.yy > date2.yy) {
        return 1;
    } else {
        if (date1.yy == date2.yy) {
            if (date1.mm > date2.mm) {
                return 1;
            } else {
                if (date1.mm == date2.mm) {
                    if (date1.dd > date2.dd) {
                        return 1;
                    } else {
                        if (date1.dd == date2.dd) { return 0; }
                        else {
                            return -1;
                        };
                    }
                } else {
                    return -1;
                }
            }
        } else {
            return -1;
        }
    }
    return -1;
}

void assignDate(Date *date, char stringDate[]) {

    char year[5];
    char month[3];
    char day[3];
    strncpy(year, stringDate, 4);
    strncpy(month, stringDate + 5, 2);
    strncpy(day, stringDate + 8, 2);

    year[4] = '\0';
    month[2] = '\0';
    day[2] = '\0';

    date->yy = atoi(year);
    date->mm = atoi(month);
    date->dd = atoi(day);


}

bool isDateInFuture(char date[]) {

    char year[5];
    char month[3];
    char day[3];
    strncpy(year, date, 4);
    strncpy(month, date + 5, 2);
    strncpy(day, date + 8, 2);

    year[4] = '\0';
    month[2] = '\0';
    day[2] = '\0';


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int current_year = tm.tm_year + 1900;
    int current_month = tm.tm_mon + 1;
    int current_day = tm.tm_mday;

    int test_year = atoi(year);
    int test_month = atoi(month);
    int test_day = atoi(day);


    if (test_year < current_year) {
        return false;
    } else if (test_year == current_year) {
        if (test_month < current_month) {
            return false;
        } else if (test_month == current_month) {
            if (test_day < current_day) {
                return false;
            }
        }
    }

    return true;
}

void showMainMenu() {

    printf("--------------------");
    printf("WELCOME TO");
    printf("Riyadh Season 2021");
    printf("Imagine, MORE!!");
    printf("--------------------");

    readFile();


    int entered = 0;
    do {

        printf("Enter the corresponding no");
        printf("1.Add new attendee record");
        printf("2.Search or edit record");
        printf("3.Edit attendee");
        printf("4.Edit activity");
        printf("5.Show report");
        printf("6.Know the records of attendees");
        printf("7.Delete the records");
        printf("8.Exit from the program");

        scanf("%d", &entered);
        switch (entered) {
            case 1: {
                addNewAttendee();
                break;
            }

            case 2: {
                editRecord();
                break;
            }

            case 3: {
                editRecord();
                break;
            }


            case 4: {
                editActivity();
                break;
            }


            case 5: {
                showAttendeeReport();
                break;
            }


            case 6: {
                showAttendee();
                break;
            }


            case 7: {
                deleteRecord();
                break;
            }


            case 8: {
                printf("Goodbye!");
                break;
            }


            default: {
                printf("invalid input, please try again.");
            }


        };

    } while (entered != 8);
}


void showAttendee() {

}

void deleteRecord() {

}

void editRecord() {

}

void showAttendeeReport() {

}

/* void insertAtBeginning(struct node **head, Attendee attendee) {
     Node *newNode = (Node *) malloc(sizeof(Node));
     newNode->val = attendee;
     newNode->next = *head;
     *head = newNode;
 }

 void insertAtEnd(struct node **head, Attendee attendee){
     if (*head == NULL) { //if the list is empty
         *head = (Node *) malloc(sizeof(Node));
         (*head)->val = attendee;
         (*head)->next = NULL; }
     else { //if the list has at least one node
         Node * current = *head;
         while (current->next != NULL) {
             current = current->next;
         }
 /* now we can add a new variable */
/*   current->next = (Node *)malloc(sizeof(Node));
   current->next->val = attendee;
   current->next->next = NULL;
} }


void printList(Node* head) {
Node * current = head;
while(current != NULL)
{
   printf("%d->",current->val); // edit this to show the details of attendee
   current = current ->next;
}
}


void deleteNode(Node **head, int id) {
if (*head != NULL) {
   if ((*head)->val.id == id) { //if the deleted node is the first node
       Node * temp = *head;
       *head = (*head)->next;
       free(temp);
   }
   else {
       Node *prev = *head;
       Node *cur = (*head)->next ;
       while (cur != NULL) {
           if (cur->val.id == id) {
               prev->next = cur->next;
               free(cur);
               break; } //exit loop when delete the node
           prev = cur;
           cur = cur ->next;
       } } } } */




//struct node *registered_head, *prev, *cur;
//registered_head = (struct node *) malloc(sizeof(struct node));



//registered_head->val = registered;

//struct node *singleVisit_head;
//singleVisit_head = (struct node *) malloc(sizeof(struct node));

// allocate memory for Activity list (array)
//Activity *ActivitiesList = (Activity *) calloc(10, sizeof(Activity));


// Data structures
//void deleteNode(struct node **head, int id);
//void printList(struct node * head);
//void insertAtEnd(struct node **head, Attendee attendee);
//void insertAtBeginning(struct node **head, Attendee attendee);


/*  printf("Enter The Attende State:");
scanf("%c", &temp -> state );
if( temp -> state == 'V'   || temp -> state == 'v' )
temp ->numOfCompanion = 0 ;
else if( temp -> state == 'R'   || temp -> state == 'r' ){
printf("Enter numuer Of Companion:");
scanf("%d", &temp -> numOfCompanion );
temp -> listOfCompanion = (Companion*) calloc(temp -> numOfCompanion , sizeof (Companion) ) ;
int i ;
Companion Ctemp ; */
   
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
    Date startDate;  // 21/11/2021
    Date endDate;   // 24/11/2021
    int freePassAge;    // -1 if no pass age
    int ageRestriction; // -1 if no restriction
    int nDays;  // 4 (days)
    Day *days; // { { "21/11/2021", 25} , { "22/11/2021", 7}, { "23/11/2021", 4}, { "24/11/2021", 19} }
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

void writeAttendee(char *fileName, struct Attendee *attendee);

bool isDateInFuture(char date[]);

void printList();

void setDaysList(Day *daysList, Activity *activity);

bool isDateValid(char date[]);

bool isDateFormatValid(char date[]);

int compareDates(Date date1, Date date2);

void assignDate(Date *date, char stringDate[]);

int getnDays(Date startDate, Date endDate);

void testDaysList(int nDaysDifference, Day *daysList);
void createFiles();
struct Attendee *registered = NULL;
struct Attendee *singleVisit = NULL;
struct Attendee *registered_head, *singleVisit_head, *registered_cur, *singleVisit_cur;
Activity *activities = NULL;
int numRegistered, numSingle;
Day *daysList = NULL;
int nActivities;
char *SINGLE_VISIT_ATTENDEE_FILENAME = "Single Visit Attendee.txt";
char *REGISTERED_ATTENDEE_FILENAME = "RegisteredAttendee.txt";


int main() {


    // read file and fill Activity list
    readFile();
//    addNewAttendee();
//    editActivity();
    showAttendeeReport();
    //editActivity();
    createFiles();
    struct Attendee at1 = {123, "Heila"};
    struct Attendee at2 = {321, "Anood"};
    struct Attendee at3 = {111, "Haila"};
    //writeAttendee(SINGLE_VISIT_ATTENDEE_FILENAME, at1);
    //writeAttendee(SINGLE_VISIT_ATTENDEE_FILENAME, at2);
    //writeAttendee(SINGLE_VISIT_ATTENDEE_FILENAME, at3);
//    getDaysList(activities+1, (activities+1)->startDate, (activities+1)->endDate);

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


    bool FoundSameDate = true;
    while (FoundSameDate) {


        printf("Enter the day of your Reservation ");
        scanf("%d", &temp->date->dd);
        printf("Enter the month of your Reservation ");
        scanf("%d", &temp->date->mm);
        printf("Enter the year of your Reservation ");
        scanf("%d", &temp->date->yy);

        FoundSameDate = false;

        struct Attendee *temp_cur = singleVisit_head;
        while (temp_cur->next !=
               NULL) {//to check if the Attende is a single vistor  and have an reservation in the same date
            if (temp->id == temp_cur->id && temp_cur->date->dd == temp->date->dd &&
                temp_cur->date->mm == temp->date->mm && temp_cur->date->yy == temp->date->yy) {
                FoundSameDate = true;
                break;
            }
            temp_cur = temp_cur->next;
        }
        if (temp->id == temp_cur->id && temp_cur->date->dd == temp->date->dd && temp_cur->date->mm == temp->date->mm &&
            temp_cur->date->yy ==
            temp->date->yy) {//to check the date .. if there is just one node or this is the last node
            FoundSameDate = true;
            printf("Sorry you already booked an Event in the same date .. try again with another day :(  ");
            break;
        }


        if (!FoundSameDate) {
            temp_cur = registered_head;

            while (temp_cur->next !=
                   NULL) {//to check if the Attende is a registerd  and have an reservation in the same date
                if (temp->id == temp_cur->id && temp_cur->date->dd == temp->date->dd &&
                    temp_cur->date->mm == temp->date->mm && temp_cur->date->yy == temp->date->yy) {
                    FoundSameDate = true;
                    break;
                }
                temp_cur = temp_cur->next;
            }
            if (temp->id == temp_cur->id && temp_cur->date->dd == temp->date->dd &&
                temp_cur->date->mm == temp->date->mm && temp_cur->date->yy ==
                                                        temp->date->yy) {//to check the date .. if there is just one node or this is the last node
                printf("Sorry you already booked an Event in the same date .. try again with another day :(  ");
                break;
            }
        }//end else
    }//end will

    char tempActivityZone[35];
    bool ActivityFound = false;

    int j, counterfreePassAge = 0;

    while (!ActivityFound) {
        printf("Enter The ActivityZone:");
        scanf("%s", tempActivityZone);

        for (j = 0; j < 10; j++) {//its better to change 10 with the number of activities
            Activity TempPName = *(activities + j);
            if (strstr(TempPName.name, tempActivityZone) != NULL) { //tempActivityZone.equals( TempPName.name )??
                strcpy (temp->ActivityZone, tempActivityZone);
                temp->activityFee = TempPName.price;


                printf("Enter numuer Of Companion:");
                scanf("%d", &temp->numOfCompanion);
                if (temp->numOfCompanion == 0) {
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

                        bool ageRestriction = true;
                        while (ageRestriction) {
                            ageRestriction = false;
                            printf("Enter #%d  Companion Age:", (i + 1));
                            scanf("%d", &Ctemp.age);

                            if (TempPName.ageRestriction == -1);
                            else if (Ctemp.age <
                                     TempPName.ageRestriction) {// if the Companion's age dose not match the ageRestriction
                                printf("Sorry There is a ageRestriction in this event( age must be > %d  years )  .. try again ! ",
                                       TempPName.ageRestriction);
                                ageRestriction = true;
                                break;
                            }
                        }// end while

                        if (TempPName.freePassAge == -1);
                        else if (Ctemp.age <= TempPName.freePassAge)
                            counterfreePassAge++;

                        printf("Enter The Attende Addres as (3 alphabet characters then 3 digits):");
                        scanf("%s", Ctemp.address);

                        *(temp->listOfCompanion + i) = Ctemp;
                    }//end loop

                }//end if val.state == 'R'



                temp->totalFees =
                        temp->numOfCompanion > 0 ? (temp->activityFee +
                                                    ((temp->numOfCompanion - counterfreePassAge) * temp->activityFee))
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
            printf("Sorry you need to recharge your Balance to To complete the reservation .. Try again");
        else
            break;
    }
    int x ,z ;
    
   
        
        for (x = 0; x < nActivities; x++) {
                Activity TempPName = *(activities + x);
                if (strstr(TempPName.name, temp->ActivityZone) != NULL) {
                 for (z = 0; z < TempPName.nDays; z++) {
                 if(  temp->date->dd == ((TempPName.days) + z )->date.dd &&  temp->date->mm == ((TempPName.days) + z )->date.mm  &&  temp->date->yy == ((TempPName.days) + z )->date.yy   )
                  if ( ( ((TempPName.days) + z )->attendeeCounter + 1 + temp->numOfCompanion ) <=50 )
                  ((TempPName.days) + z )->attendeeCounter += 1+ temp->numOfCompanion ;
                  else
                  printf("Sorry this Activity is FULL for today  .. try with another date or Activity"); 
                   }                                    
           
        } else("wrong Activity name");
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
    char *NameOfRegisteredFile = "RegisteredAttendee.txt", *NameOfSingleVisitFile = "Single Visit Attendee.txt";

    if (temp->state == 'R')
        writeAttendee(NameOfRegisteredFile , temp);
    else if (temp->state == 'S')
        writeAttendee(NameOfSingleVisitFile , temp );
}//end addNewAttendee


void editRecord() {
    int Attende_ID;
    printf("Enter the Attende ID That you want to Edit his companions: ");
    scanf("%d", &Attende_ID);

    bool found = false;
    struct Attendee *temp_cur = singleVisit_head;
    while (temp_cur->next != NULL) {//to check if the Attende is a single vistor
        if (temp_cur->id == Attende_ID) {
            found = true;
            break;
        }
        temp_cur = temp_cur->next;
    }
    if (temp_cur->id ==
        Attende_ID)//to check ifthe Attende is a single vistor and  there is just one node or this is the last node
        found = true;

    if (found && temp_cur->numOfCompanion == 0)
        printf("You do not have any companion .. So you can not edit this record");

    else if (!found) {
        temp_cur = registered_head;

        while (temp_cur->next != NULL) {//to check if the Attende is a registered vistor
            if (temp_cur->id == Attende_ID) {
                found = true;
                break;
            }
            temp_cur = temp_cur->next;
        }
        if (temp_cur->id ==
            Attende_ID)//to check ifthe Attende is a registered vistor and  there is just one node or this is the last node
            found = true;

        char DeleteOrAdd;
        if (found && temp_cur->numOfCompanion > 0)
            printf("Do you want to delete a Companion or add Companion? ( ENTER D to DELETE or A to ADD): ");
        scanf("%c", &DeleteOrAdd);

        int NumberOfIDS, counter_realcompanion = 0, Companion_ID, k, s, m, counter_IDS = 0, counterfreePassAge2 = 0;
        Companion Companion_temp;
        float morebalance;

        if (DeleteOrAdd == 'D' || DeleteOrAdd == 'd') {
            printf("How many Companions do you want to delete them?");
            scanf("%d", &NumberOfIDS);

            if (temp_cur->numOfCompanion == NumberOfIDS)
                temp_cur->listOfCompanion = NULL; //or free ??


            int size_of_memoryloc = temp_cur->numOfCompanion;

            while (counter_IDS != NumberOfIDS) {//counter_IDS == NumberOfIDS
                counter_IDS++;

                Companion *Temp_listOfCompanion = (Companion *) calloc((size_of_memoryloc - counter_IDS),
                                                                       sizeof(Companion));

                printf("Enter the #%d id:", (counter_IDS));
                scanf("%d", &Companion_ID);

                for (k = 0; k < temp_cur->numOfCompanion; k++) {

                    if (Companion_temp.id != Companion_ID) {
                        *(Temp_listOfCompanion + counter_realcompanion) = Companion_temp;
                        counter_realcompanion++;
                    }//end if  Companion_temp.id != Companion_ID
                }//end for to check the real list of Companion
                temp_cur->listOfCompanion = Temp_listOfCompanion;
            }//end while to check if we delete all NumberOfIDS
            temp_cur->totalFees = (temp_cur->totalFees) - ((temp_cur->activityFee) * NumberOfIDS);
            temp_cur->balance = temp_cur->balance + ((temp_cur->activityFee) * NumberOfIDS);
        }//end if delete

            //temp_cur->balance = ((temp_cur->activityFee)*NumberOfIDS)
        else if (DeleteOrAdd == 'A' || DeleteOrAdd == 'a') {

            for (m = 0; m < 10; m++) {//its better to change 10 with the number of activities
                Activity TempPName = *(activities + m);
                if (strstr(TempPName.name, temp_cur->ActivityZone) != NULL) {

                    printf("How many Companions do you want to add them?");
                    scanf("%d", &NumberOfIDS);

                    Companion Ctemp;
                    temp_cur->listOfCompanion = (Companion *) realloc(temp_cur->listOfCompanion,
                                                                      (temp_cur->numOfCompanion + NumberOfIDS) *
                                                                      sizeof(Companion));

                    for (s = 0; s < NumberOfIDS; s++) {
                        // ctemp = NULL ;
                        printf("Enter #%d  Companion ID:", (s + 1));
                        scanf("%d", &Ctemp.id);

                        printf("Enter #%d  Companion Name:", (s + 1));
                        scanf("%s", Ctemp.name);

                        bool ageRestriction = true;
                        while (ageRestriction) {
                            ageRestriction = false;
                            printf("Enter #%d  Companion Age:", (s + 1));
                            scanf("%d", &Ctemp.age);

                            if (TempPName.ageRestriction == -1);
                            else if (Ctemp.age <
                                     TempPName.ageRestriction) {// if the Companion's age dose not match the ageRestriction
                                printf("Sorry There is a ageRestriction in this event( age must be > %d  years )  .. try again ! ",
                                       TempPName.ageRestriction);
                                ageRestriction = true;
                                break;
                            }
                        }// end while

                        if (TempPName.freePassAge == -1);
                        else if (Ctemp.age <= TempPName.freePassAge)
                            counterfreePassAge2++;

                        printf("Enter The Attende Addres as (3 alphabet characters then 3 digits):");
                        scanf("%s", Ctemp.address);

                        *(temp_cur->listOfCompanion + (temp_cur->numOfCompanion + NumberOfIDS)) = Ctemp;
                    }//end loop
                    temp_cur->totalFees = (temp_cur->totalFees) + ((temp_cur->activityFee) * NumberOfIDS);
                    while (1) {
                        printf("Enter The Attende Balance:");
                        scanf("%f", &morebalance);

                        if (morebalance < (temp_cur->totalFees))
                            printf("Sorry you need to recharge your Balance to To complete the reservation .. Try again ");
                        else
                            break;
                    }
                    temp_cur->balance = temp_cur->balance + morebalance;
                }
            }
        }// end if (add)
    }//end else (!found)
    else printf("Wrong input :(");

}//end function editRecord



void readFile() {


    nActivities = 0;

    FILE *fp;
    fp = fopen("../Activities.txt", "r");

    if (fp == NULL) {
        printf("Can not open %s\n", "Activities.txt");
        return;
    }


    char tx[200];
    char name[35];
    double price = 0;

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
//        printf("Date: %s\n", tx);
        sscanf(tx, "%s", fullDate);
//        printf("Full date is is %s\n", fullDate);
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
//        printf("Ignored sign: %s\n", tx);

        if (strcmp(tx, "-") == 0) {
            freePassAge = -1;
            eof = fgets(tx, 19, fp);
        } else {
            // Get FREEPASS
            eof = fgets(tx, 19, fp);
//            printf("Free pass: %s\n", tx);
            sscanf(tx, "%d", &freePassAge);
        }

        // ignore the > or
        eof = fgets(tx, 2, fp);
//        printf("Ignored sign: %s\n", tx);

        if (strcmp(tx, "-") == 0) {
            ageRestriction = -1;
            eof = fgets(tx, 20, fp);
        } else {
            // Get minimum age
            eof = fgets(tx, 20, fp);
//            printf("Min Age: %s\n", tx);
            sscanf(tx, "%d", &ageRestriction);
        }

        line_counter++;


        ac.freePassAge = freePassAge;
        ac.ageRestriction = ageRestriction;
        setDaysList(NULL, &ac);

        // setting attendees counters
        int i;
        for (i = 0; i < ac.nDays; i++) {
            (ac.days + i)->attendeeCounter = 0;
        }

//        printf("\nTesting::\n");
//        printf("\nn days: %d || first date is %d/%d/%d\n", ac.nDays, ac.days->date.dd, ac.days->date.mm, ac.days->date.yy);
//        testDaysList(ac.nDays, ac.days);
//*(activities + nActivities)
        *(activities + nActivities) = ac;
        nActivities++;
    };


    fclose(fp);

    test_readFile(activities);
}

void test_readFile(Activity *activities) {
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d | Name: %-32s\t Price: %-18lf\t Date:%d/%d/%d-%d/%d/%d \t freePassAge:%d\t ageRestriction: %d\n",
               i + 1,
               (activities + i)->name,
               (activities + i)->price,
               (activities + i)->startDate.dd,
               (activities + i)->startDate.mm,
               (activities + i)->startDate.yy,
               (activities + i)->endDate.dd,
               (activities + i)->endDate.mm,
               (activities + i)->endDate.yy,
               (activities + i)->freePassAge,
               (activities + i)->ageRestriction
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

    int i;
    for (i = 0; i < nDaysDifference; i++) {
        printf("%d | %d/%d/%d\n ",
               i + 1,
               (daysList + i)->date.yy,
               (daysList + i)->date.mm,
               (daysList + i)->date.dd);
    }

}

void setDaysList(Day *daysList, Activity *activity) {

    struct tm date1;
    date1.tm_year = activity->startDate.yy - 1900;
    date1.tm_mon = activity->startDate.mm - 1;
    date1.tm_mday = activity->startDate.dd;
    date1.tm_hour = 0;
    date1.tm_min = 0;
    date1.tm_sec = 0;
    // Heila: I used this to solve this problem https://stackoverflow.com/questions/26788470/difftime-returns-strange-value-on-particular-date
    date1.tm_isdst = -1;

    struct tm date2;
    date2.tm_year = activity->endDate.yy - 1900;
    date2.tm_mon = activity->endDate.mm - 1;
    date2.tm_mday = activity->endDate.dd;
    date2.tm_hour = 0;
    date2.tm_min = 0;
    date2.tm_sec = 0;
    date2.tm_isdst = -1;


//    printf("Year: %d\t", date1.tm_year + 1900);
//    printf("Month: %d\t", date1.tm_mon + 1);
//    printf("Day: %d\n", date1.tm_mday);
//    printf("Year: %d\t", date2.tm_year + 1900);
//    printf("Month: %d\t", date2.tm_mon + 1);
//    printf("Day: %d\t", date2.tm_mday);


    int daysDifference = (int) ((int) (difftime(mktime(&date2), mktime(&date1))) / 60 / 60 / 24) + 1;
//    printf("Date Difference = %d Days\n", daysDifference);
    activity->nDays = (int) daysDifference;

    daysList = (Day *) realloc(daysList, daysDifference * sizeof(Day));

    Date currentDate = activity->startDate;

    int i;


    // Fill all days except last day
    for (i = 0; i < daysDifference; i++) {
        (daysList + i)->date.yy = currentDate.yy;
        (daysList + i)->date.mm = currentDate.mm;
        (daysList + i)->date.dd = currentDate.dd;

        if (currentDate.dd != activity->endDate.dd || currentDate.mm != activity->endDate.mm ||
            currentDate.yy != activity->endDate.yy) {
            if (currentDate.dd < maxDaysDependingOnMonth(currentDate.mm)) {
                currentDate.dd++;
            } else {
                currentDate.dd = 1;
                if (currentDate.mm < 12) {
                    currentDate.mm++;
                } else {
                    currentDate.mm = 1;
                    currentDate.yy++;
                }
            }
        }


    }

//    return daysList;
    activity->days = daysList;
//    activity->nDays = daysDifference;
//    testDaysList(daysDifference, activity->days);
}

Date findNextDate(Date currentDate) {

    Date nextDate;
    if (currentDate.dd < maxDaysDependingOnMonth(currentDate.mm)) {
        nextDate.dd = currentDate.dd + 1;
        nextDate.mm = currentDate.mm;
        nextDate.yy = currentDate.yy;
    } else {
        nextDate.dd = 1;
        if (currentDate.mm < 12) {
            nextDate.mm = currentDate.mm + 1;
            nextDate.yy = currentDate.yy;
        } else {
            nextDate.mm = 1;
            nextDate.yy = currentDate.yy + 1;
        }
    }
    return nextDate;
}

void editActivity() {


    char activity_name[53];
    bool found = false;
    printf("Enter the name of the Activity you want to edit\n> ");
    scanf("%[^\n]s", activity_name);
    int i;
    for (i = 0; i < 10; i++) {
//        printf("%s VS %s\n", activities[i].name, activity_name);
        if (strcmp((activities + i)->name, activity_name) == 0) {
            found = true;
            printf("Activity found!\nWhat Do you to edit:\n");
//            printf("1. Activity Name\n");
            printf("1. Activity Price\n");
//            printf("3. Activity Start Date\n");
            printf("2. Activity End Date\n> ");
//            printf("5. Activity Free Pass Age\n");
//            printf("6. Activity Age Restriction\n> ");
            int option;
            bool valid_option;
            do {
                valid_option = true;
                scanf("%d", &option);
                switch (option) {
//                    case 1: {
//                        char new_name[30];
//                        printf("Enter the new name:\n> ");
//                        scanf(" %[^\n]s", new_name);
//                        strcpy(activities[i].name, new_name);
//                        printf("Done! ✨");
//                    };
//                        break;
                    case 1: {
                        float new_price;
                        printf("Enter the new price:\n> ");
                        scanf(" %f", &new_price);
                        (activities + i)->price = new_price;
                        printf("Done! ✨");
                    };
                        break;
//                    case 3: {
//                        bool valid_date = true;
//                        printf("Enter the new start date (in the format yyyy/mm/dd):\n> ");
//                        char new_startDate[30];
//                        do {
//                            valid_date = true;
//                            scanf(" %[^\n]s", new_startDate);
//
//                            if (!isDateValid(new_startDate)) {
//                                valid_date = false;
//                                if (!isDateFormatValid(new_startDate)) {
//                                    printf("Date format is invalid, please re-enter the date:\n> ");
//                                }
//                            }
//
//                        } while (!valid_date);
//
//                        assignDate(&(activities[i].startDate), new_startDate);
//                        printf("result: %d/%d/%d", activities[i].startDate.yy, activities[i].startDate.mm,
//                               activities[i].startDate.dd);
//                        printf("Done! ✨");
//                    };
//                        break;
                    case 2: {

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
                                }
                            } else {
                                Date dateToCompare;
                                assignDate(&(dateToCompare), new_endDate);
                                if (compareDates((activities + i)->endDate, dateToCompare) > 0) {
                                    valid_date = false;
                                    printf("You can only extend the event period. Please enter another date:\n >");
                                }
                            }
                        } while (!valid_date);


                        assignDate(&((activities + i)->endDate), new_endDate);

                        printf("\nBefore: (%d Days)\n", (activities + i)->nDays);
                        testDaysList((activities + i)->nDays, (activities + i)->days);
                        setDaysList((activities + i)->days, activities + i);
                        printf("\nAfter: (%d Days)\n", (activities + i)->nDays);
                        testDaysList((activities + i)->nDays, (activities + i)->days);


                        printf("Done! ✨");

                    };
                        break;
//                    case 5: {
//                        int new_freePassAge;
//                        printf("Enter the new free pass age:\n> ");
//                        scanf(" %d", &new_freePassAge);
//                        activities[i].freePassAge = new_freePassAge;
//                        printf("Done! ✨");
//                    };
//                        break;
//                    case 6: {
//                        int new_ageRestriction;
//                        printf("Enter the new age restriction:\n> ");
//                        scanf(" %d", &new_ageRestriction);
//                        activities[i].ageRestriction = new_ageRestriction;
//                        printf("Done! ✨");
//                    };
//                        break;
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

int getnDays(Date startDate, Date endDate) {
    struct tm date1;
    date1.tm_year = startDate.yy - 1900;
    date1.tm_mon = startDate.mm - 1;
    date1.tm_mday = startDate.dd;
    date1.tm_hour = 0;
    date1.tm_min = 0;
    date1.tm_sec = 0;
    date1.tm_isdst = -1;

    struct tm date2;
    date2.tm_year = endDate.yy - 1900;
    date2.tm_mon = endDate.mm - 1;
    date2.tm_mday = endDate.dd;
    date2.tm_hour = 0;
    date2.tm_min = 0;
    date2.tm_sec = 0;
    date2.tm_isdst = -1;

    int daysDifference = (int) ((int) (difftime(mktime(&date2), mktime(&date1))) / 60 / 60 / 24) + 1;
    return daysDifference;
}

bool isDateValid(char date[]) {
    if (isDateFormatValid(date)) {
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

    int SANum = 0;
    do {
        printf("Enter the corresponding no \n");
        printf("1.Records of attendees in alphabetical order \n");
        printf("2.Records of single visit attendees\n");
        printf("3.Records of registered attendees\n");
        printf("4.Records in particular date\n");
        printf("5.Return to main menu\n");
        scanf("%d", &SANum);

        switch (SANum) {
            case 1: {
                //Records of attendees in alphabetical order
                singleVisit_cur = singleVisit_head;
                registered_cur = registered_head;
                struct Attendee *temp;
                struct Attendee *allAttendeess = (struct Attendee *) calloc(numRegistered + numSingle,sizeof(struct Attendee));
                    int i ,j ;                                                       
                for ( i = 0; registered_cur != NULL; i++) {
                    *(allAttendeess + i) = *registered_cur;
                    registered_cur = registered_cur->next;
                }

                for ( i = 0; singleVisit_cur != NULL; i++) {
                    *(allAttendeess + i) = *singleVisit_cur;
                    singleVisit_cur = singleVisit_cur->next;
                }

                for ( i = 0; i < numRegistered + numSingle; i++) {
                    for ( j = i + 1; j < numRegistered + numSingle; j++) {
                        if (strcmp((allAttendeess + i)->name, (allAttendeess + j)->name) > 0) {
                            *temp = *(allAttendeess + i);
                            *(allAttendeess + i) = *(allAttendeess + j);
                            *(allAttendeess + j) = *temp;

                        }

                    }

                }
                 i = 0;
                while ((allAttendeess + i)->next != NULL) {
                    printf("%d \t %s \t %d \t %c \t %s \t %s \t %d \t {", (allAttendeess + i)->id,
                           (allAttendeess + i)->name, (allAttendeess + i)->age, (allAttendeess + i)->state,
                           (allAttendeess + i)->address, (allAttendeess + i)->ActivityZone,
                           (allAttendeess + i)->numOfCompanion);
                    if ((allAttendeess + i)->state == 'v') {
                        for ( i = 0; i < (allAttendeess + i)->numOfCompanion; i++) {

                            printf("{%d", ((allAttendeess + i)->listOfCompanion + i)->id);
                            printf("%s", ((allAttendeess + i)->listOfCompanion + i)->name);
                            printf("%d", ((allAttendeess + i)->listOfCompanion + i)->age);
                            printf("%c", ((allAttendeess + i)->listOfCompanion + i)->gender);
                            printf("%s}", ((allAttendeess + i)->listOfCompanion + i)->address);
                        }//for
                    }//if
                    else printf("{");
                    printf("} \t %f \t %f \t %f\n", (allAttendeess + i)->activityFee, (allAttendeess + i)->totalFees,
                           (allAttendeess + i)->balance);
                    i++;
                }//while


                free(allAttendeess);
                break;
            }//case 1


            case 2: {
                //"2.Records of single visit attendees
                singleVisit_cur = singleVisit_head;
                while (singleVisit_cur->next != NULL) {
                    printf("%d \t %s \t %d \t %c \t %s \t %s \t %d \t {", singleVisit_cur->id, singleVisit_cur->name,
                           singleVisit_cur->age, singleVisit_cur->state, singleVisit_cur->address,
                           singleVisit_cur->ActivityZone, singleVisit_cur->numOfCompanion);
                    printf("} \t %f \t %f \t %f\n", singleVisit_cur->activityFee, singleVisit_cur->totalFees,
                           singleVisit_cur->balance);

                    singleVisit_cur = singleVisit_cur->next;
                }
                break;
            }

            case 3: {
            int i ;
                //3.Records of registered attendees
                registered_cur = registered_head;
                struct Attendee temp;
                while (registered_cur->next != NULL) {
                    printf("%d \t %s \t %d \t %c \t %s \t %s \t %d \t {", temp.id, temp.name, temp.age, temp.state,
                           temp.address, temp.ActivityZone, temp.numOfCompanion);
                    for ( i = 0; i < temp.numOfCompanion; i++) {
                        printf("{%d", (temp.listOfCompanion + i)->id);
                        printf("%s", (temp.listOfCompanion + i)->name);
                        printf("%d", (temp.listOfCompanion + i)->age);
                        printf("%c", (temp.listOfCompanion + i)->gender);
                        printf("%s}", (temp.listOfCompanion + i)->address);
                    }
                    printf("} \t %.2f \t %.2f \t %.2f\n", temp.activityFee, temp.totalFees, temp.balance);

                    registered_cur = registered_cur->next;
                }
                break;
            }


            case 4: {
                /*Records in particular date
                singleVisit_cur = singleVisit_head; 
                registered_cur = registered_head;
                
                struct Attendee* allAttendeess=(struct Attendee*)calloc(numRegistered+numSingle,sizeof(struct Attendee));
                for(int i=0; registered_cur!=NULL;i++){
                    *(allAttendeess+i)=*registered_cur;
                    registered_cur=registered_cur->next;
                }

                for(int i=0; singleVisit_cur!=NULL;i++){
                    *(allAttendeess+i)=*singleVisit_cur;
                    singleVisit_cur=singleVisit_cur->next;
                };*/

                Date *tempd;
                printf("please enter the Year of the paticular date");
                scanf("%d", &(tempd->yy));
                printf("please enter the Month of the paticular date");
                scanf("%d", &(tempd->mm));
                printf("please enter the Day of the paticular date");
                scanf("%d", (tempd->yy));

                while (singleVisit_cur->next != NULL) {
                    if (compareDates(*tempd, *singleVisit_cur->date) == 0) {
                        printf("%d \t %s \t %d \t %c \t %s \t %s \t %d \t {", singleVisit_cur->id,
                               singleVisit_cur->name, singleVisit_cur->age, singleVisit_cur->state,
                               singleVisit_cur->address, singleVisit_cur->ActivityZone,
                               singleVisit_cur->numOfCompanion);
                        printf("} \t %f \t %f \t %f\n", singleVisit_cur->activityFee, singleVisit_cur->totalFees,
                               singleVisit_cur->balance);
                    }
                    singleVisit_cur = singleVisit_cur->next;

                }

                while (registered_cur->next != NULL) {
                int i ;
                    if (compareDates(*tempd, *registered_cur->date) == 0) {
                        printf("%d \t %s \t %d \t %c \t %s \t %s \t %d \t {", registered_cur->id, registered_cur->name,
                               registered_cur->age, registered_cur->state, registered_cur->address,
                               registered_cur->ActivityZone, registered_cur->numOfCompanion);
                        for ( i = 0; i < registered_cur->numOfCompanion; i++) {
                            printf("{%d", (registered_cur->listOfCompanion + i)->id);
                            printf("%s", (registered_cur->listOfCompanion + i)->name);
                            printf("%d", (registered_cur->listOfCompanion + i)->age);
                            printf("%c", (registered_cur->listOfCompanion + i)->gender);
                            printf("%s}", (registered_cur->listOfCompanion + i)->address);
                        }
                        printf("} \t %.2f \t %.2f \t %.2f\n", registered_cur->activityFee, registered_cur->totalFees,
                               registered_cur->balance);
                    }
                    registered_cur = registered_cur->next;
                }

                break;
            }


            case 5: {

                break;
            }

            default: {
                printf("invalid input, please try again.");
            }


        };
    } while (SANum != 0);

}


void deleteRecord() {
    char ch;
    int ID;
    char Aname[35];

    registered_cur = (registered_head)->next;
    struct Attendee *registered_prev = registered_head;

    singleVisit_cur = (singleVisit_head)->next;
    struct Attendee *singleVisit_prev = singleVisit_head;
    printf("Enter Attendee id : ");
    scanf("%d", &ID);
    //to display the names of the activites
    while (registered_cur != NULL) {
        if (registered_cur->id == ID) {
            printf("Activity name : %s \n", registered_cur->ActivityZone);
        }
    }//while
    while (singleVisit_cur != NULL) {
        if (singleVisit_cur->id == ID) {
            printf("Activity name : %s \n", singleVisit_cur->ActivityZone);
        }
    }//while
    printf("to delete all activities enter 'A' , to delete single activity enter 'S'");
    getchar();
    scanf("%c", &ch);
    if (ch == 'A' || ch == 'a') {

        while (registered_cur != NULL) {
            if (registered_cur->id == ID) {
                registered_prev->next = registered_cur->next;
            }//if
            registered_prev = registered_cur;
            registered_cur = registered_cur->next;
        }//while

        while (singleVisit_cur != NULL) {
            if (singleVisit_cur->id == ID) {
                singleVisit_prev->next = singleVisit_cur->next;
            }//if
            singleVisit_prev = singleVisit_cur;
            singleVisit_cur = singleVisit_cur->next;
        }//while

    }//if a

    if (ch == 'S' || ch == 's') {

// the user write the name of the activity that he want to delete
        printf("Enter the name of the Activity you want to delete \n");
        gets(Aname);
        // serch by id and activity name to delete  single activite
        while (registered_cur != NULL) {
            if (registered_cur->id == ID && registered_cur->ActivityZone == Aname) {
                registered_prev->next = registered_cur->next;
            }
            registered_prev = registered_cur;
            registered_cur = registered_cur->next;
        }//while

        while (singleVisit_cur != NULL && singleVisit_cur->ActivityZone == Aname) {
            if (singleVisit_cur->id == ID) {
                singleVisit_prev->next = singleVisit_cur->next;
            }
            singleVisit_prev = singleVisit_cur;
            singleVisit_cur = singleVisit_cur->next;
        }//ehile


    }//if s
}//deleterecord

//void showAttendeeReport(){
//
//    char Aname[35];
//    int NOA = 0 ;//counter for the number of attendees
//    int i = 0 ;
//
//    printf("total attendees’ numbers for each activity\n");
//    registered_cur = registered_head;
//    singleVisit_cur = singleVisit_head;
//    int TNA;//total number of atndees at activity
//    while( *(activities+i) != NULL ){
//        while(registered_cur->next != NULL){
//            if(strstr((registered_cur->ActivityZone ) , (*(activities+i)->name)))
//                TNA++;
//            registered_cur=registered_cur->next;}//while
//
//
//        while(singleVisit_cur->next != NULL){
//            if(strstr( singleVisit_cur->ActivityZone , (*(activities+i)->name) ) )
//                TNA++;
//            singleVisit_cur=singleVisit_cur->next;}//while
//
//
//        printf(" %s has %d Attendee \n" , *(activities+i)->name , TNA  );
//        i++;
//    }//while
//
//    //////////////////other sol //////////////////////////////////
//
//    i=0;
//    printf("total attendees’ numbers for each activity\n");
////first asc the user to enter the name of the activity
//    printf(" Enter the name of the activitee : \n");
//    scanf("%s", Aname );
//    // then we loop on activities to find the name of the activity
//    //the ad the number of attendes on the activity
//    while( *(activities + i) != NULL ){
//        if(strstr( (*(activities+i)->name) ,Aname ) != NULL )
//            NOA += (activities+i)->days->attendeeCounter;
//        i++;
//    }//while
//    printf(" %s has %d Attendee \n",  Aname , NOA  );
//
//
//
//
//
////attendees’ numbers for each activity by date
//    printf("attendees’ numbers for each activity by date\n");
//    Date *t_date ;
//    NOA = 0 ;//counter for the number of attendees
//    i=0;
//
////ask the user to inter the day , month and year in the struct of day
////then ask the user to enter the name of the activitee
//
//    printf("Enter date : ");
//    printf("Enter the day :\n ");
//    scanf("%d  ", t_date->dd);
//    printf("Enter the month: \n ");
//    scanf("%d  ", t_date->mm);
//    printf("Enter the year: \n ");
//    scanf("%d  ", t_date->yy);
//
//    printf("Enter the activitee name  : \n");
//    scanf("%s", Aname );
////loop on activities to find the name of the activitee and the date
//    while( (activities+i) != NULL ){
//        if( (*(activities+i)->name ,Aname) != NULL && (compareDates((*(activities+i)->days->date), *t_date) == 0 ))
//            NOA = (*(activities+i)->days->attendeeCounter);
//        i++;
//    }//while
//    printf("the number of attendees at %s on %d / %d / %d  is %d \n  ", Aname ,t_date->dd  ,t_date->mm ,t_date->yy  , NOA );
//
////total attendees’ numbers for each date
//    printf("atotal attendees’ numbers for each date \n");
////ask the user to inter the day , month and year in the struct of day
////then we created a loop on activities
////to count thr number of attendees on all activities on the giving date
////by ading the number on attendees for all activities on the giving date
//    i=0;
//
//    NOA = 0 ;//counter for the number of attendees
//    printf("Enter date :  \n  ");
//    printf("Enter the day : \n ");
//    scanf("%d", t_date->dd);
//    printf("Enter the month : \n  ");
//    scanf("%d", t_date->mm);
//    printf("Enter the year : \n ");
//    scanf("%d", t_date->yy);
//    while( (*(activities+i)) != NULL ){// activities temp = *(activities+i) ;
//        if(compareDates((*(activities+i)->days->date), *t_date) == 0)
//            NOA += *(activities+i)->*(days+i)->attendeeCounter;
//        i++;
//    }//while
//    printf("number of attendees on this date is %d  \n " , NOA );
//
//
////total income coming from all activities by dates
//    float INC = 0 ; // income
//    i=0;
//
////ask the user to inter the day , month and year in the struct of day
////then loop on activities to find activities on the same date
////then multiplay the price of the activity by the number of attendees to get the income of a singlr activity on that date
////then sum the incums of all activities on thet date
//
//    printf("total income coming from all activities by dates \n " );
//
//    printf("Enter date :  \n  ");
//    printf("Enter the day : \n ");
//    scanf("%d", t_date->dd);
//    printf("Enter the month : \n  ");
//    scanf("%d", t_date->mm);
//    printf("Enter the year : \n ");
//    scanf("%d", t_date->yy);
//    while( (activities+i) != NULL ){
//        if(compareDates((activities+i)->days->date, *t_date) == 0 )
//            INC += ((activities+i)->price)*((activities+i)->days->attendeeCounter);
//        i++;
//    }//while
//    printf("the total income coming from the activities at %d / %d / %d is %f  \n " ,t_date->dd  ,t_date->mm ,t_date->yy  , INC );
//
//
//} //show attendee report

void showAttendeeReport() {

    printf("---------- Attendees Report ----------\n");

    //  summary of total attendees’ numbers for each activity
    printf("\t Total attendees for each activity:\n");
    printf("\t  %-35s | %s\n", "Activity Name", "Total Attendees");
    Activity currentActivity;
    char *activityName;
    int totalAttendeesForActivity = 0;

    int i, j;
    for (i = 0; i < nActivities; i++) {
        currentActivity = *(activities + i);
        activityName = (activities + i)->name;
        for (j = 0; j < currentActivity.nDays; j++) {
            totalAttendeesForActivity += ((currentActivity.days) + j)->attendeeCounter;
        }
        printf("%3d | %-35s | %3d\n", i + 1, activityName, totalAttendeesForActivity);
    }

    // attendees’ numbers for each activity by date
    printf("\tAttendees’ numbers for each activity by date:\n");
    Date currentDate;
    Date startDate;
    Date endDate;
    for (i = 0; i < nActivities; i++) {
        currentActivity = *(activities + i);
        activityName = currentActivity.name;
        startDate = currentActivity.startDate;
        endDate = currentActivity.endDate;
        printf("%d |  %s (%d days, from %d/%d/%d to %d/%d/%d)\n", i + 1, activityName, currentActivity.nDays,
               startDate.dd,
               startDate.mm, startDate.yy, endDate.dd,
               endDate.mm, endDate.yy);
        for (j = 0; j < currentActivity.nDays; j++) {
            currentDate = ((currentActivity.days) + j)->date;
            printf("\t %2d | %d/%d/%d | %d\n", j + 1, currentDate.dd, currentDate.mm, currentDate.yy,
                   ((currentActivity.days) + j)->attendeeCounter);
        }

    }

    // Total attendees’ numbers for each date
    // get the earliest start date
    Date earliestDateFound = activities->startDate;
    Date currentActivityStartDate;
    for (i = 0; i < nActivities; i++) {
        currentActivity = *(activities + i);
        currentActivityStartDate = currentActivity.startDate;
        if (compareDates(currentActivityStartDate, earliestDateFound) < 0) {
            earliestDateFound = currentActivityStartDate;
        }
    }


    // get the latest end date
    Date latestDateFound = activities->endDate;
    Date currentActivityendDate;
    for (i = 0; i < nActivities; i++) {
        currentActivity = *(activities + i);
        currentActivityendDate = currentActivity.endDate;
        if (compareDates(currentActivityendDate, latestDateFound) > 0) {
            latestDateFound = currentActivityendDate;
        }
    }

    int eventDuration = getnDays(earliestDateFound, latestDateFound);
    printf("The season is between %d/%d/%d and %d/%d/%d (%d Days)\n", earliestDateFound.dd, earliestDateFound.mm,
           earliestDateFound.yy, latestDateFound.dd, latestDateFound.mm, latestDateFound.yy, eventDuration);

    int k;
    currentDate = earliestDateFound;
    int currentDateAttendees;
    for (k = 0; k < eventDuration; k++) {
        printf("Date: %d/%d/%d | ", currentDate.dd, currentDate.mm, currentDate.yy);
        currentDateAttendees = 0;
        for (i = 0; i < nActivities; i++) {
            currentActivity = *(activities + i);
            for (j = 0; j < currentActivity.nDays; j++) {
                if (compareDates(((currentActivity.days) + j)->date, currentDate) == 0) {
                    currentDateAttendees += ((currentActivity.days) + j)->attendeeCounter;
                }
            }
        }
        printf("%d\n", currentDateAttendees);
        currentDate = findNextDate(currentDate);
    }


    // Total Income
    printf("Total income of each activity by date\n");
    for (i = 0; i < nActivities; i++) {
        currentActivity = *(activities + i);
        activityName = currentActivity.name;
        printf("%d |  %s\n", i + 1, activityName);
        for (j = 0; j < currentActivity.nDays; j++) {
            currentDate = ((currentActivity.days) + j)->date;
            printf("\t %2d | %d/%d/%d | SAR %.2lf\n", j + 1, currentDate.dd, currentDate.mm, currentDate.yy,
                   (float) (((currentActivity.days) + j)->attendeeCounter) * currentActivity.price);
        }

    }

} //show attendee report

void createFiles(){
    FILE *singleVisitAttendeeFile;
    singleVisitAttendeeFile = fopen(SINGLE_VISIT_ATTENDEE_FILENAME, "ab+");
    fprintf(singleVisitAttendeeFile, "Single Visit Attendees:\n");
    fclose(singleVisitAttendeeFile);

    FILE *RegisteredAttendeeFile;
    RegisteredAttendeeFile = fopen(REGISTERED_ATTENDEE_FILENAME, "ab+");
    fprintf(RegisteredAttendeeFile, "Registered Attendees:\n");
    fclose(RegisteredAttendeeFile);


}

void writeAttendee(char *fileName, struct Attendee *attendee) {

  bool FirstTimeOpeningFile = true ;
  if(FirstTimeOpeningFile ){
  createFiles();
  FirstTimeOpeningFile = false;
  }
    FILE *fp;
    fp = fopen(fileName, "ab+");
    if (strcmp(fileName, SINGLE_VISIT_ATTENDEE_FILENAME) == 0) {
        fprintf(fp, "%d %s %d %s %s %lf %f\n", attendee->id, attendee->name, attendee->age, attendee->address, attendee->ActivityZone,
                attendee->activityFee, attendee->balance);
    } else {
        if (strcmp(fileName, REGISTERED_ATTENDEE_FILENAME) == 0) {
            fprintf(fp, "%d %s %d %s %s %d %lf %f\n", attendee->id, attendee->name, attendee->age, attendee->address, attendee->ActivityZone,
                    attendee->numOfCompanion, attendee->activityFee, attendee->balance);
        }
        }
    fclose(fp);
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
  now we can add a new variable 
   current->next = (Node *)malloc(sizeof(Node));
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
<<<<<<< Updated upstream
Companion Ctemp ; */




/*  Companion_temp = *(temp_cur->listOfCompanion + k);
              if( Companion_temp.id == Companion_ID ){
               counter_IDS++ ; 
               break ;
               }
              else {
              if( counter_realcompanion != 0 )
               Temp_listOfCompanion =(Companion *) realloc(Temp_listOfCompanion,counter_realcompanion*sizeof(Companion)) ;
               
                *(Temp_listOfCompanion + counter_realcompanion) = Companion_temp ; //temp_cur->listOfCompanion = (Companion *) calloc(temp_cur->numOfCompanion, sizeof(Companion));
                counter_realcompanion++ ;
                   
            }//end else Companion_temp.id != Companion_ID 
            }//end for to check all the list
            //if( Companion_temp.id == Companion_ID )  counter_IDS++ ; 
            }//end while to check if we delete all NumberOfIDS
           // temp_cur->listOfCompanion = Temp_listOfCompanion ;*/


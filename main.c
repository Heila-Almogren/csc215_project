#include <stdio.h>

// Attendee struct
struct Attendee {
    int id;
    char *name;
    int age;
    char state;
    char *address;
    char *ActivityZone;
    int numOfCompanion;
    char **listOfCompanion;
    float totalFees;
    float balance;
    float activityFee;
    struct Attendee *next;
    struct {
        int yy;
        int mm;
        int dd;
    } date[];
};

int main() {

    struct Attendee registered;
    struct Attendee singleVisit;

    return 0;
}

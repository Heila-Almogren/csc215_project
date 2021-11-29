   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <stdbool.h>
   
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
      struct Attendee *next ;
   } ;
   
   
   typedef struct {
       char name[35];
       float price;
       Date startDate;
       Date endDate;
       int freePassAge;
       int ageRestriction;
   } activity;
   
      
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
      
   struct Attendee *registered = NULL ;
   struct Attendee *singleVisit = NULL ;
   struct Attendee *registered_head,*singleVisit_head, *registered_cur, *singleVisit_cur;
   struct activity *ActivitiesList = NULL;
       
   
   int main() {


    // read file and fill activity list
    readFile();

    

    return 0;
   }
   
   
   void addNewAttendee(){
   struct Attendee *temp = (struct Attendee*) malloc(sizeof(struct Attendee));
   
   printf("Enter The Attende ID:");
   scanf("%d", &temp -> id );
   
   printf("Enter The Attende Name:");
   scanf("%s", temp -> name );
   
   printf("Enter The Attende Age:");
   scanf("%d", &temp -> age );
   
   printf("Enter The Attende Addres as (3 alphabet characters then 3 digits):");
   scanf("%s", temp -> address );
   
   printf("Enter numuer Of Companion:");
   scanf("%d", &temp -> numOfCompanion );
   if( temp -> numOfCompanion = 0 ){
   temp -> state = 'V' ;
   temp -> listOfCompanion = NULL ;
   }
   else if ( temp -> numOfCompanion > 0 ){
   temp -> state = 'R' ;
   
   temp -> listOfCompanion = (Companion*) calloc(temp -> numOfCompanion , sizeof (Companion) ) ;
   Companion Ctemp ;
   int i ;
   
   for ( i = 0 ; i<temp -> numOfCompanion ; i++){
   
   printf("Enter #%d  Companion ID:" , (i+1) );
   scanf("%d", &Ctemp.id );
   
   printf("Enter #%d  Companion Name:" , (i+1) );
   scanf("%s", Ctemp.name );
   
   printf("Enter #%d  Companion Age:" , (i+1) );
   scanf("%d", &Ctemp.age );
   
   printf("Enter The Attende Addres as (3 alphabet characters then 3 digits):" , (i+1) );
   scanf("%d", &Ctemp.address );
      
   *(temp -> listOfCompanion + i) = Ctemp ;
   }//end loop
   
   }//end if val.state == 'R'
   
   printf("Enter the day of your Reservation ");
   scanf("%d", temp -> date ->dd );
   printf("Enter the month of your Reservation ");
   scanf("%d", temp -> date ->mm );
   printf("Enter the year of your Reservation ");
   scanf("%d", temp -> date ->yy );
   
   
   if( temp -> numOfCompanion > 0 ){ //add the record to the registered linked list
     if (registered_head == NULL) { //if the list is empty
           registered_head = (struct Attendee *) malloc(sizeof(struct Attendee));
           (registered_head) = temp;
           (registered_head)->next = NULL; }
      else { //if the list has at least one node
            registered_cur = registered_head;
      while (registered_cur->next != NULL) 
            registered_cur = registered_cur->next; }
           } 
           
   else {//add the record to the singleVisit linked list
     if (singleVisit_head == NULL) { //if the list is empty
           singleVisit_head = (struct Attendee *) malloc(sizeof(struct Attendee));
           (singleVisit_head) = temp;
           (singleVisit_head)->next = NULL; }
      else { //if the list has at least one node
            singleVisit_cur = singleVisit_head;
      while (singleVisit_cur->next != NULL) 
            singleVisit_cur = singleVisit_cur->next; }
        } 

       
   }//end addNewAttendee
   
   
   void readFile() {
   
   }
   
   void showMainMenu() {
   
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

    // allocate memory for activity list (array)
    //activity *ActivitiesList = (activity *) calloc(10, sizeof(activity));


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
   
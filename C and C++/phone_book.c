#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
/*This is a interactive code using C language coded on 03/24/2024 for the Intro to C and C++
course by Dr. Roman V. Yampolskiy by Bethanie Bairen
*/

//Definition of variables
int i;
int a = 0;
int x = 0;
int n = 0;
int p = 0;
int exitQ = 0;
int validContact = 0;
int contactlist;

//Structure containing first names, last names, and phone numbers
typedef struct{
        char first [15];
        char last [15];
        char phone [10];
        }contactbook;
        
contactbook contacts[100];

//Function to add contact
void contEntry(){
    contactlist++;
    printf("\nEnter First Name: ");
    scanf("%s", contacts[a].first);
    printf("Enter Last Name: ");
    scanf("%s", contacts[a].last);
    printf("Enter Phone Number: ");
    scanf("%s", contacts[a].phone);
    getchar();
    a++;
}

//Function to delete contact
void delContact(){
    char delFirst[15];
    char delLast[15];
    
    //Do While loop to ensure valid contact
    do{
        validContact = 0;
        printf("\nEnter first name of contact to delete:\n");
        scanf("%s", delFirst);
        printf("Enter last name of contact to delete:\n");
        scanf("%s", delLast);
        
        for (x=0; x<=contactlist; x++){
          //Check that selection matches valid entry
          if (strcmp(delFirst, contacts[x].first) == 0  && strcmp(delLast, contacts[x].last) == 0){
            strcpy(contacts[x].first, "");
            strcpy(contacts[x].last, "");
            strcpy(contacts[x].phone, "");
            printf("\nContact deleted.\n");
            validContact = 1;
            break;
          }
        }
        //Throw error message if selection does not match
        if (x>contactlist){
            validContact = 0;
            printf("\nContact entered does not exist.\n");
            break;
        }
      }while (validContact == 0);
}

//Function to display phone book
void printBook(){
    printf("\nPhone book:");
        //Iterate through contact book and print each entry
        for(i=0; i<contactlist; i++){
            //Skip entry if NULL
            if (strcmp(contacts[i].first,"") == 0){
                continue;
            } else {
                printf("\n%s, %s - %s", contacts[i].last, contacts[i].first, contacts[i].phone);
            }
        }
        printf("\n");
}

//Function to sort contacts by last name
void sortContact(){
  int y,z;
  char temp[20];
  
  for(y=1;y<contactlist;y++)
      for(z=1;z<contactlist;z++)
      {
           //Compare adjacent values
           if(strcmp(contacts[z-1].last,contacts[z].last)>0)
           {
              strcpy(temp,contacts[z-1].first);
              strcpy(contacts[z-1].first,contacts[z].first);
              strcpy(contacts[z].first,temp);
              
              strcpy(temp,contacts[z-1].last);
              strcpy(contacts[z-1].last,contacts[z].last);
              strcpy(contacts[z].last,temp);
              
              strcpy(temp,contacts[z-1].phone);
              strcpy(contacts[z-1].phone,contacts[z].phone);
              strcpy(contacts[z].phone,temp);
           }
      }
      printf("\nContacts sorted.\n");
}

      
      

//Function to find phone number from given name
void findNum(){
    char findFirst[15];
    char findLast[15];
    //Do While loop to ensure valid contact
    do{
        validContact = 0;
        printf("\nEnter first name of contact to search:\n");
        scanf("%s", findFirst);
        printf("Enter last name of contact to search:\n");
        scanf("%s", findLast);
        
        for (x=0; x<=contactlist; x++){
          //Check that selection matches valid contact
          if (strcmp(findFirst, contacts[x].first) == 0  && strcmp(findLast, contacts[x].last) == 0){
            printf("\n%s %s's phone number is %s.\n", contacts[x].first, contacts[x].last, contacts[x].phone);
            validContact = 1;
            break;
          }
        }
        //Display error message if selection is invalid
        if (x>contactlist){
            validContact = 0;
            printf("\nContact entered does not exist.\n");
            break;
        }
    }while(validContact == 0);
}

//Function to pull random contact
void rContact(){
    //Initialize truly random integer
    srand(time(NULL));
    int randInt = rand();
    //Confine random number to length of contact book
    int randNum = randInt%contactlist;
    printf("\n%s %s selected. Their phone number is %s.\n", contacts[randNum].first, contacts[randNum].last, contacts[randNum].phone);
}

//Function to delete all contacts
void delAll(){
    //Iterate through arrays and clear entries
    for (x=0; x < contactlist; x++){
                strcpy(contacts[x].first,"");
                strcpy(contacts[x].last,"");
                strcpy(contacts[x].phone,"");
            }
            printf("\nPhone book has been cleared.\n");
}


//Function to import contacts from external text file
int importCont (){
    //Local variable/array initialization
    char fileChoice[100];
    char fileLocation[100];
    FILE *contRead;
    char impFNames[50];
    char impLNames[50];
    char impPhone[50];

    //Initialize storage for current directory
    char *buf;
    buf=(char *)malloc(100*sizeof(char));
    char defaultPath[100];
    strcpy(defaultPath, getcwd(buf,100));
    free(buf);

    //Ask user for file path. Enter/Return assigns current directory
    printf("\nEnter path to file location. ('Enter' for current directory.)\n");
    fgets(fileLocation, 100, stdin);
    fileLocation[strcspn(fileLocation, "\n")] = 0;

    //Current directory assigned to file location if empty path is provided
    //if (fileLocation == NULL){
      //  strcpy(fileLocation, defaultPath);
        //printf("Default path, %s selected.\n", fileLocation);
    if (strcmp(fileLocation, "") == 0){
        strcpy(fileLocation, defaultPath);
        printf("Default path, %s selected.\n", fileLocation);
    }else if (strcmp(fileLocation, "\n") == 0){
        strcpy(fileLocation, defaultPath);
        printf("Default path, %s selected.\n", fileLocation);
    }

    //Path divider handling based off of major OS's
    #ifdef _WIN32
        strcat(fileLocation, "\\");
    
    #elif _WIN64
        strcat(fileLocation, "\\");
        
    #elif __APPLE__
        strcat(fileLocation, "/");
        
    #elif __linux__
        strcat(fileLocation, "/");
        
    #endif

    //Ask user for file name
    printf("\nEnter file name to open, including file extension.\n");
    scanf("%[^\n]%*c", fileChoice);

    //Array initialization to hold final path
    char fileImpPath[200];
    strcpy(fileImpPath, fileLocation);
    strcat(fileImpPath, fileChoice);

    //Check for existing file; exit if file does not exist; import contacts if file exists
    contRead = fopen(fileImpPath,"r");

    if (contRead == NULL){
        printf("\nFile could not be opened or does not exist. Please try another file.\n");
        return 0;
    } else {
        int y = 0;
        contactlist=0;
        while (fscanf(contRead,"%s%s%s",impLNames,impFNames,impPhone) != EOF) {
            strcpy(contacts[y].first,impFNames);
            strcpy(contacts[y].last,impLNames);
            strcpy(contacts[y].phone,impPhone);
            contactlist++;
            a++;
            y++;
        }
        printf("\nContacts have been successfully imported.\n");
    }
    
    fclose(contRead);
    return 1;
}

//Function to export contacts to external text file
void exportCont(){
   //Local variable/array initialization
   char fileExpPath[500]="";
   FILE *contRead;
   FILE *contWrite;
   char expFNames[50];
   char expLNames[50];
   char expPhone[50];
   int r = 0;
   
   //Initialize storage for current directory
   char *buf;
   buf=(char *)malloc(100*sizeof(char));
   char defaultPath[100];
   strcpy(defaultPath, getcwd(buf,100));
   free(buf);
   
   //Allocate appropriate memory for file location and file name
   char* fileChoice = malloc(100*sizeof(char));
   if (fileChoice == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
    }

   char* fileLocation = malloc(100*sizeof(char));
   if (fileLocation == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
    }
   
    //Ask user for path to file location
    printf("\nEnter path to file location.\n");
    fgets(fileLocation, 100, stdin);
    fileLocation[strcspn(fileLocation, "\n")] = 0;
    
    //If blank input, assign file location to current directory
    if (fileLocation == NULL){
        strcpy(fileLocation, defaultPath);
        printf("Current directory, %s selected.\n", fileLocation);
    }else if (strcmp(fileLocation, "") == 0){
        strcpy(fileLocation, defaultPath);
        printf("Current directory, %s selected.\n", fileLocation);
    }else if (strcmp(fileLocation, "\n") == 0){
        strcpy(fileLocation, defaultPath);
        printf("Current directory, %s selected.\n", fileLocation);
    }
    
    //Path divider handling based on common OS's
    #ifdef _WIN32
        strcat(fileLocation, "\\");
    
    #elif _WIN64
        strcat(fileLocation, "\\");
        
    #elif __APPLE__
        strcat(fileLocation, "/");
        
    #elif __linux__
        strcat(fileLocation, "/");
        
    #endif
    
    //Assure appropriate memory for final path
    if (strlen(fileExpPath) + strlen(fileLocation) < 500) {
        strncat(fileExpPath, fileLocation, 500 - strlen(fileExpPath) - 1);
    } else {
        printf("Error: not enough memory to store path.\n");
        free(fileLocation);
        free(fileChoice);
    return;
    }
    
    //Ask user for file name
    printf("\nEnter file name to open, including file extension.\n");
    fgets(fileChoice, 100, stdin);
    fileChoice[strcspn(fileChoice, "\n")] = 0;
    
    //Assure appropriate memory for final path
    if (strlen(fileExpPath) + strlen(fileChoice) < 500) {
        strncat(fileExpPath, fileChoice, 500 - strlen(fileExpPath) - 1);
    } else {
        printf("Error: not enough memory to store path.\n");
        free(fileLocation);
        free(fileChoice);
    return;
    }
    
    char* finalExpPath = malloc(strlen(fileExpPath) + 1);
    if(finalExpPath == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(finalExpPath,fileExpPath);
    
    //Determine if file already exists, alert user of new file creation if one does not already exist
    contRead = fopen(finalExpPath,"r");
    if (contRead == NULL){
        printf("\nCreating new file in directory: %s\n",fileLocation);
        fclose(contRead);
    }

    //Open file for writing; iterates through arrays and prints to file
    contWrite = fopen(finalExpPath,"w");    
    for (r=0;r<contactlist;r++){
        fprintf(contWrite,"%s\t%s\t%s\n",contacts[r].last,contacts[r].first,contacts[r].phone);
    }
    fclose(contWrite);
    
    printf("\nContacts successfully exported. Please close program to save changes.\n");

    free(fileLocation);
    free(fileChoice);
    free(finalExpPath);
    
}


//Main function
int main (){
        char choiceStr[3];
        int choice;
        
        //Loop of program, runs until '4' is entered
        do {
        printf("\nMenu:\n");
        printf("1 Add Friend\n");
        printf("2 Delete Friend\n");
        printf("3 Show Phone Book\n");
        printf("4 Sort contacts by last name\n");
        printf("5 Find Phone Number\n");
        printf("6 Choose random contact\n");
        printf("7 Delete All Contacts\n");
        printf("8 Import Contacts\n");
        printf("9 Export Contacts\n");
        printf("10 Exit\n");
        printf("What do you want to do? ");
        fgets(choiceStr, 3, stdin);
        choice = atoi(choiceStr);
        
        switch (choice){
        
        //Option 1, Contact entry
        case 1:
            contEntry();
            break;
        
        //Option 2, Contact deletion
        case 2:
          delContact();
          break;
        
        //Option 3, print phone book
        case 3:
            printBook();
            break;
        
        //Option 4, sort contacts by last name
        case 4:
            sortContact();
            break;
        
        //Option 5, find phone number
        case 5:
            findNum();
            break;
        
        //Option 6, randomly choose contact to call
        case 6:
            rContact();
            break;
            
        //Option 7, delete all contacts
        case 7:
            delAll();
            break;
        
        //Option 8, import contacts from external file
        case 8:
            importCont();
            break;
            
        //Option 9, export contacts to external file
        case 9:
            exportCont();
            break;
        
        //Option 10, exit program
        case 10:
            exitQ = 1;
            return 0;
            break;
                        }
        }  while (exitQ != 1);
        
        return 0;
}
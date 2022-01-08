// k2kanhai, Kanhai, Kerry, 501063750, section 4
// a4tandon, Tandon, Adit 500527157, section 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"


int numberOfLines(FILE *f);
void printCard (char row[5][4], int number);
void printAllFive(char first[5][4], char second[5][4], char third[5][4], char fourth[5][4], char fifth[5][4], int number);
int columnCheck(char first[5][4], char second[5][4], char third[5][4], char fourth[5][4], char fifth[5][4]);
int rowCheck(char row[5][4]);
void printLinux();
int cornerCheck(char firstRow[5][4], char fifthRow[5][4]);
int checkZero(char thirdRow[5][4]);
int firstColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]);
int secondColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]);
int thirdColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]);
int fourthColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]);
int fifthColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]);
void printCardNoUpdate(char row[5][4]);
void nonUpdatePrintAllFive(char first[5][4], char second[5][4], char third[5][4], char fourth[5][4], char fifth[5][4]);
int duplicateColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]);



int main(int argc, char *argv[]) {
    
    char firstRow[5][4] = {"", "", "", "", ""}; 
    char secondRow[5][4] = {"", "", "", "", ""}; 
    char thirdRow[5][4] = {"", "", "", "", ""};
    char fourthRow[5][4] = {"", "", "", "", ""};
    char fifthRow[5][4] = {"", "", "", "", ""};
    int dupCheck;
    char input[75];
    char letter;
    int colWin;
    int cornerWin;
    List *callList = (List*)malloc(sizeof(List));
    FILE *fp;



    int index;
    int secondIndex = 0;
    int lineCount;
    char n;
    int number;
    int min = 1;
    int max = 75;

    srand(atoi(argv[1]));

    fp = fopen(argv[2], "r");

    if (argc < 3 || argc > 3) {
        fprintf(stderr, "Usage: %s seed cardFile\n",argv[0]);
        exit(1);
    }

    if (isdigit(*argv[1]) == 0) {
        fprintf(stderr, "Expected integer seed, but got %s\n", argv[1]);
        exit(2);
    }


    if (fp == NULL) {
        fprintf(stderr, "%s is nonexistent or unreadable\n", argv[2]);
        exit(3);
    }

    lineCount = numberOfLines(fp);

    if (lineCount != 5) {
        fprintf(stderr, "%s has bad format\n", argv[2]);
        exit(4);
    }

    rewind(fp);

    // Inputs each line to each array (ex, first line into first array, etc.)
    fscanf(fp, "%s %s %s %s %s", firstRow[0], firstRow[1], firstRow[2], firstRow[3], firstRow[4]);
    fscanf(fp, "%s %s %s %s %s", secondRow[0], secondRow[1], secondRow[2], secondRow[3], secondRow[4]);
    fscanf(fp, "%s %s %s %s %s", thirdRow[0], thirdRow[1], thirdRow[2], thirdRow[3], thirdRow[4]);
    fscanf(fp, "%s %s %s %s %s", fourthRow[0], fourthRow[1], fourthRow[2], fourthRow[3], fourthRow[4]);
    fscanf(fp, "%s %s %s %s %s", fifthRow[0], fifthRow[1], fifthRow[2], fifthRow[3], fifthRow[4]);

    if (checkZero(thirdRow) == 0 || firstColCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow) == 0 || secondColCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow) == 0 ||
    thirdColCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow) == 0 || fourthColCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow) == 0 || fifthColCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow) == 0 ||
    duplicateColCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow) == 0) {
        fprintf(stderr, "%s has bad format\n", argv[2]);
        exit(4);
    }


    
    // Initiates a callList struct
    init(callList);

    printLinux();
    printAllFive(firstRow, secondRow, thirdRow, fourthRow, fifthRow, 0);

    while (1) {
        printf("enter any non-enter key for Call (q to quit): ");
        fgets(input, 75, stdin);


        if (input[0] == 'q') {
            exit(0);
        }


        if (strcmp(input, "\n") != 0) {
            system("clear");

            // Generates random number
            number = (rand () % (max - min + 1 )) + min;

            // Uses the check function to check for duplicate generated number
            dupCheck = check(callList, number);

            // Regenerates random number if a duplicate exists
            while (dupCheck == 1) {
                number = (rand () % (max - min + 1 )) + min;
                dupCheck = check(callList, number);
            }

            add(callList, number);

            printf("CallList: ");
            print(callList);

            printf("\n\n");

            printAllFive(firstRow, secondRow, thirdRow, fourthRow, fifthRow, number);

            cornerWin = cornerCheck(firstRow, fifthRow);
            colWin = columnCheck(firstRow, secondRow, thirdRow, fourthRow, fifthRow);

            // Checks for corner and column wins
            if (cornerWin == 1 || colWin == 1) {
                printf("WINNER!\n");
                exit(0);
            }

            // Checks for row win
            if (rowCheck(firstRow) == 1 || rowCheck(secondRow) == 1 || rowCheck(thirdRow) == 1 || rowCheck(fourthRow) == 1 || rowCheck(fifthRow) == 1) {
                printf("WINNER!\n");
                exit(0);
            }
        }
        else {

            // Code executes if the user presses enter without entering anything before it
            system("clear");
            printf("CallList: ");
            print(callList);

            printf("\n\n");

            nonUpdatePrintAllFive(firstRow, secondRow, thirdRow, fourthRow, fifthRow);
        }
    }

    fclose(fp);

    return 0;
}

int duplicateColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]) {
    int i;
    int check;
    check = 1;

    // Loop to check each column for duplicate values
    // If duplicate found, 0 is assigned to check

    for (i = 0; i < 5; i++) {
        if ((atoi(firstRow[i]) == atoi(secondRow[i])) || (atoi(firstRow[i]) == atoi(secondRow[i])) || (atoi(firstRow[i]) == atoi(thirdRow[i])) || (atoi(firstRow[i]) == atoi(fourthRow[i]))
        || (atoi(firstRow[i]) == atoi(fifthRow[i])) || (atoi(secondRow[i]) == atoi(thirdRow[i])) || (atoi(secondRow[i]) == atoi(fourthRow[i])) || (atoi(secondRow[i]) == atoi(fifthRow[i])) || 
        (atoi(thirdRow[i]) == atoi(fourthRow[i])) || (atoi(thirdRow[i]) == atoi(fourthRow[i])) || (atoi(fourthRow[i]) == atoi(fifthRow[i]))) {
            check = 0;
        }
    }

    return check;
}

int firstColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]) {
    int check;
    check = 0;

    // Used to check if first column has correct range of values 
    if ((atoi(firstRow[0]) >= 1 && atoi(firstRow[0]) <=15)  && (atoi(secondRow[0]) >= 1 && atoi(secondRow[0]) <=15) && (atoi(thirdRow[0]) >= 1 && atoi(thirdRow[0]) <=15) && 
    (atoi(fourthRow[0]) >= 1 && atoi(fourthRow[0]) <=15) && (atoi(fifthRow[0]) >= 1 && atoi(fifthRow[0]) <= 15)) {
        check = 1;
    }

    return check;

}

int secondColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]) {
    int check;
    check = 0;

    // Used to check if second column has correct range of values 
    if ((atoi(firstRow[1]) >= 16 && atoi(firstRow[1]) <=30)  && (atoi(secondRow[1]) >= 16 && atoi(secondRow[1]) <=30) && (atoi(thirdRow[1]) >= 16 && atoi(thirdRow[1]) <=30) && 
    (atoi(fourthRow[1]) >= 16 && atoi(fourthRow[1]) <=30) && (atoi(fifthRow[1]) >= 16 && atoi(fifthRow[1]) <=30)) {
        check = 1;
    }

    return check;

}

int thirdColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]) {
    int check;
    check = 0;

    // Used to check if third column has correct range of values 
    if ((atoi(firstRow[2]) >= 31 && atoi(firstRow[2]) <=45) && (atoi(secondRow[2]) >= 31 && atoi(secondRow[2]) <=45) && (atoi(fourthRow[2]) >= 31 && atoi(fourthRow[2]) <=45) && (atoi(fifthRow[2]) >= 31 && atoi(fifthRow[2]) <=45)) {
        check = 1;
    }

    return check;
}

int fourthColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]) {
    int check;
    check = 0;

    // Used to check if fourth column has correct range of values 
    if ((atoi(firstRow[3]) >= 46 && atoi(firstRow[3]) <= 60) && (atoi(secondRow[3]) >= 46 && atoi(secondRow[3]) <= 60) && (atoi(thirdRow[3]) >= 46 && atoi(thirdRow[3]) <= 60) && 
    (atoi(fourthRow[3]) >= 46 && atoi(fourthRow[3]) <= 60) && (atoi(fifthRow[3]) >= 46 && atoi(fifthRow[3]) <= 60)) {
            check = 1;
    }

    return check;
}

int fifthColCheck(char firstRow[5][4], char secondRow[5][4], char thirdRow[5][4], char fourthRow[5][4], char fifthRow[5][4]) {
    int check;
    check = 0;

    // Used to check if fifth column has correct range of values 
    if ((atoi(firstRow[4]) >= 61 && atoi(firstRow[4]) <= 75) && (atoi(secondRow[4]) >= 61 && atoi(secondRow[4]) <= 75) && (atoi(thirdRow[4]) >= 61 && atoi(thirdRow[4]) <= 75) && 
    (atoi(fourthRow[4]) >= 61 && atoi(fourthRow[4]) <= 75) && (atoi(fifthRow[4]) >= 61 && atoi(fifthRow[4]) <= 75)) {
            check = 1;
    }

    return check;
}

// Used to verify that middle value is 0
int checkZero(char thirdRow[5][4]) {
    if (atoi(thirdRow[2]) == 0) {
        return 1;
    }
    return 0;
}

int cornerCheck(char firstRow[5][4], char fifthRow[5][4]) {

    if (firstRow[0][strlen(firstRow[0]) - 1] == 'm' && firstRow[4][strlen(firstRow[4]) - 1] == 'm' && fifthRow[0][strlen(fifthRow[0])-1] == 'm'
    && fifthRow[4][strlen(fifthRow[4]) - 1] == 'm') {
      return 1;
    }

    return 0;

}


int columnCheck(char first[5][4], char second[5][4], char third[5][4], char fourth[5][4], char fifth[5][4]) {
    int i;
    for (i = 0; i< 5; i++) {
        if (first[i][strlen(first[i]) - 1] == 'm' && second[i][strlen(second[i]) - 1] == 'm' && third[i][strlen(third[i]) - 1] == 'm' && fourth[i][strlen(fourth[i]) - 1] == 'm' && fifth[i][strlen(fifth[i]) - 1] == 'm') {
            return 1;
        }
    }
    return 0;
}


int rowCheck(char row[5][4]) {
    int i;
    for (i = 0; i < 5; i++) {

        if (row[i][strlen(row[i]) - 1] != 'm') {
            return 0;
        }
    }

    return 1;
}

// Counts number of lines in file 
// Wherever there is a '\n', the lineCount is incremented
int numberOfLines(FILE *f) {
    int lines = 0;
    char digit;
    while ((digit = fgetc(f)) != EOF) {
        if (digit == '\n') {
            lines = lines + 1;
        }
    }

    return lines;
}

// Prints 1 row 
// Gets a number as int to check if that number exists in the row and if it does, it marks it with a 'm'
void printCard(char row[5][4], int number) {

    int i;
    int temp;

    for (i = 0; i < 5; i++) {
        temp = atoi(row[i]);
        if (number == temp) {
            strcat(row[i], "m");
        }
        printf("%-4s", row[i]);
    }
    printf("\n");
}

// Prints all five rows to simulate a card
void printAllFive(char first[5][4], char second[5][4], char third[5][4], char fourth[5][4], char fifth[5][4], int number) {

    printCard(first, number);
    printCard(second, number);
    printCard(third, number);
    printCard(fourth, number);
    printCard(fifth, number);
}

// Used for when there is no update need to be done (for when user presses enter without entering anything)
void printCardNoUpdate(char row[5][4]) {
    int i;

    for (i = 0; i < 5; i++) {
        printf("%-4s", row[i]);
    }
    printf("\n");
}

void nonUpdatePrintAllFive(char first[5][4], char second[5][4], char third[5][4], char fourth[5][4], char fifth[5][4]) {
    printCardNoUpdate(first);
    printCardNoUpdate(second);
    printCardNoUpdate(third);
    printCardNoUpdate(fourth);
    printCardNoUpdate(fifth);
}

// Prints the linux letters with the appropriate spacing
void printLinux() {
    char word[6];
    int i;

    strcpy(word, "LINUX");

    for (i = 0; i < 5; i++) {
        printf("%-4c", word[i]);
    }

    printf("\n");
}
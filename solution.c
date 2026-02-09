
#include <stdio.h>
#include <string.h>

#define SEATS 24

/* seat structure */
struct seat {
    int seatNum;
    int taken;            // 0 = empty, 1 = assigned
    char fname[20];
    char lname[20];
};

/* function declarations */
void setup(struct seat s[]);
void menuFlight(struct seat s[]);
void countEmpty(struct seat s[]);
void listEmpty(struct seat s[]);
void listAlphabetical(struct seat s[]);
void assignSeat(struct seat s[]);
void removeSeat(struct seat s[]);

int main() {
    struct seat outbound[SEATS];
    struct seat inbound[SEATS];
    char choice;

    setup(outbound);
    setup(inbound);

    do {
        printf("\nMAIN MENU\n");
        printf("a) Outbound Flight\n");
        printf("b) Inbound Flight\n");
        printf("c) Quit\n");
        printf("Choice: ");
        scanf(" %c", &choice);

        if (choice == 'a') {
            menuFlight(outbound);
        } else if (choice == 'b') {
            menuFlight(inbound);
        } else if (choice == 'c') {
            printf("Goodbye!\n");
        } else {
            printf("Invalid choice\n");
        }

    } while (choice != 'c');

    return 0;
}

void setup(struct seat s[]) {
    int i;
    for (i = 0; i < SEATS; i++) {
        s[i].seatNum = i + 1;
        s[i].taken = 0;
        strcpy(s[i].fname, "");
        strcpy(s[i].lname, "");
    }
}

void menuFlight(struct seat s[]) {
    char choice;

    do {
        printf("\nFLIGHT MENU\n");
        printf("a) Show number of empty seats\n");
        printf("b) Show list of empty seats\n");
        printf("c) Show alphabetical list\n");
        printf("d) Assign seat\n");
        printf("e) Delete seat assignment\n");
        printf("f) Return to main menu\n");
        printf("Choice: ");
        scanf(" %c", &choice);

        if (choice == 'a')
            countEmpty(s);
        else if (choice == 'b')
            listEmpty(s);
        else if (choice == 'c')
            listAlphabetical(s);
        else if (choice == 'd')
            assignSeat(s);
        else if (choice == 'e')
            removeSeat(s);
        else if (choice == 'f')
            return;
        else
            printf("Invalid choice\n");

    } while (1);
}

void countEmpty(struct seat s[]) {
    int i, count = 0;

    for (i = 0; i < SEATS; i++) {
        if (s[i].taken == 0)
            count++;
    }

    printf("Empty seats: %d\n", count);
}

void listEmpty(struct seat s[]) {
    int i;

    printf("Empty seats:\n");
    for (i = 0; i < SEATS; i++) {
        if (s[i].taken == 0)
            printf("Seat %d\n", s[i].seatNum);
    }
}

void listAlphabetical(struct seat s[]) {
    struct seat temp[SEATS];
    int i, j, count = 0;

    for (i = 0; i < SEATS; i++) {
        if (s[i].taken == 1) {
            temp[count] = s[i];
            count++;
        }
    }

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(temp[i].lname, temp[j].lname) > 0) {
                struct seat swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    for (i = 0; i < count; i++) {
        printf("Seat %d: %s %s\n",
               temp[i].seatNum,
               temp[i].fname,
               temp[i].lname);
    }
}

void assignSeat(struct seat s[]) {
    int num;

    printf("Enter seat number (1-24, 0 to cancel): ");
    scanf("%d", &num);

    if (num == 0)
        return;

    if (num < 1 || num > 24) {
        printf("Invalid seat number\n");
        return;
    }

    if (s[num - 1].taken == 1) {
        printf("Seat already taken\n");
        return;
    }

    printf("First name: ");
    scanf("%s", s[num - 1].fname);
    printf("Last name: ");
    scanf("%s", s[num - 1].lname);

    s[num - 1].taken = 1;
    printf("Seat assigned\n");
}

void removeSeat(struct seat s[]) {
    int num;

    printf("Enter seat number to delete (0 to cancel): ");
    scanf("%d", &num);

    if (num == 0)
        return;

    if (num < 1 || num > 24) {
        printf("Invalid seat number\n");
        return;
    }

    s[num - 1].taken = 0;
    strcpy(s[num - 1].fname, "");
    strcpy(s[num - 1].lname, "");

    printf("Seat assignment removed\n");
}

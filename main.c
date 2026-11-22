#include <stdio.h>
#include <string.h>

#define FLOORS 10
#define ROOMS_PER_FLOOR 10
#define MAX_ROOMS (FLOORS * ROOMS_PER_FLOOR)
#define FILE_NAME "hostel.dat"


struct Student {
    int  id;
    char name[50];
    char course[30];
};

struct Room {
    int roomNo;
    int floor;
    int occupied;            
    struct Student student;
};

struct Room rooms[MAX_ROOMS];


void initRooms(void) {
    int i;
    for (i = 0; i < MAX_ROOMS; i++) {
        rooms[i].floor = i / ROOMS_PER_FLOOR + 1;
        rooms[i].roomNo = rooms[i].floor * 100 + (i % ROOMS_PER_FLOOR) + 1;
        rooms[i].occupied = 0;
        rooms[i].student.id = 0;
        strcpy(rooms[i].student.name, "");
        strcpy(rooms[i].student.course, "");
    }
}

void saveData(void) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        return;                    
    }
    fwrite(rooms, sizeof(struct Room), MAX_ROOMS, fp);
    fclose(fp);
}

void loadData(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {              
        initRooms();
        saveData();
        return;
    }
    if (fread(rooms, sizeof(struct Room), MAX_ROOMS, fp) != MAX_ROOMS)
        initRooms();                
    fclose(fp);
}

int findStudent(int id) {
    int i;
    for (i = 0; i < MAX_ROOMS; i++)
        if (rooms[i].occupied && rooms[i].student.id == id)
            return i;
    return -1;
}

int findRoom(int roomNo) {
    int i;
    for (i = 0; i < MAX_ROOMS; i++)
        if (rooms[i].roomNo == roomNo)
            return i;
    return -1;
}

/* ---------- Main features ---------- */
void displayAvailable(void) {
    int f, r, idx, count, total = 0;
    printf("\n--- Available Rooms (floor wise) ---\n");
    for (f = 1; f <= FLOORS; f++) {
        count = 0;
        printf("Floor %2d: ", f);
        for (r = 0; r < ROOMS_PER_FLOOR; r++) {
            idx = (f - 1) * ROOMS_PER_FLOOR + r;
            if (!rooms[idx].occupied) {
                printf("%d ", rooms[idx].roomNo);
                count++;
            }
        }
        if (count == 0) printf("(full)");
        printf("\n");
        total += count;
    }
    printf("Total available rooms: %d\n", total);
}

void displayOccupied(void) {
    int i, count = 0;
    printf("\n--- Occupied Rooms ---\n");
    printf("%-6s %-6s %-8s %-20s %-15s\n", "Floor", "Room", "ID", "Name", "Course");
    for (i = 0; i < MAX_ROOMS; i++)
        if (rooms[i].occupied) {
            printf("%-6d %-6d %-8d %-20s %-15s\n", rooms[i].floor, rooms[i].roomNo,
                   rooms[i].student.id, rooms[i].student.name,
                   rooms[i].student.course);
            count++;
        }
    if (count == 0) printf("No rooms occupied.\n");
    else printf("Total occupied rooms: %d\n", count);
}

void allocateRoom(void) {
    struct Student s;
    int roomNo, idx;

    printf("\nEnter Student ID: ");
    if (scanf("%d", &s.id) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); return; }
    if (findStudent(s.id) != -1) {
        printf("This student already has a room!\n");
        return;
    }
    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);
    printf("Enter Course: ");
    scanf(" %29[^\n]", s.course);

    displayAvailable();
    printf("Enter Room number to allocate: ");
    if (scanf("%d", &roomNo) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); return; }

    idx = findRoom(roomNo);
    if (idx == -1) {
        printf("Room does not exist!\n");
    } else if (rooms[idx].occupied) {
        printf("Room %d is already occupied!\n", roomNo);
    } else {
        rooms[idx].student = s;
        rooms[idx].occupied = 1;
        saveData();
        printf("Room %d (Floor %d) allocated to %s successfully.\n",
               roomNo, rooms[idx].floor, s.name);
    }
}

void searchByStudentId(void) {
    int id, idx;
    printf("\nEnter Student ID to search: ");
    if (scanf("%d", &id) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); return; }
    idx = findStudent(id);
    if (idx == -1) {
        printf("No allocation found for ID %d.\n", id);
    } else {
        printf("Student ID : %d\n", rooms[idx].student.id);
        printf("Name       : %s\n", rooms[idx].student.name);
        printf("Course     : %s\n", rooms[idx].student.course);
        printf("Floor      : %d\n", rooms[idx].floor);
        printf("Room No    : %d\n", rooms[idx].roomNo);
    }
}

void vacateRoom(void) {
    int roomNo, idx;
    printf("\nEnter Room number to vacate: ");
    if (scanf("%d", &roomNo) != 1) { while (getchar() != '\n'); printf("Invalid input!\n"); return; }
    idx = findRoom(roomNo);
    if (idx == -1) {
        printf("Room does not exist!\n");
    } else if (!rooms[idx].occupied) {
        printf("Room %d is already empty.\n", roomNo);
    } else {
        printf("Room %d vacated (student %s).\n", roomNo, rooms[idx].student.name);
        rooms[idx].occupied = 0;
        rooms[idx].student.id = 0;
        strcpy(rooms[idx].student.name, "");
        strcpy(rooms[idx].student.course, "");
        saveData();
    }
}

int main(void) {
    int choice;
    loadData();

    do {
        printf("\n===== HOSTEL MANAGEMENT =====\n");
        printf("1. Allocate Room\n");
        printf("2. Display Available Rooms\n");
        printf("3. Display Occupied Rooms (Allocations)\n");
        printf("4. Search Allocation by Student ID\n");
        printf("5. Vacate Room\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: allocateRoom();      break;
            case 2: displayAvailable();  break;
            case 3: displayOccupied();   break;
            case 4: searchByStudentId(); break;
            case 5: vacateRoom();        break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 6);

    return 0;
}

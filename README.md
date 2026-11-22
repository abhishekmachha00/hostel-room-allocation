# Hostel Room Allocation System (C)

A menu-driven C program that manages hostel room allocations. It stores
student and room details, shows available and occupied rooms, allocates
only free rooms, searches allocations by student ID, and vacates rooms.
All data is saved to a file, so allocations are not lost when the
program closes.

## Features

- Allocate a room to a student (student ID, name, course). A room that
  is already occupied cannot be allocated again, and a student who
  already has a room cannot get a second one.
- Display available rooms, floor by floor.
- Display all occupied rooms with the student's details.
- Search for an allocation by student ID.
- Vacate a room, which makes it available again.
- Data is saved automatically after every change (file handling).

## C concepts used

- Structures (`struct Student`, `struct Room`)
- Arrays (all rooms stored in one array)
- Functions (one function per feature)
- File handling (`fopen`, `fwrite`, `fread` - data is stored in
  `hostel.dat`)
- Loops, switch-case menu, and basic input validation

## How to run

You need a C compiler such as `gcc`.

```sh
gcc main.c -o main
./main        # on Windows: main.exe
```

Or with the included Makefile:

```sh
make run
```

## How the program works

All rooms are kept in one array of `struct Room`. Each room has a room
number, a floor number, an occupied flag, and a `struct Student` for the
student living in it. Room numbers are generated as
`floor * 100 + room index`, so room 305 means floor 3, room 5.

When the program starts, it loads the saved data from `hostel.dat`. If
the file does not exist yet, it creates all rooms as empty and saves
them. Every allocation or vacate operation updates the file immediately.

By default the hostel has 10 floors with 10 rooms per floor. This can be
changed at the top of `main.c`:

```c
#define FLOORS 10
#define ROOMS_PER_FLOOR 10
```

Note: `hostel.dat` is created when the program runs and contains saved
student data. It is not part of the source code and should not be
uploaded.
## Team

- Abhishek
- Kartavyamani

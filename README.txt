CAMPUS RESOURCE RESERVATION SYSTEM

1. PROJECT TITLE

Campus Resource Reservation System

2. TEAM MEMBERS

* Vijay Ram Sanvi Bhaskarla (GitHub: VijayramS90104)
* Anish Dahal (GitHub: Anish2061)
* Sushil Gautam (GitHub: gsush701-gif)

3. PROJECT DESCRIPTION

This project is a C++ program for managing campus resource reservations. Users can view resources, make and cancel reservations, and join waiting lists. The program also checks reservation dates to prevent conflicts and keeps a history of cancelled reservations.

4. FEATURES AND DATA STRUCTURES

The program includes:

* Loading and displaying campus resources
* Creating and cancelling reservations
* Checking for date conflicts
* Managing waiting lists
* Automatically assigning resources when possible
* Undoing cancelled reservations
* Keeping cancellation history

The project uses four main data structures:

* Vector for the resource inventory
* Linked list for active reservations
* Queue for waiting lists
* Stack for cancellation history

5. FILE STRUCTURE AND DATA FORMAT

The `include/` folder contains the header files, `src/` contains the C++ source files, and `data/` contains the project's data files.

The `resources.txt` file uses pipe-separated values:

R101|Study Room 101|Study Room|Available

The availability value is either `Available` or `Unavailable`.

The `reservations.txt` file is sample/reference data and is not automatically loaded when the program starts.

6. BUILD AND RUN

Compile the project from the project root:

g++ -Iinclude -c src/main.cpp -o main.o
g++ -Iinclude -c src/Resource.cpp -o Resource.o
g++ -Iinclude -c src/Reservation.cpp -o Reservation.o
g++ -Iinclude -c src/ReservationManager.cpp -o ReservationManager.o
g++ -Iinclude -c src/CancellationHistory.cpp -o CancellationHistory.o
g++ -Iinclude -c src/WaitingList.cpp -o WaitingList.o
g++ -Iinclude -c src/Student.cpp -o Student.o
g++ -Iinclude -c src/Sorting.cpp -o Sorting.o
g++ -Iinclude -c src/ReportGenerator.cpp -o ReportGenerator.o
g++ -Iinclude -c src/Searching.cpp -o Searching.o

Then create the executable:

g++ *.o -o campus_system

Run the program with:

./campus_system

7. DESIGN NOTES AND GITHUB

Resource availability is stored as general information. Actual availability for a specific date is checked by looking at existing reservations and checking for date conflicts.

The project repository is:

https://github.com/gsush701-gif/campus-reservation-system

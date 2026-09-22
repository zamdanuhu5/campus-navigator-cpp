/*
 * ============================================================
 *  LDCW6123 - Part 2: Interactive C++ Program
 *  Title   : Smart Campus Navigator
 *  Purpose : Console-based wayfinding assistant inspired by
 *            the Smart Campus Navigation System researched
 *            in Part 1 (Winston's Sustaining Innovation Model).
 *
 *  The user selects their current location and destination
 *  from a list of campus buildings. The program looks up the
 *  route, walking distance, estimated time, and a helpful tip,
 *  then displays the result - similar to how a real campus
 *  navigation app would guide a student between buildings.
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int NUM_BUILDINGS = 6;

// List of campus buildings the navigator supports
string buildingNames[NUM_BUILDINGS] = {
    "Main Library",
    "Faculty of Computing & Informatics",
    "Student Cafeteria",
    "Sports Complex",
    "Administration Building",
    "Student Hostel"
};

// distanceTable[i][j] = walking distance (in metres) from building i to building j
int distanceTable[NUM_BUILDINGS][NUM_BUILDINGS] = {
    /*                  Library  Computing  Cafeteria  Sports  Admin  Hostel */
    /* Library     */ {    0,      250,        400,      600,   350,    700 },
    /* Computing   */ {  250,        0,        300,      550,   200,    650 },
    /* Cafeteria   */ {  400,      300,          0,      450,   500,    300 },
    /* Sports      */ {  600,      550,        450,        0,   700,    500 },
    /* Admin       */ {  350,      200,        500,      700,     0,    800 },
    /* Hostel      */ {  700,      650,        300,      500,   800,      0 }
};

// Average walking speed assumption: 80 metres per minute
const double WALK_SPEED_M_PER_MIN = 80.0;

// Prints the main menu of buildings
void displayBuildingMenu() {
    cout << "\n----------------------------------------\n";
    cout << " Campus Buildings\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        cout << " [" << (i + 1) << "] " << buildingNames[i] << endl;
    }
    cout << "----------------------------------------\n";
}

// Reads and validates a building choice (1..NUM_BUILDINGS) from the user
int readBuildingChoice(const string &label) {
    int choice;
    while (true) {
        cout << label << " (1-" << NUM_BUILDINGS << "): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a number.\n";
            continue;
        }
        if (choice < 1 || choice > NUM_BUILDINGS) {
            cout << "  Please choose a number between 1 and " << NUM_BUILDINGS << ".\n";
            continue;
        }
        return choice - 1; // convert to zero-based index
    }
}

// Returns a short navigation tip depending on the route
string getRouteTip(int from, int to) {
    if (from == to) {
        return "Tip: You are already there!";
    } else if (buildingNames[from] == "Student Hostel" && buildingNames[to] == "Faculty of Computing & Informatics") {
        return "Tip: Cut through the Cafeteria walkway to avoid the morning crowd.";
    } else if (buildingNames[to] == "Main Library") {
        return "Tip: The Library's main entrance is on the east side, near the fountain.";
    } else if (buildingNames[to] == "Sports Complex") {
        return "Tip: Sports Complex is a longer walk - consider cycling if in a hurry.";
    } else {
        return "Tip: Follow the main pathway signboards for the fastest route.";
    }
}

// Displays the computed route information
void showRoute(int from, int to) {
    if (from == to) {
        cout << "\nYou selected the same building for start and destination.\n";
        cout << getRouteTip(from, to) << endl;
        return;
    }

    int distance = distanceTable[from][to];
    int minutes = (int)((distance + WALK_SPEED_M_PER_MIN - 1) / WALK_SPEED_M_PER_MIN);


    cout << "\n========== Route Found ==========\n";
    cout << "From        : " << buildingNames[from] << endl;
    cout << "To          : " << buildingNames[to] << endl;
    cout << "Distance    : " << distance << " metres" << endl;
    cout << fixed << setprecision(1);
    cout << "Est. Time   : " << minutes << " min (walking)" << endl;
	cout << getRouteTip(from, to) << endl;
    cout << "==================================\n";
}

// Displays the welcome banner
void showWelcome() {
    cout << "==========================================\n";
    cout << "   SMART CAMPUS NAVIGATOR\n";
    cout << "   LDCW6123 Group Project - Part 2\n";
    cout << "==========================================\n";
    cout << "This tool helps you find your way around campus,\n";
    cout << "just like the Smart Campus Navigation Systems\n";
    cout << "researched in Part 1.\n";
}

int main() {
    showWelcome();

    char again = 'y';

    // Loop so the user can plan multiple trips without restarting the program
    while (again == 'y' || again == 'Y') {
    displayBuildingMenu();

    int from = readBuildingChoice("Enter your CURRENT location");
	int to   = readBuildingChoice("Enter your DESTINATION");


    showRoute(from, to);

        cout << "\nWould you like to plan another route? (y/n): ";
        cin >> again;
    }

    cout << "\nThank you for using Smart Campus Navigator. Safe travels!\n";
    return 0;
}

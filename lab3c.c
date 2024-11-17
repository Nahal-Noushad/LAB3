#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_TEAMS 5       // Maximum number of teams
#define SQUAD_SIZE 11     // Maximum players per team

// Structure for player age
typedef struct {
    int day;
    int month;
    int year;
} age_t;

// Structure for player details
typedef struct {
    char name[26];         // Player name (max 25 chars + null terminator)
    int kit_number;        // Player kit number
    char club[26];         // Club name
    age_t age;             // Player age
    char position[16];     // Player position (max 15 chars + null terminator)
} player_t;

// Structure for team details
typedef struct {
    char team_name[21];    // Team name (max 20 chars + null terminator)
    player_t players[SQUAD_SIZE]; // Array of players in the team
    int active_size;       // Current number of players in the team
} team_t;

team_t teams[NUM_TEAMS];   // Array to store teams
int enrolled_teams = 0;    // Counter for enrolled teams

// Function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(char message[100]);

int main() {
    int choice;

    // Main menu loop
    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from input buffer

        // Handle menu choices
        if (choice == 1) enroll_club();
        else if (choice == 2) add_player();
        else if (choice == 3) search_update();
        else if (choice == 4) display_club_statistics();
        else {
            printf("Exiting the program.\n");
            break;
        }
    } while (1);

    return 0;
}

void display_menu() {
    // Display the main menu
    printf("\n--- League Team Application Menu ---\n");
    printf("1. Enroll a Club\n");
    printf("2. Add a Player to a Club\n");
    printf("3. Search and Update Player Details\n");
    printf("4. Display Club Statistics\n");
    printf("Any other key to Exit\n");
}

void enroll_club() {
    // Add a new club
    if (enrolled_teams >= NUM_TEAMS) {
        handle_error("Maximum number of clubs already enrolled.");
        return;
    }

    char new_team_name[21];
    printf("Enter club name (max 20 characters): ");
    fgets(new_team_name, sizeof(new_team_name), stdin);

    // Remove newline character from input
    size_t len = strlen(new_team_name);
    if (len > 0 && new_team_name[len - 1] == '\n') {
        new_team_name[len - 1] = '\0';
    }

    // Check for duplicate club name
    for (int i = 0; i < enrolled_teams; i++) {
        if (strcasecmp(teams[i].team_name, new_team_name) == 0) {
            handle_error("Duplicate club name found.");
            return;
        }
    }

    // Add club to the list
    strcpy(teams[enrolled_teams].team_name, new_team_name);
    teams[enrolled_teams].active_size = 0;
    enrolled_teams++;
    printf("Club successfully enrolled.\n");
}

void add_player() {
    // Add a player to a club
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    printf("Select a club by index:\n");
    for (int i = 0; i < enrolled_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].team_name);
    }

    int club_index;
    scanf("%d", &club_index);
    getchar(); // Clear newline character
    club_index--;

    if (club_index < 0 || club_index >= enrolled_teams) {
        handle_error("Invalid club selection.");
        return;
    }

    if (teams[club_index].active_size >= SQUAD_SIZE) {
        handle_error("Squad is full for this club.");
        return;
    }

    player_t new_player;
    printf("Enter player name (max 25 characters): ");
    fgets(new_player.name, sizeof(new_player.name), stdin);

    // Remove newline character from input
    size_t len = strlen(new_player.name);
    if (len > 0 && new_player.name[len - 1] == '\n') {
        new_player.name[len - 1] = '\0';
    }

    printf("Enter kit number (1-99): ");
    scanf("%d", &new_player.kit_number);
    getchar(); // Clear newline character

    // Validate date of birth
    bool valid_date = false;
    do {
        printf("Enter date of birth (DD MM YYYY): ");
        scanf("%d %d %d", &new_player.age.day, &new_player.age.month, &new_player.age.year);
        getchar(); // Clear newline character

        if (new_player.age.day >= 1 && new_player.age.day <= 31 &&
            new_player.age.month >= 1 && new_player.age.month <= 12) {
            valid_date = true;
        } else {
            handle_error("Invalid date of birth. Day should be between 01 and 31, and month between 01 and 12.");
        }
    } while (!valid_date);

    printf("Enter position (max 15 characters): ");
    fgets(new_player.position, sizeof(new_player.position), stdin);

    // Remove newline character
    len = strlen(new_player.position);
    if (len > 0 && new_player.position[len - 1] == '\n') {
        new_player.position[len - 1] = '\0';
    }

    // Assign player's club
    strcpy(new_player.club, teams[club_index].team_name);

    // Check for duplicate players
    for (int i = 0; i < teams[club_index].active_size; i++) {
        if (strcasecmp(teams[club_index].players[i].name, new_player.name) == 0 ||
            teams[club_index].players[i].kit_number == new_player.kit_number) {
            handle_error("Duplicate player name or kit number found.");
            return;
        }
    }

    // Add player to the club
    teams[club_index].players[teams[club_index].active_size] = new_player;
    teams[club_index].active_size++;
    printf("Player added successfully.\n");
}


void search_update() {
    // Search and update a player's details
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    char search_name[26];
    int search_kit_number;
    bool found = false;

    printf("Enter player name to search: ");
    fgets(search_name, sizeof(search_name), stdin);

    // Remove newline character
    size_t len = strlen(search_name);
    if (len > 0 && search_name[len - 1] == '\n') {
        search_name[len - 1] = '\0';
    }

    printf("Enter kit number to search: ");
    scanf("%d", &search_kit_number);
    getchar(); // Clear newline character

    // Search for the player in all teams
    for (int i = 0; i < enrolled_teams; i++) {
        for (int j = 0; j < teams[i].active_size; j++) {
            if (strcasecmp(teams[i].players[j].name, search_name) == 0 ||
                teams[i].players[j].kit_number == search_kit_number) {
                found = true;

                // Display player details
                printf("\nPlayer found: %s\n", teams[i].players[j].name);
                printf("Kit: %d\n", teams[i].players[j].kit_number);
                printf("Position: %s\n", teams[i].players[j].position);
                printf("Date of Birth: %02d/%02d/%04d\n",
                       teams[i].players[j].age.day,
                       teams[i].players[j].age.month,
                       teams[i].players[j].age.year);

                // Update details
                printf("Enter new kit number (1-99): ");
                scanf("%d", &teams[i].players[j].kit_number);
                getchar(); // Clear newline
                printf("Enter new position (max 15 characters): ");
                fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin);

                // Remove newline character
                len = strlen(teams[i].players[j].position);
                if (len > 0 && teams[i].players[j].position[len - 1] == '\n') {
                    teams[i].players[j].position[len - 1] = '\0';
                }

                printf("Enter new date of birth (DD MM YYYY): ");
                scanf("%d %d %d", &teams[i].players[j].age.day, &teams[i].players[j].age.month, &teams[i].players[j].age.year);
                getchar(); // Clear newline
                printf("Player updated successfully.\n");
                return;
            }
        }
    }

    if (!found) {
        printf("No matching player found.\n");
    }
}

void display_club_statistics() {
    // Display statistics for all clubs
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    for (int i = 0; i < enrolled_teams; i++) {
        printf("\nTeam: %s\n", teams[i].team_name);
        printf("Number of players: %d\n", teams[i].active_size);

        int total_age = 0;
        for (int j = 0; j < teams[i].active_size; j++) {
            // Calculate and display each player's details
            total_age += 2024 - teams[i].players[j].age.year; // Adjust for current year
            printf("Player: %s, Kit: %d, Position: %s, Age: %d\n",
                   teams[i].players[j].name,
                   teams[i].players[j].kit_number,
                   teams[i].players[j].position,
                   2024 - teams[i].players[j].age.year);
        }

        if (teams[i].active_size > 0) {
            printf("Average age: %.2f\n", (float)total_age / teams[i].active_size);
        }
    }
}

void handle_error(char message[100]) {
    // Handle and display errors
    printf("Error: %s\n", message);
}

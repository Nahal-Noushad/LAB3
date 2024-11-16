#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_TEAMS 5
#define SQUAD_SIZE 11

typedef struct {
    int day;
    int month;
    int year;
} age_t;

typedef struct {
    char name[26]; // 25 + 1 for null terminator
    int kit_number;
    char club[26];
    age_t age;
    char position[16]; // Adjust size as needed
} player_t;

typedef struct {
    char team_name[21]; // 20 + 1 for null terminator
    player_t players[SQUAD_SIZE];
    int active_size;
} team_t;

team_t teams[NUM_TEAMS];
int enrolled_teams = 0;

// Function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(char message[100]);

int main() {
    int choice;

    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character left in the input buffer

        if (choice == 1) {
            enroll_club();
        } else if (choice == 2) {
            add_player();
        } else if (choice == 3) {
            search_update();
        } else if (choice == 4) {
            display_club_statistics();
        } else {
            printf("Exiting the program.\n");
            break;
        }
    } while (1);

    return 0;
}

void display_menu() {
    printf("\n--- League Team Application Menu ---\n");
    printf("1. Enroll a Club\n");
    printf("2. Add a Player to a Club\n");
    printf("3. Search and Update Player Details\n");
    printf("4. Display Club Statistics\n");
    printf("Any other key to Exit\n");
}

void enroll_club() {
    if (enrolled_teams >= NUM_TEAMS) {
        handle_error("Maximum number of clubs already enrolled.");
        return;
    }

    char new_team_name[21];
    printf("Enter club name (max 20 characters): ");
    fgets(new_team_name, sizeof(new_team_name), stdin);

    // Handle newline character
    size_t len = strlen(new_team_name);
    if (len > 0 && new_team_name[len - 1] == '\n') {
        new_team_name[len - 1] = '\0';
    }

    // Check for duplicate team name
    for (int i = 0; i < enrolled_teams; i++) {
        if (strcasecmp(teams[i].team_name, new_team_name) == 0) {
            handle_error("Duplicate club name found.");
            return;
        }
    }

    strcpy(teams[enrolled_teams].team_name, new_team_name);
    teams[enrolled_teams].active_size = 0;
    enrolled_teams++;

    printf("Club successfully enrolled.\n");
}

void add_player() {
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
    getchar(); // Clear the newline character left in the input buffer
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
    // Handle newline character
    size_t len = strlen(new_player.name);
    if (len > 0 && new_player.name[len - 1] == '\n') {
        new_player.name[len - 1] = '\0';
    }

    printf("Enter kit number (1-99): ");
    scanf("%d", &new_player.kit_number);
    getchar(); // Clear the newline character left in the input buffer
    printf("Enter date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &new_player.age.day, &new_player.age.month, &new_player.age.year);
    getchar(); // Clear the newline character left in the input buffer
    printf("Enter position (max 15 characters): ");
    fgets(new_player.position, sizeof(new_player.position), stdin);
    // Handle newline character
    len = strlen(new_player.position);
    if (len > 0 && new_player.position[len - 1] == '\n') {
        new_player.position[len - 1] = '\0';
    }

    // Assign the player's club to the current team's name
    strcpy(new_player.club, teams[club_index].team_name);

    // Check for duplicates
    for (int i = 0; i < teams[club_index].active_size; i++) {
        if (strcasecmp(teams[club_index].players[i].name, new_player.name) == 0 ||
            teams[club_index].players[i].kit_number == new_player.kit_number) {
            handle_error("Duplicate player name or kit number found.");
            return;
        }
    }

    // Add player
    teams[club_index].players[teams[club_index].active_size] = new_player;
    teams[club_index].active_size++;
    printf("Player added successfully.\n");
}

void search_update() {
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    char search_name[26];
    int search_kit_number;
    bool found = false;

    printf("Enter player name to search: ");
    fgets(search_name, sizeof(search_name), stdin);
    // Handle newline character
    size_t len = strlen(search_name);
    if (len > 0 && search_name[len - 1] == '\n') {
        search_name[len - 1] = '\0';
    }
    printf("Enter kit number to search: ");
    scanf("%d", &search_kit_number);
    getchar(); // Clear the newline character left in the input buffer

    for (int i = 0; i < enrolled_teams; i++) {
        for (int j = 0; j < teams[i].active_size; j++) {
            if (strcasecmp(teams[i].players[j].name, search_name) == 0 ||
                teams[i].players[j].kit_number == search_kit_number) {
                found = true;
                printf("\nPlayer found: %s\n", teams[i].players[j].name);
                printf("Kit: %d\n", teams[i].players[j].kit_number);
                printf("Position: %s\n", teams[i].players[j].position);
                printf("Date of Birth: %02d/%02d/%04d\n",
                       teams[i].players[j].age.day,
                       teams[i].players[j].age.month,
                       teams[i].players[j].age.year);

                // Update player details
                printf("Enter new kit number (1-99): ");
                scanf("%d", &teams[i].players[j].kit_number);
                getchar(); // Clear the newline character left in the input buffer
                printf("Enter new position (max 15 characters): ");
                fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin);
                // Handle newline character
                len = strlen(teams[i].players[j].position);
                if (len > 0 && teams[i].players[j].position[len - 1] == '\n') {
                    teams[i].players[j].position[len - 1] = '\0';
                }
                printf("Enter new date of birth (DD MM YYYY): ");
                scanf("%d %d %d", &teams[i].players[j].age.day, &teams[i].players[j].age.month, &teams[i].players[j].age.year);
                getchar(); // Clear the newline character left in the input buffer

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
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    for (int i = 0; i < enrolled_teams; i++) {
        printf("\nTeam: %s\n", teams[i].team_name);
        printf("Number of players: %d\n", teams[i].active_size);

        int total_age = 0;
        for (int j = 0; j < teams[i].active_size; j++) {
            total_age += 2024 - teams[i].players[j].age.year; // Adjust current year
            printf("Player: %s, Kit: %d, Position: %s, Age: %d\n",
                   teams[i].players[j].name,
                   teams[i].players[j].kit_number,
                   teams[i].players[j].position,
                   (2024 - teams[i].players[j].age.year));
        }

        if (teams[i].active_size > 0) {
            printf("Average age: %.2f\n", (float)total_age / teams[i].active_size);
        }
    }
}

void handle_error(char message[100]) {
    printf("Error: %s\n", message);
}

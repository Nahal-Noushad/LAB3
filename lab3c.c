#include <stdio.h> 
#include <stdbool.h> 
#include <string.h>

#define NO_TEAMS 5
#define NO_PLAYERS 11

struct fb_player{
    char full_name_p[30];
    int kit_no;
    char club_name[20];
    char position[10];
    struct age{
        int day;
        int month;
        int year;
    };
};

struct team_info{
    char team_name[30];
    struct team_details[NO_PLAYERS];
    int current_no_p;
};


void display_menu(int value){
    printf("ENTER 1: Enroll CLub \nENTER 2: Add player\nENTER 3: Search update\nENTER 4: Display club\nENTER 5: handle error")
}

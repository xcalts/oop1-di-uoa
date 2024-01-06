#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <string>
#include <algorithm>
#include <vector>

#include "secretary.h"

using namespace std;

void display_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices) {
    int x = 2, y = 2;
    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}


int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // Initialize secretery
    Secretary secretary;
    secretary.loadAll();

    // Define the Menu options
    int n_choices = 21;
    const char *choices[] = {
        " 1. Create a new course.",
        " 2. Read an existing course.",
        " 3. Update an existing course.",
        " 4. Delete an existing course.",
        " 5. List all courses.",
        " 6. Create a new student.",
        " 7. Read an existing student.",
        " 8. Update an existing student.",
        " 9. Delete an existing student.",
        "10. List all students.",
        "11. Create a new professor.",
        "12. Read an existing professor.",
        "13. Update an existing professor.",
        "14. Delete an existing professor.",
        "15. List all professors.",
        "16. Assign a course to a professor.",
        "17. Register a student in a course.",
        "18. Add a passed course to a student.",
        "19. ",
        "20. ",
        "21. Save the database."
    };

    // Get screen size
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    // Calculate dimensions
    int menuWidth = maxX / 4;
    int mainWidth = maxX - menuWidth;

    // Create a menu window on the left
    WINDOW* menuWindow = newwin(maxY, menuWidth, 0, 0);
    keypad(menuWindow, TRUE);
    mvwprintw(menuWindow, 1, 1, "Menu");

    // Create a main window on the right
    WINDOW* mainWindow = newwin(maxY, mainWidth, 0, menuWidth);
    box(mainWindow, 0, 0);
    mvwprintw(mainWindow, 1, 1, " ____  ____  ____        ____  ____  ____     _  _____ ____  _____      ____");
    mvwprintw(mainWindow, 2, 1, "/  _ \\/  _ \\/  __\\      /  __\\/  __\\/  _ \\   / |/  __//   _\\/__ __\\    /_   \\");
    mvwprintw(mainWindow, 3, 1, "| / \\|| / \\||  \\/|_____ |  \\/||  \\/|| / \\|   | ||  \\  |  /    / \\_____  /   /");
    mvwprintw(mainWindow, 4, 1, "| \\_/|| \\_/||  __/\\____\\|  __/|    /| \\_/|/\\_| ||  /_ |  \\_   | |\\____\\/   /_");
    mvwprintw(mainWindow, 5, 1, "\\____/\\____/\\_/         \\_/   \\_/\\_\\____/\\____/\\____\\____/  \\_/      \\____/");
    mvwprintw(mainWindow, 7, 1, " ");
    mvwprintw(mainWindow, 8, 1, "OOP - Project 2");
    mvwprintw(mainWindow, 9, 1, "Christos Kaltsas");
    mvwprintw(mainWindow, 10, 1, "1115202000289");
    wrefresh(mainWindow);

    // Menu interaction
    int highlight = 1;
    int choice = 0;
    int c;
    bool exit_program = false;

    display_menu(menuWindow, highlight, choices, n_choices);
    while(!exit_program) {
        c = wgetch(menuWindow);

        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else 
                    ++highlight;
                break;
            case 'q': // Add this case to handle 'q' key
                exit_program = true;
                break;
            case 10: // Enter key
                choice = highlight;
                werase(mainWindow);
                box(mainWindow, 0, 0);
                wrefresh(mainWindow);
                switch (choice)
                {
                    case 1:
                        secretary.createCourse(mainWindow);
                        break;
                    case 2:
                        secretary.readCourse(mainWindow);
                        break;
                    case 3:
                        secretary.updateCourse(mainWindow);
                        break;
                    case 4:
                        secretary.deleteCourse(mainWindow);
                        break;
                    case 5:
                        secretary.listCourses(mainWindow);
                        break;
                    case 6:
                        secretary.createStudent(mainWindow);
                        break;
                    case 7:
                        secretary.readStudent(mainWindow);
                        break;
                    case 8:
                        secretary.updateStudent(mainWindow);
                        break;
                    case 9:
                        secretary.deleteStudent(mainWindow);
                        break;
                    case 10:
                        secretary.listStudents(mainWindow);
                        break;
                    case 11:
                        secretary.createProfessor(mainWindow);
                        break;
                    case 12:
                        secretary.readProfessor(mainWindow);
                        break;
                    case 13:
                        secretary.updateProfessor(mainWindow);
                        break;
                    case 14:
                        secretary.deleteProfessor(mainWindow);
                        break;
                    case 15:
                        secretary.listProfessors(mainWindow);
                        break;
                    case 16:
                        secretary.assignProfessor(mainWindow);
                        break;
                    case 17:
                        secretary.registerStudent(mainWindow);
                        break;
                    case 18:
                        secretary.passCourse(mainWindow);
                        break;
                    case 21:
                        secretary.saveAll();
                        break;
                    
                    default:
                        break;
                }
            default:
                break;
        }
        display_menu(menuWindow, highlight, choices, n_choices);
        if(choice != 0) {
            // Process the choice
            wrefresh(mainWindow);
        }
    }

    // Cleanup
    delwin(menuWindow);
    delwin(mainWindow);
    endwin();

    // Save
    secretary.saveAll();

    return 0;
}
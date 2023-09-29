#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

int ch, s = 4, i;
char arr[20], shot[20], starts, help, arr1[20], arr2[20];
int x1 = 200, y1 = 350, x2 = 200, y2 = 350, i, bc1 = 100, bc2 = 150;
int y = 400, x3 = 180, y3 = 390, x4 = 220, y4 = 390, k = 0, bh = 100, bh2 = 50;
int min = 100, max = 330, min1 = 101, max1 = 331;
int incre = 2, level = 50, lev = 1, move = 7;

void start() {
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    refresh();

    bh = 100;
    bh2 = 50;
    incre = 2;
    level = 50;
    lev = 1;
    move = 7;
    k = 0;
    s = 4;
    attron(COLOR_PAIR(2));
    mvprintw(5, 5, "ROCKET SHOT");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(8, 5, "Press s to start");
    mvprintw(10, 5, "Press h for help");
    mvprintw(12, 5, "Press e to exit");
    attroff(COLOR_PAIR(3));
}

void ghelp() {
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(1, 1, "1. Press <- (left arrow key) for moving to the left side.");
    mvprintw(2, 1, "2. Press -> (right arrow key) for moving to the right side.");
    mvprintw(3, 1, "3. Press F key to fire on the space objects.");
    mvprintw(4, 1, "4. SHOTS :) Number of fire shot remaining.");
    mvprintw(5, 1, "5. LEVEL :) Difficulty level.");
    mvprintw(6, 1, "6. TARGET :) Your aim. You need to get a minimum target score");
    mvprintw(7, 1, "   to complete the level.");
    mvprintw(8, 1, "7. SCORE :) Your score. Hit the middle of the object to get");
    mvprintw(9, 1, "   high score.");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvprintw(11, 1, "TIP: Your movement speed and the object's falling speed");
    mvprintw(12, 1, "     increase when difficulty level goes up.");
    attroff(COLOR_PAIR(3));
    refresh();
    getch();
}

void loading() {
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(10, 5, "LOADING");
    attroff(COLOR_PAIR(2));
    for (i = 0; i < 20; i++) {
        attron(COLOR_PAIR(2));
        mvaddch(12, 10 + i, ACS_BLOCK);
        attroff(COLOR_PAIR(2));
        refresh();
        usleep(100000);
    }
}

void rocket() {
    attron(COLOR_PAIR(2));
    mvaddch(y1, x1, '|');
    mvaddch(y2, x2, '|');
    mvaddch(y3, x3, '|');
    mvaddch(y4, x4, '|');
    mvprintw(y4 + 1, x4 - 2, "|||");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    mvaddch(y4 + 2, x4 - 1, '|');
    mvaddch(y4 + 3, x4 - 1, '|');
    mvaddch(y4 + 2, x4 + 1, '|');
    mvaddch(y4 + 3, x4 + 1, '|');
    mvaddch(y4 + 4, x4, '|');
    attroff(COLOR_PAIR(3));
    refresh();
}

void target(int bc1, int bh) {
    attron(COLOR_PAIR(2));
    mvprintw(bh - 1, bc1 - 1, "@");
    mvprintw(bh - 1, bc1 + 1, "@");
    mvprintw(bh, bc1 - 2, "@@@");
    mvprintw(bh, bc1 + 2, "@@@");
    mvprintw(bh + 1, bc1 - 1, "@");
    mvprintw(bh + 1, bc1 + 1, "@");
    attroff(COLOR_PAIR(2));
}

void target2(int bc2, int bh2) {
    attron(COLOR_PAIR(2));
    mvprintw(bh2 - 1, bc2 - 1, "@");
    mvprintw(bh2 - 1, bc2 + 1, "@");
    mvprintw(bh2, bc2 - 2, "@@@");
    mvprintw(bh2, bc2 + 2, "@@@");
    mvprintw(bh2 + 1, bc2 - 1, "@");
    mvprintw(bh2 + 1, bc2 + 1, "@");
    attroff(COLOR_PAIR(2));
}

void crst(int xx1, int xx2, int yy1, int yy2) {
    attron(COLOR_PAIR(2));
    mvaddch(yy1, xx1, '+');
    mvaddch(yy1, xx2, '+');
    mvaddch(yy2, xx1, '+');
    mvaddch(yy2, xx2, '+');
    attroff(COLOR_PAIR(2));
}

void stars() {
    int sx1 = 50, sx2 = 60, sy1 = 0, sy2 = 10;
    crst(sx1 + 10, sx2 + 10, sy1 + 10, sy2 + 10);
    crst(sx1 + 20, sx2 + 20, sy1 + 30, sy2 + 30);
    crst(sx1 + 30, sx2 + 30, sy1 + 40, sy2 + 40);
    crst(sx1 + 60, sx2 + 60, sy1 + 30, sy2 + 30);
    crst(sx1 + 250, sx2 + 250, sy1 + 30, sy2 + 30);
    crst(sx1 + 200, sx2 + 200, sy1 + 60, sy2 + 60);
    crst(sx1 + 230, sx2 + 230, sy1 + 200, sy2 + 200);
    crst(sx1 + 100, sx2 + 100, sy1 + 80, sy2 + 80);
    crst(sx1 + 20, sx2 + 20, sy1 + 330, sy2 + 330);
    crst(sx1 + 50, sx2 + 50, sy1 + 300, sy2 + 300);
    crst(sx1 + 20, sx2 + 20, sy1 + 200, sy2 + 200);
    crst(sx1 + 200, sx2 + 200, sy1 + 230, sy2 + 230);
    crst(sx1 + 150, sx2 + 150, sy1 + 180, sy2 + 180);
    crst(sx1 + 20, sx2 + 20, sy1 + 30, sy2 + 30);
    crst(sx1 + 100, sx2 + 100, sy1 + 120, sy2 + 120);
    crst(sx1 + 50, sx2 + 50, sy1 + 300, sy2 + 300);
    crst(sx1 + 70, sx2 + 70, sy1 + 340, sy2 + 340);
    crst(sx1 + 280, sx2 + 280, sy1 + 320, sy2 + 320);
    crst(sx1 + 250, sx2 + 250, sy1 + 380, sy2 + 380);
    crst(sx1 + 180, sx2 + 180, sy1 + 270, sy2 + 270);
    refresh();
}

int main() {
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    int midX = maxX / 2;
    int midY = maxY / 2;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\Turboc3\\BGI");
    detectgraph(&gd, &gm);
    bc1 = (rand() % (max - min + 1)) + min;
    bc2 = (rand() % (max1 - min1 + 1)) + min1;

    do {
        clear();
        start();
        starts = getch();
        if (starts == 'e')
            break;
        else if (starts == 's') {
            loading();
            while (1) {
                clear();
                stars();
                mvhline(0, 50, ACS_HLINE, maxX - 100);
                mvhline(maxY - 1, 50, ACS_HLINE, maxX - 100);
                mvvline(0, 50, ACS_VLINE, maxY - 1);
                mvvline(0, maxX - 50, ACS_VLINE, maxY - 1);

                attron(COLOR_PAIR(2));
                mvprintw(1, midX - 5, "LEVEL = %d", lev);
                mvprintw(2, midX - 5, "SCORE = %d", k);
                mvprintw(3, midX - 5, "SHOTS = %d", s);
                mvprintw(4, midX - 5, "TARGET = %d", level);
                attroff(COLOR_PAIR(2));

                rocket();
                y = y1;
                target(bc1, bh);
                target2(bc2, bh2);
                ch = getch();
                if (ch == 'e')
                    break;
                else if (ch == 'f') {
                    s--;
                    if (s >= 0) {
                        for (i = 0; i < 100; i = i + 10) {
                            clear();
                            target(bc1, bh);
                            target2(bc2, bh2);
                            rocket();
                            mvaddch(y, x1, '|');
                            y = y - 1;
                            refresh();
                            usleep(100000);
                        }
                        if (x1 > bc1 - 30 && x1 < bc1 + 30) {
                            clear();
                            if (x1 >= bc1 - 30 && x1 <= bc1 - 20 || x1 <= bc1 + 30 && x1 >= bc1 + 20) {
                                k = k + 5;
                                attron(COLOR_PAIR(3));
                                mvprintw(midY, midX - 5, "5 points");
                                attroff(COLOR_PAIR(3));
                            } else if (x1 >= bc1 - 20 && x1 <= bc1 - 10 || x1 <= bc1 + 20 && x1 >= bc1 + 10) {
                                k = k + 10;
                                attron(COLOR_PAIR(3));
                                mvprintw(midY, midX - 5, "10 points");
                                attroff(COLOR_PAIR(3));
                            } else if (x1 > bc1 - 10 && x1 < bc1 || x1 > bc1 && x1 < bc1 + 10 || x1 == bc1) {
                                k = k + 20;
                                attron(COLOR_PAIR(3));
                                mvprintw(midY, midX - 5, "15 points");
                                attroff(COLOR_PAIR(3));
                            }
                            usleep(300000);
                            goto label;
                        } else if (x1 > bc2 - 20 && x1 < bc2 + 20) {
                            clear();
                            if (x1 >= bc2 - 30 && x1 <= bc2 - 20 || x1 <= bc2 + 30 && x1 >= bc2 + 20) {
                                k = k + 5;
                                attron(COLOR_PAIR(3));
                                mvprintw(midY, midX - 5, "5 points");
                                attroff(COLOR_PAIR(3));
                            } else if (x1 >= bc2 - 20 && x1 <= bc2 - 10 || x1 <= bc2 + 20 && x1 >= bc2 + 10) {
                                k = k + 10;
                                attron(COLOR_PAIR(3));
                                mvprintw(midY, midX - 5, "10 points");
                                attroff(COLOR_PAIR(3));
                            } else if (x1 > bc2 - 10 && x1 < bc2 || x1 > bc2 && x1 < bc2 + 10 || x1 == bc2) {
                                k = k + 20;
                                attron(COLOR_PAIR(3));
                                mvprintw(midY, midX - 5, "15 points");
                                attroff(COLOR_PAIR(3));
                            }
                            usleep(100000);
                            goto key;
                        }
                    } else if (s < 0) {
                        attron(COLOR_PAIR(3));
                        mvprintw(midY, midX - 5, "no more shots remaining");
                        attroff(COLOR_PAIR(3));
                        if (k >= level) {
                            clear();
                            s = 5;
                            incre = incre + 3;
                            level = level + 10;
                            k = 0;
                            lev++;
                            attron(COLOR_PAIR(2));
                            mvprintw(midY, midX - 5, "LEVEL INCREASED");
                            attroff(COLOR_PAIR(2));
                            usleep(200000);
                        } else if (k < level) {
                            clear();
                            attron(COLOR_PAIR(2));
                            mvprintw(midY, midX - 5, "YOU LOST");
                            attroff(COLOR_PAIR(2));
                            usleep(200000);
                            break;
                        }
                    }
                } else if (ch == KEY_RIGHT) {
                    if (x4 >= maxX - 50) {
                        x1 = x1 + 0;
                        x2 = x2 + 0;
                        x3 = x3 + 0;
                        x4 = x4 + 0;
                    } else {
                        x1 = x1 + move;
                        x2 = x2 + move;
                        x3 = x3 + move;
                        x4 = x4 + move;
                    }
                } else if (ch == KEY_LEFT) {
                    if (x3 <= 50) {
                        x1 = x1 - 0;
                        x2 = x2 - 0;
                        x3 = x3 - 0;
                        x4 = x4 - 0;
                    } else {
                        x1 = x1 - move;
                        x2 = x2 - move;
                        x3 = x3 - move;
                        x4 = x4 - move;
                    }
                }
                usleep(10000);
            }
        } else if (starts == 'h' || starts == 'H')
            ghelp();
    } while (starts != 'e' || starts != 'E');

    getch();
    endwin();
    closegraph();
    return 0;
}

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

const int y = 65;
const int x = 104;
int board[y][x] = { 0 };
char *filename;

int spaceship[4][5] = { { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 1 } };

int glider[3][3] = { { 1, 1, 1 }, { 0, 0, 1 }, { 0, 1, 0 } };


void setup() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	clear();
	noecho();
	cbreak();
	curs_set(0);
	cbreak();
	noecho();
	start_color();
	
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
}

void progress() {
	int sboard[y][x] = { 0 };
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			int prevy = (i != 0)? i-1: 0;
            int posty = (i != y-1)? i+1: y-1;
            int prevx = (j != 0)? j-1: 0;
            int postx = (j != x-1)? j+1: x-1;
            int suround = 0;
            for (int k=prevy; k<posty+1; k++){
                for (int l=prevx; l<postx+1; l++){
                    suround += board[k][l];
                }
            }
			suround -= board[i][j];

			if (board[i][j] == 1 && !(suround == 2 || suround == 3)) sboard[i][j] = 0;   
			else if (board[i][j] == 0 && suround == 3) sboard[i][j] = 1;   
			else sboard[i][j] = board[i][j];
		}
	}
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			board[i][j] = sboard[i][j];
		}
	}
}

void printboard() {
	clear();
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			if (board[i][j] == 1) {
				attron(COLOR_PAIR(1));
				mvprintw(i,j*2, "  ");
				attroff(COLOR_PAIR(1));
			} else if (board[i][j] == 0) {
				attron(COLOR_PAIR(2));
				mvprintw(i,j*2, "  ");
				attroff(COLOR_PAIR(2));
			} else {
				attron(COLOR_PAIR(3));
				mvprintw(i,j*2, "+>");
				attroff(COLOR_PAIR(3));
			}
		}
	}
	refresh();
}

void makeThings() {
	char in = 'i';
	int cursposx = 0, cursposy = 0;
	printboard();
	while (in != 'q') {
		int nch = 0;
		if (board[cursposy][cursposx] == 2) board[cursposy][cursposx] = 0;
		switch ((int)in) {
			case 3:
				cursposy --;	
				if (cursposy < 0) cursposy = 0;
				break;
			case 2:
				cursposy ++;
				break;
			case 4:
				cursposx --; 
				if (cursposx < 0) cursposx = 0;
				break;
			case 5:
				cursposx ++;
				break;
			case 32:
				board[cursposy][cursposx] = board[cursposy][cursposx]? 0:1;
				nch = 1;
				break;
			case 103:
				for (int i=0; i<3; i++) {
					for (int j=0; j<3; j++) {
						board[cursposy+i][cursposx+j] = glider[i][j];
					}
				}
				nch = 1;
				break;
			case 115:
				for (int i=0; i<4; i++) {
					for (int j=0; j<5; j++) {
						board[cursposy+i][cursposx+j] = spaceship[i][j];
					}
				}
				nch = 1;
				break;
			default:
				nch = 1;
				break;
		}
		
		if (nch == 0 && board[cursposy][cursposx] == 0) board[cursposy][cursposx] = 2;
		printboard();

		in = getch();
			
	}		
	if (board[cursposy][cursposx] == 2) board[cursposy][cursposx] = 0;
	FILE *fp = fopen(filename, "w");
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			fprintf(fp, "%d ", board[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void input() {
	printw("Rand(R) | Input(I) | Load(L) | Edit(E)?");
	
	char in = getch();
	if (in == 'R' || in == 'r') {
		// srand(time(NULL));
		struct timespec ts;

        	timespec_get(&ts, TIME_UTC);

        	srand(&ts.tv_nsec);

		for (int i=0; i<y; i++)
			for (int j=0; j<x; j++)
				board[i][j] = (rand()%100 < 50)? 0:1;
	} else if (in == 'L' || in == 'l' || in == 'E' || in == 'e') {
		FILE *fp = fopen(filename, "r");
		for (int i=0; i<y; i++) {
			for (int j=0; j<x; j++) {
				fscanf(fp, "%d", &board[i][j]);
			}
		}
		fclose(fp);
		if (in == 'E' || in == 'e') {
			makeThings();
		}	
	} else {
		makeThings();
	}
}

void mainloop() {
	for (int i=0; i<300; i++) {
		printboard();
		progress();
		usleep(50000);
	}	
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		filename = (char *) malloc(9);
		strcpy(filename, "Save.gol");
	} else if (!strcmp(argv[1], "-h")) { 
		printf("Useage:\n");
		printf("\t./gol filename\n");
		printf("\tThe filename is used to read from and write to\n");
		return 0;
	} else {
		filename = (char *) malloc(strlen(argv[1]) + 1);
		strcpy(filename, argv[1]);
	}
	setup();
	input();
	char in = 'c';
	while (in == 'c') {
		mainloop();
		char *tmp;
		// scanf("%s", tmp);
		in = getch();
		if (in == ' ') {
			in = 'c';
			int oscelator = 0;
			for (int i=-10; i<11; i++) { 
				for (int j=-10; j<11; j++) {
					oscelator = oscelator? 0:1;
					board[(int)y/2 + i][(int)x/2 + j] = oscelator;
				}
			}
		}
	}
	endwin();

	return 0;
}










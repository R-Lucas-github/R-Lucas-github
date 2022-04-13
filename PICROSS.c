#include<stdio.h>

                  /*Tableau 1D avec une valeur*/
void initArray1D(int size,int iArray[size], int val)
{
	for(int i = 0; i < size; i++)
	{
		iArray[i] = val;
	}
}

                  /*Tableau 2D avec une valeur**/
void initArray(int nbLin, int nbCol, int iArray[nbLin][nbCol], int val) 
{
	int i,j;
	for ( i = 0; i < nbLin; i++)
	{
		for ( j = 0; j < nbCol; j++)
		{
			iArray[i][j] = val;
		}
	}
}

                  /*Affichage tableau 2D*/
void showArray(int nbLin, int nbCol, int iArray[nbLin][nbCol]) 
{
	int i,j;
	for(i = 0; i < nbLin; i++)
	{
		for(j = 0; j < nbCol; j++)
			printw("%3d ", iArray[i][j]);
		printw("\n");
	}
}

int L, C; /*L pour désigner la ligne et C la colonne du clic de la souris*/



/**Initialisation de ncurses**/
void ncurses_initialiser() {
  initscr();	        /* Démarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Désactive l'affichage des caractères saisis */
  keypad(stdscr, TRUE);	/* Active les touches spécifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}


/**Initialisation des couleurs**/
void ncurses_couleurs() {
  /* Vérification du support de la couleur */
  if(has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    exit(EXIT_FAILURE);
  }

  /* Activation des couleurs */
  	start_color();
  //init_color(COLOR_BLACK, 1000, 1000, 1000);
  	init_pair(1, COLOR_WHITE, COLOR_BLACK);
  	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_BLUE,  COLOR_BLACK);
	init_pair(6, COLOR_YELLOW,COLOR_BLACK);

}

/**Initialisation de la souris**/
void ncurses_souris() {
  if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
    endwin();
    fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
    exit(EXIT_FAILURE);
  }

  if(has_mouse() != TRUE) {
    endwin();
    fprintf(stderr, "Aucune souris n'est détectée.\n");
    exit(EXIT_FAILURE);
  }
}


/**Pour récupérer les coordonnées (x,y) du clic de la souris**/
int click_souris()
{
  MEVENT event ;
  int ch;

  while((ch = getch()) != KEY_F(1)) 
  {
    switch(ch) 
    {
      case KEY_F(2): /*Pour quitter la boucle*/
	return 1;
      case KEY_MOUSE:
        if(getmouse(&event) == OK) 
	{
	  C = event.x;
	  L = event.y;
	  if(event.bstate & BUTTON1_CLICKED)
	  { 
	    return 0;
	  }
	}
    }
  }
  return 0;
}



/*Pour récupérer les données saisies par l'utilisateur sans bloquer le jeu*/
char key_pressed() {
struct termios oldterm, newterm;
int oldfd;
char c, result = 0;
tcgetattr (STDIN_FILENO, &oldterm);
newterm = oldterm;
newterm.c_lflag &= ~(ICANON | ECHO);
tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
c = getchar();
tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
fcntl (STDIN_FILENO, F_SETFL, oldfd);
if (c != EOF) {
ungetc(c, stdin);
result = getchar();
}
return result;
}



void LANCEMENT_JEU()
{
  while (click_souris() == 0)
  {
    clear();
    printw("Vous avez cliqué sur la position (%d, %d)\n", L, C);
  }
}

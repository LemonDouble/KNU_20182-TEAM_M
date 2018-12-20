/*
 * =====================================================================================
 *
 *       Filename:  snake.c
 *
 *    Description:  main source of snake program
 *
 *        Version:  1.0
 *        Created:  12/09/18 23:08:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  조수현(Su hyeon cho)
 *   Organization:  KNU
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "snake.h"
#include "client.h"

snake *mysnake;
screen *myscreen;

#define SERVERADDRESS "54.180.71.148"
#define SERVERPORT "9872"

void move_snake(int);
int set_ticker(int);

char userName[21] = {0,};  //user's name (scoreboard name)
char scoreChar[21] = {0,};
int score = 0;
char scoreStructure[42] = {0,}; //structure to send server!!
int main(){

  printf("What is your name?(Max 20 char) : ");
  scanf("%s",userName);

  initscr(); // to use ncurses lib
  cbreak(), crmode(); noecho(); //buffering off, echo mode off
  keypad(stdscr, TRUE); // to use arrow keys
  curs_set(0); //hide cursor
  timeout(100);
  int delay = 20; // 100ms = 0.1 seconds

  mysnake = malloc(sizeof(snake));
  myscreen = malloc(sizeof(screen));

  int xmax;
  int ymax;
  getmaxyx(stdscr, ymax, xmax);

  init_snake(mysnake);
  init_screen(xmax, ymax,myscreen);


  signal(SIGALRM,move_snake);
  set_ticker(delay);

  while(1){
    clear();
    print_screen(mysnake->snakebody,'o');
    print_screen(myscreen->food,'*');
    refresh();
    mysnake->dir = get_key(mysnake->dir);
   

  }
  getch();
  endwin();
  
  return 0;
}

void move_snake(int signum){

  signal(SIGALRM, move_snake);
  point *nextMovingPoint = (point*)malloc(sizeof(point));

  switch(mysnake->dir){
    case UP://UP 
      nextMovingPoint->x = mysnake->tail->x;
      nextMovingPoint->y = mysnake->tail->y-1;
      break;
    case DOWN://DOWN
      nextMovingPoint->x = mysnake->tail->x;
      nextMovingPoint->y = mysnake->tail->y+1;
      break;
    case LEFT://LEFT
      nextMovingPoint->x = mysnake->tail->x-1;
      nextMovingPoint->y = mysnake->tail->y;
      break;
    case RIGHT://RIGHT
      nextMovingPoint->x = mysnake->tail->x+1;
      nextMovingPoint->y = mysnake->tail->y;
      break;
  }
  nextMovingPoint->next = NULL;

  mysnake->tail->next = nextMovingPoint;
  mysnake->tail = nextMovingPoint;

  point *deleteTmp = mysnake->head;


  //border check
  if(nextMovingPoint->x < 0 || nextMovingPoint->x > myscreen->xmax || nextMovingPoint->y < 0 || nextMovingPoint->y > myscreen->ymax){
    endwin();
    fprintf(stderr,"you lose! out of border!\n"); 
  for(int i = 0 ; i < strlen(userName); i++){
    if(userName[i] == 32){ //if space exist, make sending error
      userName[i] = 95; // so replace space to underbar '_'
    }
  }

  userName[strlen(userName)] = 32;
  userName[strlen(userName) + 1] = 0; //userName + space

  sprintf(scoreChar,"%d",score); //itoa is not standard function. so use sprintf

  strcat(scoreStructure,userName);
  strcat(scoreStructure,scoreChar);

  puts(scoreStructure);

  sendScoreToServer(scoreStructure, SERVERADDRESS, SERVERPORT);

  exit(1);
  }

  //food check
  if(nextMovingPoint->x == myscreen->food.list->x && nextMovingPoint->y == myscreen->food.list->y){
    get_new_food(myscreen, mysnake);
    score += 50;
  }else{
    mysnake->head = mysnake->head->next;
    free(deleteTmp);
  }
  return;
}

int set_ticker(int n_msecs){
        struct itimerval new_timeset;
        long    n_sec, n_usecs;

        n_sec = n_msecs / 1000 ;
        n_usecs = ( n_msecs % 1000 ) * 1000L ;

        new_timeset.it_interval.tv_sec  = n_sec;        /* set reload  */
        new_timeset.it_interval.tv_usec = n_usecs;      /* new ticker value */
        new_timeset.it_value.tv_sec     = n_sec  ;      /* store this   */
        new_timeset.it_value.tv_usec    = n_usecs ;     /* and this     */

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}


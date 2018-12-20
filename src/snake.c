/*
 * =====================================================================================
 *
 *       Filename:  snake.c
 *
 *    Description:  handle about snake and food. 
 *
 *        Version:  1.0
 *        Created:  12/10/18 01:24:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  조수현 (SU HYEON CHO)
 *   Organization:  KNU
 *
 * =====================================================================================
 */
#include <stdlib.h> //to use malloc(), rand()...
#include <time.h> // to use srand()
#include <ncurses.h> // to use ncurses lib..
#include <signal.h> // to use signal..

#include "snake.h"

//the function of initalize snake struct
int init_snake(snake *mysnake){
  point *tmp = (point*)malloc(sizeof(point));

  tmp-> x = 1;
  tmp-> y = 1;
  tmp-> next = NULL;

  mysnake->snakebody.list = tmp; //initalize snake by (1,1) point
  mysnake->dir = RIGHT; //initalize snake's head by right
  mysnake->head = tmp;
  mysnake->tail = tmp;
}

//the function of initalize screen struct
int init_screen(int _xmax, int _ymax, screen *myscreen){
  myscreen->xmax = _xmax;
  myscreen->ymax = _ymax; //initalize by user terminal's max size
  
  point *foodtmp = (point*)malloc(sizeof(point));
  
  myscreen->food.list = foodtmp; 

  myscreen->food.list->x = make_random(myscreen->xmax);
  myscreen->food.list->y = make_random(myscreen->ymax); //generate random food
  myscreen->food.list->next = NULL; //food is just one!
  
  return 0;
}

//make random value that 1 ~ (maxvalue - 1)
int make_random(int maxvalue){
  int returnval;
  srand(time(NULL));
  returnval = rand()%maxvalue + 1;

  if(returnval == maxvalue){
    returnval -= 1;
  }

  return returnval;
}


void print_screen(pointList mylist, char printChar){
  point *currentPoint = mylist.list;
  
  while(currentPoint->next != NULL){
    mvaddch(currentPoint->y,currentPoint->x,printChar);
    currentPoint = currentPoint->next;
  }

   mvaddch(currentPoint->y,currentPoint->x,printChar);
   return;
}

enum direction get_key(enum direction pre){
  int ch = getch();

  switch (ch) {
    case KEY_LEFT:
      if (pre != RIGHT) return LEFT;
    case KEY_RIGHT:
      if (pre != LEFT) return RIGHT;
    case KEY_DOWN:
      if (pre != UP) return DOWN;
    case KEY_UP:
      if (pre != DOWN) return UP;
    default:
      return pre;
  }
}

int get_new_food(screen *myscreen, snake *mysnake){
    
  myscreen->food.list->x = make_random(myscreen->xmax);
  myscreen->food.list->y = make_random(myscreen->ymax);

  return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  screen.c
 *
 *    Description:  handle function about screen
 *
 *        Version:  1.0
 *        Created:  12/10/18 01:29:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  조수현 (SU HYEON CHO)
 *   Organization:  KNU
 *
 * =====================================================================================
 */
#include <stdlib.h> //to use rand()
#include <time.h> // to use srand()

int init_screen(int _xmax, int _ymax, screen *myscreen){
  myscreen->xmax = _xmax;
  myscreen->ymax = _ymax; //initalize by user terminal's max size
  
  point foodtmp = (point*)malloc(sizeof(point));
  
  myscreen->list = foodtmp; 

  myscreen->list->food.x = make_random(myscreen->xmax);
  myscreen->list->food.y = make_random(myscreen->ymax); //generate random food
  myscreen->list->next = NULL; //food is just one!
  
  return 0;
}

int make_random(int maxvalue){
  int returnval;
  srand(time(NULL));
  rand()%maxvalue + 1;

  if(returnval == maxvalue){
    returnval -= 1;
  }

  return returnval;
}

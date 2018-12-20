/*
 * =====================================================================================
 *
 *       Filename:  snake.h
 *
 *    Description:  header file of snake 
 *
 *        Version:  1.0
 *        Created:  12/10/18 01:24:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  조수현 (SU HYEON CHO)
 *   Organization:  KNU
 *
 * =====================================================================================
 */

enum direction {UP, DOWN, LEFT, RIGHT};

typedef struct point{
  int x;
  int y;
  struct point *next;
}point;

typedef struct pointList{
  point *list;
}pointList;

typedef struct snake{
  pointList snakebody;
  point *head;
  point *tail;
  enum direction dir;
}snake;

typedef struct screen{
  int xmax;
  int ymax;
  pointList food;
}screen;

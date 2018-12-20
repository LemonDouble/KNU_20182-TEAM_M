/*
 * =====================================================================================
 *
 *       Filename:  client.h
 *
 *    Description:  header file of client.c
 *
 *        Version:  1.0
 *        Created:  12/20/18 22:52:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  조수현(SU HYEON CHO)
 *   Organization:  KNU
 *
 * =====================================================================================
 */
int sendMessage(int, char*,struct sockaddr_in*,int);
int sendScoreToServer(char*,char*,char*);


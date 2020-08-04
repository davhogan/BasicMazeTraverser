#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 int num_cols,num_rows,start_col,start_row,end_col,end_row,cur_col,cur_row;
 int i,j,check;
 char ornt;
 int  **maze;
 FILE *file;

 int checkArgs(int argc,char *argv[]); 
 int getVars(int *num1, int *num2, FILE *file);
 void display(int num_cols, int num_rows, int** maze);
 char initialOrnt(int start_col, int start_row,int num_rows);
 char traverse(int *cur_col, int *cur_row, int **maze, char ornt);
 

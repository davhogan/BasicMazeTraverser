/*Program by David Hogan
  Student ID: 989671828
  Email: davhogan@pdx.edu
  For an explanantion of the program please view the readme file.
*/
#include "hw1.h"


int main(int argc, char *argv[])
{
   /*Check arguments provided*/
   check=checkArgs(argc,argv);
   if(!check)
    return 1;

   /*Open file*/
   file = fopen(argv[1],"r");
   if(!file)
   {
      printf("Could not open file %s.\n",argv[1]);
      return 1;
   }
    /*Get the variables for all the row and column variables*/
    check=getVars(&num_cols,&num_rows,file);
    if(!check)
     return 1;
     check=getVars(&start_col,&start_row,file);
    if(!check)
     return 1;
     check=getVars(&end_col,&end_row,file);
    if(!check)
     return 1;

    cur_col=start_col;
    cur_row=start_row;

    /*Allocate memory for the maze*/ 
    maze=(int**)malloc(sizeof(int*)*num_rows);
    for(i=0; i<=num_cols;++i)
    {
      maze[i]=(int*)malloc(sizeof(int)*num_cols); 
    }   
    /*Read in the maze*/    
    for(i=0;i<num_rows;++i)
    {
      for(j=0;j<=num_cols;j++)
       {
        maze[i][j]=fgetc(file);
       }
    }
  
    printf("\nMaze before traversal:\n");
    display(num_cols,num_rows,maze);
    
    ornt=initialOrnt(start_col,start_row,num_rows);
    /*Traverse the maze, until the finished is reached. Relabel all visted tiles as W*/
    while(cur_col!=end_col||cur_row!=end_row)
    {
       if(maze[cur_row][cur_col]=='0')
         maze[cur_row][cur_col]='W';
     
       ornt=traverse(&cur_col,&cur_row,maze,ornt);
    }
    maze[cur_row][cur_col]='W';/*label the final visted tile*/

    printf("\nMaze after traversal\n");
    display(num_cols,num_rows,maze);
 
 /*Free up the dynamicaly allocated memory */  
  for(i=0;i<=num_cols;++i)
  {
    maze[i]=NULL;
    free(maze[i]);
  
  }
  maze=NULL;
  free(maze);
 
 printf("\n");
 return 0;
}

/*Checks the arguments passed into the program. The program should only provide a single text file to open when calling.
If the arguments provided aren't correct then a 0 is returned*/
int checkArgs(int argc, char *argv[])
{
   int len;
   char *ptr;

    if(argc!=2)
    {
     printf("Enter one and only one filename when calling this program.\nExample: hw1.c filename.txt\n");
     return 0;
    }
   
   len=strlen(argv[1]);
   ptr=argv[1]+(len-4);
   
   if(strcmp(ptr,".txt\0"))
   {
     printf("File must be a text file.\n");
     return 0;
   }
  
  return 1;
}

/*This function assigns the two vaiables on a single line in the text file.
Takes in two variables by reference as well as the file pointer to the opened text file.
The function gets the line of the file then parses out the 2 variables on the line. 
The function returns a zero if the file pointer is NULL*/
int getVars(int *num1, int *num2, FILE *file)
{
   char temp[20];
   char *endptr;
   if(!file)
   {
    printf("Problem opening file. Make sure file contents are properly formatted\n");
    return 0;
   }
   fgets(temp,20,file);
   *num1=strtol(temp,&endptr,10);
   ++endptr;
   *num2=strtol(endptr,NULL,10);
    return 1; 
}

/*This function is used to display the maze.
The function takes in the number of rows and columns as well as the 2D array representing the maze.
The function then goes through the 2D array and displays every value as a char.*/
void display(int num_cols, int num_rows, int** maze)
{
     for(i=0;i<num_rows;++i)
     {
       for(j=0;j<num_cols;++j)
       {
         printf("%c", maze[i][j]);
       }
       printf("\n");    
     }
  return;
}

/*This function is used to get the initial orientaion for the traversal of the maze.
The function takes in the starting column and row and returns a char to represent the correct starting oreintation.*/
char initialOrnt(int start_col, int start_row,int num_rows)
{
  if(start_row==0)
   return 'S';
  else if(start_row==num_rows-1)
   return 'N';
  else if(start_col==0)
   return 'E';
  else
   return 'W';
}
/*This function traverses one block in the maze. It takes in the current row and column by reference.
The function also takes in the 2D array representing the maze and the current orientation. It returns the 
orientation after a traversal has occured.
The function checkes the orientation then first checks if the tile to the right is free,if it is then the current location
is changed to the free tile.It then changes the orientation to the proper direction. If the right is filled then it checks staright ahead and
moves forward if free. If both prevous checks have failed then it checks to the left and changes the current location to the free tile if the avalible 
and change the orinetation to the proper direction. If all other checks have failed then the orientaion is flipped 180 degrees.*/
char traverse(int *cur_col, int *cur_row, int **maze, char ornt)
{
   /*Orientaion is north*/
   if(ornt=='N')
   {
     if(maze[*cur_row][*cur_col+1]!='X')
     {
       ++(*cur_col);
       return 'E';
     }
     else if(maze[*cur_row-1][*cur_col]!='X')
     {
       --(*cur_row);
       return 'N';
     }
     else if(maze[*cur_row][*cur_col-1]!='X')
     {
       --(*cur_col);
       return 'W';
     }
     else
      return 'S';
   }
   /*Orienation is south*/
   else if(ornt=='S')
   {
     if(maze[*cur_row][*cur_col-1]!='X')
     {
       --(*cur_col);
       return 'W';
     }
     else if(maze[*cur_row+1][*cur_col]!='X')
     {
       ++(*cur_row);
       return 'S';
     }
     else if(maze[*cur_row][*cur_col+1]!='X')
     {
       ++(*cur_col);
       return 'E';
     }
     else
      return 'N';
     }
    /*Orientaion is east*/
    else if(ornt=='E')
    {
      if(maze[*cur_row+1][*cur_col]!='X')
      {
        ++(*cur_row);
        return 'S';
      }
      else if(maze[*cur_row][*cur_col+1]!='X')
      {
        ++(*cur_col);
        return 'E';
      }
      else if(maze[*cur_row-1][*cur_col]!='X')
      {
        --(*cur_row);
        return 'N';
      }
      else
        return 'W';
    }
    /*Oreintation is west*/
    else if(ornt=='W')
    {
      if(maze[*cur_row-1][*cur_col]!='X')
      {
        --(*cur_row);
         return 'N';
      }
      else if(maze[*cur_row][*cur_col-1]!='X')
      {
        --(*cur_col);
        return 'W';
      }
      else if(maze[*cur_row+1][*cur_col]!='X')
      {
        ++(*cur_row);
        return 'S';
      }
      else
       return 'E';
    }

return '\0';
}

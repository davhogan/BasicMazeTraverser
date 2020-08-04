This program is used to solve a maze. This program implements the Wall Follower algorithm. This algorithm assumes that all the walls of the maze are connected together or to the maze’s outer boundary, therefore, following the right wall at some point will lead you to the exit. The program opens a file contaning the information for the maze. The first line of the maze file will contain the number of rows and columns of the maze as a comma separated value. The first value will be number of columns (X-axis) and the second value will be the number of rows (Y-value). The second line in the file will contain the X, Y coordinate within the array that specifies the entry to the maze. Your maze traversal algorithm should use this coordinate as starting point.The third line in the file will contain the X, Y coordinate within the array that specifies the exit to the maze.The rest of the file contains the maze array specified as an array of characters. The ‘X’ character indicates a wall and the ‘0’ indicates a walkable tile within the maze. At the end of each row the file will contain a line feed character (“\n”). Note: There should be no line breaks in the file.

Example of maze file:
5,3
1,0
4,2
X0XXX
X000X
XXX0X

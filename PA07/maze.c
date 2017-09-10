#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

//#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {

  FILE * fp = fopen(mazeFilename, "r");

  if(fp == NULL)
  {
	fprintf(stderr, "file didn't open\n");
	return NULL;
  }
  Maze * m;
  m = malloc(sizeof(Maze));
  if(m == NULL)
  {
    fprintf(stderr, "first malloc\n");
	fclose(fp);
	return NULL;
  }
  int err = 0;
  err = fscanf(fp, "%d ", &m -> height);
  if(err != 1)
  {
	fprintf(stderr, "scan height\n");
	fclose(fp);
	return NULL;
  }
  err = fscanf(fp, "%d\n", &m -> width);
  if(err != 1)
  {
    fprintf(stderr, "scan width\n");
	fclose(fp);
	return NULL;
  }
  m -> maze = malloc((m -> height) * sizeof(MazeSquare*));
  if(m -> maze == NULL)
  {
  	fprintf(stderr, "second malloc\n");
	fclose(fp);
	return NULL;
  }
  int i;
  for(i = 0; i < (m -> height); i++)
  {
    m -> maze[i] = malloc((m -> width) * sizeof(MazeSquare));
  }
  
  //MazeSquare pointer;
  char temp;
  for(i = 0; i < (m -> height); i++)
  {
    for(int j = 0; j < (m -> width); j++)
	{
	  err = 0;
	  err = fscanf(fp, "%c", &temp);
	  m -> maze[i][j].type = temp;
	  m -> maze[i][j].visited = false;
	  if(err != 1)
	  {
	  	fprintf(stderr, "temp\n");
		fclose(fp);
		return NULL;
	  }
	  if(temp == '\n')
	  {
	  	err = 0;
		err = fscanf(fp, "%c", &temp);
		if(err != 1)
		{
		  fprintf(stderr, "temp2\n");
		  fclose(fp);
		  return NULL;
		}
	  }
	  if(temp == START)
	  {
		m -> start.xpos = j;
		m -> start.ypos = i;
	  }
	  else if(temp == END)
	  {
		m -> end.xpos = j;
		m -> end.ypos = i;
	  }
	}
		
  }
  fclose(fp);
  return m; 	
}
//#endif //#ifndef READMAZE_OFF

//#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
  for(int i = 0; i < (m -> height); i++)
  {
    free(m -> maze[i]);
  }
  free(m -> maze);
	//2. Free the "spine" of the array
}
//#endif //#ifndef FREEMAZE_OFF

#include <stdio.h>
#include <stdlib.h>
#include "path.h"

//#ifndef READPATH_OFF
char * readPath(char * pathFilename) {
	
  FILE * fp = fopen(pathFilename, "r");

  if(fp == NULL)
  {
	fprintf(stderr, "file didn't open\n");
	return NULL;
  }
  int count = 0;
  while(!feof(fp))
  {
  	fgetc(fp);
	count++;
  }
  if(fseek(fp, 0, SEEK_SET) != 0)
  {
  	fprintf(stderr, "fseek failed\n");
	return NULL;
  }
  
  char * path = malloc(sizeof(char) * count);
  if(path == NULL)
  {
    fprintf(stderr, "malloc\n");
	fclose(fp);
	return NULL;
  }
  int i = 0;
  int err = 0;
  
  for(i = 0; i < count; i++)
  {
    err = fscanf(fp, "%c", &path[i]);
	if(path[i] == '\n')
	{
		break;
	}
  }
  path[i] = '\0';
  fclose(fp);
  return path;
}
//#endif //#ifndef READPATH_OFF

//#ifndef CHECKPATH_OFF
bool checkPath(Maze * m, char * path) {

  int pointer_x = m -> start.xpos;
  int pointer_y = m -> start.ypos; 
  m -> maze[pointer_y][pointer_x].visited = true;
  for(int i = 0; path[i] != '\0'; i++)
  {
  	m -> maze[pointer_y][pointer_x].visited = true;
  	if (path[i] == NORTH)
	{
		pointer_y--;
	}
	else if(path[i] == SOUTH)
	{
		pointer_y++;
	}
	else if(path[i] == EAST)
	{
		pointer_x++;
	}
	else if(path[i] == WEST)
	{
		pointer_x--;
	}
	if(pointer_x < 0 || pointer_y < 0)
	{
		return false;
	}
	
	if(pointer_x >= m -> width || pointer_y >= m -> height)
	{
		return false;
	}

	if(m -> maze[pointer_y][pointer_x].type == WALL)
	{
		return false;
	}
	if((pointer_x == m -> end.xpos) && (pointer_y == m -> end.ypos))
	{
		return true;
	}
	if(m -> maze[pointer_y][pointer_x].visited == true)
	{
		return false;
	}
	
  }
  if((pointer_x != m -> end.xpos) || (pointer_y != m -> end.ypos))
  {
  	return false;
  }
  return true;
}
//#endif //#ifndef CHECKPATH_OFF

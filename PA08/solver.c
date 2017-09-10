#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"

char * solveMaze(Maze * m) {
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {

	int pointer_x = curpos.xpos;
	int pointer_y = curpos.ypos;
	if(pointer_x < 0 || pointer_y < 0)
	{
		return false;
	}
	if(pointer_x >= m -> width || pointer_y >= m -> height)
	{
		return false;
	}
  	if(m -> maze[pointer_y][pointer_x].visited == true)
	{
    	return false;
	}
	if(m -> maze[pointer_y][pointer_x].type == WALL)
	{
		return false;
	}
	if((pointer_x == m -> end.xpos) && (pointer_y == m -> end.ypos))
	{
		path[step] = '\0';
		return true;
	}
	m -> maze[pointer_y][pointer_x].visited = true;
	
	MazePos north = {.xpos = curpos.xpos, .ypos = curpos.ypos - 1}; //to go north
	if(depthFirstSolve(m, north, path, step + 1))
	{	
		path[step] = 'n';
		return true;
	}
	MazePos south = {.xpos = curpos.xpos, .ypos = curpos.ypos + 1}; //to go south
	if(depthFirstSolve(m, south, path, step + 1))
	{
		path[step] = 's';
		return true;
	}
	MazePos west = { .xpos = curpos.xpos - 1, .ypos = curpos.ypos}; //to go west
	if(depthFirstSolve(m, west, path, step + 1))
	{
		path[step] = 'w';
		return true;
	}
	MazePos east = { .xpos = curpos.xpos + 1, .ypos = curpos.ypos}; //to go east
	if(depthFirstSolve(m, east, path, step + 1))
	{
		path[step] = 'e';
		return true;
	}
	return false;
}

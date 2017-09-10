// Do not remove #ifdef ... #endif before and after each function.
// 
// They are used to test different functions in your program and give
// partial credits, in case your program does not work completely.

#include "student.h"
#include "msort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StudentPrint(Student * stu, int num)
{
  printf("There are %d students\n", num);
  for (int ind = 0; ind < num; ind ++)
    {
      printf("ID = %d, First Name = %s, Last Name = %s\n",
	     stu[ind].ID,  stu[ind].firstname, stu[ind].lastname);
    }
}

//#ifdef TEST_READ
// return false if anything is wrong 
// return true if reading the file successfully and the data is save in
// the allocated memory
// input: filename, the name of the input file
// output: address of the allocated memory
// output: number of students
bool StudentRead(char * filename, Student * * stu, int * numelem)
{
  // open the file to read
  FILE * fp = fopen(filename, "r");
  // if fopen fails, return false
  // do not use fclose since fopen already fails
  if(fp == NULL)
  {
  	fprintf(stderr, "file didn't open\n");
  	return false;
  }
  // count the number of lines to determine the number of students
  char ch;
  while(!feof(fp))
  {
  	ch = fgetc(fp);
	if(ch == '\n')
	{
		(*numelem)++;
	}
  }
  // return to the beginning of the file
  // you can use fseek or
  // fclose followed by fopen
  // You need to check whether fseek or fopen fails
  // Do not use rewind because it does not report whether it fails
  if(fseek(fp, 0, SEEK_SET) != 0)
  {
  	fprintf(stderr, "fseek failed\n");
  	return false;
  }
  // allocate memory for the data
  *stu = malloc(sizeof(**stu) * *numelem);

  // check whether memory allocation fails
  if(*stu == NULL)
  {
  	fprintf(stderr, "malloc\n");
  	return false;
  }
  int err = 0;
  // read the data from the file and store the data in the allocated memory
  for(int i = 0; i < *numelem; i++)
  {
  	err = fscanf(fp, "%d ", & (*stu)[i].ID);
	if(err != 1)
	{
		fprintf(stderr, "scan ID\n");
		fclose(fp);
		return false;
	}
	err = 0;
	err = fscanf(fp, "%s ", (*stu)[i].firstname);
	if(err != 1)
	{
		fprintf(stderr, "scan firstname\n");
		fclose(fp);
		return false;
	}
	err = 0;
	err = fscanf(fp, "%s\n", (*stu)[i].lastname);
    if(err != 1)
	{
		fprintf(stderr, "scan lastname\n");
		fclose(fp);
		return false;
	}
  }
  // close the file
  fclose(fp);

  return true;
}
//#endif

//#ifdef TEST_WRITE
// return false if anything is wrong 
// return true if writing the file successfully
// input: filename, the name of the output file
// input: address of the student array
// input: number of students

bool StudentWrite(char * filename, Student * stu, int numelem)
{
  // open the file to write
  FILE * outf = fopen(filename, "w");

  // if fopen fails, return false
  // do not use fclose since fopen already fails
  if(outf == NULL)
  {
  	return false;
  }
  int err = 0;
  // write the students to the output file
  int i = 0;
  for(i = 0; i < numelem; i++)
  {
  	err = fprintf(outf, "%d ", stu[i].ID);
	if(err < 1)
	{
	  fclose(outf);
	  return false;
	}
    err = 0;
	err = fprintf(outf, "%s ", stu[i].firstname);
	if(err < 1)
	{
	  fclose(outf);
	  return false;
	}
	err = 0;
	err = fprintf(outf, "%s\n", stu[i].lastname);
	if(err < 1)
	{
	  fclose(outf);
	  return false;
	}
  }
  fclose(outf);
  return true;
}
//#endif 

//#ifdef TEST_SORTID
void StudentSortbyID(Student * stu, int numelem)
{
  msort(stu, numelem, comparefunc); 
}
//#endif

//#ifdef TEST_SORTFIRSTNAME
void StudentSortbyFirstName(Student * stu, int numelem)
{
  msort(stu, numelem, cmpstringp);
}
//#endif

//#ifdef TEST_SORTLASTNAME

void StudentSortbyLastName(Student * stu, int numelem)
{
  msort(stu, numelem, cmpstringp1);
}
//#endif

int comparefunc(const void * arg1, const void * arg2)
{
  const Student * ptr1 = (const Student *) arg1;
  const Student * ptr2 = (const Student *) arg2;
  int val1 =  ptr1 -> ID;
  int val2 =  ptr2 -> ID;
  if(val1 < val2)
  {
	return -1;
  }
  if(val1 == val2)
  {
  	return 0;
  }

  return 1;
}

int cmpstringp(const void *arg1, const void *arg2)
{
  const Student * ptr1 = (const Student *) arg1;
  const Student * ptr2 = (const Student *) arg2;
  const char * str1 =  ptr1 -> firstname;
  const char * str2 =  ptr2 -> firstname;

  return strcmp(str1, str2);
}

int cmpstringp1(const void *arg1, const void *arg2)
{
	const Student * ptr1 = (const Student *) arg1;
	const Student * ptr2 = (const Student *) arg2;
	const char * str1 = ptr1 -> lastname;
	const char * str2 = ptr2 -> lastname;

	return strcmp(str1, str2);
}

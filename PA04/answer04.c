#include <stdio.h>
#include <stdbool.h>
#include "pa04.h"

// must enclose the function by #ifdef TEST_INTEGRATE 
// and #endif to enable partial credits
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  // integrate the function stored in intrg's func
  // store the result in intrg's answer
  int i;
  double answer = 0;

  for(i = 0; i < intrg -> intervals; i++)
  {
    answer += intrg -> func((intrg -> lowerlimit) + (i * ((intrg -> upperlimit - intrg -> lowerlimit) / intrg -> intervals)));
  }
  answer *= ((intrg -> upperlimit - intrg -> lowerlimit) / (intrg -> intervals));
  intrg -> answer = answer;
}
#endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE
// and #endif to enable partial credits

#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
  // open the input file name for reading
  FILE * fp = fopen(infilename, "r");
  // if fopen fails, return false
  if(fp == NULL)
  {
	return false;
  }
  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  Integration intrg;
  int err = 0;
  err = fscanf(fp, "%lf\n", & intrg.lowerlimit);
  if(err != 1)
  {
	fclose(fp);
	return false;
  }
  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  err = 0;
  err = fscanf(fp, "%lf\n", & intrg.upperlimit);
  if(err != 1)
  {
	fclose(fp);
	return false;
  }
  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
  err = 0;
  err = fscanf(fp, "%d\n", & intrg.intervals);
  if(err != 1)
  {
	fclose(fp);
	return false;
  }
  // close the input file
  fclose(fp);
  // open the output file for writing
  // if fopen fails, return false
  FILE * outf = fopen(outfilename, "w");
  if(outf == NULL)
  {
	return false;
  }
  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5
  funcptr func[5];
  func[0] = func1;
  func[1] = func2;
  func[2] = func3;
  func[3] = func4;
  func[4] = func5;
  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf
  int works = 0;
  for(int i = 0; i < 5; i++)
  {
  	intrg.func = func[i];
  	integrate(&intrg);
	works = fprintf(outf, "%lf\n", intrg.answer);
	if(works < 1)
	{
	  fclose(outf);
	  return false;
    }
  }
  // check the return value of fprintf. 
  // If it is less one one, close the output
  // file and return false
  // after going through all functions in funcs
  // close the output file
  fclose(outf);
  // if the function reaches here, return true
  return true;
}
#endif // RUN_INTEGRATE

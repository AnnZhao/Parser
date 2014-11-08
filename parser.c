/** CS 2506 fall 2014
 *  Assignment 3: String Parsing and Translation 
 *  Student:      Zhenshu Zhao
 *  PID:          zzhens7
 */
#include <stdio.h>      
#include <stdlib.h>     
#include <stdbool.h>    
#include <stdint.h>     
#include <inttypes.h>
#include <string.h>
#include <limits.h>
#define MAXLEN 400
#define MAX_NUM_TYPES    17

struct _RegMapping {    // register name to number
   char* regName;       // symbolic name as C-string
   char* regNumber;     // string for binary representation
};
//typedef struct _RegMapping RegMapping; 


static const struct _RegMapping RegMapping[MAX_NUM_TYPES] = {
     /*regName   regNumber*/
   	{ "add", "100000"},
	{"and", "100100"},
	{ "addi", "001000"},
	{ "andi", "001100"},
	{ "lui", "001111"},
	{ "ori", "001101"},
	{"or", "100101"},
	{"sub", "100010"},
	{"$at",   "00001"},
        {"$t0",   "01000"},
        {"$t1",   "01001"},
        {"$t2",   "01010"},
        {"$t3",   "01011"},
        {"$s0",   "10000"},
        {"$s1",   "10001"},
        {"$s2",   "10010"},
        {"$s3",   "10011"},
};

//search in the table
char *get(const char * str)
{
	for(int i = 0;i<17;i++){
		if(strcmp(str,RegMapping[i].regName)==0){
			return RegMapping[i].regNumber;
		}
	}
	return NULL;
}



//Main function
int main(int argc, char **argv){
	FILE *TextIn = fopen("MIPSInstructions.txt","r");//open the input file
	FILE *TextOut = fopen("MIPSParse.txt","w");//open the result file


//convert decimal to binary
int int_to_int(int n) {
	int c, k;
    for (c = 15; c >= 0; c--)
  {
    k = n >> c;
 
    if (k & 1)
      fprintf(TextOut, "1");
    else
      fprintf(TextOut, "0");
  }
}

	//get the tokens in one line
	char *tok;
	char Line[MAXLEN + 1];
	char *line;
while (fgets(Line, MAXLEN, TextIn ) != NULL){
	line = strtok(Line, "\n");
	tok = strtok(line, " ,");
	int i = 0;
	char *a[4];
	while(tok!= NULL){
		a[i] = malloc(strlen(tok) + 1);
		strcpy(a[i], tok);
		//fprintf(TextOut, "%s", a[i]);
		i++;
		tok = strtok(NULL, " ,");
	}
	
	//there are 3 token in the line.
	
	if(i == 3)
	{
		if(get(a[0]) == NULL || get(a[1]) == NULL)
		{
			if(get(a[0]) == NULL){
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s\n", a[0] );
			}
			else{
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s\n", a[1] );
			}
		}
		else{
			//instruction
			fprintf(TextOut,"I-Format:  ");
			fprintf(TextOut,"%s  ",get(a[0]));
			//register
			fprintf(TextOut,"%s  ",get(a[1]));
			//immediate
			int x = atoi(a[2]);
			int_to_int(x);
			fprintf(TextOut,"\n");
		}
	}
	//there are 4 token in the line.
	else
	{
		//is R type which means all toks are register.
		if(strcmp(a[0],"add")==0 || strcmp(a[0],"and")==0 ||strcmp(a[0],"or")==0 ||strcmp(a[0],"sub") ==0)
		{
			//not error			
			if(get(a[1]) == NULL){
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s\n", a[1] );
				}
			else if(get(a[2]) == NULL){
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s\n", a[2] );
				}
			else if (get(a[3]) == NULL){
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s", a[3] );
				}
			//error
			else{
			//instruction
			fprintf(TextOut,"R-Format:  ");
			fprintf(TextOut,"%s  ",get(a[0]));
			//register
			fprintf(TextOut,"%s  ",get(a[1]));
			//register
			fprintf(TextOut,"%s  ",get(a[2]));
			//register
			fprintf(TextOut,"%s \n",get(a[3]));
			}
		}
		//is I tpye which means tok[3] is immediate
		else if(strcmp(a[0],"addi")==0 || strcmp(a[0],"andi")==0 ||strcmp(a[0],"ori")==0 ||strcmp(a[0],"lui") ==0)
		{
			//error
			if(get(a[1]) == NULL || get(a[2]) == NULL)
			{
				if(get(a[1]) == NULL){
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s\n", a[1] );
				}
				else{
				fprintf(TextOut,"Error: ");
				fprintf(TextOut,"%s\n", a[2] );
				}
			}
			//not error then translate
			else
			{
			//instruction
			fprintf(TextOut,"I-Format:  ");
			fprintf(TextOut,"%s  ",get(a[0]));
			//register
			fprintf(TextOut,"%s  ",get(a[1]));
			//register
			fprintf(TextOut,"%s  ",get(a[2]));
			//immediate
			//int a = a[3] - '0';
			int x = atoi(a[3]);
			int_to_int(x);
			fprintf(TextOut,"\n");
			}
		}
		//instruction error
		else
		{
		fprintf(TextOut,"Error: ");
		fprintf(TextOut,"%s\n", a[0] );	
		}
	}
	//Empty the tok array a.
	memset(a, 0, 255);
	
}
}
// On my honor: 
// 
// - I have not discussed the C language code in my program with 
// anyone other than my instructor or the teaching assistants 
// assigned to this course. 
// 
// - I have not used C language code obtained from another student, 
// or any other unauthorized source, either modified or unmodified. 
// 
// - If any C language code or documentation used in my program 
// was obtained from another source, such as a text book or course 
// notes, that has been clearly noted with a proper citation in 
// the comments of my program. 
// 
// Zhenshu Zhao




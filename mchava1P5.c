/* Made by Miguel Chavarria  UIN 652215109 mchava1@uic.edu */

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct stack{
	char * stack;
	int  top;
	int size;
}stack;


int StackEmpty(stack *theStack){
	if(theStack->top==0)
		return 1;
	else
		return 0;
}	

void Push(stack *theStack, char item,int dflag){
	theStack->stack[theStack->top] = item;
	theStack->top++;
	if(dflag == 1)
		printf("The following character has been pushed onto the stack:\t=%c\n",item);
}	

char Pop(stack *theStack,int *empty,int dflag){
	if(StackEmpty(theStack) == 1){
		*empty = 1;
		if(dflag == 1)
			printf("The stack is empty.\n");
		return ' ';
	}	
	else{
		*empty = 0;
		theStack->top--;
		if(dflag == 1)
                        printf("The following character has been popped from the stack:\t=%c\n",theStack->stack[theStack->top]);
		return theStack->stack[theStack->top];
	}
}	

int main(int argc,char **argv){
	int dflag = 0;
	int c;

	if(argc == 2  && argv[1][1] == 'd')
		dflag =1;	
	
	printf("This is project 4 for CS211.  Enter a phrase with parenthesis, square brackets, curly brackets or greater than and less than signs.\n");
	printf("This program will tell you if any of these characters are missing their opening or closing pair.\n");
	printf("When you want to finish the program enter the character q.\n");
	printf("Please enter your first phrase below:\n");
	

	size_t size = 10;
	while(1){	
		char * phrase;
		phrase = (char*) malloc(size*sizeof(char));
		size_t length = 10;
		int read;
		read = getline(&phrase,&length,stdin);
		if(read == 2 && phrase[0]=='q')
			break;
		int size = 3;
		int increment = 3;
		stack theStruct;
		theStruct.stack = (char*) malloc(size * sizeof(char));
		theStruct.size = 0;
		theStruct.top = 0;
		char characterMissing;
		int scenario;
		
		char * temp;
		temp = phrase;
		int positionOfMistake = 0;
		int j;
		for(j=0;j<read;j++)
		//while(*temp != '\0')
		{
			//printf("%c\n",*temp);
			int boolean;
			if(*temp=='(' || *temp=='[' || *temp=='{' || *temp=='<'){
				theStruct.size++;
				if(theStruct.size > size){
					boolean = 1;
					char *tempStack;
					tempStack = (char*) malloc(size=size+increment * sizeof(char));
					int i;
				//	char * temp2;
				//	temp2 = theStruct.stack;		
					for(i=0;i<theStruct.size;i++){
						*(tempStack+i) = *(theStruct.stack+i);
					}
					free(theStruct.stack);
					theStruct.stack = tempStack;
				}
				char itemPushed = *temp;
				Push(&theStruct,itemPushed,dflag);
				if(dflag == 1 && boolean == 1)
                                {
                                       printf("The size of the stack has increased from %d to %d, %d characters were copied from the old array to the new\n",(size-increment),size,theStruct.size);
					boolean = 0;
                                }
			}	
			if(*temp==')' || *temp == ']' || *temp == '}' || *temp == '>' || j+2==read){
				int empty;
				char itemPopped = Pop(&theStruct,&empty,dflag);
				if(empty == 0)
					theStruct.size--;
				//printf("this is itemPopped: %c\n",itemPopped);
				//CASE 3 stack is empty when a closing symbol is encountered
				if(empty == 1){
					switch(*temp){
						case ')':
						characterMissing = '(';
						break;
						case ']':
						characterMissing = '[';
						break;
						case '}':
						characterMissing = '{';
						break;
						case '>':
						characterMissing = '<';
						break;
						default:
						break;
					}
					scenario = 3;
					break;
				}
				//CASE 2 the wrong opening symbol is on top of the stack
				char compare;
				if(itemPopped == '(')
					compare = ')';
				else if(itemPopped == '<')
					compare = '>';
				else if(itemPopped == '[')
					compare = ']';
				else if(itemPopped == '{')
					compare = '}';
				//printf("%c\n",compare);
				if(compare != *temp)
				{
					switch(itemPopped){
						case '(':
						characterMissing = ')';
						break;
						case '[':
						characterMissing = ']';
						break;
						case '{':
						characterMissing = '}';
						break;
						case '<':
						characterMissing = '>';
						break;
						default:
						break;
					}
					scenario = 2;
					break;
				}	
				//CASE 4 line ends while the stack is not empty
				//printf("j=%d\tTOp=%d\n",j,theStruct.top);
				if(j+2==read && theStruct.top>0)
				{
					itemPopped = Pop(&theStruct,&empty,dflag);
					theStruct.size--;
					switch(itemPopped){
						case '(':
						characterMissing = ')';
						break;
						case '[':
						characterMissing = ']';
						break;
						case '{':
						characterMissing = '}';
						break;
						case '<':
						characterMissing = '>';
						break;
						default:
						break;
					}
					scenario = 4;
					break;
				}		
			}
			positionOfMistake++;
			temp++;
		}
		char* temp2 = phrase;
		while(*temp2 != '\0')
		{
			printf("%c",*temp2);
			temp2++;
		}
		printf("\n");		
		if(scenario == 3 || scenario == 4)
		{
			int i;
			for(i=0;i<positionOfMistake;i++)
				printf(" ");
			printf("^ missing %c\n",characterMissing);
		}
		else if(scenario == 2)
		{
			int i;
			for(i=0;i<positionOfMistake;i++)
				printf(" ");
			printf("^ expecting %c\n",characterMissing);
		}
		else
		{
			printf("Expression is balanced.\n");
		}			
		scenario = 0;
		free(phrase);
		free(theStruct.stack);	
	}
	printf("Thank you for using this program. Goodbye.\n");
	return 0;		
	
}
	

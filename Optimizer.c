 /*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2017                              *
 *  Author: Ulrich Kremer                    *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	head->critical = 'a';
	/* YOUR CODE GOES HERE */
	Instruction *end, *instr;
	end = LastInstruction(head);
	
	while(head)
	{
		if(end->opcode == OUTPUTAI)
		{
			break;
		}
		end = end->prev;
	}
	//Now end pointer is pointing to OUTPUTAI
	end->critical = 'a'; //made OUTPUTAI crictical
	end = end->prev; // Moved to above register
	while(end != head)
	{
		switch(end->opcode)
		{
			case STOREAI:
				if(end->next->field1 == end->field2 && end->next->field2 == end->field3)
				{
					end->critical = 'a';
				}
				break;
			
			case ADD:
			case SUB:
			case DIV:
			case MUL:
				if(end->next->field1 == end->field3 || end->field2 == end->prev->field3 || end->field2 == end->prev->field2 || end->field1 == end->prev->field3)
				{
					end->critical = 'a';
				}
				break;
			case LOADAI:
				if((end->field1 == end->prev->field2 && end->field2 == end->prev->field3) || end->field3==end->next->field1)
				{
					end->critical = 'a';
				}
				break;
		
			default:
				ERROR("Illegal instructions\n");
		}
		end = end->prev;
			
	}
	
	end = head;
	while(end) {
		instr = end->next;
		if (end->critical == 'a')
			PrintInstruction(stdout, end);
		free(end);
		end = instr;
	}
	
	//if (head) 
	//	PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}


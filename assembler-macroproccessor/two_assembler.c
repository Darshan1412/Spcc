#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *ptr1,*ptr2,*ptr3,*ptr4,*ptr5;
	char opcode[20],label[20],operand[20],mnemonic[3],code[20],mcode[3],index1[2],adr[3],symbol[2],dubmcode[3];
	int lc,start;
	int index=0;
	ptr1=fopen("input.txt","r");
	ptr2=fopen("opcode.txt","r");
	ptr3=fopen("output.txt","w");
	ptr4=fopen("symtab.txt","w+");
	ptr5=fopen("machine.txt","w");
	fscanf(ptr1,"%s\t%s\t%s",label,opcode,operand);
	fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
	fprintf(ptr3,"Two pass Assembler - PASS 1\n");
	fprintf(ptr5,"Two pass Assembler - PASS 2\n");
	fprintf(ptr3,"=============================================================\n");
	fprintf(ptr3,"|| ASSEMBLY PROGRAM\t| LC \t| INTERMEDIATE CODE\tTARGETCODE\t||\n");
	fprintf(ptr3,"=============================================================\n");
	fprintf(ptr5,"ASSEMBLY PROGRAM\tLC\tTARGET CODE\n");
	//for comparing start opcode
	if(strcmp(opcode,"START")==0)
	{
		start=atoi(operand);
		lc=start;
		fprintf(ptr3,"%s\t%s\t%s\t",label,opcode,operand);
		fprintf(ptr5,"%s\t%s\t%s\t",label,opcode,operand);
		while(strcmp(code,"START")!=0)
		{
			fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
		}
		fprintf(ptr3,"\t(%s , %s)(c , %d)",mnemonic,mcode,lc);
		fprintf(ptr3,"\t\t-\n");
		fprintf(ptr5,"\t\t-\n");
		fscanf(ptr1,"%s\t%s\t%s",label,opcode,operand);
		
	}
//while loop for read line of file
	while(strcmp(opcode,"END")!=0)
	{
		
		//for comparing ds
	    if(strcmp(opcode,"DS")==0)
		{
			fprintf(ptr3,"%s\t%s\t%s\t",label,opcode,operand);
			fprintf(ptr5,"%s\t%s\t%s\t",label,opcode,operand);
			//FINDING DS IN OPCODE TABLE
			while(strcmp(code,"DS")!=0)
			{
			    fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
				}
			fprintf(ptr3,"%d\t(s , %d)(%s , %s)(c , %s)",lc,index,mnemonic,mcode,operand);
			//TO STORE IN SYMBOL TABLE
		    fprintf(ptr4,"%d\t%s\t%d\n",index,label,lc);
		    fprintf(ptr3,"\t\t-\n");
		    fprintf(ptr5,"%d\t\t-\n",lc);
		    index+=1;
		    lc+=1;
			}
		
		// fro comparing read
		if(strcmp(opcode,"READ")==0)
		{
			fprintf(ptr3,"%s\t%s\t%s\t",label,opcode,operand);
			fprintf(ptr5,"%s\t%s\t%s\t",label,opcode,operand);
			rewind(ptr2);
			fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			while(strcmp(code,"READ")!=0)
			{
				fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			}
			fprintf(ptr3,"%d\t(%s , %s)",lc,mnemonic,mcode);
			
			rewind(ptr4);
			fscanf(ptr4,"%s\t%s\t%s",index1,symbol,adr);
			while(strcmp(symbol,operand)!=0)
			{
				fscanf(ptr4,"%s\t%s\t%s",index1,symbol,adr);
			}
			if(strcmp(symbol,operand)==0)
			{
				fprintf(ptr3,"(S , %s)",index1);
			}
			fprintf(ptr3,"\t\t%s 00 %s\n",mcode,adr);
		    fprintf(ptr5,"%d\t\t%s 00 %s\n",lc,mcode,adr);
//			rewind(ptr4);
			lc+=1;
		}
		
		//for comparing areg register
		if(strcmp(opcode,"AREG")==0)
		{
			fprintf(ptr3,"%s\t%s\t%s\t",label,opcode,operand);
			fprintf(ptr5,"%s\t%s\t%s\t",label,opcode,operand);
			rewind(ptr2);
			fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			while(strcmp(code,label)!=0)
			{
				fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			}
			if(strcmp(code,label)==0)
			{
				fprintf(ptr3,"%d\t(%s , %s)",lc,mnemonic,mcode);
			}
		    strcpy(dubmcode,mcode);
			rewind(ptr2);
			fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			while(strcmp(code,opcode)!=0)
			{
				fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			}
			fprintf(ptr3,"(%s , %s)",mnemonic,mcode);
			rewind(ptr4);
			fscanf(ptr4,"%s\t%s\t%s",index1,symbol,adr);
			while(strcmp(symbol,operand)!=0)
			{
				fscanf(ptr4,"%s\t%s\t%s",index1,symbol,adr);
			}
			
			if(strcmp(symbol,operand)==0)
			{
				fprintf(ptr3,"(S , %s)",index1);
			}
			fprintf(ptr3,"\t%s %s %s\n",dubmcode,mcode,adr);
		    fprintf(ptr5,"%d\t\t%s %s %s\n",lc,dubmcode,mcode,adr);
			lc+=1;
		}
		
		//for comparing print
		if(strcmp(opcode,"PRINT")==0)
		{
			fprintf(ptr3,"%s\t%s\t%s\t",label,opcode,operand);
			fprintf(ptr5,"%s\t%s\t%s\t",label,opcode,operand);
			rewind(ptr2);
			fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			while(strcmp(code,opcode)!=0)
			{
				fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
			}
			fprintf(ptr3,"%d\t(%s , %s)",lc,mnemonic,mcode);
			
			rewind(ptr4);
			fscanf(ptr4,"%s\t%s\t%s",index1,symbol,adr);
			while(strcmp(symbol,operand)!=0)
			{
				fscanf(ptr4,"%s\t%s\t%s",index1,symbol,adr);
			}
			if(strcmp(symbol,operand)==0)
			{
				fprintf(ptr3,"(S , %s)",index1);
			}
			fprintf(ptr3,"\t\t%s 00 %s\n",mcode,adr);
			fprintf(ptr5,"%d\t\t%s 00 %s\n",lc,mcode,adr);
			lc+=1;
		}
		
		fscanf(ptr1,"%s\t%s\t%s",label,opcode,operand);
			
	}
	//for string compariing end
	if(strcmp(opcode,"END")==0)
	{
		fprintf(ptr3,"%s\t%s\t%s\t",label,opcode,operand);
		fprintf(ptr5,"%s\t%s\t%s\t",label,opcode,operand);
		rewind(ptr2);
		fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
		while(strcmp(code,opcode)!=0)
		{
			fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
		}
		fprintf(ptr3,"%d\t(%s , %s)",lc,mnemonic,mcode);
		fprintf(ptr3,"\t\t\t-");
		fprintf(ptr5,"%d\t\t-",lc);
		lc+=1;
	}
	
	//to close file
	fclose(ptr1);
	fclose(ptr2);
	fclose(ptr3);
	fclose(ptr4);
	fclose(ptr5);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
	FILE *ptr1,*ptr2,*ptr3,*ptr4,*ptr5,*ptr6;
	char label[10],opcode[10],argument[10],ala1[10],ala2[10],dubopcode[10],ind[10],op[10],ind_mdt[10];
	char *str,*str1,*str2;
	int inde,index,index1,index2,len,i,j;
	ptr1=fopen("input2.txt","r");
	ptr2=fopen("mdt1.txt","w+");
	ptr3=fopen("ala1.txt","w+");
	ptr4=fopen("mnt1.txt","w+");
	ptr5=fopen("mdt2.txt","w");
	ptr6=fopen("ala2.txt","w+");
	index=1;index1=1;index2=1;inde=1;
	fscanf(ptr1,"%s\t%s\t%s",label,opcode,argument);
	if(strcmp(opcode,"START")==0)
	{
		fprintf(ptr2,"MDT\n");
		fprintf(ptr2,"Index\tDefinitions");
		fprintf(ptr4,"*\tMNT\t*");
		fprintf(ptr4,"\nIndex\tName\tMDT_Index");
		fscanf(ptr1,"%s\t%s\t%s",label,opcode,argument);
	}
	while(strcmp(opcode,"END")!=0)
	{
		if(strcmp(opcode,"MACRO")==0)
		{
			fscanf(ptr1,"%s\t%s\t%s",label,opcode,argument);
			strcpy(dubopcode,opcode);
		    fprintf(ptr2,"\n%d\t%s\t",index,opcode);
		    fprintf(ptr4,"\n%d",index2);
		    fprintf(ptr4,"\t%s\t%d",opcode,index);
		    fseek(ptr4,0,SEEK_CUR);
		    index2+=1;
            str1=strtok(argument,",");
            while(str1!=NULL)
            {
            	fprintf(ptr3,"%d\t%s",index1,str1);
            	fprintf(ptr2,"#%d",index1);
            	fprintf(ptr3,"\n");
            	index1+=1;
            	str1=strtok(NULL,",");
            	if(str1!=NULL)
            	{
            		fprintf(ptr2,",");
				}
            	
			}
			fseek(ptr3,0,SEEK_CUR);
			while(strcmp(opcode,"MEND")!=0)
			{
				if(strcmp(dubopcode,opcode)!=0)
				{
					fprintf(ptr2,"\n%d\t%s\t",index,opcode);
					str=strtok(argument,",");
					while(str!=NULL)
					{
//						printf("%s\n",str);
						rewind(ptr3);
						fscanf(ptr3,"%s\t%s",ala1,ala2);
						while(!feof(ptr3))
						{
							if(strcmp(ala2,str)==0)
							{
								break;
							}
							fscanf(ptr3,"%s\t%s",ala1,ala2);
						}
						if(strcmp(ala2,str)==0)
						{
							fprintf(ptr2,"#%s",ala1);
						}
						else{
							fprintf(ptr2,"%s,",str);
						}
						fseek(ptr3,1,SEEK_CUR);
						str=strtok(NULL,",");
					}
				}
				index+=1;
				fscanf(ptr1,"%s\t%s\t%s",label,opcode,argument);
			}
			if(strcmp(opcode,"MEND")==0)
			{
				fprintf(ptr2,"\n%d\t%s\t*",index,opcode);
				index+=1;
			}
		}
		rewind(ptr4);
		fscanf(ptr4,"%s\t%s\%s",ind,op,ind_mdt);
		while(!feof(ptr4))
		{
			if(strcmp(op,opcode)==0)
			{
				break;
			}
			fscanf(ptr4,"%s\t%s\%s",ind,op,ind_mdt);
		}
		if(strcmp(op,opcode)==0)
		{
			str2=strtok(argument,",");
			while(str2!=NULL)
			{
				fprintf(ptr6,"%d\t%s\n",inde,str2);
				inde+=1;
				str2=strtok(NULL,",");
			}
		}
		fseek(ptr4,1,SEEK_CUR);
		fscanf(ptr1,"%s\t%s\t%s",label,opcode,argument);
	}
	if(strcmp(opcode,"END")==0)
	{
		fprintf(ptr2,"\n%d",index);
		fprintf(ptr4,"\n%d",index2);
	}
	
	//for pass 2
	rewind(ptr2);
	fscanf(ptr2,"%s\t%s\t%s",label,opcode,argument);
	fscanf(ptr2,"%s\t%s\t%s",label,opcode,argument);
	while(!feof(ptr2))
	{
		fprintf(ptr5,"%s\t%s\t",label,opcode);
		str=strtok(argument,",");
	    while(str!=NULL)
	    {
		    rewind(ptr6);
		    fscanf(ptr6,"%s\t%s",ala1,ala2);
		    while(!feof(ptr6))
		    {
		      	if(str[1]==ala1[0])
		    	{
		    		break;
		    	}
			    fscanf(ptr6,"%s\t%s",ala1,ala2);
		    }
		    if(str[1]==ala1[0] && str[0]=='#')
		    {
			    fprintf(ptr5,"%s",ala2);
		    }
		    else if(strcmp(str,"*")!=0){
		    	fprintf(ptr5,"%s",str);
			}
		    str=strtok(NULL,",");
		    if(str!=NULL)
		    {
		    	fprintf(ptr5,",");
			}
	    }
	    fprintf(ptr5,"\n");
	    fscanf(ptr2,"%s\t%s\t%s",label,opcode,argument);
	}
	fprintf(ptr5,"%s",label);
    
	fclose(ptr1); 
	fclose(ptr2);
	fclose(ptr3);
	fclose(ptr4);
	fclose(ptr5);
	return 0;
}

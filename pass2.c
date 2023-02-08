#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char label[10],opcode[10],operand[10],code[10],symtab[10],symadd[10],locctr[10],obj[10];
	int length,i,start,flag=0;
	FILE *fim,*foc,*fal,*fst,*fot,*flen;
	fim = fopen("output.txt","r");
	foc = fopen("objectcode.txt","w");
	fal = fopen("assmlist.txt","w");

	fscanf(fim,"\t%s\t%s\t%s",label,opcode,operand);
	start=atoi(operand);   //strtil(operand,null,16)
	flen = fopen("length.txt","r");
	fscanf(flen,"%d",&length);
	
	if(strcmp(opcode,"START")==0)
	{
		fprintf(fal,"\t%s\t%s\t%s",label,opcode,operand);
		fprintf(foc,"H^%6s^%6s^%6d\nT^%6s^%2d^",label,operand,length,operand,length);
		fscanf(fim,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);	
		fprintf(fal,"\n%s\t%s\t%s\t%s\t",locctr,label,opcode,operand);
	}
	while(strcmp(opcode,"END")!=0)
	{	
		if(strcmp(opcode,"WORD")==0||strcmp(opcode,"BYTE")==0)
		{
			if(operand[0]=='C'||operand[0]=='X')
			{
				for(i=2;i<strlen(operand)-1;i++)
				{
						fprintf(foc,"%d",operand[i]);
						fprintf(fal,"%d",operand[i]);
				}
			}
				else
				{
					fprintf(foc,"%s^",operand);
					fprintf(fal,"%s",operand);
				}			
		}
		else
		{
			fot = fopen("optab.txt","r");
			fscanf(fot,"%s\t%s",code,obj);
			while(strcmp(code,"END")!=0)
			{
				if(strcmp(code,opcode)==0)
				{    
					fprintf(foc,"%s",obj); 
					fprintf(fal,"%s",obj); 
					fclose(fot);
					fst = fopen("symtab.txt","r");
					fscanf(fst,"%s\t%s",symtab,symadd);
					while(strcmp(symtab,"END")!=0)
					{
						if(strcmp(operand,symtab)==0)
						{   fclose(fst);
							fprintf(foc,"%s^",symadd);
							fprintf(fal,"%s",symadd);
							flag=1;							
							break;
						}
						fscanf(fst,"%s\t%s",symtab,symadd);
					}
				}
				if(flag==1)
					break;
				fscanf(fot,"%s\t%s",code,obj);
			}
		}
		fscanf(fim,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);
		fprintf(fal,"\n%s\t%s\t%s\t%s\t",locctr,label,opcode,operand);
		flag=0;
	}	
	fprintf(foc,"\nE^%6d",start);
	printf("\n\nObject code created in\"objectcode.txt\"\nAssembly list created in \"assmlist\"\n\n");
	fclose(fim);
	fclose(foc);
	fclose(fal);
	return 0;
}

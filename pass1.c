#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
int main() 
{ 
 char opcode[10],operand[10],label[10],code[10],mnemonic[3],i; 
 int locctr,start,length; 
 FILE *fip,*fot,*fst,*fop,*flen; 
 fip = fopen("input.txt","r"); 
 fot = fopen("optab.txt","r"); 
 fst = fopen("symtab.txt","w"); 
 fop = fopen("output.txt","w"); 
 flen = fopen("length.txt","w"); 
 
 fscanf(fip,"%s\t%s\t%s",label,opcode,operand); 
  
 if(strcmp(opcode,"START")==0) 
 { 
  start=atoi(operand); 
  locctr=start; 
  fprintf(fop,"\t%s\t%s\t%s\n",label,opcode,operand);  //\t bcos no locctr value for starting line 
  fscanf(fip,"%s\t%s\t%s",label,opcode,operand); 
 } 
 else 
  locctr=0; 
 while(strcmp(opcode,"END")!=0) 
 { 
  fprintf(fop, "%d\t", locctr); 
   if(strcmp(label,"**")!=0) 
   fprintf(fst,"%s\t%d\n",label,locctr); 
  fscanf(fot,"%s\t%s",code,mnemonic); 
 
  while(strcmp(code,"END")!=0) 
  { 
   if(strcmp(opcode,code)==0) 
   { 
    locctr+=3; 
                break; 
   } 
   fscanf(fot,"%s\t%s",code,mnemonic); 
  } 
  if(strcmp(opcode,"WORD")==0) 
   locctr+=3; 
  else if(strcmp(opcode,"RESW")==0) 
   locctr+=(3*(atoi(operand))); 
  else if(strcmp(opcode,"RESB")==0) 
   locctr+=atoi(operand); 
  else if(strcmp(opcode,"BYTE")==0) 
  { 
   if(operand[0]=='C'||operand[0]=='X') 
    for(i=2;i<strlen(operand)-1;i++) 
      ++locctr; 
   else 
    ++locctr; 
    
  } 
   
  fprintf(fop,"%s\t%s\t%s\t\n",label,opcode,operand); 
  fscanf(fip,"%s\t%s\t%s",label,opcode,operand); 
 }  
 fprintf(fop,"%d\t%s\t%s\t%s\t\n",locctr,label,opcode,operand); 
  
 length = locctr-start; 
 
 printf("\n\nThe length of the code is %d\n\n",length); 
 fprintf(flen,"%d",length); 
 fclose(fip); 
 fclose(fot); 
 fclose(fst); 
 fclose(fop); 
 return 0; 
}

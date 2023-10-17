#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _GNU_SOURCE
void main()
{
char opcode[10],mnemonic[10],operand[10],label[10],code[10];
int l,locctr,start,length;
FILE *fp1,*fp2,*fp3,*fp4;
fp1=fopen("input.dat","w");
fputs("COPY START 2000\n** LDA FIVE\n** STA ALPHA\n** LDCH CHARZ\n** STCH C1\n
ALPHA RESW 1\n FIVE WORD 5\n CHARZ BYTE C'E'\nC1 RESB 1\n** END **",fp1);
fclose(fp1);
fp2=fopen("symtab.dat","w");
fp3=fopen("inter.dat","w");
fp4=fopen("optab.dat","w");
fputs("ADD\t
18\nSUB\t1C\nMUL\t20\nDIV\t24\nLDA\t00\nLDB\t68\nLDX\t04\nLDCH\t50\nSTA\t0C\nSTB\t78\
nSTX\t10\nSTCH\t54\nSTART\t*\nEND\t*\n",fp4);
fclose(fp4);
fp1=fopen("input.dat","r");
fscanf(fp1,"%s%s%s",label,opcode,operand);
if(strcmp(opcode,"START")==0)
{
start=atoi(operand);
locctr=start;
fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(fp1,"%s%s%s",label,opcode,operand);
}
else
locctr=0;
fp4=fopen("optab.dat","r");
while(strcmp(opcode,"END")!=0)
{
fprintf(fp3,"%d\t",locctr);
if(strcmp(label,"**")!=0)
fprintf(fp2,"%s\t%d\n",label,locctr);
rewind(fp4);
fscanf(fp4,"%s",mnemonic);
while(strcmp(mnemonic,"END")!=0)
{
if(strcmp(opcode,mnemonic)==0)
{
locctr+=3;
break;
}
fscanf(fp4,"%s",mnemonic);
}
if(strcmp(opcode,"WORD")==0)
locctr+=3;
else if(strcmp(opcode,"RESW")==0)
locctr+=(3*(atoi(operand)));
else if(strcmp(opcode,"RESB")==0)
locctr+=(atoi(operand));
else if(strcmp(opcode,"BYTE")==0)
{
l=strlen(operand)-3;
locctr+=1;
}
fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(fp1,"%s%s%s",label,opcode,operand);
}
fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
length=locctr-start;
printf("The length of the program is %d\n",length);
fclose(fp1);
fclose(fp2);
fclose(fp3);
fclose(fp4);
}
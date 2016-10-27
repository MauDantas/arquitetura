#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <ctype.h>

unsigned int* pilha = NULL;
unsigned int int_pilha[3];
unsigned int stopme;
unsigned int R[64];
unsigned int x, y;
float z;
unsigned int controlFpu;
int xisfloat, yisfloat, zisint;

FILE *saida;
char flag1=0; 
/* 0-31 Registradores de proposito geral
	 32 PC - Controle de Fluxo
	 33 IR - Instrucao atual
	 34 ER - Registrador de extensao
	 35 FR - Dados de comparacoes e info do processador
	 36 CR - Registrador de código de interrupcao
	 37 IPC - Valor do PC na checagem de interrupcao*/

//Nome dos registradores em minusculo	 
 char* reg_name(unsigned int registrador){
	char* retorno;
	retorno = (char*)malloc(4*sizeof(char));
	int aux = registrador/10;
	if(registrador<32){
		if(registrador<10){
			retorno[0]='r';
			retorno[1]='0'+registrador;
			retorno[2]='\0';
			retorno[3]='\0';
			return retorno;
		}
		else{
			retorno[0]='r';
			retorno[1]='0'+aux;
			retorno[2]=abs('0'+(registrador-(aux*10)));
			retorno[3]='\0';
			return retorno;
		}
			
	}
	else{
		switch(registrador){
			case 32:
				strcat(retorno,"pc");
			break;
			case 33:
				strcat(retorno,"ir");
			break;
			case 34:
				strcat(retorno,"er");
			break;
			case 35:
				strcat(retorno,"fr");
			break;
			case 36:
				strcat(retorno,"cr");
			break;
			case 37:
				strcat(retorno,"ipc");
			break;
		}
	}
}
//Nome dos registradores em maiúsculo
char* reg_name_UP(unsigned int registrador){
	char* retorno;
	retorno = (char*)malloc(4*sizeof(char));
	int aux = registrador/10;
	if(registrador<32){
		if(registrador<10){
			retorno[0]='R';
			retorno[1]='0'+registrador;
			retorno[2]='\0';
			retorno[3]='\0';
			return retorno;
		}
		else{
			retorno[0]='R';
			retorno[1]='0'+aux;
			retorno[2]=abs('0'+(registrador-(aux*10)));
			retorno[3]='\0';
			return retorno;
		}
	}
	else{
		switch(registrador){
			case 32:
				strcat(retorno,"PC");
			break;
			case 33:
				strcat(retorno,"IR");
			break;
			case 34:
				strcat(retorno,"ER");
			break;
			case 35:
				strcat(retorno,"FR");
			break;
			case 36:
				strcat(retorno,"CR");
			break;
			case 37:
				strcat(retorno,"IPC");
			break;
		}
	}
}
//todos registradores são zerados
void cleanR(){
	char i;
	for(i=0; i<36; i++){
		R[i]=0;
	}
	for(i=0; i<100; i++){
		pilha[i]=0;
	}
}

//Simulador FPU (float process unit)
void fpu(){
	unsigned int xint;
	float aux1, aux2;
	switch((controlFpu&0x0000001F)){
		case 0:
			break;
		case 1:
			if(xisfloat==1)
			aux1=*((float*)&x);
			else
			aux1=x;	
			if(yisfloat==1)
			aux2=*((float*)&y);
			else
			aux2=y;	
			z=aux1+aux2;
			printf("\n\nAdicao %f+%f=%f\n\n",aux1,aux2,z);
			zisint=0;
			controlFpu=0;
			break;
		case 2:
			if(xisfloat==1)
			aux1=*((float*)&x);
			else
			aux1=x;	
			if(yisfloat==1)
			aux2=*((float*)&y);
			else
			aux2=y;
			z= aux1-aux2;
			printf("\n\nSubtracao %f-%f=%f\n\n",aux1,aux2,z);
			zisint=0;
			controlFpu=0;
			break;
		case 3:
			if(xisfloat==1)
			aux1=*((float*)&x);
			else
			aux1=x;	
			if(yisfloat==1)
			aux2=*((float*)&y);
			else
			aux2=y;
			z= aux1*aux2;
			zisint=0;
			printf("\n\nMultiplicacao %f*%f=%f\n\n",aux1,aux2,z);
			controlFpu=0;
			break;
		case 4:
			if(xisfloat==1)
			aux1=*((float*)&x);
			else
			aux1=x;	
			if(yisfloat==1)
			aux2=*((float*)&y);
			else
			aux2=y;
			if(y==0){
				z=0;
				controlFpu=0x00000020;
			}
			else{
				z=aux1/aux2;
				controlFpu=0;
			}
			printf("\n\nDivisao %f/%f=%f\n\n",aux1,aux2,z);
			zisint=0;
			break;
		case 5:
			memcpy(&x, &z, sizeof (x));
			printf("\n\nAtribuicao x=0x%08X\n\n",x);
			xisfloat=1;
			controlFpu=0;
			break;
		case 6:
			memcpy(&y, &z, sizeof (y));
			printf("\n\nAtribuicao x=0x%08X\n\n",y);
			yisfloat=1;
			controlFpu=0;
			break;
		case 7:
			xint=z;
			z=xint;
			zisint=1;
			printf("\n\nPiso %f\n\n",z);
			controlFpu=0;
			break;
		case 8: 
			xint=z;
			z=xint+1;
			zisint=1;
			printf("\n\nTeto %f\n\n",z);
			controlFpu=0;
			break;
		case 9:
			xint=z;
			if((z-xint)>=0.5){
				z=xint +1;
			}
			else{
				z=xint;
			}
			printf("\n\nArredondamento %f\n\n",z);
			zisint=1;
			controlFpu=0;
			break;
		default: 
			printf("\n\nOperacao invalida\n\n");
			controlFpu=0x00000020;
			break;
		}
		//printf("X %d 0x%08X\n Y %d 0x%08X\n Z %f 0x%08X\n", x,x,y,y,z,z);
		//system("pause");
} 
//R0 sempre zero
void persistR0(){
	R[0]=0;}
//Metodo de retorno da operacao utilizada
char* operacao (unsigned int instruction){
	switch(instruction){
		case 0:
			return "add U\0";
		case 1:
			return "addiF\0";
		case 2:
			return "sub U\0";
		case 3:
			return "subiF\0";
		case 4:
			return "mul U\0";
		case 5:
			return "muliF\0";
		case 6:
			return "div U\0";
		case 7:
			return "diviF\0";
		case 8:
			return "cmp U\0";
		case 9:
			return "cmpiF\0";
		case 10:
			return "shl U\0";
		case 11:
			return "shr U\0";
		case 12:
			return "and U\0";
		case 13:
			return "andiF\0";
		case 14:
			return "not U\0";
		case 15:
			return "notiF\0";
		case 16:
			return "or  U\0";
		case 17:
			return "ori F\0";
		case 18:
			return "xor U\0";
		case 19:
			return "xoriF\0";
		case 20:
			return "ldw F\0";
		case 21:
			return "ldb F\0";
		case 22:
			return "stw F\0";
		case 23:
			return "stb F\0";
		case 24:
			return "pushU\0";
		case 25:
			return "pop U\0";
		case 26:
			return "bun S\0";
		case 27:
			return "beq S\0";
		case 28:
			return "blt S\0"; 
		case 29:
			return "bgt S\0";
		case 30:
			return "bne S\0";
		case 31:   
			return "ble S\0";
		case 32:
			return "bge S\0"; 
		case 33:
			return "bzd S\0";
		case 34:
			return "bnz S\0";
		case 35:   
			return "bzi S\0";
		case 36:   
			return "bni S\0";	
		case 37:   
			return "callF\0";
		case 38:   
			return "ret F\0";
		case 39:   
			return "isr F\0";
		case 40:   
			return "retiF\0";		
		case 63:
			return "int S\0";
		default: 
			return "erroE\0";}
}
//retorna a instrução
unsigned int instrucao(unsigned int wholeWord){
	unsigned int instruction=(wholeWord & 0xFC000000)>>26;
	return instruction;
}
//printer de execucao U
void excU(unsigned int instruction, unsigned int Rz , unsigned int Rx, unsigned int Ry, unsigned int extensao){
	switch (instruction){
		//add
		case 0:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			fprintf(saida, "add %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			printf("add %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			printf("[U] FR = 0x%08X, %s = %s + %s = 0x%08X\n", R[35],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);
			fprintf(saida, "[U] FR = 0x%08X, %s = %s + %s = 0x%08X\n", R[35],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);
		break;
		//sub
		case 2:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			fprintf(saida, "sub %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			printf("sub %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida, "[U] FR = 0x%08X, %s = %s - %s = 0x%08X\n", R[35],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);
			printf("[U] FR = 0x%08X, %s = %s - %s = 0x%08X\n", R[35],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);	
		break;
		//mul
		case 4:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			fprintf(saida,"mul %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry) );
			printf("mul %s, %s, %s \n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida, "[U] FR = 0x%08X, ER = 0x%08X, %s = %s * %s = 0x%08X\n", R[35], R[34],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);
			printf("[U] FR = 0x%08X, ER = 0x%08X, %s = %s * %s = 0x%08X\n", R[35], R[34],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);
			//system("pause");
		break;
		//div (DUVIDA - SLIDE 5)
		case 6:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("div %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida, "div %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida,"[U] FR = 0x%08X, ER = 0x%08X, %s = %s / %s = 0x%08X\n", R[35],R[34],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
			printf("[U] FR = 0x%08X, ER = 0x%08X, %s = %s / %s = 0x%08X\n", R[35],R[34],reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz]);
		break;
		//cmp (DUVIDA - SLIDE 5)
		case 8:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("cmp %s, %s\n",reg_name(Rx),reg_name(Ry));
			fprintf(saida,"cmp %s, %s\n",reg_name(Rx),reg_name(Ry));
			printf("[U] FR = 0x%08X\n",R[35]);
			fprintf(saida, "[U] FR = 0x%08X\n",R[35]);
		break;
		//shl
		case 10:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			if(Rz==0){
				printf("shl %s, %s, %d\n", reg_name(Rz),reg_name(Rx),(Ry+32));
				printf("[U] ER = 0x%08X,",R[34]);
				printf(" %s ", reg_name_UP(Rz));
				printf("= %s ",reg_name(Rx)); 
				printf("<< %d = ", (Ry+33));
				printf("0x%08X\n", R[Rz] );
				fprintf(saida,"[U] ER = 0x%08X, %s = %s << %d = 0x%08X\n",R[34], reg_name_UP(Rz),reg_name_UP(Rx),(Ry+33),R[Rz] );
			}
			else{
				printf("shl %s, %s, %d\n", reg_name(Rz),reg_name(Rx),Ry);
				fprintf(saida,"shl %s, %s, %d\n",reg_name(Rz),reg_name(Rx),Ry );
				printf("[U] ER = 0x%08X,",R[34]);
				printf(" %s ", reg_name_UP(Rz));
				printf("= %s ",reg_name_UP(Rx)); 
				printf("<< %d = ", (Ry+1));
				printf("0x%08X\n", R[Rz] );
				fprintf(saida,"[U] ER = 0x%08X,",R[34]);
				fprintf(saida," %s ", reg_name_UP(Rz));
				fprintf(saida,"= %s ",reg_name_UP(Rx)); 
				fprintf(saida,"<< %d = ", (Ry+1));
				fprintf(saida,"0x%08X\n", R[Rz] );
			}
			//system("pause");
				
		break;
		//shr
		case 11:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("shr %s, %s, %d\n",reg_name(Rz),reg_name(Rx),Ry);
			fprintf(saida,"shr %s, %s, %d\n",reg_name(Rz),reg_name(Rx),Ry);
			fprintf(saida, "[U] ER = 0x%08X, %s = %s >> %d = 0x%08X\n",R[34], reg_name_UP(Rz),reg_name_UP(Rx),Ry+1,R[Rz] );
			printf("[U] ER = 0x%08X, %s = %s >> %d = 0x%08X\n",R[34], reg_name_UP(Rz),reg_name_UP(Rx),Ry+1,R[Rz] );
		break;
		//and
		case 12:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("and %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida,"and %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida,"[U] %s = %s & %s = 0x%08X\n", reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
			printf("[U] %s = %s & %s = 0x%08X\n", reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
		break;
		//not
		case 14:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("not %s, %s\n",reg_name(Rx),reg_name(Ry));
			fprintf(saida,"not %s, %s\n",reg_name(Rx),reg_name(Ry));
			printf("[U] %s = ~%s = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),R[Rx] );
			fprintf(saida,"[U] %s = ~%s = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),R[Rx] );
		break;
		//or
		case 16:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("or %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida,"or %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			printf("[U] %s = %s | %s = 0x%08X\n", reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
			fprintf(saida,"[U] %s = %s | %s = 0x%08X\n", reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
		break;
		//xor
		case 18: 
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("xor %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			fprintf(saida, "xor %s, %s, %s\n",reg_name(Rz),reg_name(Rx),reg_name(Ry));
			printf("[U] %s = %s ^ %s = 0x%08X\n", reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
			fprintf(saida,"[U] %s = %s ^ %s = 0x%08X\n", reg_name_UP(Rz),reg_name_UP(Rx),reg_name_UP(Ry),R[Rz] );
		break;
		//push
		case 24:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			printf("push %s, %s\n", reg_name(Rx),reg_name(Ry));
			fprintf(saida, "push %s, %s\n",reg_name(Rx),reg_name(Ry));
			printf("[U] MEM[%s--] = %s = 0x%08X\n",reg_name_UP(Rx),reg_name_UP(Ry),R[Ry]);
			fprintf(saida, "[U] MEM[%s--] = %s = 0x%08X\n",reg_name_UP(Rx),reg_name_UP(Ry),R[Ry]);
		break;
		//pop
		case 25:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			printf("pop %s, %s\n",reg_name(Rx),reg_name(Ry));
			fprintf(saida,"pop %s, %s\n",reg_name(Rx),reg_name(Ry));
			printf("[U] %s = MEM[++%s] = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),R[Rx]);
			fprintf(saida, "[U] %s = MEM[++%s] = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),R[Rx]);
		break;
		}
}
//printer de execucao de F
void excF(unsigned int instruction, unsigned int IM16 , unsigned int Rx, unsigned int Ry){
	switch (instruction){
		//addi
		case 1:
			printf("addi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida, "addi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] FR = 0x%08X, %s = %s + 0x%04X = 0x%08X\n", R[35],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			fprintf(saida, "[F] FR = 0x%08X, %s = %s + 0x%04X = 0x%08X\n", R[35],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
		break;
		//subi
		case 3:
			fprintf(saida, "subi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("subi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida, "[F] FR = 0x%08X, %s = %s - 0x%04X = 0x%08X\n", R[35],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			printf("[F] FR = 0x%08X, %s = %s - 0x%04X = 0x%08X\n", R[35],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);	
		break;
		//muli
		case 5:
			printf("muli %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida,"muli %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] FR = 0x%08X, ER = 0x%08X, %s = %s * 0x%04X = 0x%08X\n", R[35], R[34],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			fprintf(saida,"[F] FR = 0x%08X, ER = 0x%08X, %s = %s * 0x%04X = 0x%08X\n", R[35], R[34],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
		break;
		//divi (DUVIDA - SLIDE 5)
		case 7:
			printf("divi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida,"divi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] FR = 0x%08X, ER = 0x%08X, %s = %s / 0x%04X = 0x%08X\n", R[35],R[34],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			fprintf(saida,"[F] FR = 0x%08X, ER = 0x%08X, %s = %s / 0x%04X = 0x%08X\n", R[35],R[34],reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
		break;
		//cmpi (DUVIDA - SLIDE 5)
		case 9:
			printf("cmpi %s, %d\n", reg_name(Rx),IM16);
			fprintf(saida,"cmpi %s, %d\n",reg_name(Rx),IM16);
			printf("[F] FR = 0x%08X\n",R[35]);
			fprintf(saida,"[F] FR = 0x%08X\n",R[35]);
		break;
		//andi
		case 13:
			printf("andi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida,"andi %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] %s = %s & 0x%04X = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry), IM16,R[Rx] );
			fprintf(saida,"[F] %s = %s & 0x%04X = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry), IM16,R[Rx] );
		break;
		//noti
		case 15:
			printf("noti %s, %d\n",reg_name(Rx),IM16);
			fprintf(saida, "noti %s, %d\n",reg_name(Rx),IM16);
			printf("[F] %s = ~0x%04X = 0x%08X\n", reg_name_UP(Rx),IM16,R[Rx] );
			fprintf(saida,"[F] %s = ~0x%04X = 0x%08X\n", reg_name_UP(Rx),IM16,R[Rx] );
		break;
		//ori
		case 17:
			printf("ori %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida, "ori %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] %s = %s | 0x%04X = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx] );
			fprintf(saida, "[F] %s = %s | 0x%04X = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx] );
		break;
		//xori
		case 19: 
			printf("xori %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida, "xori %s, %s, %d\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] %s = %s ^ 0x%08X = 0x%X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			fprintf(saida, "[F] %s = %s ^ 0x%04X = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
		break;
		//ldw
		case 20:
			printf("ldw %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida,"ldw %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida, "[F] %s = MEM[(%s + 0x%04X) << 2] = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			printf("[F] %s = MEM[(%s + 0x%04X) << 2] = 0x%08X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
		break;
		
		//ldb
		case 21:
			printf("ldb %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida, "ldb %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] %s = MEM[%s + 0x%04X] = 0x%02X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
			fprintf(saida,"[F] %s = MEM[%s + 0x%04X] = 0x%02X\n", reg_name_UP(Rx),reg_name_UP(Ry),IM16,R[Rx]);
		break;
		//stw
		case 22:
			printf("stw %s, 0x%04X, %s\n",reg_name(Rx),IM16,reg_name(Ry));
			fprintf(saida, "stw %s, 0x%04X, %s\n",reg_name(Rx),IM16,reg_name(Ry));
			printf("[F] MEM[(%s + 0x%04X) << 2] = %s = 0x%08X\n", reg_name_UP(Rx),IM16,reg_name_UP(Ry),R[Ry]);
			fprintf(saida,"[F] MEM[(%s + 0x%04X) << 2] = %s = 0x%08X\n", reg_name_UP(Rx),IM16, reg_name_UP(Ry),R[Ry]);
		break;
		//stb
		case 23:
			printf("stb %s, 0x%04X, %s\n",reg_name(Rx),IM16, reg_name(Ry));
			fprintf(saida, "stb %s, 0x%04X, %s\n",reg_name(Rx),IM16, reg_name(Ry));
			printf("[F] MEM[%s + 0x%04X] = %s = 0x%02X\n", reg_name_UP(Rx),IM16, reg_name_UP(Ry),(0x000000FF&R[Ry]));
			fprintf(saida, "[F] MEM[%s + 0x%04X] = %s = 0x%02X\n", reg_name_UP(Rx),IM16, reg_name_UP(Ry),(0x000000FF&R[Ry]));
		break;
		//call
		case 37:
			persistR0();
			printf("call %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida,"call %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] %s = (PC + 4) >> 2 = 0x%08X, PC = (%s + 0x%04X) << 2 = 0x%08X\n", reg_name_UP(Rx),R[Rx],reg_name_UP(Ry),IM16, ((Ry+IM16)<<2));
			fprintf(saida,"[F] %s = (PC + 4) >> 2 = 0x%08X, PC = (%s + 0x%04X) << 2 = 0x%08X\n", reg_name_UP(Rx),R[Rx],reg_name_UP(Ry),IM16, ((Ry+IM16)<<2));
		break;
		//ret
		case 38:
			printf("ret %s \n",reg_name(Rx));
			fprintf(saida, "ret %s\n",reg_name(Rx));
			printf("[F] PC = %s << 2 = 0x%08X\n", reg_name_UP(Rx),(R[Rx]<<2));
			fprintf(saida, "[F] PC = %s << 2 = 0x%08X\n",reg_name_UP(Rx), (R[Rx]<<2));
		break;
		//isr
		case 39:
			printf("isr %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			fprintf(saida,"isr %s, %s, 0x%04X\n",reg_name(Rx),reg_name(Ry),IM16);
			printf("[F] %s = IPC >> 2 = 0x%08X, %s = CR = 0x%08X, PC = 0x%08X\n", reg_name_UP(Rx),R[37],reg_name_UP(Ry),R[36], (IM16)<<2);
			fprintf(saida,"[F] %s = IPC >> 2 = 0x%08X, %s = CR = 0x%08X, PC = 0x%08X\n", reg_name_UP(Rx),R[37],reg_name_UP(Ry),R[36], (IM16)<<2);
		break;
		//reti
		case 40:
			printf("reti %s\n",reg_name(Rx));
			fprintf(saida, "reti %s\n",reg_name(Rx));
			printf("[F] PC = %s << 2 = 0x%08X\n",reg_name_UP(Rx),(R[Rx]<<2));
			fprintf(saida, "[F] PC = %s << 2 = 0x%08X\n",reg_name_UP(Rx),(R[Rx]<<2));	
		 }
}
//printer de execucao de S
void excS(unsigned int instruction, unsigned int S){
	int PC=R[32]*4;
	switch (instruction){
	//bun
	case 26:
		printf("bun 0x%08X\n", S);
		fprintf(saida,"bun 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida,"[S] PC = 0x%08X\n", PC);
	break;
	//beq
	case 27:
		printf("beq 0x%08X\n", S);
		fprintf(saida, "beq 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida, "[S] PC = 0x%08X\n", PC);
	break;
	//blt
	case 28:
		printf("blt 0x%08X\n", S);
		fprintf(saida,"blt 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida,"[S] PC = 0x%08X\n", PC);
	break;
	//bgt
	case 29:
		printf("bgt 0x%08X\n", S);
		fprintf(saida, "bgt 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida, "[S] PC = 0x%08X\n", PC);
	break;
	//bne
	case 30:
		printf("bne 0x%08X\n", S);
		fprintf(saida,"bne 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida,"[S] PC = 0x%08X\n", PC);
	break;
	//bge
	case 32:
		printf("bge 0x%08X\n", S);
		fprintf(saida, "bge 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida, "[S] PC = 0x%08X\n", PC);
	break;
	//ble
	case 31:
		printf("ble 0x%08X\n", S);
		fprintf(saida,"ble 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
		fprintf(saida,"[S] PC = 0x%08X\n", PC);
	break;
	//bzd
	case 33:
		printf("bzd 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n",PC);
		fprintf(saida,"bzd 0x%08X\n", S);
		fprintf(saida,"[S] PC = 0x%08X\n",PC);
	break;
	//bnz
	case 34:
		printf("bnz 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n",PC);
		fprintf(saida,"bnz 0x%08X\n", S);
		fprintf(saida,"[S] PC = 0x%08X\n",PC);
	break;
	//biv
	case 35:
		printf("biv 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n",PC);
		fprintf(saida, "biv 0x%08X\n", S);
		fprintf(saida, "[S] PC = 0x%08X\n",PC);
	break;
	//bni
	case 36:
		printf("bni 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n",PC);	
		fprintf(saida, "bni 0x%08X\n", S);
		fprintf(saida,"[S] PC = 0x%08X\n",PC);			
	break;
	//int
	case 63:
		fprintf(saida, "int %d\n[S] CR = 0x%08X, PC = 0x0000000C\n", S, R[36]);
		printf("int %d\n[S] CR = %d, PC = 0x0000000C\n", S, R[36]);
	break;
	}
}
//Parametros para operacoes tipo U
unsigned int opXU(unsigned int wholeWord){
	unsigned int Rx=(wholeWord&0x000003E0)>>05;
	return Rx;
}
unsigned int opZU(unsigned int wholeWord){
	unsigned int Rz=(wholeWord&0x00007C00)>>10;
	return Rz;
}
unsigned int opYU(unsigned int wholeWord){
	unsigned int Ry=(wholeWord&0x0000001F);
	return Ry;
}
unsigned int opEU(unsigned int wholeWord){
	unsigned int E=(wholeWord&0x00038000)>>15;
	return E;
} 
//Parametros para operacoes tipo F
unsigned int opxF(unsigned int wholeWord){
	unsigned int Rx=  (wholeWord&0x000003E0)>>05;
	persistR0();
	return Rx;
}
unsigned int opyF(unsigned int wholeWord){
	unsigned int Ry=  (wholeWord&0x0000001F);
	return Ry;
}
unsigned int opIM16F(unsigned int wholeWord){
	unsigned int IM16=(wholeWord&0x03FFFC00)>>10;
	return IM16;
}
//Parametros para operacoes tipo S
unsigned int opS(unsigned int wholeWord){
	unsigned int IM16=(wholeWord&0x03FFFFFF);
	//printf("IM16: %d \n", IM16);
	persistR0();
	return IM16;
}
//modificacoes feitas por instrucoes tipo U
void RspU(unsigned int instruction, unsigned int Rz, unsigned int Rx, unsigned int Ry, unsigned int extensao){
	unsigned int aux1, aux2;
	unsigned int aux3;
	unsigned int aux4;
	unsigned int aux5;
	uint64_t mult, param1, param2;
	switch (instruction){
		//add
		case 0:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			//printf("Rx R%d Ry R%d Rz R%d\n", Rx, Ry, Rz);
			param1 = ((uint64_t)R[Rx]) + ((uint64_t)R[Ry]);
			R[Rz]=(uint32_t)(param1&0x00000000FFFFFFFF);
			if(param1>0xFFFFFFFF)
			{
				R[35]=R[35]|0x00000010;
			}
			else{
				R[35]=R[35]&(0xFFFFFFEF);
			}
		break;
		//sub
		case 2:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			//printf("Rx R%d Ry R%d Rz R%d\n", Rx, Ry, Rz);
			aux1=R[Rx];
			aux2=R[Ry];
			R[Rz]=R[Rx]-R[Ry];
			if((aux1-aux2)<0xFFFFFFFF)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
		break;
		//mul
		case 4:
				Rx=Rx+((extensao&0x00000002)<<4);
				Ry=Ry+((extensao&0x00000001)<<5);
				Rz=Rz+((extensao&0x00000004)<<3);
				//printf("Rz R%d Rx R%d Ry R%d\n", Rz, Rx, Ry);
				//aux1=R[Rx];
				//aux2=R[Ry];
				param1 = ((uint64_t)R[Rx]) * ((uint64_t)R[Ry]);
				R[Rz] = (uint32_t)(param1&0x00000000FFFFFFFF);
				R[34] = (uint32_t)(param1>>32);
				//printf("\nRz 0x%08X \n Rx 0x%08X Ry 0x%08X\n aux3 0x%08X\n",R[Rz],aux1, aux2, R[34]);
				//system("pause");
				if(R[34]!=0){
					R[35]=R[35]|0x00000010;
				}
				else{
					R[35]=R[35]&0xFFFFFFEF;
				}
				
		break;
		//div (DUVIDA - SLIDE 5)
		case 6:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			//printf("R[y]%d\n",R[Ry]);
			if(R[Ry]==0)
			{
				R[35]=R[35]+0x00000008;
			}
			else 
			{
				aux3=R[Rx];
				aux4=R[Ry];
				aux5=aux3/aux4;
				R[34]=R[Rx]%R[Ry];
				R[Rz]=aux5;
				R[35]=R[35]&0xFFFFFFE7;
				//printf("\n\nR%d = %d/%d = %d, Resto eh %d\n\n",Rz,R[Rx],R[Ry],R[Rz], R[34]);
				/* if(R[34]!=0)
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	 */
			}
		break;
		//cmp (DUVIDA - SLIDE 5)
		case 8:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			if(R[Rx]>R[Ry]){
				R[35]=(R[35]&0xFFFFFFF8)+0x00000004;
			}
			else if(R[Rx]<R[Ry]){
				R[35]=(R[35]&0xFFFFFFF8)+0x00000002;
			}
			else if(R[Rx]==R[Ry]){
				R[35]=(R[35]&0xFFFFFFF8)+0x00000001;
			}
		break;
		//shl
		case 10:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			//printf("The flag is %d ",flag1);
			param1 = (((uint64_t)R[Rx])+(((uint64_t)R[34])<<32)) << (Ry+1);
			R[Rz] = (uint32_t)(param1&0x00000000FFFFFFFF);
			R[34] = (uint32_t)(param1>>32);
		break;
		//shr
		case 11:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			if(Rz==0){
				R[34]=0;
				R[Rz]=0;
			}
			else{
				param1 = (((uint64_t)R[Rx])+(((uint64_t)R[34])<<32)) >> (Ry+1);
				R[Rz] = (uint32_t)(param1&0x00000000FFFFFFFF);
				R[34] = (uint32_t)(param1>>32);
			}
		break;
		//and
		case 12:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			R[Rz]=R[Rx]&R[Ry];
		break;
		//not
		case 14:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			R[Rx]=~R[Ry];
		break;
		//or
		case 16:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			R[Rz]=R[Rx]|R[Ry];
		break;
		//xor
		case 18: 
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			R[Rz]=R[Rx]^R[Ry];
		break;
		//push
		case 24:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			pilha[R[Rx]]=R[Ry];
			R[Rx]=R[Rx]-1;
		break;
		//pop
		case 25:
			/* for(aux5=0;aux5<100;aux5++)
				printf("Elemento %d %08x\n", aux5, pilha[aux5]);  */
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			R[Ry]=R[Ry]+1;
			//printf("R%d = %d Pilha[%d] = %d\n", Ry, R[Ry], R[Ry], pilha[R[Ry]] );
			R[Rx]=pilha[R[Ry]];
			//printf("Rx = 0x%08X\n", R[Rx]);
		break;	
		}
}

//modificacoes feitas por instrucoes tipo F
void RspF(unsigned int instruction, unsigned int IM16, unsigned int Rx, unsigned int Ry){
	unsigned int aux1, aux2;
	unsigned int aux3, aux4, aux5;
	uint64_t superaux;
	uint64_t mult, param1, param2;
	switch (instruction){
		//addi
		case 1:
			//printf("R[y] %d\n",R[Ry] );
			aux1=R[Ry];
			aux2=IM16;
			R[Rx]=IM16+R[Ry];
			//printf("Resp %X\n",R[Rx]);
			//printf("%d+%d=%d\n", aux1, IM16,R[Rx]);
			if(R[Ry]>R[Rx])
			{
				R[35]=R[35]|0x00000010;
			}
			else{
				R[35]=R[35]&(0xFFFFFFEF);
			}
			
		break;
		//subi
		case 3:
			//
			superaux=R[Ry]-IM16;
			aux1=R[Ry];
			R[Rx]=R[Ry]-IM16;
			printf("R[Rx] %d R[Ry] %d IM16 0x%04X \n", R[Rx], aux1, IM16);
			//system("pause");
			if((aux1&0x10000000)!=(R[Ry]&0x10000000))
			{
				R[35]=R[35]|0x00000010;
			}
			else{
				//system("pause");
				R[35]=R[35]&0xFFFFFFEF;
				}
		break;
		//muli
		case 5:
			param1 = ((uint64_t)IM16) * ((uint64_t)R[Ry]);
			R[Rx] = (uint32_t)(param1&0x00000000FFFFFFFF);
			R[34]=(uint32_t)(param1>>32);
			if(R[34]!=0){
				R[35]=R[35]|0x00000010;
			}
			else{
				R[35]=R[35]&0xFFFFFFEF;
			}
			//printf("\nRz 0x%08X \n Rx 0x%08X Ry 0x%08X\n aux3 0x%08X\n",R[Rz],aux1, aux2, R[34]);
			//system("pause");
		break;
		//divi (DUVIDA - SLIDE 5)
		case 7:
			if(IM16==0)
			{
				R[35]=R[35]+0x00000008;
			}
			else 
			{
				R[34]=R[Ry]%IM16;
				R[Rx]=R[Ry]/IM16;
				//printf("\n\nR%d = %d/%d = %d, Resto eh %d\n\n",Rx,R[Ry],IM16,R[Rx], R[34]);
				/* if(R[34]!=0)
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	 */
			}
		break;
		//cmpi (DUVIDA - SLIDE 5)
		case 9:
			if(R[Rx]>IM16){
				R[35]=(R[35]&0xFFFFFFF8)+0x00000004;
			}
			else if(R[Rx]<IM16){
				R[35]=(R[35]&0xFFFFFFF8)+0x00000002;
			}
			else if(R[Rx]==IM16){
				R[35]=(R[35]&0xFFFFFFF8)+0x00000001;
			}
		break;
		//andi
		case 13:
			R[Rx]=IM16&R[Ry];
		break;
		//noti
		case 15:
			R[Rx]=~IM16;
		break;
		//ori
		case 17:
			R[Rx]=IM16|R[Ry];
		break;
		//xori
		case 19: 
			R[Rx]=IM16^R[Ry];
		break;
		/* //isr
		case 39:
			printf("isr r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			fprintf(saida,"isr r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			printf("[F] R%d = IPC >> 2 = 0x%08X, R%d = CR = 0x%08X, PC = 0x%08X\n", Rx,R[37],Ry,R[36], (IM16)<<2);
			fprintf(saida,"[F] R%d = IPC >> 2 = 0x%08X, R%d = CR = 0x%08X, PC = 0x%08X\n", Rx,R[37],Ry,R[36], (IM16)<<2);
		

		break; */
	}
		
	persistR0();
}
//modificacoes feitas por instrucoes tipo S
void RspS(unsigned int instruction, unsigned int S){
	unsigned int aux1;
	switch (instruction){
	//bun
	case 26:
		if(S==0)
			R[32]=S/4;
		else
			R[32]=S;
	break;
	//beq
	case 27:
		if((R[35]&0x00000001)==1)
			R[32]=S;
		else 
			R[32]++;
	break;
	//blt
	case 28:
		if((R[35]&0x00000002)==1)
			R[32]=S;
		else 
			R[32]++;
	break;
	//bgt
	case 29:
		aux1=R[35]&0x00000007;
		if(0x00000004==aux1)
			R[32]=S;
		else 
			R[32]++;
	break;
	//bne
	case 30:
		if((R[35]&0x00000001)==0)
			R[32]=S;
		else 
			R[32]++;
	break;
	//bge
	case 32:
		printf("FR = 0x%08X\n", R[35]);
		//system("pause");
		if((R[35]&0x00000001)==1){
			R[32]=S;
		}
		else if((R[35]&0x00000004)==0x4){
			//system("pause");
			R[32]=S;
		}
		else 
			R[32]++;
	break;
	//ble
	case 31:
		if((R[35]&0x00000001)==1)
			R[32]=S;
		else if((R[35]&0x00000002)==1)
			R[32]=S;
		else 
			R[32]++;
	break;
	//bzd
	case 33:
		aux1=(R[35]&0x00000008)>>3;
		if(aux1==1)
			R[32]=S;
		else
			R[32]++;
	break;
	//bnz
	case 34:
		aux1=(R[35]&0x00000008)>>3;
		if(aux1!=1)
			R[32]=S;
		else
			R[32]++;	
	break;
	//biv
	case 35:
		aux1=(R[35]&0x00000020)>>5;
		if(aux1==1){
			R[32]=S;
	}
		else{
			R[32]++;
			//printf("HERE %d \n", R[32]);
		}		
	break;
	//bni
	case 36:
		aux1=(R[35]&0x00000020)>>5;
		if(aux1!=1)
			R[32]=S;
		else
			R[32]++;	
	break;
	}
	persistR0();	

}
int main(int argc, char *argv[]){
	pilha=(unsigned int*)malloc(1000*sizeof(sizeof(unsigned int)));
	persistR0();
	cleanR();
	int_pilha[0]=0;
	int_pilha[1]=0;
	int_pilha[2]=0;
	int i =0, j, n=0;
	unsigned int* wholeWord;
	char *terminal;
	FILE *hexa;
	//char destino[40]="poxim2\0";
	//char path[40];
	wholeWord= malloc(i*sizeof(unsigned int));
	char origem[100];
	char destino[100];
	strcpy(origem,argv[1]);
	strcpy(destino,argv[2]);
	//strcat(origem, ".input");
	//strcat(destino,".output");
	//printf("\n%s\n", destino);
	printf("\n%s\n", origem);
	printf("\n%s\n", destino);
	hexa = fopen(origem, "r");
	if (hexa == NULL)  // Se houve erro na abertura
	  {
		 printf("Problemas na abertura do arquivo\n");
		 return 1;
	  }
	while(!feof(hexa)){
		i++;
		//printf("j %d\n", i);
		wholeWord= realloc(wholeWord,i*sizeof(unsigned int));
		wholeWord[i-1]=0;
		fscanf(hexa, "%X", &wholeWord[i-1]);
		//printf ("%08X\n", wholeWord[i-1]);	
	}
	unsigned int *instruction;
	printf("j %d\n", i);
	instruction =malloc(i*sizeof(unsigned int));
	terminal =malloc(n*sizeof(char));
	j=i;
	for (i=0; i<j; i++){
		instruction[i]=instrucao(wholeWord[i]);
		//printf ("%08X\n", wholeWord[i]);
	}
	char* parse;
	unsigned int E, Rz,Rx,Ry,IM16;
	unsigned int S;
	unsigned int decounter, instruc, watchdog,aux, aux1 = 0,aux2, atual, counter;
	watchdog=0;
	unsigned int trig, Sfpu, stb_fixer;
	float a, b;
	counter=0;
	i=0;
	trig =0;
	decounter =0;
	controlFpu=0;
	x=0;
	y=0;
	z=0;
	saida=fopen(destino, "w");
	printf("[START OF SIMULATION]\n");
	fprintf(saida, "[START OF SIMULATION]\n");
	/*
	#####################################################
				  Loop de execução principal
	#####################################################
	*/
	while(counter<120000){
		counter++;
		//printf("0x%08X\n", wholeWord[R[32]]);
		atual=R[32];
		parse=operacao(instruction[R[32]]);
		R[33]=wholeWord[R[32]];
		//printf ("here %08X\n", wholeWord[R[32]]);
		//printf("PC = %d\n", R[32]);
		//printf("OP = %d \n",instruction[R[32]]);
		if(wholeWord[R[32]]==0){
			printf ("here \n");
			R[32]++;
			}
		else if(parse[4] == 85){ //U U0=E U1=Rz	U2=Rx U3=Ry;
				//printf("0x%08X instruc %s\n", wholeWord[R[32]], parse);
				Rx=opXU(wholeWord[R[32]]);
				Ry=opYU(wholeWord[R[32]]);
				Rz=opZU(wholeWord[R[32]]);
				E=opEU(wholeWord[R[32]]);
				//printf("passei \n");
				//printf("Rz R%d Rx R%d Ry R%d\n", Rz, Rx, Ry);
				RspU(instruction[R[32]], Rz, Rx, Ry,E);
				//printf("Rz R%d Rx R%d Ry R%d\n",U[1], U[2], U[3]);
				excU(instruction[R[32]], Rz ,Rx, Ry,E);
				R[32]++;
				persistR0();
				//R[35]=R[35]&0xFFFFFFDF;
		}
		else if(parse[4] == 70){ //F f0=IM16 F1=Rx F2=Ry
				IM16=opIM16F(wholeWord[R[32]]);
				Rx=opxF(wholeWord[R[32]]);
				Ry=opyF(wholeWord[R[32]]);
				aux=Ry+0;
				int something=24-(8*IM16);
				RspF(instruction[R[32]], IM16, Rx, Ry);
				//stw
				if(instruction[R[32]]==22)
				{
					//printf("R[Rx]+IM16 = 0x%08X\n", R[Rx]+IM16);

					if((R[Rx]+IM16)==0x2020){
						watchdog=R[Ry];
					}
					else if((R[Rx]+IM16)==0x2203){
						controlFpu=R[Ry];
						printf("\n\nR[Ry] = 0x%08X\n\n\n", R[Ry]);
						printf("\n\nControl = 0x%08X\n\n\n", controlFpu);
						//system("pause");
					}
					else if((R[Rx]+IM16)==0x2202){
						z=R[Ry];
						printf("Z sobrescrito");
						//system("pause");
					}
					else if((R[Rx]+IM16)==0x2201){
						y=R[Ry];
						printf("\n\nR[Ry] = 0x%08X\n\n\n", R[Ry]);
						printf("\n\nY = 0x%08X\n\n\n", y);
					//	system("pause");
					}
					else if((R[Rx]+IM16)==0x2200){
						x=R[Ry];
						printf("\n\nR[Ry] = 0x%08X\n\n\n", R[Ry]);
						printf("\n\nX = 0x%08X\n\n\n", x);
						//system("pause");
					}
					else{
						wholeWord[R[Rx]+IM16]=R[Ry];
					}
				}
				//stb
				else if(instruction[R[32]]==23)
				{
					//printf("\n\ncame here\n\n");
					if((R[Rx]+IM16)==0x888B){
						n++;
						terminal=realloc(terminal,n*sizeof(char));
						terminal[n-1]=R[Ry];
						//printf("\n\nhere i put %c on terminal\n\n", terminal[n-1]);
					}
					else{
						aux=(R[Rx]+IM16)%4;
						aux2=(R[Rx]+IM16)/4;
						//printf("\n\nTHIS IS THE AUX %d\n\n", aux);
						switch(aux){
							case 3:
								printf("\n\n0x%08X\n",wholeWord[aux2]);
								wholeWord[aux2]=wholeWord[aux2]&0xFFFFFF00;
								wholeWord[aux2]=(R[Ry]&0x000000FF)+wholeWord[aux2];
								printf("\n\nMem=%d Ry eh %d seu valor eh 0x%08X, IM16 eh%d\n Como resultado foi escrito0x%08X\n",aux2, Ry, R[Ry],IM16, wholeWord[aux2]);
							break;
							case 2:
								printf("\n\n0x%08X\n",wholeWord[aux2]);
								wholeWord[aux2]=(wholeWord[aux2]&0xFFFF00FF);
								wholeWord[aux2]=((R[Ry]&0x000000FF)<<8)+wholeWord[aux2];
								printf("\n\nMem=%d Ry eh %d seu valor eh 0x%08X, IM16 eh%d\n Como resultado foi escrito0x%08X\n",aux2, Ry, R[Ry],IM16, wholeWord[aux2]);
							break;
							case 1:
								printf("\n\n0x%08X\n",wholeWord[aux2]);
								wholeWord[aux2]=(wholeWord[aux2]&0xFF00FFFF);
								wholeWord[aux2]=((R[Ry]&0x000000FF)<<16)+wholeWord[aux2];
								printf("\n\nMem=%d Ry eh %d seu valor eh 0x%08X, IM16 eh%d\n Como resultado foi escrito0x%08X\n",aux2, Ry, R[Ry],IM16, wholeWord[aux2]);
								//printf("0x%08X\n",wholeWord[Rx]);
							break;
							case 0:
								printf("\n\n0x%08X\n",wholeWord[aux2]);
								wholeWord[aux2]=(wholeWord[aux2]&0x00FFFFFF);
								wholeWord[aux2]=((R[Ry]&0x000000FF)<<24)+wholeWord[aux2];
								printf("\n\nMem=%d Ry eh %d seu valor eh 0x%08X, IM16 eh%d\n Como resultado foi escrito0x%08X\n",aux2, Ry, R[Ry],IM16, wholeWord[aux2]);
								//system("pause");
								//printf("0x%08X\n",wholeWord[Rx]);
							break;
						}
					}
				}
				//ldw
				else if (instruction[R[32]]==20){
					//printf("R[Ry]+IM16 = 0x%08X\n", R[Ry]+IM16);
					if((R[Ry]+IM16)==0x2020){
						R[Rx]=watchdog;
						}
					else if((R[Ry]+IM16)==0x2203){
						R[Rx]=controlFpu;
						printf("\n\nR[Ry] = 0x%08X\n\n\n", R[Ry]);
						printf("\n\nControl = 0x%08X\n\n\n", controlFpu);
						//system("pause");
					}
					else if((R[Ry]+IM16)==0x2202){
						if(zisint==1){
							R[Rx]=z;
						}
						else{
						memcpy(&aux, &z, sizeof (aux));
						R[Rx]=aux;
						aux=0;}
						printf("Z = 0x%08X\n", R[Rx]);
						//system("pause");
					}
					else if((R[Ry]+IM16)==0x2201){
						R[Rx]=y;
						xisfloat=0;
						printf("\n\nR[Ry] = 0x%08X\n\n\n", R[Ry]);
						printf("\n\nY = 0x%08X\n\n\n", y);
						//system("pause");
					}
					else if((R[Ry]+IM16)==0x2200){
						R[Rx]=x;
						yisfloat=0;
						printf("\n\nR[Ry] = 0x%08X\n\n\n", R[Ry]);
						printf("\n\nX = 0x%08X\n\n\n", x);
						//system("pause");
					}
					else{
						R[Rx]=wholeWord[R[Ry]+IM16];
						//printf("R%d = 0x%08X\n", Rx, R[Rx]);
					
					}
				}	
				//ldb 
				else if (instruction[R[32]]==21){
					if(R[Ry]==0x888B){
						R[Rx]=terminal[n-1];
						printf("0x%08X\n",terminal[n-1]);
					}
					else{
						aux=(R[Ry]+IM16)%4;
						aux2=(R[Ry]+IM16)/4;
/* 						printf("\n\nTHIS IS THE RY %d, THIS IS THE AUX %d AND THIS IS THE INDEX %d\n\n", R[Ry],aux, aux2);
 */						switch(aux){
							case 3:
								R[Rx]=(wholeWord[aux2]&0x000000FF);
/* 								printf("0x%08X\n",R[Rx]);
 */							break;
							case 2:
								R[Rx]=(wholeWord[aux2]&0x0000FF00)>>8;
/* 								printf("\n\n0x%08X\n",R[Rx]);
 */							break;
							case 1:
								R[Rx]=(wholeWord[aux2]&0x00FF0000)>>16;
/* 								printf("\n\n0x%08X\n",R[Rx]);
 */							break;
							case 0:
								R[Rx]=(wholeWord[aux2]&0xFF000000)>>24;
/* 								printf("\n\nPrimeiro bit 0x%08X\n",R[Rx]);
 */							break;
						}
					}
				}
				//call
				else if (instruction[R[32]]==37){
					//printf("IM16 0x%04X\n", IM16);
					R[Rx]=R[32]+1;
					aux1=Ry+IM16;
				}
				//ret
				else if(instruction[R[32]]==38){
					aux1=R[Rx];
					if(int_pilha[0]>0){
						int_pilha[0]--;
					}
				}
				//isr
				else if(instruction[R[32]]==39){
					R[Rx]=R[37];
					R[Ry]=R[36];
					aux1=IM16;
				}
				//reti
				else if(instruction[R[32]]==40){
					aux1=R[Rx];
					if(int_pilha[1]>0){
						int_pilha[1]--;
					}
					else if(int_pilha[2]>0){
						int_pilha[2]--;
					}
				}
				excF(instruction[R[32]], IM16 , Rx, Ry);
				//call pt2
				if(instruction[R[32]]==37){
					R[32]=aux1;
					//printf("PC %d \n", R[32]);
					//printf("0x%08X\n", wholeWord[R[32]]);
				}
				//ret pt2
				else if(instruction[R[32]]==38){
					R[32]=aux1;
					//printf("PC %d \n", R[32]);
					//printf("0x%08X\n", wholeWord[R[32]]);
				}
				//isr pt2
				else if(instruction[R[32]]==39){
					R[32]=aux1;	
					printf("\n\nR[32]=%d\n\n", R[32]);
				}
				//reti pt2
				else if(instruction[R[32]]==40){
					R[32]=aux1;
					printf("PC %d \n", R[32]);
					//system("pause");
					//printf("0x%08X\n", wholeWord[R[32]]);
				}
				else{
					R[32]++;
				}
				//R[35]=R[35]&0xFFFFFFDF;
		}
		else if(parse[4] == 83){ //S
				//printf("Palavra 0x%08X\n",wholeWord[R[32]]);
				instruc=instruction[R[32]];
				if(instruction[R[32]]==63)
					{
						S=opS(wholeWord[R[32]]);
						if(S==0){
							fprintf(saida, "int 0\n[S] CR = 0x00000000, PC = 0x00000000\n");
							printf("int 0\n[S] CR = 0x00000000, PC = 0x00000000\n");
							break;
						}
						else{
						R[36]=S;
						R[37]=R[32]+1;
						R[32]=3;
						}
					}
				else{	
					S=opS(wholeWord[R[32]]);
					RspS(instruction[R[32]],S);
					}
				excS(instruc,S);
				//R[35]=R[35]&0xFFFFFFDF;
		}
		else{	
				printf("[INVALID INSTRUCTION @ 0x%08X]\n", (R[32]<<2));
				fprintf(saida, "[INVALID INSTRUCTION @ 0x%08X]\n", (R[32]<<2));
				R[37]=R[32]+1;
				R[36]=R[32];
				R[32]=3;
				R[35]=R[35]|0x00000020;
				//system("pause");
				int_pilha[0]++;
		}
		//Condicional de interrupcao
		if((R[35]&0x00000040)==0x40){
			printf("TRIG %d \n int_pilha[0] %d int pilha 1 %d int pilha 2  %d \n decounter %d\n", trig, int_pilha[0], int_pilha[1], int_pilha[2], decounter);
			//system("pause");
			//Divisao por zero
			if(((R[35]&0x00000008)==0x8)&&(R[36]!=1)){
				R[37]=R[32];
				R[32]=3;
				R[36]=1;
				int_pilha[0]++;
			}
			//watchdog
			else if(((watchdog&0x80000000)==0x80000000)&&((watchdog&0x7FFFFFFF)<=0)&&(int_pilha[0]<1)){ //
				printf("[HARDWARE INTERRUPTION 1]\n");
				//system("pause");
				fprintf(saida,"[HARDWARE INTERRUPTION 1]\n");
				R[37]=R[32];
				R[36]=0xE1AC04DA;
				watchdog=1;
				R[32]=1;
				int_pilha[1]=1;
			}
			//fpu
			else if((decounter==0)&&(int_pilha[1]<1)&&(int_pilha[2]<1)&&trig==1&&(int_pilha[0]<1)){ //
					R[37]=R[32];
					R[36]=0x01EEE754;
					R[32]=2;
					printf("[HARDWARE INTERRUPTION 2]\n");
					fprintf(saida, "[HARDWARE INTERRUPTION 2]\n");
					fpu();
					//controlFpu=controlFpu&0xFFFFFFE0;
					trig=0;
					int_pilha[2]=1;
				}
		}
				
		//fpu decounter and operation setter
		if((trig==0)&&(decounter ==0)&&((0x0000001F&controlFpu)!=0)){
			if(((controlFpu&0x0000001F)>9 ||(controlFpu&0x0000001F)==5 ||(controlFpu&0x0000001F)==6 
			||(controlFpu&0x0000001F)==7 || (controlFpu&0x0000001F) ==8 || (controlFpu&0x0000001F) == 9)
				){
					decounter=0;
					trig=1;
				}
			else {
				if((xisfloat==1) && (yisfloat==1)){
					b=y;
					a=x;
					memcpy(&aux1, &b, sizeof (aux1));
					memcpy(&aux, &a, sizeof (aux));
				}
				else if(yisfloat==1){
						a=x;	
						memcpy(&aux, &a, sizeof (aux));
						aux1=y;
					}
				else if(xisfloat==1){
						b=y;
						memcpy(&aux1, &b, sizeof (aux1));
						aux=x;
					}
				else{
						a=x;	
						memcpy(&aux, &a, sizeof (aux));
						b=y;
						memcpy(&aux1, &b, sizeof (aux1));
					}
				//printf("\n\naux 1 eh 0x%08X e x eh 0x%08X a eh %f\n\n", aux,x, a);
				//printf("\n\naux 2 eh 0x%08X e y eh 0x%08X b eh %f\n\n", aux1,y, b);
				aux=(aux&0x7F800000)>>23;
				aux1=(aux1&0x7F800000)>>23;
				decounter = abs(aux1-aux);
				trig=1;
				printf("parametro x %d parametro y %d \n Contador setado em %d\n", aux1, aux, decounter);
				//system("pause");
				}
			}
		else if(decounter>0){
			decounter--;
			}
		
		//watchdog decounter
		if((watchdog&0x7FFFFFFF)>0)
			watchdog--;
		//Sinalizador de interrupcao
		if(R[32]==3){
			printf("[SOFTWARE INTERRUPTION]\n");
			fprintf(saida, "[SOFTWARE INTERRUPTION]\n");
			}	
	}
	printf("[TERMINAL]\n");
	fprintf(saida, "[TERMINAL]\n");
	i=0;
	while(i<n){
		printf("%c",terminal[i]);
		fprintf(saida,"%c",terminal[i]);
		i++;
	}
	fprintf(saida,"\n[END OF SIMULATION]\n");
	printf("\n[END OF SIMULATION]\n");
	fclose(saida);
	fclose(hexa);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long R[35]; 
/* 0-31 Registradores de proposito geral
	 32 PC - Controle de Fluxo
	 33 IR - Instrucao atual
	 34 ER - Registrador de extensao
	 35 FR - Dados de comparacoes e info do processador*/

//R0 sempre zero
void cleanR(){
	char i;
	for(i=0; i<35; i++){
		R[i]=0;
	}
}
void persistR0(){
	R[0]=0;}
//Metodo de retorno da operacao utilizada
char* operacao (long instruction){
	switch(instruction){
		case 0:
			return "add U\0";
		case 1:
			return "addiF\0";
		case 2:
			return "sub U\0";
		case 3:
			return "subiU\0";
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
			return "ori U\0";
		case 18:
			return "xor U\0";
		case 19:
			return "xoriU\0";
		case 20:
			return "ldw F\0";
		case 21:
			return "ldb F\0";
		case 22:
			return "stw F\0";
		case 23:
			return "stb F\0";
		case 24:
			return "erroE\0";
		case 25:
			return "erroE\0";
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
			return "erroE\0";
		case 34:
			return "erroE\0";
		case 35:   
			return "erroE\0";
		case 63:
			return "int S\0";
		default: 
			return "erroE\0";}


}

//retorna a instrução
long instrucao(long wholeWord){
	int instruction=(wholeWord & 0xFC000000)>>26;
	return instruction;
}

//Operacoes tipo U
long* opU(long instruction, long wholeWord){
	char E=(wholeWord&0x00038000)>>15;
	//printf("E: %d ", E);
	long Rz=(wholeWord&0x00007C00)>>11;
	//printf("Rz: %d ", Rz);
	long Rx=(wholeWord&0x000003E0)>>05;
	//printf("Rx: %d ", Rx);
	long Ry=(wholeWord&0x0000001F);
	//printf("Ry: %d \n", Ry);
	long U[4];
	U[0]=E;
	U[1]=Rz;
	U[2]=Rx;
	U[3]=Ry;
	persistR0();
	return U;
}
//Operacoes tipo F
long* opF(long wholeWord){
	long IM16=(wholeWord&0x03FFFC00)>>10;
	//printf("IM16: %d ", IM16);
	long Rx=  (wholeWord&0x000003E0)>>05;
	//printf("Rx: %d ", Rx);
	long Ry=  (wholeWord&0x0000001F);
	//printf("Ry: %d \n", Ry);
	long F[3];
	F[0]=IM16;
	F[1]=Rx;
	F[2]=Ry;
	persistR0();
	return F;
}
//Operacoes tipo S
long opS(long wholeWord){
	long IM16=(wholeWord&0x03FFFFFF)>>10;
	//printf("IM16: %d \n", IM16);
	persistR0();
	return IM16;
}
int main(){
	persistR0();
	cleanR();
	int i =0, j;
	long wholeWord[1000];
	FILE *hexa;
	hexa = fopen("1_factorial.hex", "r");
	if (hexa == NULL)  // Se houve erro na abertura
	  {
		 printf("Problemas na abertura do arquivo\n");
		 return;
	  }
	while(!feof(hexa)){
		fscanf(hexa, "%x", &wholeWord[i]);  // o 'fgets' lê até 99 caracteres ou até o '\n'
		i++;
	}
	long *instruction;
	instruction =malloc(i*sizeof(long));
	fclose(hexa);
	j=i;
	for (i=0; i<j; i++){
		instruction[i]=instrucao(wholeWord[i]);
	}
	char* parse;
	long* U;
	long* F;
	long S;
	for (i=0; i<j; i++){
		parse=operacao(instruction[i]);
		//printf("%d %c\n", parse[4], parse[4]);
		if(parse[4] == 85){ //U
				U=opU(instruction[i], wholeWord[i]);	
				printf("%s E: %d Rz: %d Rx: %d Ry: %d \n", parse, U[0],U[1],U[2],U[3]);
		}
		else if(parse[4] == 70){ //F{
				F=opF(wholeWord[i]);
				printf("%s IM16: %d Rx: %d Ry: %d \n", parse, F[0],F[1],F[2]);
		}
		else if(parse[4] == 83){ //S
				S=opS(wholeWord[i]);
				printf("%s IM16: %d \n", parse, S);
		}
		else{	
				printf("ERRO \n");
		break;
		}
	}
}

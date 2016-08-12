#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
long instrucao(long wholeWorld){
	int instruction=(wholeWorld & 0xFC000000)>>26;
	return instruction;
}
int main(){
	//long *linhaComando;
	//linhaComando = (long *)malloc (sizeof (long));
	int i =0, j;
	long Linha[1000];
	char* coding[30];
	int result;
	FILE *hexa;
	hexa = fopen("1_factorial.hex", "r");
	if (hexa == NULL)  // Se houve erro na abertura
	  {
		 printf("Problemas na abertura do arquivo\n");
		 return;
	  }
	while(!feof(hexa)){
		fscanf(hexa, "%x", &Linha[i]);  // o 'fgets' lê até 99 caracteres ou até o '\n'
		i++;
	}
	long *instruction;
	instruction =malloc(i*sizeof(long));
	fclose(hexa);
	printf("Nro de elementos lidos: %d\n", i);
	j=i;
	for (i=0; i<j; i++)
		printf("%x\n", Linha[i]);
	for (i=0; i<j; i++){
		instruction[i]=instrucao(Linha[i]);
		//printf("%x\n", instruction[i]);
		//printf("Linha %d\n", i);
		//printf("%s \n", operacao(instruction[i]));
	}
	char* parse;
	for (i=0; i<j; i++){
		parse=operacao(instruction[i]);
		//printf("%d %c\n", parse[4], parse[4]);
		if(parse[4] == 85) //U
				printf("%s \n", parse);
		else if(parse[4] == 70) //F
				printf("%s \n", parse);
		else if(parse[4] == 83) //S
				printf("%s \n", parse);
		/*switch (parse[4]){
			case 85: //U
				printf("%s \n", parse);
			case 70: //F
				printf("%s \n", parse);
			case 83: //S
 				printf("%s \n", parse);
			default:*/
		else{	
				printf("ERRO \n");
		break;
		}
		
	}
	
}

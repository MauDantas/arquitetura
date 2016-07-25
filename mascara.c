#include <stdio.h>

//Metodo de retorno da operacao utilizada

/*Intrucoes de impressao
unsigned int a=0;
	int b=0;
	a=a-1;
	b=b-1;
	printf("A=%i, B=%u \n", a, b);
	printf("A=0x%08x, B=0x%08x \n", a, b);
*/
char* operacao (int instruction){


}
//retorna a instrução
int instrucao(int wholeWorld){
	int instruction=(0x68000004 & 0xFC000000)>>26;
	return instruction;
}
int main(){
	
	return 0;
}

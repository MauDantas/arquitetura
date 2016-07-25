#include <stdio.h>

//Metodo de retorno da operacao utilizada


char* operacao (int instruction){
	/*switch(instruction)
		case 0:
		break
		case 1:
		break
		case 2:
		break
		case 3:
		break
		case 4:
		break
		case 5:
		break
		case 6:
		break
		case 7:
		break
		case 8:
		break
		case 9:
		break
		case 10:
		break
		case 11:
		break
		case 12:
		break
		case 13:
		break
		case 14:
		break
		case 15:
		break
		case 16:
		break
		case 17:
		break
		case 18:
		break
		case 19:
		break
		case 20:
		break
*/
}
//retorna a instrução
int instrucao(int wholeWorld){
	int instruction=(wholeWorld & 0xFC000000)>>26;
	return instruction;
}
int main(){
	
}

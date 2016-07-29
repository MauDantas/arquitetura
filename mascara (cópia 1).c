#include <stdio.h>

//Metodo de retorno da operacao utilizada


char* operacao (int instruction){
	switch(instruction){
		case 0:
			return "add U";
		case 1:
			return "addiF";
		case 2:
			return "sub U";
		case 3:
			return "subiU";
		case 4:
			return "mul U";
		case 5:
			return "muliF";
		case 6:
			return "div U";
		case 7:
			return "diviF";
		case 8:
			return "cmp U";
		case 9:
			return "cmpiF";
		case 10:
			return "shl U";
		case 11:
			return "shr U";
		case 12:
			return "and U";
		case 13:
			return "andiF";
		case 14:
			return "not U";
		case 15:
			return "notiF";
		case 16:
			return "or  U";
		case 17:
			return "ori U";
		case 18:
			return "xor U";
		case 19:
			return "xoriU";
		case 20:
			return "ldw F";
		case 21:
			return "ldb F";
		case 22:
			return "stw F";
		case 23:
			return "stb F";
		case 24:
			return "erroE";
		case 25:
			return "erroE";
		case 26:
			return "erroE";
		case 27:
			return "beq S";
		case 28:
			return "blt S"; 
		case 29:
			return "bgt S";
		case 30:
			return "bne S";
		case 31:   
			return "ble S";
		case 32:
			return "bge S"; 
		case 33:
			return "erroE";
		case 34:
			return "erroE";
		case 35:   
			return "erroE";
		case 63:
			return "int S";
		default: 
			return "erroE";}


}
//retorna a instrução
int instrucao(int wholeWorld){
	int instruction=(wholeWorld & 0xFC000000)>>26;
	return instruction;
}
int main(){
	
}

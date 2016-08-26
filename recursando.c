#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>

unsigned long R[36];
char flag1=0; 
/* 0-31 Registradores de proposito geral
	 32 PC - Controle de Fluxo
	 33 IR - Instrucao atual
	 34 ER - Registrador de extensao
	 35 FR - Dados de comparacoes e info do processador*/
//todos registradores são zerados
void cleanR(){
	char i;
	for(i=0; i<36; i++){
		R[i]=0;
	}
}

//R0 sempre zero
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
		case 37:   
			return "callF\0";
		case 38:   
			return "ret F\0";	
		case 63:
			return "int S\0";
		default: 
			return "erroE\0";}


}

//retorna a instrução
long instrucao(unsigned long wholeWord){
	int instruction=(wholeWord & 0xFC000000)>>26;
	return instruction;
}
//printer de execucao U
void excU(long instruction, long Rz , long Rx, long Ry, long extensao){
	switch (instruction){
		//add
		case 0:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<4);
			Rz=Rz+((extensao&0x00000004)<<4);
			if(Rx<32 && Ry<32 && Rz<32){
				//printf("Ry R%d\n", Ry);
				printf("add r%d, r%d, r%d \n",Rz,Rx,Ry);
				printf("[U] FR = 0x%08X, R%d = R%d + R%d = 0x%08X\n", R[35],Rz,Rx,Ry,R[Rz]);
			}
			else if(Rx == 32 && Rz == 32 && Ry ==32){
				printf("add pc, pc, pc \n");
				printf("[U] FR = 0x%08X, PC = PC + PC = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 33 && Rz == 32 && Ry ==32){
				printf("add pc, ir, pc \n");
				printf("[U] FR = 0x%08X, PC = IR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 32 && Ry ==32){
				printf("add pc, er, pc \n");
				printf("[U] FR = 0x%08X, PC = ER + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 32 && Ry ==32){
				printf("add pc, fr, pc \n");
				printf("[U] FR = 0x%08X, PC = FR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 32 && Rz == 33 && Ry ==32){
				printf("add ir, pc, pc \n");
				printf("[U] FR = 0x%08X, IR = PC + PC = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 34 && Ry ==32){
				printf("add er, pc, pc \n");
				printf("[U] FR = 0x%08X, ER = PC + PC = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 35 && Ry ==32){
				printf("add fr, pc, pc \n");
				printf("[U] FR = 0x%08X, FR = PC + PC = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 32 && Ry ==33){
				printf("add pc, pc, ir \n");
				printf("[U] FR = 0x%08X, PC = PC + IR = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 32 && Ry ==34){
				printf("add pc, pc, er \n");
				printf("[U] FR = 0x%08X, PC = PC + ER = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 32 && Ry ==35){
				printf("add pc, pc, pc \n");
				printf("[U] FR = 0x%08X, PC = PC + FR = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 33 && Ry ==33){
				printf("add ir, pc, ir \n");
				printf("[U] FR = 0x%08X, IR = PC + IR = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 34 && Ry ==33){
				printf("add er, pc, ir \n");
				printf("[U] FR = 0x%08X, ER = PC + IR = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 35 && Ry ==33){
				printf("add fr, pc, ir \n");
				printf("[U] FR = 0x%08X, FR = PC + IR = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 33 && Rz == 33 && Ry ==32){
				printf("add ir, ir, pc \n");
				printf("[U] FR = 0x%08X, PC = IR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 34 && Ry ==32){
				printf("add er, ir, pc \n");
				printf("[U] FR = 0x%08X, PC = IR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 35 && Ry ==32){
				printf("add fr, ir, pc \n");
				printf("[U] FR = 0x%08X, PC = IR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 32 && Ry ==33){
				printf("add pc, ir, pc \n");
				printf("[U] FR = 0x%08X, PC = IR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 32 && Ry ==34){
				printf("add pc, ir, pc \n");
				printf("[U] FR = 0x%08X, PC = IR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 32 && Ry ==35){
				printf("add pc, ir, fr \n");
				printf("[U] FR = 0x%08X, PC = IR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 32 && Rz == 33 && Ry ==34){
				printf("add ir, pc, er \n");
				printf("[U] FR = 0x%08X, IR = PC + ER = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 34 && Ry ==34){
				printf("add er, pc, er \n");
				printf("[U] FR = 0x%08X, ER = PC + ER = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 35 && Ry ==34){
				printf("add fr, pc, er \n");
				printf("[U] FR = 0x%08X, FR = PC + ER = 0x%08X\n", R[35],R[Rz]);
			}
			else if(Rx == 32 && Rz == 33 && Ry ==35){
				printf("add ir, pc, fr \n");
				printf("[U] FR = 0x%08X, IR = PC + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 32 && Rz == 34 && Ry ==35){
				printf("add er, pc, fr \n");
				printf("[U] FR = 0x%08X, ER = PC + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 32 && Rz == 35 && Ry ==35){
				printf("add fr, pc, fr \n");
				printf("[U] FR = 0x%08X, FR = PC + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 32 && Rz == 33 && Ry ==35){
				printf("add ir, pc, fr \n");
				printf("[U] FR = 0x%08X, IR = PC + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 32 && Rz == 34 && Ry ==35){
				printf("add er, pc, fr \n");
				printf("[U] FR = 0x%08X, ER = PC + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 33 && Ry ==33){
				printf("add ir, ir, ir \n");
				printf("[U] FR = 0x%08X, IR = IR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 34 && Ry ==33){
				printf("add er, ir, ir \n");
				printf("[U] FR = 0x%08X, ER = IR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 35 && Ry ==33){
				printf("add fr, ir, ir \n");
				printf("[U] FR = 0x%08X, FR = IR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 33 && Ry ==34){
				printf("add ir, ir, er \n");
				printf("[U] FR = 0x%08X, IR = IR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 34 && Ry ==34){
				printf("add er, ir, er \n");
				printf("[U] FR = 0x%08X, ER = IR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 35 && Ry ==34){
				printf("add fr, ir, er \n");
				printf("[U] FR = 0x%08X, FR = IR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 33 && Ry ==35){
				printf("add ir, ir, fr \n");
				printf("[U] FR = 0x%08X, IR = IR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 34 && Ry ==35){
				printf("add er, ir, fr \n");
				printf("[U] FR = 0x%08X, ER = IR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 33 && Rz == 35 && Ry ==35){
				printf("add fr, ir, fr \n");
				printf("[U] FR = 0x%08X, fr = IR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 33 && Ry ==32){
				printf("add ir, er, pc \n");
				printf("[U] FR = 0x%08X, PC = ER + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 34 && Ry ==32){
				printf("add er, er, pc \n");
				printf("[U] FR = 0x%08X, PC = ER + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 35 && Ry ==32){
				printf("add fr, er, pc \n");
				printf("[U] FR = 0x%08X, PC = ER + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 32 && Ry ==33){
				printf("add pc, er, ir \n");
				printf("[U] FR = 0x%08X, PC = ER + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 33 && Ry ==33){
				printf("add ir, er, ir \n");
				printf("[U] FR = 0x%08X, IR = IR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 34 && Ry ==33){
				printf("add er, er, ir \n");
				printf("[U] FR = 0x%08X, ER = ER + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 35 && Ry ==33){
				printf("add fr, er, ir \n");
				printf("[U] FR = 0x%08X, FR = ER + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 32 && Ry ==34){
				printf("add pc, er, er \n");
				printf("[U] FR = 0x%08X, PC = ER + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 33 && Ry ==34){
				printf("add ir, er, er \n");
				printf("[U] FR = 0x%08X, PC = ER + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 34 && Ry ==34){
				printf("add er, er, er \n");
				printf("[U] FR = 0x%08X, ER = ER + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 35 && Ry ==34){
				printf("add fr, er, er \n");
				printf("[U] FR = 0x%08X, fr = ER + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 34 && Ry ==35){
				printf("add fr, er, fr \n");
				printf("[U] FR = 0x%08X, ER = ER + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 35 && Ry ==35){
				printf("add fr, er, fr \n");
				printf("[U] FR = 0x%08X, FR = ER + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 33 && Ry ==35){
				printf("add ir, er, fr \n");
				printf("[U] FR = 0x%08X, IR = ER + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 34 && Rz == 32 && Ry ==35){
				printf("add fr, er, fr \n");
				printf("[U] FR = 0x%08X, PC = ER + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 33 && Ry ==32){
				printf("add ir, fr, pc \n");
				printf("[U] FR = 0x%08X, IR = FR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 34 && Ry ==32){
				printf("add er, fr, pc \n");
				printf("[U] FR = 0x%08X, ER = FR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 35 && Ry ==32){
				printf("add fr, fr, pc \n");
				printf("[U] FR = 0x%08X, FR = FR + PC = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 35 && Ry ==33){
				printf("add fr, fr, ir \n");
				printf("[U] FR = 0x%08X, FR = FR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 34 && Ry ==33){
				printf("add er, fr, pc \n");
				printf("[U] FR = 0x%08X, ER = FR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 33 && Ry ==33){
				printf("add ir, fr, ir \n");
				printf("[U] FR = 0x%08X, IR = FR + IR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 32 && Ry ==33){
				printf("add pc, fr, ir \n");
				printf("[U] FR = 0x%08X, pc = FR + ir = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 35 && Ry ==34){
				printf("add fr, fr, er \n");
				printf("[U] FR = 0x%08X, FR = FR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 34 && Ry ==34){
				printf("add er, fr, er \n");
				printf("[U] FR = 0x%08X, ER = FR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 33 && Ry ==34){
				printf("add ir, fr, er \n");
				printf("[U] FR = 0x%08X, IR = FR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 32 && Ry ==34){
				printf("add pc, fr, er \n");
				printf("[U] PC = 0x%08X, FR = FR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 35 && Ry ==34){
				printf("add fr, fr, er \n");
				printf("[U] FR = 0x%08X, FR = FR + ER = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 35 && Ry ==35){
				printf("add fr, fr, fr \n");
				printf("[U] FR = 0x%08X, FR = FR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 34 && Ry ==35){
				printf("add er, fr, fr \n");
				printf("[U] FR = 0x%08X, ER = FR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 33 && Ry ==35){
				printf("add ir, fr, fr \n");
				printf("[U] FR = 0x%08X, IR = FR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			else if(Rx == 35 && Rz == 32 && Ry ==35){
				printf("add pc, fr, fr \n");
				printf("[U] FR = 0x%08X, pc = FR + FR = 0x%08X\n", R[35],R[Rx]);
			}
			
			
			
		break;
		//sub
		case 2:
			printf("sub r%d, r%d, r%d \n",Rz,Rx,Ry);
			printf("[U] FR = 0x%08X, R%d = R%d - R%d = 0x%08X\n", R[35],Rz,Rx,Ry,R[Rz]);	
		break;
		//mul
		case 4:
			printf("mul r%d, r%d, r%d \n",Rz,Rx,Ry);
			printf("[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d * R%d = 0x%08X\n", R[35], R[34],Rz,Rx,Ry,R[Rz]);
		break;
		//div (DUVIDA - SLIDE 5)
		case 6:
			printf("sub r%d, r%d, r%d \n",Rz,Rx,Ry);
			printf("[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d / R%d = 0x%08X\n", R[35],R[34],Rz,Rx,Ry,R[Rz]);
		break;
		//cmp (DUVIDA - SLIDE 5)
		case 8:
			printf("cmp r%d, r%d\n", Rx,Ry);
			printf("[U] FR = 0x%08X\n",R[35]);
		break;
		//shl
		case 10:
			if(Rz==0){
				printf("shl r%d, r%d, %d\n", Rz, Rx,(Ry+32));
				printf("[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+33),R[Rz] );
			}
			else{
				printf("shl r%d, r%d, %d\n", Rz, Rx,Ry);
				printf("[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+1),R[Rz] );
			}
				
		break;
		//shr
		case 11:
			printf("shr r%d, r%d, %d\n", Rz,Rx,Ry);
			printf("[U] ER = 0x%08X, R%d = R%d >> %d = 0x%08X\n",R[34], Rz,Rx,Ry,R[Rz] );
		break;
		//and
		case 12:
			printf("and r%d, r%d, %d\n",Rz,Rx,Ry);
			printf("[U] R%d = R%d & R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
		break;
		//not
		case 14:
			printf("not r%d, %d\n",Rx,Ry);
			printf("[U] R%d = ~R%d = 0x%08X\n", Rx,Ry,R[Rx] );
		break;
		//or
		case 16:
			printf("or r%d, r%d, %d\n",Rz,Rx,Ry);
			printf("[U] R%d = R%d | R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
		break;
		//xor
		case 18: 
			printf("xor r%d, r%d, %d\n",Rz,Rx,Ry);
			printf("[U] R%d = R%d ^ R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
		break;
		//push
			printf("push r%d, r%d", Rx, Ry);
		    printf("[U] MEM[R%d--] = R%d = 0x%08X\n", Rx,Ry,R[Ry]);
		}
}
//printer de execucao de F
void excF(long instruction, long IM16 , long Rx, long Ry){
	switch (instruction){
		//addi
		case 1:
			//printf("Ry R%d\n", Ry);
			printf("addi r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("[F] FR = 0x%08X, R%d = R%d + 0x%04X = 0x%08X\n", R[35],Rx,Ry,IM16,R[Rx]);
		break;
		//muli
		case 5:
			printf("muli r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d * 0x%04X = 0x%08X\n", R[35], R[34],Rx,Ry,IM16,R[Rx]);
		break;
		//divi (DUVIDA - SLIDE 5)
		case 7:
			printf("divi r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d / 0x%04X = 0x%08X\n", R[35],R[34],Rx,Ry,IM16,R[Rx]);
		break;
		//cmpi (DUVIDA - SLIDE 5)
		case 9:
			printf("cmpi r%d, %d\n", Rx,IM16);
			printf("[F] FR = 0x%08X\n",R[35]);
		break;
		//andi
		case 13:
			printf("andi r%d, r%d, %d\n",Rx,Ry,IM16);
			printf("[F] R%d = R%d & 0x%04X = 0x%08X\n", Rx,Ry, IM16,R[Rx] );
		break;
		//noti
		case 15:
			printf("noti r%d, 0x%X\n",Rx,IM16);
			printf("[F] R%d = ~0x%04X = 0x%08X\n", Rx,IM16,R[Rx] );
		break;
		//ori
		case 17:
			printf("ori r%d, r%d, %d\n",Rx,Ry,IM16);
			printf("[F] R%d = R%d | 0x%04X = 0x%08X\n", Rx,Ry,IM16,R[Rx] );
		break;
		//xori
		case 19: 
			printf("xori r%d, r%d, %d\n",Rx,Ry,IM16);
			printf("[F] R%d = R%d ^ 0x%08X = 0x%X\n", Rx,Ry,IM16,R[Rx]);
		break;
		//ldw
		case 20:
			printf("ldw r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			printf("[F] R%d = MEM[(R%d + 0x%04X) << 2] = 0x%08X\n", Rx,Ry,IM16,R[Rx]);
		break;
		
		//ldb
		case 21:
			printf("ldb r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			printf("[F] R%d = MEM[R%d + 0x%04X] = 0x%02X\n", Rx,Ry,IM16,R[Rx]);
		break;
		//stw
		case 22:
			printf("stw r%d, %04X, r%d\n", Rx,IM16,Ry);
			printf("[F] MEM[(R%d + 0x%04X) << 2]= R%d = 0x%08X\n", Rx,IM16,Ry,R[Ry]);
		break;
		//stb
		case 23:
			printf("stb r%d, %d, r%d\n", Rx,IM16,Ry);
			printf("[F] MEM[R%d + 0x%04X]= R%d = 0x%02X\n", Rx,IM16,Ry,(0x000000FF&R[Ry]));
		break;
		//call
		case 37:
			persistR0();
			printf("call r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			printf("[F] R%d = (PC + 4) >> 2 = 0x%08X, PC = (R%d + 0x%04X) << 2 = 0x%08x\n", Rx,R[Rx],Ry,IM16, ((Ry+IM16)<<2));
		break;
		//ret
		case 38:
			printf("ret r%d \n", Rx,Ry,IM16);
			printf("[F] PC = Rx << 2 = 0x%08X\n",(R[Rx]<<2));
		break;
		}
}
//printer de execucao de S
void excS(long instruction, long S){
	int PC=R[32]*4;
	switch (instruction){
	//bun
	case 26:
		printf("bun 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	//beq
	case 27:
		printf("beq 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	//blt
	case 28:
		printf("blt 0x%X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	//bgt
	case 29:
		printf("bgt 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	//bne
	case 30:
		printf("bne 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	//bge
	case 32:
		printf("bge 0x%X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	//ble
	case 31:
		printf("ble 0x%08X\n", S);
		printf("[S] PC = 0x%08X\n", PC);
	break;
	}
}
//Parametros para operacoes tipo U
long* opU(long wholeWord){
	char E=(wholeWord&0x00038000)>>15;
	//printf("E: %d ", E);
	long Rz=(wholeWord&0x00007C00)>>10;
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
//Parametros para operacoes tipo F
long opxF(long wholeWord){
	long Rx=  (wholeWord&0x000003E0)>>05;
	persistR0();
	return Rx;
}
long opyF(long wholeWord){
	long Ry=  (wholeWord&0x0000001F);
	return Ry;
}
long opIM16F(long wholeWord){
	long IM16=(wholeWord&0x03FFFC00)>>10;
	return IM16;
}

//Parametros para operacoes tipo S
long opS(long wholeWord){
	long IM16=(wholeWord&0x03FFFFFF);
	//printf("IM16: %d \n", IM16);
	persistR0();
	return IM16;
}

//modificacoes feitas por instrucoes tipo U
void RspU(unsigned long instruction, unsigned long Rz, unsigned long Rx, unsigned long Ry){
	unsigned long aux1, aux2;
	unsigned long aux3;
	long aux4;
	long aux5;
	switch (instruction){
		//add
		case 0:
			aux1=R[Rx];
			aux2=R[Ry];
			R[Rz]=R[Rx]+R[Ry];
			if((aux1+aux2)>0xFFFFFFFF||(R[Rx]+R[Ry])>0x7FFFFFFF)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
			else{
				R[35]=R[35]&(0xFFFFFFEF);
			}
		break;
		//sub
		case 2:
			aux1=R[Rx];
			aux2=R[Ry];
			R[Rz]=R[Rx]-R[Ry];
			if((R[Rx]-R[Ry])<0x80000000)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
		break;
		//mul
		case 4:
				R[34]=0;
				R[Rz]=R[Rx]*R[Ry];		
				if((R[Ry] > (ULONG_MAX / R[Rx]))||(R[Rx] > (ULONG_MAX / R[Ry]))){
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
				}
				else{
					R[35]=R[35]&0xFFFFFFEF;
				}
				flag1=Rz;
		break;
		//div (DUVIDA - SLIDE 5)
		case 6:
			if(Ry==0)
			{
				R[35]=R[35]+0x00000008;
			}
			else 
			{
				aux3=R[Rx];
				aux4=R[Ry];
				aux5=aux3/aux4;
				R[Rz]=aux5;
				R[34]=R[Rx]%R[Ry];
				if(R[34]!=0)
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
			}
		break;
		//cmp (DUVIDA - SLIDE 5)
		case 8:
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
			//printf("The flag is %d ",flag1);
			if(Rz==0){
				R[34]=R[Rx]<<(Ry+1);
			}
			else if(flag1 == Rx){
				//printf("Rz = R%d. R%d=%X Ry=%d ",Rz,Rx,R[Rx],Ry);
				R[34]=(R[34]<<(Ry+1))+(R[Rx]>>(32-(Ry+1)));
				R[Rz]=R[Rx]<<(Ry+1);
				//printf ("Er=%X Rz=%X \n", R[34], R[Rz]);
			}
			else{
				//printf("Rz = R%d. R%d=%X Ry=%d ",Rz,Rx,R[Rx],Ry);
				R[34]=R[Rx]>>(32-(Ry+1));
				R[Rz]=R[Rx]<<(Ry+1);
				//printf ("Er=%X Rz=%X \n", R[34], R[Rz]);
				flag1=Rz;
			}
		break;
		//shr
		case 11:
			if(Rz==0){
				R[34]=0;
				R[Rz]=0;
			}
			else if(flag1 == Rx){
				R[Rz]=R[Rx]>>(Ry+1);
				aux1=R[34]<<(31-Ry);
				R[Rz]=R[Rz]+aux1;
				R[34]=R[34]>>(Ry+1);
				//printf ("Er=%X Rz=%X \n", R[34], R[Rz]);
			}
			else{
				R[34]=0;
				R[Rz]=R[Rx]>>(Ry+1);
				//printf ("Er=%X Rz=%X \n", R[34], R[Rz]);
				flag1=Rz;
			}
		break;
		//and
		case 12:
			R[Rz]=R[Rx]&R[Ry];
		break;
		//not
		case 14:
			R[Rx]=~R[Ry];
		break;
		//or
		case 16:
			R[Rz]=R[Rx]|R[Ry];
		break;
		//xor
		case 18: 
			R[Rz]=R[Rx]^R[Ry];
		break;		
		}
}

//modificacoes feitas por instrucoes tipo F
void RspF(unsigned long instruction, unsigned long IM16, unsigned long Rx, unsigned long Ry){
	unsigned long aux1, aux2;
	unsigned long aux3, aux4, aux5;
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
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
			else{
				R[35]=R[35]&(0xFFFFFFEF);
			}
			
		break;
		//subi
		case 3:
			aux1=IM16;
			aux2=R[Ry];
			R[Rx]=R[Ry]-IM16;
			if((R[Ry]-IM16)<0x80000000)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
		break;
		//muli
		case 5:
			R[34]=0;
			R[Rx]=IM16*R[Ry];		
			if(IM16 > ULONG_MAX / R[Ry]){
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;	
			}
			else{
				R[35]=R[35]&0xFFFFFFEF;
			}
				flag1=Rx;
		break;
		//divi (DUVIDA - SLIDE 5)
		case 7:
			if(IM16==0)
			{
				R[35]=R[35]+0x00000008;
			}
			else 
			{
				aux3=IM16;
				aux4=R[Ry];
				aux5=aux4/aux3;
				R[Rx]=aux5;
				R[34]=R[Ry]%IM16;
				if(R[34]!=0)
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
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
		}
		
	persistR0();
}
//modificacoes feitas por instrucoes tipo S
void RspS(unsigned long instruction, long S){
	long aux1;
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
	case 31:
		if((R[35]&0x00000001)==1)
			R[32]=S;
		else if((R[35]&0x00000004)==1)
			R[32]=S;
		else 
			R[32]++;
	break;
	//ble
	case 32:
		if((R[35]&0x00000001)==1)
			R[32]=S;
		else if((R[35]&0x00000002)==1)
			R[32]=S;
		else 
			R[32]++;
	break;
	}
	persistR0();	

}
int main(){
	persistR0();
	cleanR();
	int i =0, j;
	unsigned long wholeWord[1000];
	FILE *hexa;
	hexa = fopen("poxim1.input", "r");
	if (hexa == NULL)  // Se houve erro na abertura
	  {
		 printf("Problemas na abertura do arquivo\n");
		 return;
	  }
	while(!feof(hexa)){
		fscanf(hexa, "%X", &wholeWord[i]);  
		i++;
	}
	unsigned long *instruction;
	printf("j %d\n", i);
	instruction =malloc(i*sizeof(long));
	j=i;
	for (i=0; i<j; i++){
		instruction[i]=instrucao(wholeWord[i]);
		//printf ("here %08X\n", wholeWord[i]);
	}
	char* parse;
	unsigned long* U;
	unsigned long Rx,Ry,IM16;
	unsigned long S;
	unsigned long instruc;
	unsigned long aux, b, aux1;
	i=0;
	printf("[START OF SIMULATION]\n");
	while(1){
		parse=operacao(instruction[R[32]]);
		//printf ("here %08X\n", wholeWord[R[32]]);
		if(wholeWord[R[32]]==0){
			printf ("here \n");
			R[32]++;
			}
		else if(parse[4] == 85){ //U U0=E U1=Rz	U2=Rx U3=Ry;
				U=opU(wholeWord[R[32]]);
				//printf("Rz R%d Rx R%d Ry R%d\n", U[1], U[2], U[3]);
				RspU(instruction[R[32]], U[1], U[2], U[3]);
				//printf("Rz R%d Rx R%d Ry R%d\n",U[1], U[2], U[3]);
				excU(instruction[R[32]], U[1] ,U[2], U[3],U[0]);
				R[32]++;
				persistR0();
		}
		else if(parse[4] == 70){ //F f0=IM16 F1=Rx F2=Ry
				IM16=opIM16F(wholeWord[R[32]]);
				Rx=opxF(wholeWord[R[32]]);
				Ry=opyF(wholeWord[R[32]]);
				aux=Ry+0;
				int something=24-(8*IM16);
				RspF(instruction[R[32]], IM16, Rx, Ry);
				if(instruction[R[32]]==22)//stw
				{
					wholeWord[Rx+IM16]=R[Ry];
				}
				else if(instruction[R[32]]==23)//stb
				{
					//printf("0x%08X\n",R[Ry]);
					switch(IM16){
						case 3:
							wholeWord[Rx]=(R[Ry]&0x000000FF)+(wholeWord[Rx]&0xFFFFFF00);
							//printf("0x%08X\n",wholeWord[Rx]);
						break;
						case 2:
							wholeWord[Rx]=((R[Ry]&0x000000FF)<<8)+(wholeWord[Rx]&0xFFFF00FF);
							//printf("0x%08X\n",wholeWord[Rx]);
						break;
						case 1:
							wholeWord[Rx]=((R[Ry]&0x000000FF)<<16)+(wholeWord[Rx]&0xFF00FFFF);
							//printf("0x%08X\n",wholeWord[Rx]);
						break;
						case 0:
							wholeWord[Rx]=((R[Ry]&0x000000FF)<<24)+(wholeWord[Rx]&0x00FFFFFFF);
							//printf("0x%08X\n",wholeWord[Rx]);
						break;
					}
				}
				//ldw
				else if (instruction[R[32]]==20){
					R[Rx]=wholeWord[R[Ry]+IM16];
				}	
				//ldb 
				else if (instruction[R[32]]==21){
					//printf("b %d\n", IM16);
					//printf("b %d\n", something);
					int a=0;
					aux=R[aux];
					//printf("");
					aux=aux/4;
					aux=wholeWord[aux];
					//printf("aux 0x%08X\n",aux );
					a=aux>>something;
					a=a&0x000000FF;
					R[Rx]=a;
				}
				//call
				else if (instruction[R[32]]==37){
					//printf("IM16 0x%04X\n", IM16);
					R[Rx]=R[32]+1;
					aux1=Ry+IM16;
				}
				else if(instruction[R[32]]==38){
					aux1=R[Rx];
				}
				excF(instruction[R[32]], IM16 , Rx, Ry);
				if(instruction[R[32]]==37){
					R[32]=aux1;
				}
				else if(instruction[R[32]]==38){
					R[32]=aux1;
				}
				else{
					R[32]++;
				}
		}
		else if(parse[4] == 83){ //S
				instruc=instruction[R[32]];
				if(instruction[R[32]]==63)
					{
						printf("int 0 \n[S] CR = 0x00000000, PC = 0x00000000\n");
						printf("[END OF SIMULATION]\n");
						break;
						
					}
				else{	
					S=opS(wholeWord[R[32]]);
					RspS(instruction[R[32]],S);
					}
				excS(instruc,S);
		}
		else{	
				printf("ERRO \n");
		break;
		}
	}
	fclose(hexa);
	return 0;
}

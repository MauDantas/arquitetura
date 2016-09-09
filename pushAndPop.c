#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>

unsigned long pilha[100];
unsigned long R[36];
FILE *saida;
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
	for(i=0; i<100; i++){
		pilha[i]=0;
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
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			fprintf(saida, "add r%d, r%d, r%d \n",Rz,Rx,Ry);
			printf("add r%d, r%d, r%d \n",Rz,Rx,Ry);
			printf("[U] FR = 0x%08X, R%d = R%d + R%d = 0x%08X\n", R[35],Rz,Rx,Ry,R[Rz]);
			fprintf(saida, "[U] FR = 0x%08X, R%d = R%d + R%d = 0x%08X\n", R[35],Rz,Rx,Ry,R[Rz]);
		break;
		//sub
		case 2:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			fprintf(saida, "sub r%d, r%d, r%d \n",Rz,Rx,Ry);
			printf("sub r%d, r%d, r%d \n",Rz,Rx,Ry);
			fprintf(saida, "[U] FR = 0x%08X, R%d = R%d - R%d = 0x%08X\n", R[35],Rz,Rx,Ry,R[Rz]);
			printf("[U] FR = 0x%08X, R%d = R%d - R%d = 0x%08X\n", R[35],Rz,Rx,Ry,R[Rz]);	
		break;
		//mul
		case 4:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			fprintf(saida,"mul r%d, r%d, r%d \n",Rz,Rx,Ry );
			printf("mul r%d, r%d, r%d \n",Rz,Rx,Ry);
			fprintf(saida, "[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d * R%d = 0x%08X\n", R[35], R[34],Rz,Rx,Ry,R[Rz]);
			printf("[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d * R%d = 0x%08X\n", R[35], R[34],Rz,Rx,Ry,R[Rz]);
		break;
		//div (DUVIDA - SLIDE 5)
		case 6:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("div r%d, r%d, r%d \n",Rz,Rx,Ry);
			fprintf(saida, "div r%d, r%d, r%d \n",Rz,Rx,Ry);
			fprintf(saida,"[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d / R%d = 0x%08X\n", R[35],R[34],Rz,Rx,Ry,R[Rz] );
			printf("[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d / R%d = 0x%08X\n", R[35],R[34],Rz,Rx,Ry,R[Rz]);
		break;
		//cmp (DUVIDA - SLIDE 5)
		case 8:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			printf("cmp r%d, r%d\n", Rx,Ry);
			fprintf(saida,"cmp r%d, r%d\n", Rx,Ry);
			printf("[U] FR = 0x%08X\n",R[35]);
			fprintf(saida, "[U] FR = 0x%08X\n",R[35]);
		break;
		//shl
		case 10:
			if(Rz==0){
				printf("shl r%d, r%d, %d\n", Rz, Rx,(Ry+32));
				fprintf(saida, "[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+33),R[Rz] );
				printf("[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+33),R[Rz] );
				fprintf(saida,"[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+33),R[Rz] );
			}
			else{
				printf("shl r%d, r%d, %d\n", Rz, Rx,Ry);
				fprintf(saida,"shl r%d, r%d, %d\n", Rz, Rx,Ry );
				printf("[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+1),R[Rz] );
				fprintf(saida, "[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n",R[34], Rz,Rx,(Ry+1),R[Rz] );
			}
				
		break;
		//shr
		case 11:
			printf("shr r%d, r%d, %d\n", Rz,Rx,Ry);
			fprintf(saida,"shr r%d, r%d, %d\n", Rz,Rx,Ry);
			fprintf(saida, "[U] ER = 0x%08X, R%d = R%d >> %d = 0x%08X\n",R[34], Rz,Rx,Ry,R[Rz] );
			printf("[U] ER = 0x%08X, R%d = R%d >> %d = 0x%08X\n",R[34], Rz,Rx,Ry,R[Rz] );
		break;
		//and
		case 12:
			printf("and r%d, r%d, %d\n",Rz,Rx,Ry);
			fprintf(saida,"and r%d, r%d, %d\n",Rz,Rx,Ry);
			printf("[U] R%d = R%d & R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
			fprintf(saida,"and r%d, r%d, %d\n",Rz,Rx,Ry);
		break;
		//not
		case 14:
			printf("not r%d, %d\n",Rx,Ry);
			fprintf(saida,"not r%d, %d\n",Rx,Ry);
			printf("[U] R%d = ~R%d = 0x%08X\n", Rx,Ry,R[Rx] );
			fprintf(saida,"[U] R%d = ~R%d = 0x%08X\n", Rx,Ry,R[Rx] );
		break;
		//or
		case 16:
			printf("or r%d, r%d, %d\n",Rz,Rx,Ry);
			fprintf(saida,"or r%d, r%d, %d\n",Rz,Rx,Ry);
			printf("[U] R%d = R%d | R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
			fprintf(saida,"[U] R%d = R%d | R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
		break;
		//xor
		case 18: 
			printf("xor r%d, r%d, %d\n",Rz,Rx,Ry);
			fprintf(saida, "xor r%d, r%d, %d\n",Rz,Rx,Ry);
			printf("[U] R%d = R%d ^ R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
			fprintf(saida,"[U] R%d = R%d ^ R%d = 0x%08X\n", Rz,Rx,Ry,R[Rz] );
		break;
		//push
		case 24:
			printf("push r%d, r%d\n", Rx, Ry);
			fprintf(saida, "push r%d, r%d\n", Rx, Ry);
			printf("[U] MEM[R%d--] = R%d = 0x%08X\n",Rx, Ry,R[Ry]);
			fprintf(saida, "[U] MEM[R%d--] = R%d = 0x%08X\n",Rx, Ry,R[Ry]);
		break;
		//pop
		case 25:
			printf("pop r%d, r%d\n", Rx, Ry);
			fprintf(saida,"pop r%d, r%d\n", Rx, Ry);
			printf("[U] R%d = MEM[++R%d] = 0x%08X\n", Rx, Ry,R[Rx]);
			fprintf(saida, "[U] R%d = MEM[++R%d] = 0x%08X\n", Rx, Ry,R[Rx]);
		break;
		}
}
//printer de execucao de F
void excF(long instruction, long IM16 , long Rx, long Ry){
	switch (instruction){
		//addi
		case 1:
			printf("addi r%d, r%d, %d \n",Rx,Ry,IM16);
			fprintf(saida, "addi r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("[F] FR = 0x%08X, R%d = R%d + 0x%04X = 0x%08X\n", R[35],Rx,Ry,IM16,R[Rx]);
			fprintf(saida, "[F] FR = 0x%08X, R%d = R%d + 0x%04X = 0x%08X\n", R[35],Rx,Ry,IM16,R[Rx]);
		break;
		//subi
		case 3:
			fprintf(saida, "subi r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("subi r%d, r%d, %d \n",Rx,Ry,IM16);
			fprintf(saida, "[U] FR = 0x%08X, R%d = R%d - 0x%04X = 0x%08X\n", R[35],Rx,Ry,IM16,R[Rx]);
			printf("[F] FR = 0x%08X, R%d = R%d - 0x%04X = 0x%08X\n", R[35],Rx,Ry,IM16,R[Rx]);	
		break;
		//muli
		case 5:
			printf("muli r%d, r%d, %d \n",Rx,Ry,IM16);
			fprintf(saida,"muli r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d * 0x%04X = 0x%08X\n", R[35], R[34],Rx,Ry,IM16,R[Rx]);
			fprintf(saida,"[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d * 0x%04X = 0x%08X\n", R[35], R[34],Rx,Ry,IM16,R[Rx]);
		break;
		//divi (DUVIDA - SLIDE 5)
		case 7:
			printf("divi r%d, r%d, %d \n",Rx,Ry,IM16);
			fprintf(saida,"divi r%d, r%d, %d \n",Rx,Ry,IM16);
			printf("[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d / 0x%04X = 0x%08X\n", R[35],R[34],Rx,Ry,IM16,R[Rx]);
			fprintf(saida,"[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d / 0x%04X = 0x%08X\n", R[35],R[34],Rx,Ry,IM16,R[Rx]);
		break;
		//cmpi (DUVIDA - SLIDE 5)
		case 9:
			printf("cmpi r%d, %d\n", Rx,IM16);
			fprintf(saida,"cmpi r%d, %d\n", Rx,IM16);
			printf("[F] FR = 0x%08X\n",R[35]);
			fprintf(saida,"[F] FR = 0x%08X\n",R[35]);
		break;
		//andi
		case 13:
			printf("andi r%d, r%d, %d\n",Rx,Ry,IM16);
			fprintf(saida,"andi r%d, r%d, %d\n",Rx,Ry,IM16);
			printf("[F] R%d = R%d & 0x%04X = 0x%08X\n", Rx,Ry, IM16,R[Rx] );
			fprintf(saida,"[F] R%d = R%d & 0x%04X = 0x%08X\n", Rx,Ry, IM16,R[Rx] );
		break;
		//noti
		case 15:
			printf("noti r%d, 0x%X\n",Rx,IM16);
			fprintf(saida, "noti r%d, 0x%X\n",Rx,IM16);
			printf("[F] R%d = ~0x%04X = 0x%08X\n", Rx,IM16,R[Rx] );
			fprintf(saida,"[F] R%d = ~0x%04X = 0x%08X\n", Rx,IM16,R[Rx] );
		break;
		//ori
		case 17:
			printf("ori r%d, r%d, %d\n",Rx,Ry,IM16);
			fprintf(saida,"[F] R%d = ~0x%04X = 0x%08X\n", Rx,IM16,R[Rx] );
			printf("[F] R%d = R%d | 0x%04X = 0x%08X\n", Rx,Ry,IM16,R[Rx] );
			fprintf(saida, "[F] R%d = R%d | 0x%04X = 0x%08X\n", Rx,Ry,IM16,R[Rx] );
		break;
		//xori
		case 19: 
			printf("xori r%d, r%d, %d\n",Rx,Ry,IM16);
			fprintf(saida, "xori r%d, r%d, %d\n",Rx,Ry,IM16);
			printf("[F] R%d = R%d ^ 0x%08X = 0x%X\n", Rx,Ry,IM16,R[Rx]);
			fprintf(saida, "[F] R%d = R%d ^ 0x%08X = 0x%X\n", Rx,Ry,IM16,R[Rx]);
		break;
		//ldw
		case 20:
			printf("ldw r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			fprintf(saida,"ldw r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			fprintf(saida, "[F] R%d = MEM[(R%d + 0x%04X) << 2] = 0x%08X\n", Rx,Ry,IM16,R[Rx]);
			printf("[F] R%d = MEM[(R%d + 0x%04X) << 2] = 0x%08X\n", Rx,Ry,IM16,R[Rx]);
		break;
		
		//ldb
		case 21:
			printf("ldb r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			fprintf(saida, "ldb r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			printf("[F] R%d = MEM[R%d + 0x%04X] = 0x%02X\n", Rx,Ry,IM16,R[Rx]);
			fprintf(saida,"[F] R%d = MEM[R%d + 0x%04X] = 0x%02X\n", Rx,Ry,IM16,R[Rx]);
		break;
		//stw
		case 22:
			printf("stw r%d, %04X, r%d\n", Rx,IM16,Ry);
			fprintf(saida, "stw r%d, %04X, r%d\n", Rx,IM16,Ry);
			printf("[F] MEM[(R%d + 0x%04X) << 2]= R%d = 0x%08X\n", Rx,IM16,Ry,R[Ry]);
			fprintf(saida,"[F] MEM[(R%d + 0x%04X) << 2]= R%d = 0x%08X\n", Rx,IM16,Ry,R[Ry]);
		break;
		//stb
		case 23:
			printf("stb r%d, %d, r%d\n", Rx,IM16,Ry);
			fprintf(saida, "stb r%d, %d, r%d\n", Rx,IM16,Ry);
			printf("[F] MEM[R%d + 0x%04X]= R%d = 0x%02X\n", Rx,IM16,Ry,(0x000000FF&R[Ry]));
			fprintf(saida, "[F] MEM[R%d + 0x%04X]= R%d = 0x%02X\n", Rx,IM16,Ry,(0x000000FF&R[Ry]));
		break;
		//call
		case 37:
			persistR0();
			printf("call r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			fprintf(saida,"call r%d, r%d, 0x%04X\n", Rx,Ry,IM16);
			printf("[F] R%d = (PC + 4) >> 2 = 0x%08X, PC = (R%d + 0x%04X) << 2 = 0x%08x\n", Rx,R[Rx],Ry,IM16, ((Ry+IM16)<<2));
			fprintf(saida,"[F] R%d = (PC + 4) >> 2 = 0x%08X, PC = (R%d + 0x%04X) << 2 = 0x%08x\n", Rx,R[Rx],Ry,IM16, ((Ry+IM16)<<2));
		break;
		//ret
		case 38:
			printf("ret r%d \n", Rx,Ry,IM16);
			fprintf(saida, "ret r%d \n", Rx,Ry,IM16);
			printf("[F] PC = Rx << 2 = 0x%08X\n",(R[Rx]<<2));
			fprintf(saida, "[F] PC = Rx << 2 = 0x%08X\n",(R[Rx]<<2));
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
		printf("blt 0x%X\n", S);
		fprintf(saida,"blt 0x%X\n", S);
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
		printf("bge 0x%X\n", S);
		fprintf(saida, "bge 0x%X\n", S);
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
	}
}
//Parametros para operacoes tipo U
long opXU(long wholeWord){
	long Rx=(wholeWord&0x000003E0)>>05;
	return Rx;
}
long opZU(long wholeWord){
	long Rz=(wholeWord&0x00007C00)>>10;
	return Rz;
}
long opYU(long wholeWord){
	long Ry=(wholeWord&0x0000001F);
	return Ry;
}
long opEU(long wholeWord){
	long E=(wholeWord&0x00038000)>>15;
	return E;
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
void RspU(unsigned long instruction, unsigned long Rz, unsigned long Rx, unsigned long Ry, long extensao){
	unsigned long aux1, aux2;
	unsigned long aux3;
	long aux4;
	long aux5;
	switch (instruction){
		//add
		case 0:
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			//printf("Rx R%d Ry R%d Rz R%d\n", Rx, Ry, Rz);
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
			Rx=Rx+((extensao&0x00000002)<<4);
			Ry=Ry+((extensao&0x00000001)<<5);
			Rz=Rz+((extensao&0x00000004)<<3);
			//printf("Rx R%d Ry R%d Rz R%d\n", Rx, Ry, Rz);
			aux1=R[Rx];
			aux2=R[Ry];
			R[Rz]=R[Rx]-R[Ry];
			if((R[Rx]-R[Ry])>ULONG_MAX)
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
				R[34]=0;
				R[Rz]=R[Rx]*R[Ry];
				//printf("%d\n",R[Rz]);
				/*if(R[Rz]=!0){
				if(R[Rx]!=0)
				aux1=0xFFFFFFFF / R[Rx];
				else 
				aux1=0xFFFFFFFF;
				if(R[Rx]!=0)
				aux2=0xFFFFFFFF / R[Ry];
				else
				aux2=0xFFFFFFFF;	
				if(R[Ry] > aux1){
					printf("Resultado %d\n",R[Rz]);
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
				}
				else if(R[Rx] > aux2)
					{
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
				}
				else{
					R[35]=R[35]&0xFFFFFFEF;
				}}*/
				flag1=Rz;
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
				R[Rz]=aux5;
				R[34]=R[Rx]%R[Ry];
				if(R[34]!=0)
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
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
		//push
		case 24:
			pilha[R[Rx]]=R[Ry];
			R[Rx]=R[Rx]-1;
		break;
		//pop
		case 25:
			/* for(aux5=0;aux5<100;aux5++)
				printf("Elemento %d %08x\n", aux5, pilha[aux5]);  */
			R[Ry]=R[Ry]+1;
			//printf("R%d = %d Pilha[%d] = %d\n", Ry, R[Ry], R[Ry], pilha[R[Ry]] );
			R[Rx]=pilha[R[Ry]];
			//printf("Rx = 0x%08X\n", R[Rx]);
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
			//printf("HELLO\n");
			aux1=IM16;
			aux2=R[Ry];
			R[Rx]=R[Ry]-IM16;
			/*if((R[Ry]-IM16)<0x80000000)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}*/
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
	char destino[40]="1_recursive_factorial\0";
	char path[40];
	printf("\n%s\n", destino);
	strcpy(path,destino);
	strcat(destino, ".hex");
	//strcat(path,".out");
	printf("\n%s\n", destino);
	hexa = fopen(destino, "r");
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
	//printf("j %d\n", i);
	instruction =malloc(i*sizeof(long));
	j=i;
	for (i=0; i<j; i++){
		instruction[i]=instrucao(wholeWord[i]);
		//printf ("%08X\n", wholeWord[i]);
	}
	char* parse;
	unsigned long E, Rz,Rx,Ry,IM16;
	unsigned long S;
	unsigned long instruc;
	unsigned long aux, b, aux1;
	i=0;
	saida=fopen(path, "w");
	printf("[START OF SIMULATION]\n");
	fprintf(saida, "[START OF SIMULATION]\n");
	while(1){
		//printf("0x%08X\n", wholeWord[R[32]]);
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
				//ret
				else if(instruction[R[32]]==38){
					aux1=R[Rx];
				}
				excF(instruction[R[32]], IM16 , Rx, Ry);
				if(instruction[R[32]]==37){
					R[32]=aux1;
					//printf("PC %d \n", R[32]);
					//printf("0x%08X\n", wholeWord[R[32]]);
				}
				else if(instruction[R[32]]==38){
					R[32]=aux1;
					//printf("PC %d \n", R[32]);
					//printf("0x%08X\n", wholeWord[R[32]]);
				}
				else{
					R[32]++;
				}
				
		}
		else if(parse[4] == 83){ //S
				instruc=instruction[R[32]];
				if(instruction[R[32]]==63)
					{
						fprintf(saida, "int 0 \n[S] CR = 0x00000000, PC = 0x00000000\n");
						printf("int 0 \n[S] CR = 0x00000000, PC = 0x00000000\n");
						fprintf(saida,"[END OF SIMULATION]\n");
						printf("[END OF SIMULATION]\n");
						break;
						fclose(saida);
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

unsigned long R[36];
char flag1=0; 
/* 0-31 Registradores de proposito geral
	 32 PC - Controle de Fluxo
	 33 IR - Instrucao atual
	 34 ER - Registrador de extensao
	 35 FR - Dados de comparacoes e info do processador*/
long final=0;
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
	long aux3;
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
			R[32]++;
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
			R[32]++;
		break;
		//mul
		case 4:
			if((Rx == flag1)){
				aux3=((R[34]<<32)+R[Rx])*R[Ry];
				aux4=(0x00000000FFFFFFFF)&aux3;
				R[Rz]=aux4;
				R[34]=(0xFFFFFFFF00000000&aux3)>>32;
				//printf ("%d*%d=%d\n",R[Rx],R[Ry],R[Rz]);
				if(R[34]!=0){
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
				}
				flag1=Rz;
			}
			else if((Ry == flag1)){
				aux3=((R[34]<<32)+R[Ry])*R[Rx];
				R[Rz]= 0x00000000FFFFFFFF&aux3;
				R[34]=(0xFFFFFFFF00000000&aux3)>>32;
				//printf ("%d*%d=%d\n",R[Rx],R[Ry],R[Rz]);
				if(R[34]!=0){
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
				}
				flag1=Rz;
			}
			else{
				R[34]=0;
				aux3=R[Rx]*R[Ry];
				R[Rz]=0x00000000FFFFFFFF&aux3;
				R[34]=(0xFFFFFFFF00000000&aux3)>>32;
				//printf ("%d*%d=%d\n",R[Rx],R[Ry],R[Rz]);
				if(R[34]!=0){
					if(R[35]<0x10)
						R[35]=R[35]+0x00000010;	
				}
				flag1=Rz;
			}
			R[32]++;
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
			R[32]++;
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
			R[32]++;
		break;
		//shl
		case 10:
			//printf("The flag is %d ",flag1);
			if(Rz==0){
				R[34]=R[Rx]<<(Ry+1);
			}
			else if(flag1 == Rx){
				printf("Rz = R%d. R%d=%X Ry=%d ",Rz,Rx,R[Rx],Ry);
				R[34]=(R[34]<<(Ry+1))+(R[Rx]>>(32-(Ry+1)));
				R[R[Rz]]=R[Rx]<<(Ry+1);
				//printf ("Er=%X Rz=%X \n", R[34], R[Rz]);
			}
			else{
				//printf("Rz = R%d. R%d=%X Ry=%d ",Rz,Rx,R[Rx],Ry);
				R[34]=R[Rx]>>(32-(Ry+1));
				R[Rz]=R[Rx]<<(Ry+1);
				//printf ("Er=%X Rz=%X \n", R[34], R[Rz]);
				flag1=Rz;
			}
			R[32]++;
		break;
		//shr
		case 11:
			if(flag1 == Rx){
				aux3=((R[34]<<32)+R[Rx])>>(Ry+1);
				R[Rz]=(0x00000000FFFFFFFF&aux3);
				R[34]=(0xFFFFFFFF00000000&aux3)>>32;
			}
			else{
				aux3=R[Rx]>>(Ry+1);
				R[Rz]=(0x00000000FFFFFFFF&aux3);
				R[34]=(0xFFFFFFFF00000000&aux3)>>32;
			}
			R[32]++;
		break;
		//and
		case 12:
			R[Rz]=R[Rx]&R[Ry];
			R[32]++;
		break;
		//not
		case 14:
			R[Rx]=~R[Ry];
			R[32]++;
		break;
		//or
		case 16:
			R[Rz]=R[Rx]|R[Ry];
			R[32]++;
		break;
		//xor
		case 18: 
			R[Rz]=R[Rx]^R[Ry];
			R[32]++;
		break;		
		}
}

//modificacoes feitas por instrucoes tipo F
void RspF(unsigned long instruction, unsigned long IM16, unsigned long Rx, unsigned long Ry){
	unsigned long aux1, aux2;
	int aux3, aux4, aux5;
	switch (instruction){
		//addi
		case 1:
			aux1=R[Ry];
			aux2=IM16;
			R[Rx]=IM16+R[Ry];
			//printf("%d+%d=%d\n", aux1, IM16,R[Rx]);
			if((aux1+aux2)>0xFFFFFFFF||(R[Rx]+R[Ry])>0x7FFFFFFF)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
			R[32]++;
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
			R[32]++;
		break;
		//muli
		case 5:
			R[34]=0;
			aux1=IM16;
			aux2=R[Ry];
			R[Rx]=IM16*R[Ry];
			if((IM16*R[Ry])<0x80000000)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
			else if((IM16*R[Ry])>0x7FFFFFFF||(aux1*aux2)>0xFFFFFFFF)
			{
				if(R[35]<0x10)
					R[35]=R[35]+0x00000010;
			}
			R[32]++;
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
			R[32]++;
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
			R[32]++;
		break;
		//andi
		case 13:
			R[Rx]=IM16&R[Ry];
			R[32]++;
		break;
		//noti
		case 15:
			R[Rx]=~IM16;
			R[32]++;
		break;
		//ori
		case 17:
			R[Rx]=IM16|R[Ry];
			R[32]++;
		break;
		//xori
		case 19: 
			R[Rx]=IM16^R[Ry];
			R[32]++;
		break;
		}
	persistR0();
}
//modificacoes feitas por instrucoes tipo S
void RspS(unsigned long instruction, long S){
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
		if((R[35]&0x00000004)==1)
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
	hexa = fopen("1_limits.hex", "r");
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
	instruction =malloc(i*sizeof(long));
	j=i;
	final=j;
	for (i=0; i<j; i++){
		instruction[i]=instrucao(wholeWord[i]);
	}
	char* parse;
	unsigned long* U;
	unsigned long* F;
	unsigned long S;
	unsigned long flag =j;
	i=0;
	while(R[32]<j){
		parse=operacao(instruction[R[32]]);
		if(wholeWord[R[32]]==0)
			R[32]++;
		else if(parse[4] == 85){ //U U0=E U1=Rz	U2=Rx U3=Ry;
				U=opU(wholeWord[R[32]]);
				RspU(instruction[R[32]], U[1], U[2], U[3]);
				persistR0();
				printf("%d %s saida: %X Rz: %X R%d: %X R%d: %X ER=%X \n", i,parse,R[U[1]],U[1],U[2], R[U[2]],U[3],R[U[3]],R[34]);
				i++;
		}
		else if(parse[4] == 70){ //F f0=IM16 F1=Rx F2=Ry
				F=opF(wholeWord[R[32]]);
				RspF(instruction[R[32]], F[0], F[1], F[2]);
				if(instruction[R[32]]==22)//stw
				{
					wholeWord[F[1]+F[0]]=R[F[2]];
					R[32]++;
				}
				else if(instruction[R[32]]==23)//stb
				{
					switch(F[0]%8){
						case 0:
							wholeWord[F[1]]=(R[F[1]]&0xFFFFFFF0)+(R[F[2]]&0x0000000F);
							R[32]++;
						break;
						case 1:
							wholeWord[F[1]]=(R[F[1]]&0xFFFFFF0F)+(R[F[2]]&0x000000F0);
							R[32]++;
						break;
						case 2:
							wholeWord[F[1]]=(R[F[1]]&0xFFFFF0FF)+(R[F[2]]&0x00000F00);
							R[32]++;
						break;
						case 3:
							wholeWord[F[1]]=(R[F[1]]&0xFFFF0FFF)+(R[F[2]]&0x0000F000);
							R[32]++;
						break;
						case 4:
							wholeWord[F[1]]=(R[F[1]]&0xFFF0FFFF)+(R[F[2]]&0x000F0000);
							R[32]++;
						break;
						case 5:
							wholeWord[F[1]]=(R[F[1]]&0xFF0FFFFF)+(R[F[2]]&0x00F00000);
							R[32]++;
						break;
						case 6:
							wholeWord[F[1]]=(R[F[1]]&0xF0FFFFFF)+(R[F[2]]&0x0F000000);
							R[32]++;
						break;
						case 7:
							wholeWord[F[1]]=(R[F[1]]&0x0FFFFFFF)+(R[F[2]]&0xF0000000);
							R[32]++;
						break;
					}
				}
				//ldw
				else if (instruction[R[32]]==20){
					R[F[1]]=wholeWord[F[2]+F[0]];
					R[32]++;
				}	
				//ldb
				else if (instruction[R[32]]==21){
					switch(F[0]%8){
						case 0:
							R[F[1]]=wholeWord[F[2]]&0x0000000F;
						break;
						case 1:
							R[F[1]]=wholeWord[F[2]]&0x000000F0;
						break;
						case 2:
							R[F[1]]=wholeWord[F[2]]&0x00000F00;
						break;
						case 3:
							R[F[1]]=wholeWord[F[2]]&0x0000F000;
						break;
						case 4:
							R[F[1]]=wholeWord[F[2]]&0x000F0000;
						break;
						case 5:
							R[F[1]]=wholeWord[F[2]]&0x00F00000;
						break;
						case 6:
							R[F[1]]=wholeWord[F[2]]&0x0F000000;
						break;
						case 7:
							R[F[1]]=wholeWord[F[2]]&0xF0000000;
						break;
						}
				R[32]++;	
				}
				printf("%d %s saida: %X R%d: %X R%d: %X IM16 %X \n", i,parse,R[F[1]],F[1],R[F[1]],F[2],R[F[2]], F[0]);
				i++;
		}
		else if(parse[4] == 83){ //S
				if(instruction[R[32]]==63)
					{
						R[32]==j;
						printf("Fim da simulacao \n");
						break;
					}
				else{	
					S=opS(wholeWord[R[32]]);
					RspS(instruction[R[32]],S);
					printf("%d %s IM16: %X \n", i,parse, S);
					i++;
					}
		}
		else{	
				printf("ERRO \n");
		break;
		}
	}
	fclose(hexa);
}

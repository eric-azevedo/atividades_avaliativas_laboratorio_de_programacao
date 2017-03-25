#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __unix__
	void _fflush(){
		__fpurge(stdin);g
	}
	#define LIMPAR "clear"
#elif defined(_WIN32) || defined(WIN32)
	void _fflush(){
		fflush(stdin);
	}
	#define LIMPAR "cls"
#endif


typedef struct coordenadas {
	int x;
	int y;
}Coordenadas;

struct tabuleiro {
	int index; 				 	//0-9
	Coordenadas coordenadas; 	//x:0 y:0...
	char posicao[3]; 			//A1, A2 ...
	char valor; 				// X, O ou E
};

int fezPonto(struct tabuleiro *b, int player){
	int i, pontuar[24]={0,1,2,3,4,5,6,7,8,0,3,6,1,4,7,2,5,8,0,4,8,2,4,6};
	char marca;
	if (player<2) marca='X'; else marca='O';
	for(i=0; i<24; i=i+3){
		if( b[ pontuar[i] ].valor == marca &&
			b[ pontuar[i+1] ].valor == marca &&
			b[ pontuar[i+2] ].valor == marca )
			return 1;
	}
	return 0;
}

int jogar(struct tabuleiro *b, Coordenadas local, int player){
	int i;
	char marca;
	if (player==1) marca='X'; else marca='O';
	for(i=0; i<9; i++){
		if( b[i].coordenadas.x == local.x &&
			b[i].coordenadas.y == local.y &&
			b[i].valor == ' ')
		{
			b[i].valor = marca;
			return 1;
		}
	}
	return 0;
}

int mostrarTabuleiro(struct tabuleiro *b, int media){
	if(media==0){
		char rotulo[]={'A','B','C'};
		int i, next=0;
		system(LIMPAR);
		printf("      1     2     3");
		printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
			201,205,205,205,205,205,203,205,205,205,205,205,203,205,205,205,205,205,187 );
		for(i=0; i<9; i=i+3){
			printf(" %c %c  ", rotulo[next] ,186);
			printf("%c  %c  ", b[i].valor, 186);
			printf("%c  %c  ", b[i+1].valor, 186);
			printf("%c  %c  ", b[i+2].valor, 186);
			printf("\n");
			if(i<6)
			printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				204,205,205,205,205,205,206,205,205,205,205,205,206,205,205,205,205,205,185 );
			next++;
		}
		printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",
			200,205,205,205,205,205,202,205,205,205,205,205,202,205,205,205,205,205,188 );
	}
	return 0;
}

void limpaTabuleiro(struct tabuleiro *b){
	int i, j, n;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++){
			n = (i*3)+j;
			b[n].index = n;
			b[n].valor = ' '; //Vazio
			b[n].coordenadas.x = i;
			b[n].coordenadas.y = j;
			b[n].posicao[0]=i+65;
			b[n].posicao[1]=j+49;
		}
}

// TIPO 1 - Lista opções depois da rodada
int menu(int tipo){
	int run=1;
	char entrada[3];
	if(tipo==1){
		while(run){
			printf("Para continuar digite 1\n");
			printf("Para sair digite 0\n");

			scanf("%s",entrada);
			_fflush();

			if (strcmp(entrada, "1")==0) return 1;
			else if (strcmp(entrada, "0")==0) return 0;
			else system(LIMPAR);
		}
	}
	return 1;
}


int main(int argc, char **argv) {
	int i, player = 1;
	struct tabuleiro $tabuleiro[9];
	limpaTabuleiro($tabuleiro);
	char entrada[3];
	char msn[]="\nJogada errada, jogue novamente!";
	int run=1, check=1;
	do{
		mostrarTabuleiro($tabuleiro,0);
		printf("Jogador %d, informe a sua jogada:",player);
		if(check==0){
			printf(msn);
			check=1;
		}
		scanf("%s",entrada);
		_fflush();
		if (strcmp(entrada, "\\q") == 0) run=0;
		for(i=0; i<9; i++){
			if ( strcmp(entrada, $tabuleiro[i].posicao)==0 ){
				check=jogar($tabuleiro, $tabuleiro[i].coordenadas, player);
				break;
			}else check=0;
		}
		if(check){
			if( fezPonto($tabuleiro, player) ){
				system(LIMPAR);
				printf("Jogador %d venceu!\n",player);
				if( !menu(1) )break;
				else limpaTabuleiro($tabuleiro);
			}
			if(player>1)player=1;else player=2;
		}
	}while(run);
}

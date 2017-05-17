/*
 *  arquivo.c
 *
 *  Created on: 17 de mai de 2017
 *  Author: eric
 */

#include <stdio.h>
#include <stdlib.h>

struct entrada{
	int v; // valores
	int d; // digitos
};

typedef struct entrada Entrada;

int casasDecimais(int n); // conta a quantidade de casas decimais
int *quebraValor(int n);
int totalDigitos(int n);
void imprimaAjustado(Entrada *e, int n);

int main(){

	Entrada ent[5];
	ent[0].v = 36;		ent[0].d = 1;
	ent[1].v = 74;		ent[1].d = 2;
	ent[2].v = 2;		ent[2].d = 3;
	ent[3].v = 997;		ent[3].d = 3;
	ent[4].v = 14678;	ent[4].d = 3;

	imprimaAjustado(ent, 5);

}

/* ATUALIZA O VALOR DA ESTRUTURA E IMPRIME */
void imprimaAjustado(Entrada *e, int n){
	int run;
	for(int i=0; i<n; i++){
		run=1;
		while(run){
			if(totalDigitos( e[i].v ) != e[i].d)
				e[i].v +=1;
			else run=0;
		}
	}
	for(int i=0; i<5; i++)
		printf("Caso %d: %d\n", (i+1) , e[i].v );
}


int totalDigitos(int n){
	int u[10], total=0;
	int *q = quebraValor(n);
	for(int i=0; i<10; i++) u[i]=0;
	// registra a ocorrencia dos numeros de 0 a 9
	for(int i=0; i<casasDecimais(n); i++)
		for(int j=0; j<10; j++)
			if(q[i] == j) u[j]=1;
	// conta as ocorrencias
	for(int i=0; i<10; i++)
		if(u[i]) total++;
	return total;
}

/* RETORNA ARRAY DE INTEIROS DO NUMERO QUEBRADo*/
int *quebraValor(int n){
	int c = casasDecimais(n),
	grandeza=1,
	unidade;
	int *q = (int *) malloc(c * sizeof(int));
	for(int i=1; i<c; i++) grandeza*=10;
	for(int i=0; i<c; i++){
		unidade = n/grandeza;
		q[i]=unidade;
		n = n%grandeza;
		grandeza/=10;
	}
	return q;
}

/* CONTA CASAS DECIMAIS */
int casasDecimais(int n){
	int grandeza=1, unidade=0, run = 1;
	if(n>0)
		while(run)
			if(n/grandeza){
				grandeza*=10;
				unidade+=1;
			}else run=0;
	return unidade;
}

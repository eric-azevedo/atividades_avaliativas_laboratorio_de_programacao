// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 19/08/2016

// #################################################

#include <stdio.h>
#include <stdlib.h>

/************************
 *                      *
 *  DADOS GERAIS        *
 *                      *
 ************************/

struct date {
   int day;
   int month;
   int year;
};

int listMonthBisexto[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
int listMonth[12] = 	   {31,28,31,30,31,30,31,31,30,31,30,31};

/************************
 *                      *
 *  FUNCOES AUXILIARES  *
 *                      *
 ************************/
int isNumber(int c){
	if(c>=48&&c<=57) return 1;
	else return 0;
}

struct date stringToDate(char dateStr[11]){
	struct date _date;
    // SEPARA OS CARACTERES EM DIAS ANOS E MESES
    int  bar=0;
    char _day[3], _month[3], _year[5];
    int i=0, j=0;

	while(dateStr[i]!='\0'){
		if(dateStr[i]=='\0') break;
		if(dateStr[i]=='/') { bar++; j=0; }else{
			if(bar==0){	_day[j]   = dateStr[i]; _day[j+1]='\0';   j++; }
			if(bar==1){	_month[j] = dateStr[i]; _month[j+1]='\0'; j++; }
			if(bar==2){	_year[j]  = dateStr[i]; _year[j+1]='\0';  j++; }
		}
		i++;
	}
	// ARMAZENA A DATA NO STRUCT DATE
	_date.day  = atoi(_day);
	_date.month = atoi(_month);
	_date.year  = atoi(_year);
	return _date;
}

// TESTA ANO BISEXTO
int isLeapYear(int year){
	int bisexto = 0;
	if(year % 4 == 0 ) bisexto = 1;
	if(year % 100 == 0 ) bisexto = 0;
	if(year % 400 == 0 ) bisexto = 1;
	return bisexto;
}

/**************
 *            *
 *  QUESTOES  *
 *            *
 **************/

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 */
int q1(char *data){
    int datavalida = 1;
    //// CRIA MASCARA
    char listMask[8][11] = {"101011","1011011","1101011","11011011","10101111","101101111","110101111","1101101111"};
    char mask[11];

    //// TRANSFORMA O PADRAO DE NUMEROS E BARRAS EM UMA MASCARA DE ZERO E UM
    int i=0, j=0, finish = 1;
    while(finish){
		if(data[i]!='\0'){
			if( isNumber(data[i]) ){
				mask[i] = '1';
			}else if(data[i]=='/'){
				mask[i] = '0';
				//RETORNA QUANDO NAO É NUMERO OU BARRA
			}else return 0;
		}else {
			mask[i] = '\0';	finish = 0;
		}
    	++i;
    }

    //// COMPARA A MASCARA
    int testeMask = -1;
    for(i=0; i<8; i++){
    	if(testeMask == -1){
			for(j=0; j<11; j++){
				if('\0' != mask[j]){
					if(listMask[i][j]!= mask[j]) break;
				}else testeMask = i;
			}
    	}else break;
    }

    //// SEPARA OS CARACTERES EM DIAS ANOS E MESES
    int  bar=0;
    char day[3], month[3], year[5];
    i=0; j=0;
	if(testeMask!=-1){
		while(data[i]!='\0'){
			if(data[i]=='\0') break;
			if(data[i]=='/') { bar++; j=0; }else{
				if(bar==0){	day[j]   = data[i]; day[j+1]='\0';   j++; }
				if(bar==1){	month[j] = data[i]; month[j+1]='\0'; j++; }
				if(bar==2){	year[j]  = data[i]; year[j+1]='\0';  j++; }
			}
			i++;
		}
	}else return 0;

	//// CONVERTE AS STRINGS EM NUMERO
	int dayN, monthN, yearN;
	dayN = atoi(day);
	monthN = atoi(month);
	yearN = atoi(year);

	//// AVALIA SE O MES É VÁLIDO
	if(monthN<1||monthN>12)return 0;

	//// AVALIA SE É BISEXTO
	int bisexto = isLeapYear(yearN);

	//// VERIFICA A QUANTIDADE DE DIAS POR MÊS (CONSIDERANDO BISEXTO)
	if( bisexto ){
		if( dayN<0 || dayN>listMonthBisexto[monthN-1] ) return 0;
	}else{
		if( dayN<0 || dayN>listMonth[monthN-1] ) return 0;
	}
    if (datavalida)
        return 1;
    else
        return 0;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. Além disso, a função tem três parâmetros qtdDias, qtdMeses e qtdAnos. Esses três parâmetros devem ser utilizados para guardar os resultados dos cálculos. Na chamada da função deve passar o valor -1 para os três
 @saida
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial < datafinal
*/
int q2(char *datainicial, char *datafinal, int *qtdDias, int *qtdMeses, int *qtdAnos){
    *qtdDias = -1;
    *qtdAnos = -1;
    *qtdMeses = -1;
    
    int days=0, months=0, years=0, temp, lastDayInitialdate, moreMonths=0, moreYears;
    // CRIA DUAS STRUCT DATE (DEFINIDA NA LINHA 39)
    struct date initialdate, finaldate;
    
    // VALIDA DATA INICIAL COM Q1
    if( q1(datainicial) ){
    	initialdate = stringToDate(datainicial);
    }else return 2;

    // VALIDA DATA FINAL QOM Q2
    if( q1(datafinal) ){
    	finaldate = stringToDate(datafinal);
    }else return 3;

    // RETORNO PARA DATA INICIAL MAIOR QUE FINAL
	if(	finaldate.year < initialdate.year) return 4;
	if(	finaldate.year == initialdate.year &&
		finaldate.month < initialdate.month){
		return 4;
	}else{
		// DATA FINAL < DATA INICIAL EM RELACAO AO "DIA"
		if(	finaldate.month == initialdate.month &&
			finaldate.year == initialdate.year &&
			finaldate.day < initialdate.day)
			return 4;
	}
	// DEFINE ULTIMO DIA DO MES (CONSIDERANDO BISEXTO)
	if( isLeapYear(initialdate.year) )
		lastDayInitialdate = listMonthBisexto[initialdate.month-1];
	else
		lastDayInitialdate = listMonth[initialdate.month-1];

	// ADEQUACAO PARA BISEXTO
	if( isLeapYear(initialdate.year) &&
		finaldate.month==initialdate.month	&&
		initialdate.day==lastDayInitialdate &&
		finaldate.day==(lastDayInitialdate-1)
		){
			temp = finaldate.day;
			finaldate.day +=1;
			if(isLeapYear(finaldate.year))finaldate.day -=1;
	}else{
		if(isLeapYear(initialdate.year) && !isLeapYear(finaldate.year)) lastDayInitialdate-=1;
		if(isLeapYear(finaldate.year) && !isLeapYear(initialdate.year)) lastDayInitialdate+=1;
	}

	// DEFINE DIAS
	days = finaldate.day + (lastDayInitialdate - initialdate.day);
	// DEFINE MES (CONSIDERA SOBRA DE DIAS)
	months = (12-(initialdate.month+1)) + finaldate.month;
	moreMonths = days / lastDayInitialdate;
	if(moreMonths){
		days = days%lastDayInitialdate;
		months += moreMonths;
	}
	// DEFINE ANOS (CONSIDERA SOBRA DE MESES)
	years = finaldate.year - (initialdate.year+1);
	moreYears = months/12;
	if(moreYears){
		months= months%12;
		years+=moreYears;
	}
	finaldate.day = temp;

	//SETA VISUALISADORES
    *qtdDias = days;
    *qtdAnos = years;
    *qtdMeses = months;
    return 1;
}


/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferências entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferências entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0. 
*/
int q3(char *texto, char c, int isCaseSensitive){
    int qtdOcorrencias = -1;
    int stop=1, i=0, n=0, charNumberA, charNumberB, max=250;
	while(stop){
		if(!(i<max)){ n=-1; break;}
		if(texto[i]!='\0'){
		    if(isCaseSensitive==1){
				if(texto[i]==c)	n+=1;
		    }else{
		    	charNumberA = c;
		    	charNumberB = texto[i];
				if(charNumberA >=65 && charNumberA <=90){
					if( charNumberA == charNumberB || (charNumberA+32) == charNumberB)
						n+=1;
				}
				else if(charNumberA >=97 && charNumberA <=122){
					if( charNumberA == charNumberB || (charNumberA-32) == charNumberB)
						n+=1;
				}
				else{ if(texto[i]==c) n+=1; }
		    }
		}else stop=0;
		i++;
	}
	qtdOcorrencias = n;
    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias.
    Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente.
    Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;
*/
int q4(char *strTexto, char *strBusca, int posicoes[30]){
    int qtdOcorrencias = -1;
    int stopTexto=1, stopBusca=1, i=0, j=0, n=0, p=0;
    while(stopTexto){
    	if(!(strTexto[i]=='\0')){
    		j=0; stopBusca=1;
			while(stopBusca){
				if(!(strBusca[j]=='\0')){
					if(strTexto[i+j] != strBusca[j])
						stopBusca=0;
					j++;
				}else{
					posicoes[p]=i+1;
					posicoes[p+1]=i+j;
					p+=2;
					n+=1;
					stopBusca=0;
				}
			}
			i++;
    	}else stopTexto=0;
    }
    qtdOcorrencias = n;
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num){
	int run=1, exp=1, terms=0, i, j, inverso=0, order;

	while(run){
		if(num/exp){
			terms+=1;
			exp*=10;
		}else run=0;
	}
	order=1;
	for(i=0; i<terms; i++){
		exp=1;
		for(j=terms-1; j>i; j--)
			exp*=10;
		inverso += (num/exp)*order;
		num = num%exp;
		order*=10;
	}
	num = inverso;
    return num;
}

/*
 Q5 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */
// RETORNA QUANTOS ELEMENTOS TEM O NUMERO
int numberLength(int number){
	int run=1, length=0, factor=1;
    while(run){
		if(number/factor){
			length+=1;
			factor*=10;
		}else run=0;
	}
    return length;
}
//QUEBRA O NUMERO EM UMA MATRIZ DINÂMICA
int *exploderNumber(int number){
	int n = number;
	int *v;
	v = (int *)malloc(n * sizeof(int));
	int length = numberLength(number), factor=1, i, j;
	int order;
	if(number!=0){
		for(i=0; i<length; i++){
			factor=1;
			for(j=(length-1); j>i; j--){
				factor*=10;
			}
			order = number/factor;
			number = number%factor;
			v[i] = order;
		}
	}else v[0]=0;
	return v;
}


int q6(int numerobase, int numerobusca){
    int qtdOcorrencias = 0 , i, j;
    int n = numberLength(numerobase),
    	s = numberLength(numerobusca);

    // DESMONTA NUMERO BASE
    int *v_numerobase =  exploderNumber(numerobase);
    if(numerobase==0)n=1;

    // DESMONATA NUMERO BUSCA
    int *v_numerobusca =  exploderNumber(numerobusca);
    if(numerobusca==0)s=1;

    // DETECTA REPETICAO
	int countSearch = 0;
	for(i=0; i<n; i++){
		for(j=0; j<s; j++){
			if( v_numerobusca[j] == v_numerobase[i+j] ){
				if(j==(s-1)){
					countSearch +=1;
				}
			}else break;
		}
	}
	qtdOcorrencias = countSearch;
	// LIBERA MEMORIA
	free(v_numerobase);
	free(v_numerobusca);

    return qtdOcorrencias;
}

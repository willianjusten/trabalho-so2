/**
 * Instituto Superior de Tecnologia - IST/FAETERJ
 * Disciplina: Sistemas Operacionais II
 * Professor: Douglas Oliveira
 * Turno: Noite
 * Aluno: Willian Justen de Vasconcellos
 */

#include <stdlib.h>
#include <stdio.h>

// definindo as matrizes globais
int **a, **b, **c;
// definindo tamanho da matriz e num de threads
int tam, num_proc;

// função para gerar uma matriz
// que vai preenchendo somando 1
int **gera_matriz(){
	int i;
	int *valores, **temp;

	// alocando memória
	valores = (int *)malloc(tam * tam * sizeof(int));
	temp = (int **)malloc(tam * sizeof(int*));

	for (i = 0; i < tam; i++){
		temp[i] = &(valores[i * tam]);
	}
	// retorna para poder ocupar na main
	return temp;
}

// função para imprimir as matrizes
void imprime_matriz(int **mat){
	int i, j;
	
	// loop para imprimir
	for (i = 0; i < tam; i++) {
		printf("\n\t| ");
		for (j = 0; j < tam; j++){
			printf("%4d", mat[i][j]);
		}
		printf("    |");
	}
	printf("\n\n");
}

void multiplica_matriz(int proc_id){
	int i, j, k;
	int inicio, final;

	float passo = ceil((float)tam/num_proc);
	inicio = proc_id * passo;
	final = (proc_id + 1)* passo - 1;
	if(final > tam){
		final = tam -1;
	}


	// multiplicação
	printf("Inicio %d => Final %d \n", inicio, final );
	for (i = inicio; i <= final; i++)
	{  
		for (j = 0; j < tam; j++)
		{
			c[i][j] = 0;
			for ( k = 0; k < tam; k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}

int main(int argc, char* argv[]){
	int i,j;

	// definindo o tamanho da matriz
	tam = atoi(argv[1]);

	// definindo tamanho da matriz
	num_proc = atoi(argv[2]);

	// Tratamento para evitar que o número de threads 
	// seja maior que o tam da matriz
	if(num_proc > tam){
		printf("O número de threads é maior que o tamanho da matriz. Por favor selecione um número menor de threads.\n");
		return 0;
	}

	// alocando matriz
	a = gera_matriz();
	b = gera_matriz();
	c = gera_matriz();

	// populando matriz com valor 1
	for(i=0;i<tam;i++){
		for(j=0;j<tam;j++){
			a[i][j] = 1;
			b[i][j] = 1;
		}
	}

	int k;
	int process[num_proc];

	// Chamo o processo, ele faz o cálculo
	// e então mato para o próximo continuar
	for(k=0;k<num_proc;k++){
		process[k] = fork();
		if(process[k] == 0)
			exit(0);

		multiplica_matriz(k);
		wait(NULL);	
	}

	// imprime as matrizes 
	imprime_matriz(a);
	imprime_matriz(b);

	//imprime resultado
	imprime_matriz(c);


	return 0;
}
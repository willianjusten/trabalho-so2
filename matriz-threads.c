/**
 * Instituto Superior de Tecnologia - IST/FAETERJ
 * Disciplina: Sistemas Operacionais II
 * Professor: Douglas Oliveira
 * Turno: Noite
 * Aluno: Willian Justen de Vasconcellos
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// definindo as matrizes globais
int **a, **b, **c;
// definindo tamanho da matriz e num de threads
int tam, num_thread;

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

void multiplica_matriz(int thread_id){
	int i, j, k;
	int inicio, final;

	float passo = ceil((float)tam/num_thread);
	inicio = thread_id * passo;
	final = (thread_id + 1)* passo - 1;
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
	pthread_t *threads;

	// definindo o tamanho da matriz
	tam = atoi(argv[1]);

	// definindo tamanho da matriz
	num_thread = atoi(argv[2]);

	// Tratamento para evitar que o número de threads 
	// seja maior que o tam da matriz
	if(num_thread > tam){
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
	
	// alocando as threads
	threads = (pthread_t *)malloc(num_thread * sizeof(pthread_t));

	// criando as threads e chamando multiplica
	for(i=0; i < num_thread; i++){
		pthread_create(&threads[i], NULL, multiplica_matriz, i);
	}

	for (i = 0; i < num_thread; i++){
		pthread_join(threads[i], NULL);
	}

	// imprime as matrizes 
	imprime_matriz(a);
	imprime_matriz(b);

	//imprime resultado
	imprime_matriz(c);

	// libera as memórias alocadas
	free(threads);

	return 0;
}
#Trabalho de SO 2

Esses são os 3 trabalhos que o Douglas pediu para passar a todos.

Para compilar os exercícios de thread e fork

```sh
gcc matriz-threads.c -o matriz-threads.exe -lpthread -lm -w
gcc matriz-forks.c -o matriz-forks.exe  -lm -w

# para rodar

./matriz-threads [TAM DA MATRIZ] [NUM DE PROCS]
```

Para compilar o exercício de MPI

```sh
mpicc matriz-mpi.c -o matriz-mpi

# para rodar
mpirun -np [NUM DE PROCS] ./matriz-mpi [TAM DA MATRIZ]
```

## Comparativo entre MPI, THREADS E FORKS

| Tipo     | 1 proc    | 2 proc     | 4 proc    | 8 proc    |
| -------- | --------- | ---------- | --------- | --------- |
| Forks    | 1m23.042s | 1m06.479s  | 0m59.322s | 0m59.841s |       
| Threads  | 1m16.012s | 0m55.693s  | 0m38.349s | 0m38.781s |
| MPI      | 2m50.572s | 2m1.690s   | 1m30.856s | 1m27.664s |

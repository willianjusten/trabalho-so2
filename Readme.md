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
mpicc -np [NUM DE PROCS] ./matriz-mpi [TAM DA MATRIZ]
```


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
#include <stdbool.h>

double get_memory_used_MB(){
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}


void heapsort(int a[], int n) {
   int i = n / 2, pai, filho, t;
   while(true) {
      if (i > 0) {
          i--;
          t = a[i];
      } else {
          n--;
          if (n <= 0) return;
          t = a[n];
          a[n] = a[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < n) {
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          if (a[filho] > t) {
             a[pai] = a[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      a[pai] = t;
   }
}

/*void ordenar(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            if (vetor[i] > vetor[j]) {
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}*/
/*void ordenarD(int *vet, int tam) {
    for (int i = 1; i < tam; i++) {
        for (int j = 0; j < i; j++) {
            if (vet[i] > vet[j]) {
                int temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }
}*/


int main(void) {
  clock_t start_time, end_time;
  double cpu_time_used, memory_used;
  size_t peakSize;
  start_time = clock();

  int tam = 128000, *vet;
  vet = (int*)malloc(tam*sizeof(int));
  srand(time(NULL));
  for(int i; i < tam; i++){
    vet[i] = rand() % 10;
  }
  //ordenarD(vet, tam);
  //ordenar(vet, tam);
  /*for(int i; i < tam; i++){
    printf("%d ", vet[i]);
  }*/
  heapsort(vet, tam);
  /*printf("Ordenado: ");
  for(int i; i < tam; i++){
    printf("%d ", vet[i]);
  }*/

  end_time = clock();
  cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
  memory_used = get_memory_used_MB();
  printf("Tempo: %0.2f segundos - Memoria: %0.2f MB\n",cpu_time_used, memory_used);

  return 0;
}

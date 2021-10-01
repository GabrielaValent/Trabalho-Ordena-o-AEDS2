#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>
#include<stdlib.h>

double get_memory_used_MB(){
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}

void swap(int vet[], int i, int j){
  int aux = vet[i];
  vet[i] = vet[j];
  vet[j] = aux;
}
void bubbleSort(int vet[], int n){
  for (int i = 0; i < n - 1; i++){
    if (vet[i] > vet[i + 1]){
      swap(vet, i, i + 1);
    }
  }
  if (n - 1 > 1) {
    bubbleSort(vet, n - 1);
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

int main(){
    clock_t start_time, end_time;
    double cpu_time_used, memory_used;
    size_t peakSize;

    start_time = clock();
    int tam = 2000, *vet;
    vet =(int*)malloc(tam*sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < tam; i++){
        vet[i] = rand() % 10;
    }
    //ordenarD(vet, tam);
    //ordenar(vet, tam);
    bubbleSort(vet, tam);
    /*for(int i = 0; i < tam; i++){
        printf("%d ",vet[i]);
    }*/

    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    memory_used = get_memory_used_MB();
    printf("Tempo: %0.2f segundos - Memoria: %0.2f MB\n",cpu_time_used, memory_used);

    return 0;
}

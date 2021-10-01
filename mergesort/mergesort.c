#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <psapi.h>

double get_memory_used_MB(){
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (double)info.PeakWorkingSetSize/ (1024*1024);
}

void merge(int vet[], int l, int m, int r){
  int i, j, k;
  int n1 = m - l + 1, n2 = r - m;
  int esquerda[n1], direita[n2];

  for (i = 0; i < n1; i++){
    esquerda[i] = vet[l + i];
  }
  for (j = 0; j < n2; j++){
    direita[j] = vet[m + 1 + j];
  }
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2){
    if (esquerda[i] <= direita[j]){
      vet[k] = esquerda[i];
      i++;

    }
    else{
      vet[k] = direita[j];
      j++;
    }
    k++;
  }
  while (i < n1){
    vet[k] = esquerda[i];
    i++;
    k++;
  }
  while(j < n2){
    vet[k] = direita[j];
    j++;
    k++;
  }
}

void mergeSort(int vet[], int l, int n){
  if (l < n){
    int m = l + (n - l) / 2;
    mergeSort(vet, l, m);
    mergeSort(vet, m + 1, n);
    merge(vet, l, m, n);
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

    int tam = 128000, *vet;
    vet = (int*)malloc(tam*sizeof(int));
    srand(time(NULL));
    for(int i; i < tam; i++){
        vet[i] = rand() % 10;
    }
    //ordenarD(vet, tam);
    //ordenar(vet, tam);
    mergeSort(vet, 0, tam - 1);
    /*for(int i; i < tam; i++){
        printf("%d", vet[i]);
    }
*/
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    memory_used = get_memory_used_MB();
    printf("Tempo: %0.2f segundos - Memoria: %0.2f MB\n",cpu_time_used, memory_used);

    return 0;
}

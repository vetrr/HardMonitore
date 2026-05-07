#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/statvfs.h>

int main(){
    return 0;
}

double ler_ram() {
    int memoriaTotal = 0;
    int memoriaDisponivel = 0;
    char buffer[256];

    // 1. Abre /proc/meminfo
    FILE *arquivo = fopen("/proc/meminfo", "r");
    // 2. Extrai Total e Available
    while (fgets(buffer, 256, arquivo) != NULL) {
        printf("%s", buffer); // Imprime a linha lida

    // Procurando o Total
    if (strncmp(buffer, "MemTotal:", 9)  == 0){
        // Achamos a linha! Agora extrai o número dela:
        sscanf(buffer, "MemTotal: %d kB", &memoriaTotal);
    }
    // Procurando o Disponível
    else if (strncmp(buffer, "MemAvailable:", 13) == 0){
        // Achamos a linha! Extrai o número:
        sscanf(buffer, "MemAvailable: %d kB", &memoriaDisponivel);
    }

    fclose(arquivo);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>

double ler_ram()
{
    int memoriaTotal = 0;
    int memoriaDisponivel = 0;
    char buffer[256];

    // 1. Abre /proc/meminfo
    FILE *arquivo = fopen("/proc/meminfo", "r");
    // 2. Extrai Total e Available
    while (fgets(buffer, 256, arquivo) != NULL)
    {
        // Procurando o Total
        if (strncmp(buffer, "MemTotal:", 9) == 0)
        {
            // Achamos a linha! Agora extrai o número dela:
            sscanf(buffer, "MemTotal: %d kB", &memoriaTotal);
        }
        // Procurando o Disponível
        else if (strncmp(buffer, "MemAvailable:", 13) == 0)
        {
            // Achamos a linha! Extrai o número:
            sscanf(buffer, "MemAvailable: %d kB", &memoriaDisponivel);
        }

    }
        fclose(arquivo);

        double uso_ram = ((double)(memoriaTotal - memoriaDisponivel) / (double)memoriaTotal) * 100.0;

        return uso_ram;
}

int main()
{
    // O número 1 em C significa "verdadeiro". Logo, while(verdadeiro) roda para sempre.
    while (1)
    {
        system("clear"); // Limpa a tela do terminal (apaga a leitura anterior)
        printf("######Monitoramento de Recursos######\n");

        double uso = ler_ram();
        printf("Uso atual da RAM: %.2f%%\n", uso);

        sleep(1); // Pausa o programa por 1 segundo antes de repetir o laço
    }

    return 0; // O programa nunca vai chegar aqui, a menos que seja forçado a parar
}

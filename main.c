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

static int ultimo_total;
static int ultimo_ocioso;
double ler_cpu(){
    char buffer[256];
    int user, nice, system, idle;
    int total_agora, ocioso_agora;

    FILE *arquivo = fopen("/proc/stat", "r");
    fgets(buffer, 256, arquivo);

    sscanf(buffer,"cpu %d %d %d %d", &user, &nice, &system, &idle);

    total_agora = user+nice+system+idle;
    ocioso_agora = idle;

    int diferenca_total = total_agora-ultimo_total;
    int diferenca_ocioso = ocioso_agora-ultimo_ocioso;

    double uso = ((double)(diferenca_total - diferenca_ocioso)/diferenca_total)*100;

    ultimo_total = total_agora;
    ultimo_ocioso = ocioso_agora;
    fclose(arquivo);
    return uso;
}

int main()
{
    // O número 1 em C significa "verdadeiro". Logo, while(verdadeiro) roda para sempre.
    while (1)
    {
        system("clear"); // Limpa a tela do terminal (apaga a leitura anterior)
        printf("###### HardMonitore ######\n");

        double ram = ler_ram();
        double cpu = ler_cpu();
        printf("Uso atual da RAM: %.2f%%\n", ram);
        printf("Uso atual da CPU: %.2f%%\n", cpu);
        printf("------------------------------------------\n");

        sleep(1); // Pausa o programa por 1 segundo antes de repetir o laço
    }

    return 0; // O programa nunca vai chegar aqui, a menos que seja forçado a parar
}

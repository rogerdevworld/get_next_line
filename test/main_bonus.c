#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"  // Asegúrate de que esta es la ruta correcta

int main(int argc, char *argv[])
{
    int fd;
    char *line;

    // Verifica que se haya pasado al menos un argumento (el nombre de un archivo)
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1.txt> <file2.txt> <file3.txt> ...\n", argv[0]);
        return (1);
    }

    // Procesa cada archivo pasado como argumento
    for (int i = 1; i < argc; i++)
    {
        // Abre el archivo especificado en el argumento
        fd = open(argv[i], O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening file");
            continue;  // Si hay un error, continua con el siguiente archivo
        }

        printf("Reading from %s:\n", argv[i]);
        // Lee líneas del archivo
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s", line);
            free(line);  // Libera la memoria de la línea leída
        }

        // Cierra el descriptor de archivo
        close(fd);
        printf("\n");  // Agrega una línea en blanco entre archivos
    }

    return (0);
}
//comand> cc -Wall -Werror -Wextra -D BUFFER_SIZE=1000 -o programa main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -I./includes
//comand>./programa file.txt file2.txt file3.txt file4.txt file5.txt
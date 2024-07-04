#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    const char *searchterm = argv[1];
    char *buffer;
    size_t buff_size = 100;
    if (argc > 2)
    {
        FILE *fp;
        for (int i = 2; i < argc; i++)
        {
            fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            while (getline(&buffer, &buff_size, fp) != -1)
            {
                if (strstr(buffer, searchterm))
                {
                    printf("%s", buffer);
                }
            }

            free(buffer);
            fclose(fp);
        }
    }
    else
    {
        buffer = (char *)malloc(buff_size * sizeof(char));
        while (fgets(buffer, buff_size, stdin) != NULL)
        {
            if (strstr(buffer, searchterm))
            {
                printf("%s", buffer);
            }   
        }

        free(buffer);
    }

    return 0;
}

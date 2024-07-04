#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        exit(0);
    }
    
    FILE *fp;
    size_t size = 100;
    char *line = (char *) malloc(size * sizeof(char));
    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {   
            printf("wcat: cannot open file\n");
            exit(1);
        }
        
        while (fgets(line, size, fp) != NULL)
        {
            printf("%s", line);
        }
        

        fclose(fp);
    }
    
    free(line);
    return 0;
}

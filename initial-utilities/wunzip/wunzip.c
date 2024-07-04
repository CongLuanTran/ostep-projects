#include <stdio.h>
#include <stdlib.h>

typedef struct run
{
    int length;
    char c; 
} run;

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    FILE *fp;
    run this;
    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");

        while (fread(&this, 5, 1, fp) == 1)
        {
            for (int j = 0; j < this.length; j++)
            {
                printf("%c", this.c);
            }
        }
    }
    
    return 0;
}

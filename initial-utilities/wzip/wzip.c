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
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    run this;
    this.c = '\0';
    char next;

    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");

        while ((next = fgetc(fp)) != EOF)
        {
            if (this.c == next)
            {
                this.length++;
            }
            else
            {
                if (this.c != '\0')
                {
                    fwrite(&this, 5, 1, stdout);
                }

                this.c = next;
                this.length = 1;
            }
        }


        fclose(fp);
    }

    fwrite(&this, 5, 1, stdout);
    return 0;
}

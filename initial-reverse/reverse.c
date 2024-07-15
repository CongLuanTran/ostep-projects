#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct Node
{
    char *s;
    struct Node *next;
    struct Node *prev;
} Node;

int main(int argc, char const *argv[])
{

    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *input = argc > 1 ? fopen(argv[1], "r") : stdin;
    FILE *output = argc > 2 ? fopen(argv[2], "w+") : stdout;

    if (!input || !output)
    {
        fprintf(stderr, "reverse: cannot open file '%s'\n", !input ? argv[1] : argv[2]);
        exit(1);
    }

    struct stat in_stat, out_stat;
    int in_no = fileno(input), out_no = fileno(output);
    fstat(in_no, &in_stat);
    fstat(out_no, &out_stat);

    if (in_stat.st_ino == out_stat.st_ino)
    {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }
    
    char *buffer;
    size_t buff_size = 100;
    Node *head = malloc(sizeof(Node));
    if (head == NULL)
    {
        fprintf(stderr, "reverse: malloc failed\n");
        exit(1);
    }

    Node *this = head;
    this->s = NULL;
    this->next = NULL;
    this->prev = NULL;

    while (getline(&buffer, &buff_size, input) != -1)
    {
        this->s = malloc(sizeof(*buffer));
        if (this->s == NULL)
        {
            if (head == NULL)
            {
                fprintf(stderr, "reverse: malloc failed\n");
                exit(1);
            }
        }

        strcpy(this->s, buffer);

        this->next = malloc(sizeof(Node));
        if (this->next == NULL)
        {
            if (head == NULL)
            {
                fprintf(stderr, "reverse: malloc failed\n");
                exit(1);
            }
        }

        Node *tmp = this;
        this = this->next;
        this->prev = tmp;
        this->next = NULL;
    }

    while (this->prev != NULL)
    {
        this = this->prev;
        fprintf(output, "%s", this->s);
    }

    fclose(input);
    fclose(output);
    return 0;
}

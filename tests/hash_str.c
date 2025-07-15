
#include <unistd.h>
#include <stdio.h>
#include <string.h>
# include <fcntl.h>
# include <stdlib.h>

#define UID_SIZE 23
#define ID_UNIQ_CHARS_SIZE 12
#define READ_SIZE (ID_UNIQ_CHARS_SIZE * sizeof(unsigned short int))

char *create_new_id(char *id, char *buf)
{
    unsigned short int *int_buf;
    int int_index;
    int i;

    int_buf = (unsigned short int *)buf;
    int_index = 0;
    i = 7;
    while (i < 22)
    {
        if (id[i] == '*')
        {
            char c = 'a' + (int_buf[int_index++] % 26);
            id[i] = c;
        }
        i++;
    }
    return (id);
}

char * id()
{
    int fd;
    char *id;
    char buf[READ_SIZE];

    id = gc_malloc(UID_SIZE);
    if (!id)
        return (NULL);
    fd = open("/dev/random", O_RDONLY);
    if (fd == -1)
    {
        free(id);
        return (NULL);
    }
    strcpy(id, "heredoc-****-********");    
    if (read(fd, buf, READ_SIZE) <= 0)
    {
        close(fd);
        free(id);
        return (NULL);
    }
    close(fd);
    return (create_new_id(id, buf));
}

int main()
{
    char *s;
    int i = 100;

    while (i--)
    {
        s = id();
        printf("id: %s\n", s);
        free(s);
    }
}
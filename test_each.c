#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

char	*erase_nl(char *line2, char *dst)
{
	int	i = 0;
	if (!dst)
		return ("");
	while (line2[i])
	{
		if (line2[i] == '\n')
		{
			line2[i] = '\0';
			break ;
		}
		i++;
	}
	return (line2);

}

int main(int ac, char **av)
{
	int 	fd;
	FILE	*fp;
	char	*line;
	char	*line2;
	char	*dst;
	int		r;

	(void)ac;
	line2 = (char *)malloc(10000);
	fd = open(av[1], O_RDONLY);
	fp = fopen(av[1], "r");
	r = 1;
	int j = 0;
	while (r > 0)
	{
		r = get_next_line(fd, &line);
		printf("\x1b[36mret:%d\x1b[39m:\n", r);
		printf("[%d]%s\n", j, line);
		dst = fgets(line2, 10000, fp);
		dst = erase_nl(line2, dst);
		printf("[%d]%s\n", j, dst);
		if (strcmp(line, dst) != 0)
		{
			printf("\x1b[31m[NG]\x1b[39m ");
			free(line);
			break ;
		}
		free(line);
		j++;
	}
	if (r == 0 && !(fgets(line2, 10000, fp)))
		printf("\x1b[32m[OK]\x1b[39m\n");
	close(fd);
	fclose(fp);

	free(line2);
	return (0) ;
}

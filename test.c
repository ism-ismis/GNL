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

int main(void)
{
	int 	fd;
	FILE	*fp;
	char	*line;
	char	*line2;
	char	*line3;
	char	*dst;
	int		r;
	int		i;
	char	*tests[] = {"test/64bit_line.txt", "test/64bit_paragraph.txt", "test/bar.txt", "test/empty.txt", "test/fewchar_perline.txt", "test/long_line.txt", "test/normal_long.txt", "test/normal.txt"};

	line3 = NULL;
	if (get_next_line(42, &line) == -1)
		printf("wrong fd:\x1b[32m[OK]\x1b[39m\n");
	else
		printf("wrong fd:\x1b[31m[NG]\x1b[39m\n");
	if (line)
		free(line);

	line2 = (char *)malloc(10000);
	i = 0;
	while (i < 8)
	{
		fd = open(tests[i], O_RDONLY);
		fp = fopen(tests[i], "r");
		r = 1;

		while (r > 0)
		{
			r = get_next_line(fd, &line);
			// printf("\x1b[36mret:%d\x1b[39m:\n", r);
			// printf("[%d]%s\n", j, line);
			dst = fgets(line2, 10000, fp);
			dst = erase_nl(line2, dst);
			// printf("[%d]%s\n", j, dst);
			if (strcmp(line, dst) != 0)
			{
				printf("%s:\x1b[31m[NG]\x1b[39m ", tests[i]);
				free(line);
				break ;
			}
			free(line);
			// j++;
		}
		if (r == 0 && !(fgets(line2, 10000, fp)))
			printf("%s:\x1b[32m[OK]\x1b[39m\n", tests[i]);

		close(fd);
		fclose(fp);
		i++;
	}
	free(line2);
	return (0) ;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line_bonus.h"

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
	int		fd1;
	int		fd2;
	int		ret1;
	int		ret2;
	char	*line;
	FILE	*fp1;
	FILE	*fp2;
	char	*line2;
	char	*dst;
	int		i;
	char	*tests[] = {"test/64bit_line.txt", "test/64bit_paragraph.txt", "test/bar.txt", "test/empty.txt", "test/fewchar_perline.txt", "test/long_line.txt", "test/normal_long.txt", "test/normal.txt"};

	line2 = (char *)malloc(10000);
	i = 0;
	while (i < 8)
	{
		fd1 = open(tests[i], O_RDONLY);
		fd2 = open(tests[i + 1], O_RDONLY);
		fp1 = fopen(tests[i], "r");
		fp2 = fopen(tests[i + 1], "r");
		ret1 = 1;
		ret2 = 1;
		// int j = 0;
		while (ret1 || ret2)
		{
			ret1 = get_next_line(fd1, &line);
			// printf("\x1b[36mret:%d\x1b[39m:\n", ret1);
			// printf("[%d]%s\n", j, line);
			dst = fgets(line2, 10000, fp1);
			dst = erase_nl(line2, dst);
			// printf("[%d]%s\n", j, dst);
			if (strcmp(line, dst) != 0)
			{
				printf("%s:\x1b[31m[NG]\x1b[39m ", tests[i]);
				free(line);
				break ;
			}
			free(line);
			ret2 = get_next_line(fd2, &line);
			// printf("\x1b[36mret:%d\x1b[39m:\n", ret2);
			// printf("[%d]%s\n", j, line);
			dst = fgets(line2, 10000, fp2);
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
		if (ret1 == 0 && ret2 == 0 && !(fgets(line2, 10000, fp1)) && !(fgets(line2, 10000, fp2)))
			printf("%s & %s:\x1b[32m[OK]\x1b[39m\n", tests[i], tests[i + 1]);

		close(fd1);
		close(fd2);
		fclose(fp1);
		fclose(fp2);
		i += 2;
	}
	free(line2);
	return (0) ;
}

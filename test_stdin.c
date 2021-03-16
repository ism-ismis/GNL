#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

int main(void)
{
	char	*line;
	char	*line2;
	int		r;
	int		r2;

	line2 = (char *)malloc(10000);
	printf("please enter a sentence\n");
	r = get_next_line(0, &line);
	printf("please enter the sentence you entered again.\n");
	r2 = scanf("%[^\n]", line2);
	if (strcmp(line, line2) != 0)
		printf("\x1b[31m[NG]\x1b[39m ");
	else
	{
		printf("\x1b[36mret:%d\x1b[39m:\n", r);
		printf("1:%s\n", line);
		printf("2:%s\n", line2);
		printf("\x1b[32m[OK]\x1b[39m\n");
	}
	free(line);
	free(line2);
	return (0) ;
}

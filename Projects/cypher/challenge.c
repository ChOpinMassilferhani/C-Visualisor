# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <string.h>

int main(int argc, char **argv)
{
	if(argc != 2)
		errx(EXIT_FAILURE,"Enter password");

	int len = (strlen(argv[1]) ^ 0) - (strlen(argv[1]) ^ 0) + 10;
	int ok = 1;
	int a = 1;
	int b = 1;
	for(int i = 0;i < len;i++)
	{
		if( argv[1][i] != a )
			ok = 0;
		int tmp = a+b;
                a = b;
                b = tmp;
	}
	printf("%s\n",(ok && argv[1][len] == 0)?"OK":"KO");
	exit(EXIT_SUCCESS);
}

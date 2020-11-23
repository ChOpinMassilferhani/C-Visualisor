# include <stdio.h>
# include <stdlib.h>

void test1()
{
	int *tab = calloc(5,sizeof(int));
	for(int i = 0; i < 5; i++)
		tab[i] = i*i;
	for(int i = 0; i < 5; i++)
                printf("%d\n",tab[i]);
	free(tab);
}

int main()
{
	test1();
	return 0;
}

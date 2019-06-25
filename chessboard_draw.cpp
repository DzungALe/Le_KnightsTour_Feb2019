#include <stdio.h>

void main()
{
	int i, j;
	printf("┌───");
	for (j = 0; j < 6; j++)
		printf("┬───");
	printf("┬───┐");
	printf("\n");

	for (i = 0; i < 7; i++) {
		printf("│");
		for (j = 0; j < 8; j++)
			printf("%02d │", i);
		printf("\n");
		printf("├───");
		for (j = 0; j < 6; j++)
			printf("┼───");
		printf("┼───┤");
		printf("\n");
	}

	printf("│");
	for (j = 0; j < 8; j++)
		printf("%02d │", i);
	printf("\n");
	printf("└───");
	for (j = 0; j < 6; j++)
		printf("┴───");
	printf("┴───┘");
	printf("\n");

	printf("\n");
}
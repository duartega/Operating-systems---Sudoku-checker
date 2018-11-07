#include <pthread.h>
#include <stdio.h>

int main() {
	char name[20]; printf("Enter Filename: \n"); scanf("%s", &name); 
	FILE *ptr; ptr = fopen(name, "r");
	char board[9][9]; int i = 0; int j = 0; int c = 0; char line[25];
	while (fgets(line, sizeof(line), ptr)){
		while (j < 9) {
			if (line[c] == ' ' || line[j] == '\0') { c++; }
			else {
				board[i][j] = line[c];
				printf("%c", board[i][j]);
				j++;
				c++;
			}
		} printf("\n"); j = 0; c =0; i++;
	} int k = 0; int l = 0;	
	for (k = 0; k < 9; k++) {
		for(l = 0; l < 9; l++) { printf("%c", board[k][l]); }
		printf("\n");
	} return 0;
}

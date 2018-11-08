#include "header.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>


int main() {
	char name[20]; printf("Enter Filename: \n"); 
	scanf("%s", &name); 
	FILE *ptr; 
	ptr = fopen(name, "r");
	char board[9][9]; 
	int i = 0; 
	int j = 0; 
	int c = 0; 
	char line[26];
	while (fgets(line, sizeof(line), ptr)){
		while (j < 9) {
			if (line[c] == '\0') break;
			if (line[c] == ' ') c++;
			else {
				board[i][j] = line[c];
				printf("%c", board[i][j]);
				//usleep(50000);
				j++;
				c++;
			}
		} 
		printf("\n");
		j = 0; 
		c =0; 
		i++;
	} 
	
	
    for (int row = 0; row < sizeof(board); row++)
    {
        for (int col = 0; col < sizeof(board[row]); col++)
        {
			
        }
    }
	
	return 0;
}

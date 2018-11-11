#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char board[9][9];
int count = 0;
void *CheckRow(void * row) {
	//char lst[9] ={'0','0','0','0','0','0','0','0','0'}; 
	pthread_mutex_t mutex;
	pthread_mutex_lock(&mutex);
	char lst[9] ={'0','0','0','0','0','0','0','0','0'};
	int *index = (int *) row;
	int temp;
	int j = *index;
	for (int i = 0; i < 9; i++) {
		temp = (int) board[j][i]-'0';
		printf("Value of temp: %d \n", temp);	
		if ( lst[temp] == '0' ) {
			lst[temp] = '1';
			//printf("TEST");
		}
		else  { 
			printf("Error found in row: %d column: %d",*index , i); 
			//printf("\n");
		}
		//printf( "%c", board[*index][i]);
	}
	count++;
	//printf("Current Index:  %d", *index);
	pthread_mutex_unlock(&mutex);
	printf("\n");
	return NULL;
}
int main() {
	char name[20]; printf("Enter Filename: \n"); scanf("%s", &name); 
	FILE *ptr; ptr = fopen(name, "r");
	int i = 0; int j = 0; int c = 0; char line[25];
	while (fgets(line, sizeof(line), ptr)){
		while (j < 9) {
			if (line[c] == '\0' || line[c] == '\n') {break;}
			if (line[c] == ' ' || line[j] == '\0') { c++; }
			else {
				board[i][j] = line[c];
				printf("%c", board[i][j]);
				j++; c++;
			}
		} printf("\n"); j = 0; c =0; 
		if (line[0] != '\n')
			i++;
	}
	//Prints Board ******	
	/*int k = 0; int l = 0;	
	for (k = 0; k < 9; k++) {
		for(l = 0; l < 9; l++) { printf("%c", board[k][l]); }
		printf("\n");
	}*/
	
	// Create Threads. *****
	pthread_t thread_id[27];
	//int count = 0;
	for (int i = 0; i < 9; i++) {
		printf("Index: %d", i);
		printf("\n");
		pthread_create(&thread_id[i], NULL, CheckRow, &count);
		//count++;
	}
	for (int i = 0; i < 9; i++) {
		pthread_join(thread_id[i], NULL);
	}
	return 0;
}

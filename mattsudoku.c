#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
struct BasicallyGlobal {
	char Vflag;
	char board[9][9];
	int count;
	pthread_mutex_t mutex;
};
void *CheckSect(void * sect) {
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) sect;
        pthread_mutex_lock(&ptr->mutex);
        char lst[9] ={'0','0','0','0','0','0','0','0','0'};
	ptr = (struct BasicallyGlobal*) sect;
	int i = 0; int j;
	for (int count = 0; count < 9; count++) {
		for (j = 0; j < 3; j++){
			//check if lst[board[count][i+j]-1] == '0'		
			if ( lst[board[count][i+j]-1] == '0' )
				 lst[board[count][i+j]-1] = '1';
		}
		if (i == 5)
			i = 0;
		else 
			i+=3;
		count++;
	}
}
void *CheckCol(void * col) {
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) col;
        pthread_mutex_lock(&ptr->mutex);
        char lst[9] ={'0','0','0','0','0','0','0','0','0'};
        ptr = (struct BasicallyGlobal*) col;
        int temp;
        int i = ptr->count;
        for (int j = 0; j < 9; j++) {
                temp = (int) ptr->board[j][i]-'0';
                if ( lst[temp-1] == '0' ) {
                        lst[temp-1] = '1';
                }
                else  {
                        printf("Error found in column: %d row: %d", ptr->count , j);
			ptr->Vflag = 'F';
                        printf("\n");
                }
                //printf( "%c", board[*index][i]);
        }
        ptr->count++;
        pthread_mutex_unlock(&ptr->mutex);
        return NULL;
}
void *CheckRow(void * row) {
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) row;
	pthread_mutex_lock(&ptr->mutex);
	char lst[9] ={'0','0','0','0','0','0','0','0','0'};
	ptr = (struct BasicallyGlobal*) row;
	int temp; 
	int j = ptr->count; 
	for (int i = 0; i < 9; i++) {
		temp = (int) ptr->board[j][i]-'0';
		if ( lst[temp-1] == '0' ) {
			lst[temp-1] = '1';
		}
		else  { 
			printf("Error found in row: %d column: %d", ptr->count , i); 
			ptr->Vflag = 'F';
			printf("\n");
		}
		//printf( "%c", board[*index][i]);
	}
	ptr->count++;
	pthread_mutex_unlock(&ptr->mutex);
	return NULL;
}
int main(int argc, char *argv[]) {
	struct BasicallyGlobal row; row.Vflag = 'T'; row.count = 0; 
	pthread_mutex_init(&row.mutex, NULL);
	int i = 0; int j = 0; int c = 0; char line[25];
	while (fgets(line, sizeof(line), stdin)){
		while (j < 9) {
			if (line[c] == '\0' || line[c] == '\n') {break;}
			if (line[c] == ' ' || line[j] == '\0') { c++; }
			else {
				row.board[i][j] = line[c];
				printf("%c", row.board[i][j]);
				j++; c++;
			}
		} printf("\n"); j = 0; c =0; 
		if (line[0] != '\n')
			i++;
	}
	struct BasicallyGlobal col = row;
	//Prints Board ******	
	int k = 0; int l = 0;	
	for (k = 0; k < 9; k++) {
		for(l = 0; l < 9; l++) { printf("%c", row.board[k][l]); }
		printf("\n");
	}
	
	// Create Threads. *****
	pthread_t thread_id[27];
	for (int i = 0; i < 9; i++) {
		pthread_create(&thread_id[i], NULL, CheckRow, &row);
		pthread_create(&thread_id[i+9], NULL, CheckCol, &col);
	}
	for (int i = 0; i < 9; i++) {
		pthread_join(thread_id[i], NULL);
	}
	if (row.Vflag == 'T' && col.Vflag == 'T') {printf("The sudoku is valid!\n");}
	return 0;
}

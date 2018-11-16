#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
struct BasicallyGlobal {
	char Vflag;
	char board[9][9];
	int count;
};
void *CheckSect(void * sect) {
	//Function that checks one sector of the board at a time.
	//******************************************************
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) sect;
	ptr = (struct BasicallyGlobal*) sect;
	// Char array to keep track of what is seen.
	char lst[9] = {'0','0','0','0','0','0','0','0','0'};
	// 2D int array to store the leftmost positions of each sector.
	int pair[9][2] = {{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};
	// Basic variables used for tracking and simplicity.
	int temp; char err = ' ';
	for(int i = pair[ptr->count][0]; i < pair[ptr->count][0]+3; i++) {
		for(int j = pair[ptr->count][1]; j < pair[ptr->count][1]+3; j++) {
			temp = (int) ptr->board[i][j]-'0';
			if (lst[temp-1] == '0')
				lst[temp-1] = '1';
			else 
				err = '1';
		}
	}
	if (err != ' '){
		printf("Error found in sector: %d \n", ptr->count);
		ptr->Vflag = 'F';
	}
	ptr->count++;
	return NULL;
}
void *CheckCol(void * col) {
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) col;
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
        }
        ptr->count++;
        return NULL;
}
void *CheckRow(void * row) {
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) row;
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
	}
	ptr->count++;
	return NULL;
}
int main(int argc, char *argv[]) {
	// Read in board from stdin. ****************************
	struct BasicallyGlobal row; row.Vflag = 'T'; row.count = 0; 
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
	struct BasicallyGlobal sect = col;
	// Create Threads. **************************************
	pthread_t thread_id[27];
	for (int i = 0; i < 9; i++) {
		pthread_create(&thread_id[i], NULL, CheckRow, &row);
		pthread_create(&thread_id[i+9], NULL, CheckCol, &col);
		pthread_create(&thread_id[i+18], NULL, CheckSect, &sect);
	}
	for (int i = 0; i < 27; i++) {
		pthread_join(thread_id[i], NULL);
	}
	if (row.Vflag == 'T' && col.Vflag == 'T' && sect.Vflag == 'T') {printf("The sudoku is valid!\n");}
	return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char board[9][9];
int count = 0;
pthread_mutex_t mutex;

struct BasicallyGlobal {
	char Vflag;
	char board[9][9];
	int Rcount;
	int Ccount;
	char Rerr;
	char Cerr;
};
void *CheckCol(void * col) {
        pthread_mutex_lock(&mutex);
        char lst[9] ={'0','0','0','0','0','0','0','0','0'};
        struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) col;
        int temp;
        int i = ptr->Ccount;
        for (int j = 0; j < 9; j++) {
                temp = (int) ptr->board[j][i]-'0';
                if ( lst[temp-1] == '0' ) {
                        lst[temp-1] = '1';
                }
                else  {
                        printf("Error found in column: %d row: %d", ptr->Ccount , j);
                        printf("\n");
                }
                //printf( "%c", board[*index][i]);
        }
        //printf("\n");
        ptr->Ccount++;
        pthread_mutex_unlock(&mutex);
        return NULL;
}

void *CheckRow(void * row) {
	pthread_mutex_lock(&mutex);
	char lst[9] ={'0','0','0','0','0','0','0','0','0'};
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) row;
	int temp; 
	int j = ptr->Rcount; 
	for (int i = 0; i < 9; i++) {
		temp = (int) ptr->board[j][i]-'0';
		if ( lst[temp-1] == '0' ) {
			lst[temp-1] = '1';
		}
		else  { 
			printf("Error found in row: %d column: %d", ptr->Rcount , i); 
			printf("\n");
		}
		//printf( "%c", board[*index][i]);
	}
	//printf("\n");
	ptr->Rcount++;
	pthread_mutex_unlock(&mutex);
	return NULL;
}
int main(int argc, char *argv[]) {
	//struct BasicallyGlobal 
	//char name[20]; printf("Enter Filename: \n"); scanf("%s", &name); 
	//FILE *ptr; ptr = fopen(name, "r");
	struct BasicallyGlobal dumb; dumb.Vflag = 'T'; dumb.Rcount = 0; 
	dumb.Rerr = ' '; dumb.Ccount = 0; dumb.Cerr = ' ';
	int i = 0; int j = 0; int c = 0; char line[25];
	while (fgets(line, sizeof(line), stdin)){
		while (j < 9) {
			if (line[c] == '\0' || line[c] == '\n') {break;}
			if (line[c] == ' ' || line[j] == '\0') { c++; }
			else {
				dumb.board[i][j] = line[c];
				printf("%c", dumb.board[i][j]);
				j++; c++;
			}
		} printf("\n"); j = 0; c =0; 
		if (line[0] != '\n')
			i++;
	}
	//Prints Board ******	
	int k = 0; int l = 0;	
	for (k = 0; k < 9; k++) {
		for(l = 0; l < 9; l++) { printf("%c", dumb.board[k][l]); }
		printf("\n");
	}
	
	// Create Threads. *****
	pthread_t thread_id[27];
	//int count = 0;
	for (int i = 0; i < 9; i++) {
		//pthread_create(&thread_id[i], NULL, CheckRow, &count);
		pthread_create(&thread_id[i], NULL, CheckRow, &dumb);
	}
	for (int i = 9; i < 18; i++) {
                //pthread_create(&thread_id[i], NULL, CheckRow, &count);
                pthread_create(&thread_id[i], NULL, CheckCol, &dumb);
        }
	for (int i = 0; i < 9; i++) {
		pthread_join(thread_id[i], NULL);
	}
	return 0;
}

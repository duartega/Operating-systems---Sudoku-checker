#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct BasicallyGlobal {
	char Vflag;
	char board[9][9];
	int count;
};
void *CheckSector(int * ii, int *jj, int * c) {
	// We could pass in the i and j as well as the count to go row by row
	struct BasicallyGlobal* ptr = (struct BasicallyGlobal*) sect;
	ptr = (struct BasicallyGlobal*) sect;
	char lst[9] = {'0','0','0','0','0','0','0','0','0'};


	int temp; char err = ' ';

	int i = (int) *ii;   int j = (int) *jj;  int count = (int) *c;
	printf ("\n HERE: \n");
    while (j != 9 && i != 9)
    {
        printf("%c",ptr->board[i][j],  ", ");
		if ( (j+1) % 3 == 0 )
        {
                if (count == 0) {printf(" TOP-LEFT");} if (count == 3) {printf(" TOP-MIDDLE");} if (count == 6) {printf(" TOP-RIGHT");}
                if (count == 9) {printf(" MIDDLE-LEFT");} if (count == 12) {printf(" MIDDLE-MIDDLE");} if (count == 15) {printf(" MIDDLE-RIGHT");}
                if (count == 18) {printf(" BOTTOM-LEFT");} if (count == 21) {printf(" BOTTOM-MIDDLE");} if (count == 24) {printf(" BOTTOM-RIGHT");}

                count ++;
                i++;

                if (count <= 2) {j = -1;}
                if (count >= 3 && count <= 5) {j = 2;}
                if (count >= 6 && count <= 8) {j = 5;}                
                if (count % 3 == 0 && count < 9) {i = 0; printf ("\n");}
                
                if (count == 9 || count == 18 || count == 27) {printf ("\n"); memset(&lst[0], '0', sizeof(lst));} // Prints new lines only
            
                if (count >= 9 && count <= 11) {j = -1;}
                if (count >= 12 && count <= 14) {j = 2;}
                if (count >= 15 && count <= 17) {j = 5;}
                if (count % 3 == 0 && count > 9 && count < 18) {i = 3; printf ("\n");}

                if (count >= 18 && count <= 20) {j = -1;}
                if (count >= 21 && count <= 23) {j = 2;}
                if (count >= 24 && count <= 26) {j = 5;}
                if (count % 3 == 0 && count > 18 && count < 30) {i = 6; printf ("\n");}
                printf ("\n");
        }
		temp = (int) ptr->board[i][j]-'0';
        if (lst[temp-1] == '0')
            lst[temp-1] = '1';
        else 
            err = '1';
        j++;
        
	}

	if (err != ' '){
		printf("Error found in sector: %d \n", ptr->count);
		ptr->Vflag = 'F';
	}

	
	ptr->count++;
	//for (int i = 0; i < 27; i++) {
	//	pthread_join(thread_id[i], NULL);
	//}
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
	pthread_t thread_id[18];
	for (int i = 0; i < 9; i++) {
		pthread_create(&thread_id[i], NULL, CheckRow, &row);
		pthread_create(&thread_id[i+9], NULL, CheckCol, &col);
	    //pthread_create(&thread_id[i+18], NULL, CheckSect, &sect);	
	}

	int *m = 0; int *n = 0; int *count = 0;
	while (*m != 9 && *n != 9){
		//CheckSector(m, n, count);
		pthread_create(&thread_id[i+18], NULL, CheckSector(m, n, count), &sect);
		
	}


	for (int i = 0; i < 18; i++) {
		pthread_join(thread_id[i], NULL);
	}
	if (row.Vflag == 'T' && col.Vflag == 'T' && sect.Vflag == 'T') {printf("The sudoku is valid!\n");}
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t row;
sem_t col;
int temp, x, y, k;
int a[4][4];
int count = 0;
pthread_t A,B,C,D;

void sortEvenRow(){
	for (k = 0;k < 4;k=k+2){
		for(x=0;x<3;x++){
			for(y = 0;y < 3 - x;y++){
				if(a[k][y] > a[k][y+1]){
					temp = a[k][y + 1];
					a[k][y + 1] = a[k][y];
					a[k][y] = temp;
				}
			}
		}
	}
}

void sortOddRow(){
	for (k = 1;k < 4;k=k+2){
		for(x=0;x<3;x++){
			for(y = 0;y < 3 - x;y++){
				if(a[k][y] < a[k][y+1]){
					temp = a[k][y + 1];
					a[k][y + 1] = a[k][y];
					a[k][y] = temp;
				}
			}
		}
	}
}

void sortCol(){
	for (k = 0; k < 4; k++)
	{
		for (x = 0; x < 3; x++)
		{
			for (y = 0; y < 3 - x; y++)
			{
				if (a[y + 1][k] < a[y][k])
				{
					temp = a[y + 1][k];
					a[y + 1][k] = a[y][k];
					a[y][k] = temp;
				}
			}
		}
	}
}

void answer(){
	int i;
	for (i=0;i<4;i++){
		printf("%d %d %d %d\n",a[i][0],a[i][1], a[i][2], a[i][3]);
	}
}

void *phaseRow(void *arg){
	while(count<3){
		sem_wait(&row);
		count++;
		sortEvenRow();
		sortOddRow();
		printf("next phase\n");
		answer();
		sem_post(&col);
	}
}

void *phaseCol(void *arg){
	while(count<2){
		sem_wait(&col);
		count++;
		sortCol();
		printf("next phase\n");
		answer();
		sem_post(&row);
	}
}

int main( ) {
	FILE *fin;
	int i;
	fin = fopen("input.txt","r");
	for (i=0;i<4;i++){
		fscanf(fin,"%d %d %d %d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]); 
	}
	fclose(fin); 
	printf("initially\n");
	answer();

	sem_init(&row, 0, 1);
	sem_init(&col, 0, 0);
	pthread_create(&A,NULL,phaseRow,NULL);
	pthread_create(&B,NULL,phaseRow,NULL);
	pthread_create(&C,NULL,phaseCol,NULL);
	pthread_create(&D,NULL,phaseCol,NULL);
	pthread_join(A,NULL);
	pthread_join(B,NULL);
	pthread_join(C,NULL);
	pthread_join(D,NULL);
	sem_destroy(&row);
	sem_destroy(&col);
	return 0;
}
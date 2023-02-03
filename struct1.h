#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

typedef struct AVL{
	int id;
	int nb;
	float dataMax;
	float dataMin;
	float dataAver;
	char date[1024];
	struct AVL *fg;
	struct AVL *fd;
	int balance;
}AVL;
typedef AVL *pAVL;

typedef struct ABR{
	int id;
	int nb;
	float dataMax;
	float dataMin;
	float dataAver;
	char date[1024];
	struct ABR *fg;
	struct ABR *fd;
}ABR;
typedef ABR *pABR;


pAVL createAVL(int id, float data, char newDate[1024]);
pAVL insertAVL(pAVL a, int id, float data, char newDate[50], int* h);
int compare_dates(char date1[1024], char date2[1024]);
void infAVL(pAVL a, FILE* file);
void revAVL(pAVL a, FILE* file);
pAVL leftRota(pAVL a);
pAVL balanceAVL(pAVL a);
pAVL rightRota(pAVL a );
pAVL doubleLeftRota(pAVL a);
pAVL doubleRightRota(pAVL a);
int max(int a, int b);
int min(int a, int b);

pABR createABR(int newId, float newData, char newDate[1024]);
pABR insertABR(pABR a, int newID, float newData, char newDate[1024]);
void infABR(pABR a, FILE* file);
void revABR(pABR a, FILE* file);

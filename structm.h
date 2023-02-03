#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLm{
	float lat;
	float longit;
	float moist;
	struct AVLm *fg;
	struct AVLm *fd;
	int balance;
}AVLm;
typedef AVLm *pAVLm;

typedef struct ABRm{
	float longit;
	float lat;
	float moist;
	struct ABRm *fg;
	struct ABRm *fd;
}ABRm;
typedef ABRm *pABRm;

pAVLm rightRotam(pAVLm a );
pAVLm doubleLeftRotam(pAVLm a);
pAVLm doubleRightRotam(pAVLm a);
int maxi(int a, int b);
int mini(int a, int b);

pAVLm createAVLm(float lat, float longit, float data);
pAVLm insertAVLm(pAVLm a, float lat, float longit, float data, int* h);
void infAVLm(pAVLm a, FILE* file);
void revAVLm(pAVLm a, FILE* file);
pAVLm balanceAVLm(pAVLm a);

pABRm createABRm(float lat, float longit, float data);
pABRm insertABRm(pABRm a, float lat, float longit, float data);
void infABRm(pABRm a, FILE* file);
void revABRm(pABRm a, FILE* file);
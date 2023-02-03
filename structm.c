#include "structm.h"

pAVLm leftRotam(pAVLm a){
	pAVLm pivot;
	int eq_a, eq_p;
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->balance;
	eq_p = pivot ->balance;
	a->balance = eq_a - maxi(eq_p, 0) -1;
	pivot->balance = mini(mini(eq_a-2, eq_a+eq_p-2), eq_p-1);
	a = pivot;
	return a;
}
pAVLm rightRotam(pAVLm a ){
	 pAVLm pivot;
	 int eq_a, eq_p;
	 pivot = a->fg;
	 a->fg = pivot->fd;
	 eq_a = a->balance;
	 eq_p = pivot->balance;
	 pivot->balance = eq_a - mini(eq_p, 0) +1;
	 pivot ->balance = maxi(maxi(eq_a+2, eq_a+eq_p+2), eq_p+1);
	 a = pivot;
	 return a;
}
pAVLm doubleLeftRotam(pAVLm a){
 	a->fd = rightRotam(a->fd);
 	return leftRotam(a);
}
pAVLm doubleRightRotam(pAVLm a){
 	a->fg = leftRotam(a->fg);
 	return rightRotam(a);
}
int maxi(int a, int b){
    if(a>=b){
    	return a;
     }
    else{ 
    	return b;
    }	
}
int mini(int a, int b){
    if(a<=b){
    	return a;
     }
    else{ 
    	return b;
    }	
}

/*------------- FUNCTION FOR AVL -------------*/
pAVLm createAVLm(float lat, float longit, float data){
	pAVLm knot = malloc(sizeof(AVLm));
	if (knot == NULL){
		exit(0);
	}

	knot->lat = lat;
	knot->longit = longit;
	knot->moist = data;
	knot->fg = NULL;
	knot->fd = NULL;
	knot->balance = 0;
	return knot;
}
pAVLm insertAVLm(pAVLm a, float lat, float longit, float data, int* h){
	if(a==NULL){
		*h = 1;
		return createAVLm(lat,longit,data);
	}
	else if(data <= a->moist && (lat!=a->lat || longit!=a->longit)){
		a->fg = insertAVLm(a->fg, lat, longit, data, h);
		*h = -*h;
	}
	else if( data > a->moist){
		a->fd = insertAVLm(a->fd, lat, longit, data, h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->balance = a->balance + *h;
	}
	if(a->balance ==0){
		*h = 0;
	}
	else{
		*h = 1;
	}
	return a;
}
void infAVLm(pAVLm a, FILE* file){
	if(a!=NULL){
		if(a->fg != NULL){
			infAVLm(a->fg,file);
		}
		fprintf(file, "%f\t%f\t%f\n", a->lat, a->longit, a->moist);
		if (a->fd != NULL){
			infAVLm(a->fd, file);
		}
	}
}
void revAVLm(pAVLm a, FILE* file){
	if(a!=NULL){
		if(a->fd != NULL){
			revAVLm(a->fd,file);
		}
		fprintf(file, "%f\t%f\t%f\n", a->lat, a->longit, a->moist);
		if (a->fg != NULL){
			revAVLm(a->fg, file);
		}
	}
}
pAVLm balanceAVLm(pAVLm a){
	if (a->balance >= 2 ){
		if ( a->fd ->balance >= 0){
			return leftRotam(a);
		} else {
			return doubleLeftRotam(a);
		}
	}
	else if (a->balance <= -2){
		if (a->fg ->balance <= 0){
			return rightRotam(a);
		}else{
			return doubleRightRotam(a);
		}
	}
	return a;
}

/*------------- FUNCTION FOR ABR -------------*/
pABRm createABRm(float lat, float longit, float data){
	pABRm knot = malloc(sizeof(ABRm));
	if (knot == NULL){
		exit(0);
	}

	knot->lat = lat;
	knot->longit = longit;
	knot->moist = data;
	knot->fg = NULL;
	knot->fd = NULL;
	return knot;
}
pABRm insertABRm(pABRm a, float lat, float longit, float data){
	if(a==NULL){
		return createABRm(lat,longit,data);
	}
	else if(data <= a->moist && (lat!=a->lat || longit!=a->longit)){
		a->fg = insertABRm(a->fg, lat, longit, data);
	}
	else if( data > a->moist){
		a->fd = insertABRm(a->fd, lat, longit, data);
	}
	else{
		return a;
	}
	return a;
}
void infABRm(pABRm a, FILE* file){
	if(a!=NULL){
		if(a->fg != NULL){
			infABRm(a->fg,file);
		}
		fprintf(file, "%f\t%f\t%f\n", a->lat, a->longit, a->moist);
		if (a->fd != NULL){
			infABRm(a->fd, file);
		}
	}
}
void revABRm(pABRm a, FILE* file){
	if(a!=NULL){
		if(a->fd != NULL){
			revABRm(a->fd,file);
		}
		fprintf(file, "%f\t%f\t%f\n", a->lat, a->longit, a->moist);
		if (a->fg != NULL){
			revABRm(a->fg, file);
		}
	}
}

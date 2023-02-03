#include "struct.h"

int compare_dates(const char *date1, const char *date2) {
    struct tm tm1, tm2;
    memset(&tm1, 0, sizeof(struct tm));
    memset(&tm2, 0, sizeof(struct tm));
    strptime(date1, "%Y-%m-%dT%H:%M:%S%z", &tm1);
    strptime(date2, "%Y-%m-%dT%H:%M:%S%z", &tm2);

    time_t t1 = mktime(&tm2);
	time_t t2 = mktime(&tm2);
    if (t1 < t2) {
        return -1;
    } else if (t1 == t2) {
        return 0;
    } else {
        return 1;
    }
}

pAVL createAVL(int id, float data, char newDate[50]){
	pAVL knot = malloc(sizeof(AVL));
	if (knot == NULL){
		exit(0);
	}
	knot->id = id;
	strcpy(knot->date, newDate);
	knot->nb = 1;
	knot->dataMax = data;
	knot->dataMin = data;
	knot->dataAver = data;
	knot->fg = NULL;
	knot->fd = NULL;
	knot->balance = 0;
	strcpy(knot->date,newDate);
	return knot;
}

//This function is based on data arguments
pAVL insertAVL(pAVL a, int id, float data, char newDate[50], int* h){
	if(a==NULL){
		*h = 1;
		return createAVL(id,data,newDate);
	}
	else if(id < a->id){
		a->fg = insertAVL(a->fg, id, data, newDate, h);
		*h = -*h;
	}
	else if( id > a->id){
		a->fd = insertAVL(a->fd, id, data, newDate, h);
	}
	else{
		*h = 0;
		if(data!=0){
			if(data >= a->dataMax){
				a->dataMax = data;
			}
			else if (data <= a->dataMin){
				a->dataMin = data;
			}
			//Calculatig the average data for a specific station ID according to the number "nb" of data collected
			a->dataAver=a->dataAver*a->nb;
			a->nb+=1;
			a->dataAver+=data;
			a->dataAver=a->dataAver/(a->nb);
		}
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

//This function is based on date arguments
pAVL insertAVL2(pAVL a, int id, float data, char newDate[50], int* h){
	if(a==NULL){
		*h = 1;
		return createAVL(id,data,newDate);
	}
	else if(compare_dates(a->date, newDate)==1){
		a->fg = insertAVL2(a->fg, id, data, newDate, h);
		*h = -*h;
	}
	else if(compare_dates(a->date, newDate)==-1){
		a->fd = insertAVL2(a->fd, id, data, newDate, h);
	}
	else{
		*h = 0;
		if(data>a->dataMax){
			a->dataMax = data;
		}
		else if (data<a->dataMin){
			a->dataMin = data;
		}
		//Calculatig the average data for a specific station ID according to the number "nb" of data collected
		a->dataAver=a->dataAver*a->nb;
		a->nb+=1;
		a->dataAver+=data;
		a->dataAver=a->dataAver/(a->nb);
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

void infAVL(pAVL a, FILE* file){
	if(a!=NULL){
		if(a->fg != NULL){
			infAVL(a->fg,file);
		}
		fprintf(file, "%d\t%f\t%f\t%f\n", a->id, a->dataAver, a->dataMin, a->dataMax);
		if (a->fd != NULL){
			infAVL(a->fd, file);
		}
	}
}

pAVL balanceAVL(pAVL a){
	if (a->balance >= 2 ){
		if ( a->fd ->balance >= 0){
			return leftRota(a);
		} else {
			return doubleLeftRota(a);
		}
	}
	else if (a->balance <= -2){
		if (a->fg ->balance <= 0){
			return rightRota(a);
		}else{
			return doubleRightRota(a);
		}
	}
	return a;
}

pAVL leftRota(pAVL a){
	pAVL pivot;
	int eq_a, eq_p;
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->balance;
	eq_p = pivot ->balance;
	a->balance = eq_a - max(eq_p, 0) -1;
	pivot->balance = min(min(eq_a-2, eq_a+eq_p-2), eq_p-1);
	a = pivot;
	return a;
}

pAVL rightRota(pAVL a ){
	 pAVL pivot;
	 int eq_a, eq_p;
	 pivot = a->fg;
	 a->fg = pivot->fd;
	 eq_a = a->balance;
	 eq_p = pivot->balance;
	 pivot->balance = eq_a - min(eq_p, 0) +1;
	 pivot ->balance = max(max(eq_a+2, eq_a+eq_p+2), eq_p+1);
	 a = pivot;
	 return a;
}

pAVL doubleLeftRota(pAVL a){
 	a->fd = rightRota(a->fd);
 	return leftRota(a);
}

pAVL doubleRightRota(pAVL a){
 	a->fg = leftRota(a->fg);
 	return rightRota(a);
}

int max(int a, int b){
    if(a>=b){
    	return a;
     }
    else{ 
    	return b;
    }	
}

int min(int a, int b){
    if(a<=b){
    	return a;
     }
    else{ 
    	return b;
    }	
}

float diff(float a, float b){
	float result;
	if (a<0){a=-a;}
	if(b<0){b=-b;}
	result = a-b;
	if(result<0){return (-result);}
	else{return result;}
}

pABR createABR(int id, float data){
	
}
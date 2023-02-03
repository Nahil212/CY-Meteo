#include "struct1.h"

int compare_dates(char date1[1024], char date2[1024]) {
    int year1, year2, month1, month2, day1, day2, hour1, hour2, minute1, minute2, second1, second2, offset1, offset2;
    double diff;

    sscanf(date1, "%d-%d-%dT%d:%d:%d%d:%d", &year1, &month1, &day1, &hour1, &minute1, &second1, &offset1, &offset1);
    sscanf(date2, "%d-%d-%dT%d:%d:%d%d:%d", &year2, &month2, &day2, &hour2, &minute2, &second2, &offset2, &offset2);

    struct tm tm1 = { 0, second1, minute1, hour1, day1 - 1, month1 - 1, year1 - 1900, 0, 0, 0 };
    struct tm tm2 = { 0, second2, minute2, hour2, day2 - 1, month2 - 1, year2 - 1900, 0, 0, 0 };

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    diff = difftime(time1, time2);

    if (diff > 0) {
        return 1;
    } else if (diff < 0) {
        return -1;
    } else {
        return 0;
    }
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

/*------------- FUNCTION FOR AVL -------------*/
pAVL createAVL(int newID, float data, char newDate[1024]){
	pAVL knot = malloc(sizeof(AVL));
	if (knot == NULL){
		exit(0);
	}
	knot->id = newID;
	strcpy(knot->date, newDate);
	knot->nb = 1;
	knot->dataMax = data;
	knot->dataMin = data;
	knot->dataAver = data;
	knot->fg = NULL;
	knot->fd = NULL;
	knot->balance = 0;
	return knot;
}
pAVL insertAVL(pAVL a, int newID, float newData, char newDate[50], int* h){
	if(a==NULL){
		*h = 1;
		return createAVL(newID,newData,newDate);
	}
	else if(newID < a->id){
		a->fg = insertAVL(a->fg, newID, newData, newDate, h);
		*h = -*h;
	}
	else if( newID > a->id){
		a->fd = insertAVL(a->fd, newID, newData, newDate, h);
	}
	else{
		*h = 0;
		if(newData!=0){
			if(newData >= a->dataMax){
				a->dataMax = newData;
			}
			else if (newData <= a->dataMin){
				a->dataMin = newData;
			}
			//Calculatig the average data for a specific station ID according to the number "nb" of data collected
			a->dataAver=a->dataAver*a->nb;
			a->nb+=1;
			a->dataAver+=newData;
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
void revAVL(pAVL a, FILE* file){
	if(a!=NULL){
		if(a->fd != NULL){
			revAVL(a->fd,file);
		}
		fprintf(file, "%d\t%f\t%f\t%f\n", a->id, a->dataAver, a->dataMin, a->dataMax);
		if (a->fg != NULL){
			revAVL(a->fg, file);
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

/*------------- FUNCTION FOR ABR -------------*/
pABR createABR(int newId, float newData, char newDate[1024]){
	pABR knot = malloc(sizeof(ABR));
	if (knot ==NULL){
		exit(0);
	}
	knot->fg = NULL;
	knot->fd = NULL;
	strcpy(knot->date, newDate);
	knot->id = newId;
	knot->dataMax = newData;
	knot->dataAver = newData;
	knot->dataMin = newData;
	knot->nb = 1;

}
pABR insertABR(pABR a, int newID, float newData, char newDate[1024]){
	if (a==NULL){
		return createABR(newID,newData,newDate);
	}
	else if (a->id > newID){
		a->fg = insertABR(a->fg,newID,newData,newDate);
	}
	else if (a->id < newID){
		a->fd = insertABR(a->fd,newID,newData,newDate);
	}
	else{
		if (newData!=0){
			a->dataAver = a->dataAver * a->nb;
			a->dataAver = a->dataAver + newData;;
			a->nb += 1;
			a->dataAver = a->dataAver / a->nb;
			if (a->dataMax < newData){
				a->dataMax = newData;
			}
			else if (a->dataMin > newData){
				a->dataMin = newData;
			}
		}
		return a;
	}
	return a;
}
void infABR(pABR a, FILE* file){
	if(a!=NULL){
		infABR(a->fg,file);
		fprintf(file, "%d\t%f\t%f\t%f\n", a->id, a->dataAver, a->dataMin, a->dataMax);
		infABR(a->fd,file);
	}
}
void revABR(pABR a, FILE* file){
	if(a!=NULL){
		revABR(a->fd,file);
		fprintf(file, "%d\t%f\t%f\t%f\n", a->id, a->dataAver, a->dataMin, a->dataMax);
		revABR(a->fg,file);
	}
}
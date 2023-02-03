#include "struct1.h"
#include "structm.h"

int main(int argc, char *argv[]){
  FILE* file = fopen(argv[2], "r"), *fileResult= fopen(argv[5], "w");
  char* arg = argv[1];
  char* sort= argv[3];
  char* order = argv[6];
  long i, nbLine = strtol(argv[4], NULL, 10);
  char date[1024];
  char line[1024];
  pAVL AVL=NULL;
  pAVLm AVLm=NULL;
  pABR ABR=NULL;
  pABRm ABRm=NULL;
  float data, lat, longit, moist;
  int id, h;



  if (file==NULL){
    printf("ERROR opening file! \n");
    exit(1);
  }
  fgets(line, 1024, file);


  //Sorting data
  for(i=0;i<nbLine-1;i++){
    if (fgets(line, 1024, file) != NULL) {
      if ((strcmp(arg,"-t1")==0)||(strcmp(arg,"-p1")==0)){
        //In the CSV file, some cases are empty then we have to fill them with 0 so the program can work
        if (sscanf(line, "%d ; %99[^;] ; %f", &id, date, &data) < 3) {
          data = 0;
        }
        if (strcmp(sort,"--abr")==0){
          ABR = insertABR(ABR,id,data,date);
        }
        else {
          AVL = insertAVL(AVL,id,data,date,&h);
        }
      }
      else if ((strcmp(arg,"-m")==0) || (strcmp(arg,"-h")==0)){
        if (sscanf(line, "%f ; %f ; %f", &lat, &longit, &moist) < 3) {
          moist = 0;
        }
        if (strcmp(sort,"--abr")==0){
          ABRm = insertABRm(ABRm,lat,longit,moist);
        }else{
          AVLm = insertAVLm(AVLm,lat,longit,moist,&h);
        }
      }
    }
  }
  


  //Writing in the data file 
  if (strcmp(sort,"--abr")==0){
    if ((strcmp(arg,"-t1")==0)||(strcmp(arg,"-p1")==0)){
      if(strcmp(order,"-r")==0){
        revABR(ABR,fileResult);
      }
      else {infABR(ABR,fileResult);}
      
    } else if ((strcmp(arg,"-m")==0) || (strcmp(arg,"-h")==0)) {
      if(strcmp(order,"-r")==0){
        revABRm(ABRm,fileResult);
      }else{infABRm(ABRm,fileResult);}
      fprintf(fileResult, "\n");
    }
  } else {
    if ((strcmp(arg,"-t1")==0)||(strcmp(arg,"-p1")==0)){
      if(strcmp(order,"-r")==0){
        revAVL(AVL,fileResult);
      }else{infAVLm(AVLm,fileResult);}
      infAVL(AVL,fileResult);
    } else if ((strcmp(arg,"-m")==0) || (strcmp(arg,"-h")==0)) {
      if(strcmp(order,"-r")==0){
        revAVLm(AVLm,fileResult);
      }else{infAVLm(AVLm,fileResult);}
      fprintf(fileResult, "\n");
    }
  }


  //Closing file
  fclose(file);
  fclose(fileResult);
}

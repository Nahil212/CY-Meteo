#include "struct.h"

int main(int argc, char *argv[]) {
  FILE* file = fopen(argv[2], "r"), *fileResult= fopen("data.dat", "w");
  char* arg = argv[1];
  char* sort= argv[3];
  long i, nbLine = strtol(argv[4], NULL, 10);
  char date[1024];
  char line[1024];
  pAVL AVL;
  float data;
  int id, h;

  if (file==NULL){
    printf("ERROR opening file! \n");
    exit(1);
  }
  
  fgets(line, 1024, file);
  fscanf(file, "%d ; %99[^;] ; %f", &id, date, &data);
  AVL = createAVL(id,data,date);

  
  //Sorting data
  for(i=0;i<nbLine-1;i++){
    if (fgets(line, 1024, file) != NULL) {
      if (sscanf(line, "%d ; %99[^;] ; %f", &id, date, &data) < 3) {
        data = 0;
      }
    }
    //printf(" ID:%d\n ", id);
    AVL = insertAVL(AVL,id,data,date,&h);
    AVL = balanceAVL(AVL);
  }

  //Writing sorted data in the file
  infAVL(AVL, fileResult);
}

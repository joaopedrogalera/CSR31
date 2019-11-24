#include <stdio.h>
#include "plotg.h"

int plotg(char* manchester){
  FILE *gp, *plot;
  int i;

  gp = popen("gnuplot -persist 2>/dev/null","w");
  if(gp == NULL){
    printf("gnuplot não instalado\n");
    return(-1);
  }
  plot = fopen("plot.txt","w");
  for(i=0;manchester[i]!='\0';i++){
    if(i>0){
      fprintf(plot, "%d\t%c\n",i,manchester[i-1]);
    }
    fprintf(plot, "%d\t%c\n",i,manchester[i]);
  }
  fclose(plot);
  fprintf(gp, "set yrange [0:2]\n");
  fprintf(gp, "set xrange [0:%d]\n",i);
  fprintf(gp, "plot 'plot.txt' with linespoints ls 1\n");
  fclose(gp);
  return (0);
}

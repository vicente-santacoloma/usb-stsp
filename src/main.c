#include <stdio.h>
#include <math.h>
#include "TSP-TEST.V0.9/instance.h"
#include "TSP-TEST.V0.9/utilities.h"
#include "TSP-TEST.V0.9/timer.h"
#include "TSP-TEST.V0.9/ls.h"
#include "iterated_hill_climber.h"

int main (int argc, char **argv) {
  
  int * best;
  int max = 0;
  read_instance(argv[1]);
  distMat = compute_distances();
  nn_ls = MIN (ncities - 1, 40);
  nnMat = compute_NNLists();
  max = ncities*100;
  start_timers();
  best = iterated_hill_climber(max);
  float time = fabs(elapsed_time( VIRTUAL));
  printf("\n\n");
  printf("RESULTS:");
  printf("\n\n");
  printf("Best Tour Found:\n");
  printTour(best);
  printf("Length: %d\n",compute_length(best));
  printf("Total Iteration Number: %d\n",max);
  printf("Total Time: %f seconds\n",time);
  printf("Iteration Best Found: %d\n",iteration_best_found);
  printf("Time Best Found: %f seconds\n", time_best_found);
  
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "TSP-TEST.V0.9/instance.h"
#include "TSP-TEST.V0.9/utilities.h"
#include "TSP-TEST.V0.9/timer.h"
#include "TSP-TEST.V0.9/ls.h"
#include "iterated_hill_climber.h"

void copy_vector (int * vector1, int * vector2) {
  int i;
  for(i = 0; i < ncities; i++)
    vector1[i] = vector2[i];
}

int * iterated_hill_climber(int max) {
  
/* BEGIN */

  int t;
  int * best;
  int * tour;
  int * random;
  
  seed = (long int) time(NULL);
  tour = malloc((ncities + 1 ) * sizeof(int));
  
/* Initialize best */
  best = malloc((ncities + 1 ) * sizeof(int));
  random = generate_random_vector();
  copy_vector(best,random);
  free(random);
  best[ncities] = best[0];
  
  for(t = 0; t < max; t++) {
    
    dlb = calloc(ncities, sizeof(int));
    random = generate_random_vector();
    copy_vector(tour,random);
    tour[ncities] = tour[0];
     
    three_opt_first(tour);
   
    if(compute_length(tour) < compute_length(best)) {
      copy_vector(best,tour);
      best[ncities] = best[0];
      iteration_best_found = t;
      time_best_found = fabs(elapsed_time( VIRTUAL ));
    }
    free(random); 
    free(dlb);
    
  }
  free(tour);
/* END */
  return best;

}
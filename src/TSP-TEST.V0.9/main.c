/*

######################################################
###    simple LS and ILS algorithms for the TSP    ###
######################################################

      Version: 0.1
      File:    main.c
      Author:  Thomas Stuetzle
      Purpose: main routines and control for local search and iterated local search
      Check:   README and gpl.txt
      Copyright (C) 2004  Thomas Stuetzle
*/

/***************************************************************************

    Program's name: tsp-test

    iterative improvement (2-opt, 3-opt) for the TSP and a
    simple ILS algorithm for the TSP

    Copyright (C) 2004  Thomas Stuetzle

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    email: stuetzle no@spam informatik.tu-darmstadt.de
    mail address: Universitaet Darmstadt
                  Fachbereich Informatik
                  Hochschulstr. 10
                  D-64283 Darmstadt
		  Germany

***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "instance.h"
#include "utilities.h"
#include "timer.h"
#include "ls.h"

#define TIMING

int main (int argc, char **argv) 

{
    printf("INT_MAX: %ld \n",LONG_MAX);
    /* remark: tours are represented as a permutation of the city
       indices 0 to n-1 (i.e., n cities); additionally, at the position n,
       the index of the first city is repeated. This eases the computation of
       tour length etc. This is also the reason why the malloc below
       allocates a vector of length ncities + 1. */

    int i, j, try;
    int *tour;     /* current tour for ILS */
    int *shadow;   /* modified tour after double-bridge move */
    int *random;   /* a random vector */
    int length;    /* length of tour */
    char temp_buffer[100];

    setbuf(stdout,NULL);
  
    if (argc < 2) {
	fprintf (stderr, "Usage:  test filename\n");
    }

    seed = (long int) time(NULL); /* initialize random number generator */
  
/*      seed = 500; */
 
#ifdef TIMING
    start_timers(); /* starts time measurement */
#endif
  
    read_instance(argv[1]);
  
    sprintf(temp_buffer,"best.%s",name);
    report = fopen(temp_buffer, "w");
    sprintf(temp_buffer,"cmp.%s",name);
    comp_report = fopen(temp_buffer, "w");
    fprintf(comp_report,"begin problem %s\n",argv[1]);


#ifdef TIMING
    printf ("Time to read instance = %4.2f\n\n", fabs(elapsed_time( VIRTUAL )));
    fprintf (comp_report,"Time to read instance = %4.2f\n\n", fabs(elapsed_time( VIRTUAL )));
#endif
  
    distMat = compute_distances();

#ifdef TIMING
    fprintf (comp_report,"Cumulative time up to compute distances = %4.2f\n\n", elapsed_time( VIRTUAL ));
#endif

    nn_ls = MIN (ncities - 1, 40);

    nnMat = compute_NNLists();

    tour = malloc((ncities + 1 ) * sizeof(int));

    for ( try = 1; try <= 25; try ++ ) {

	printf("\n");
#ifdef TIMING
	start_timers();  
#endif

	fprintf(comp_report,"begin try %d\n",try);
	/* start with random initial solution */
	random =   generate_random_vector();
	for ( j = 0 ; j < ncities ; j++ ) {
	    tour[j] = random[j];
	}
	tour[ncities] = tour[0];
	dlb = calloc(ncities, sizeof(int));

	/* comment / uncomment to choose the local search you wish to run */
/*         two_opt_first(tour); */
	three_opt_first(tour);
/*         two_opt_best(tour); */
/*         two_opt_f(tour); */
	length = compute_length( tour );

/*        printf("best %d\t time %f\t iteration 0\n",length,fabs(elapsed_time( VIRTUAL ))); */
	fprintf(comp_report,"best %d\t time %f\t iteration 0\n",length,fabs(elapsed_time( VIRTUAL )));
      
	/* choose the number of iterations to be run for ILS */
	for ( i = 0 ; i < 10 * ncities/*  000 * ncities */ ; i++ ) {

	    shadow = doublebridge_window ( tour );
/*        two_opt_first(tour); */
	    three_opt_first( shadow );
	    accept( tour, &length, shadow, i );
	    free (shadow);
/*  	    if ( elapsed_time( VIRTUAL ) > 600. ) */
/*  		break; */

	}

	free ( random );
	free( dlb );
	fprintf(report,"best %d\t time %f\t iteration %d\t total.time %f\n",length, time_best_found, iteration_best_found,fabs(elapsed_time( VIRTUAL )));
	fprintf(comp_report,"end try %d\n",try);
	length = INT_MAX;
	fflush(report);
	fflush(comp_report);
    }

    free ( tour );

    fprintf(comp_report,"end problem %s\n",argv[1]);

    return 0;
}







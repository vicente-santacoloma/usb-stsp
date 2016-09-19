/**
 * Copy one vector to another
 * @param vector1 vector to be copied
 * @param vector2 vector in which to copy
 * @return void
 */
void copy_vector (int * vector1, int * vector2);

/**
 * Find the best tour for the STSP problem by-iterated-hill-climbing heuristic 
 * @param max number of iterations
 * @return best tour found by the heuristic
 */
int * iterated_hill_climber(int max);
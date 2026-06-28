#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <pthread.h>
# include <string.h>

# include "utils/codexion_types.h"


// parsing:
int         validate_arguments(int argc, char **args);
t_config    *parse_arguments(int argc, char **argv, t_config **config);

// simulation:
void        init_simulation(t_sim **sim, t_config *config);

// utils/debugging:
void	    print_config(t_config *config);
void        print_sim(t_sim *sim);

#endif
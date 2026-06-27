#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_config
{
    int     number_of_coders;
    int     time_to_burnout;
    int     time_to_compile;
    int     time_to_debug;
    int     time_to_refactor;
    int     number_of_compiles_required;
    int     dongle_cooldown;
    char    *scheduler;

} t_config;

// parsing:
int         validate_arguments(int argc, char **args);
t_config    *parse_arguments(int argc, char **argv);

//utils:
void	    print_config(t_config *config);
#endif
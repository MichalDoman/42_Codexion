#include "codexion.h"

static void init_coders(t_coder **coders, t_config *config)
{
    int i;

    i = 0;
    while (i < config->number_of_coders)
    {
        *coders[i] = 
    }
}

static void init_dongles(t_coder **coders, t_config *config)
{
    
}

void init_simulation(t_sim **sim, t_config *config)
{
    t_coder     *coders;
    t_dongle    *dongles;

    coders = NULL;
    dongles = NULL;

    *sim = malloc(sizeof(t_sim));
    if (!sim)
        return ;
}
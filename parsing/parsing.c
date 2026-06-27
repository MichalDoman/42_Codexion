#include "../codexion.h"


t_config parse_arguments(int argc, char **argv)
{
    t_config *config;

    if (!validate_arguments(argv))
        return ;

    config = malloc(sizeof(t_config));
    if (!config)
        return ;
}


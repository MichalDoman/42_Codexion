#include "codexion.h"

int main(int argc, char **argv)
{

    t_config    config;
    t_sim       sim;

    if (validate_arguments(argc, argv))
    {
        if (!parse_arguments(argc, argv, &config))
            return (1);
        if (!init_simulation(&sim, &config))
            return (1);
        print_sim(&sim);
    }

    return (0);
}

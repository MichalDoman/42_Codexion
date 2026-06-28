#include "codexion.h"

int main(int argc, char **argv)
{

    t_config    *config;
    t_sim       *sim;

    config = NULL;
    sim = NULL;
    if (validate_arguments(argc, argv))
        parse_arguments(argc, argv, &config);
        init_simulation(&sim, config);
        print_sim(sim);

    return 0;
}

#include "codexion.h"

int main(int argc, char **argv)
{

    t_config *config;

    config = NULL;
    if (validate_arguments(argc, argv))
        config = parse_arguments(argc, argv);
        print_config(config);

    return 0;
}

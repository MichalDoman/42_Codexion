#include "codexion.h"

int main(int argc, char **argv)
{

    t_config *config;

    config = NULL;
    printf("validate_arguments(argv) = %d\n", validate_arguments(argc, argv));
    // if (validate_arguments(argc, argv))
    //     config = parse_arguments(argv);

    return 0;
}

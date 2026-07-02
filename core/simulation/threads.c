#include "codexion.h"

void	create_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_create(
			&(sim->coders[i].thread),
			NULL,
			coder_routine,
			&(sim->coders[i])
		);
		i++;
	}
}

void	join_threads(t_sim *sim)
{
	int		i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_join((sim->coders[i]).thread, NULL);
		i++;
	}
	// pthread_join(monitor_thread, NULL);
}
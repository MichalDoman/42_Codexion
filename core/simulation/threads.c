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
	pthread_create(
		&(sim->monitor_thread),
		NULL,
		monitor_routine,
		sim
	)
}

void	join_threads(t_sim *sim)
{
	int		i;

	pthread_join(sim->monitor_thread, NULL);
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_join((sim->coders[i]).thread, NULL);
		i++;
	}
}

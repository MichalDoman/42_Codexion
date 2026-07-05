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
	);
	pthread_mutex_lock(&sim->start_mutex);
	sim->start_time = get_time_ms();
	set_coders_start_time(sim);
	sim->is_ready = 1;
	pthread_cond_broadcast(&sim->start_cond);
	pthread_mutex_unlock(&sim->start_mutex);
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

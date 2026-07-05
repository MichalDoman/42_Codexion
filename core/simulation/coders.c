#include "codexion.h"

void	wait_untill_sim_is_ready(t_sim *sim)
{
	pthread_mutex_lock(&sim->start_mutex);
	while (!sim->is_ready)
		pthread_cond_wait(&sim->start_cond, &sim->start_mutex);
	pthread_mutex_unlock(&sim->start_mutex);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while(coder->sim->is_running)
	{
		wait_untill_sim_is_ready(coder->sim);
	}
	return (NULL);
}
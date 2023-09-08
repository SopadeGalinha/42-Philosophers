#include "../philo.h"

void	sleeping(t_philo *philo)
{
		pthread_mutex_lock(&philo->params->print);
			if (philo->params->finish == 0)
				printf("%lld %d is sleeping\n", get_time(philo->params->start_program), philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
		usleep(philo->params->n_time_to_sleep * 1000);

}

void	eating(t_philo *philo)
{

	//Pega no garfo da direita
	pthread_mutex_lock(&philo->params->forks[philo->id_fork_right]);

		pthread_mutex_lock(&philo->params->print);
			if (philo->params->finish == 0)
				printf("%lld %d has taken a fork\n", get_time(philo->params->start_program), philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);


		//pega no garfo da esquerda.

		pthread_mutex_lock(&philo->params->forks[philo->id_fork_left]);
			pthread_mutex_lock(&philo->params->print);
			if (philo->params->finish == 0)
				printf("%lld %d has taken a fork\n", get_time(philo->params->start_program), philo->id + 1);
			if (philo->params->finish == 0)
				printf("%lld %d is eating\n", get_time(philo->params->start_program), philo->id + 1);

			if (philo->params->n_meals != -1)
				philo->meals_count++;

			pthread_mutex_unlock(&philo->params->print);
				philo->time_lst_meal = get_time(philo->params->start_program);
			usleep(philo->params->n_time_to_eat * 1000);
		pthread_mutex_unlock(&philo->params->forks[philo->id_fork_left]);

	pthread_mutex_unlock(&philo->params->forks[philo->id_fork_right]);

}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->print);
		if (philo->params->finish == 0)
			printf("%lld %d is thinking\n", get_time(philo->params->start_program), philo->id + 1);
	pthread_mutex_unlock(&philo->params->print);
}
int	check_any_dead(t_params *params)
{
	int i;
	int	since_last_meal;

	i = 0;

	while (i < params->n_philo)
	{
		since_last_meal = get_time(params->start_program) - params->philos[i]->time_lst_meal;
		if (since_last_meal >= params->n_time_to_die)
		{
			if (params->n_philo == 1)
				return(1);
			printf("%lld %d died\n\n", get_time(params->start_program), params->philos[i]->id + 1);
			pthread_mutex_lock(&params->finish_lock);
			params->finish = 1;
			pthread_mutex_unlock(&params->finish_lock);
			return (1);
		}
		i++;
	}
	return (0);
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->params->n_philo == 1)
	{

		pthread_mutex_lock(&philo->params->print);
			printf("%d %d has taken a fork\n", philo->time_lst_meal, philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
		printf("%lld %d died\n", get_time(philo->params->start_program), philo->id + 1);
		pthread_mutex_lock(&philo->params->finish_lock);
			philo->params->finish = 1;
		pthread_mutex_unlock(&philo->params->finish_lock);
		return (0);
	}
	while (philo->params->finish == 0)
	{
		if(philo->id % 2 != 0)
		usleep(600);
		if(philo->params->finish == 0)
			eating(philo);
		if(philo->params->finish == 0)
			sleeping(philo);
		if(philo->params->finish == 0)
			thinking(philo);
	}
	return (0);
}

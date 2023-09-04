#include "../philo.h"

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->print);
			printf("%lld %d is sleeping\n", get_time(philo->params->start_program), philo->id + 1);
	pthread_mutex_unlock(&philo->params->print);
	usleep(philo->params->n_time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	//Pega no garfo da direita
	pthread_mutex_lock(&philo->params->forks[philo->id_fork_right]);
		philo->time_lst_meal = get_time(philo->params->start_program);
		pthread_mutex_lock(&philo->params->print);
			printf("%d %d has take a fork\n", philo->time_lst_meal, philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
		
		//pega no garfo da esquerda.
		pthread_mutex_lock(&philo->params->forks[philo->id_fork_left]);
			philo->time_lst_meal = get_time(philo->params->start_program);
			pthread_mutex_lock(&philo->params->print);
				printf("%d %d has take a fork\n", philo->time_lst_meal, philo->id + 1);
				printf("%d %d is eating\n", philo->time_lst_meal, philo->id + 1);
			pthread_mutex_unlock(&philo->params->print);
			usleep(philo->params->n_time_to_eat * 1000);
		pthread_mutex_unlock(&philo->params->forks[philo->id_fork_left]);

	pthread_mutex_unlock(&philo->params->forks[philo->id_fork_right]);
	
}

void	*routine(void *arg)
{
	t_philo	*philo;
	//int		i;

	//i = 0;
	philo = (t_philo *)arg;
	
	while(1)
	{
		if(philo->id % 2 != 0)
			usleep(90);
		eating(philo);
		sleeping(philo);

		pthread_mutex_lock(&philo->params->print);
			printf("%lld %d is thinking\n", get_time(philo->params->start_program), philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
	}

	return (0);
}
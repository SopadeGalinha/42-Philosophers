#include "../philo.h"

void	sleeping(t_philo *philo)
{
	
	/*if (check_philo_died(philo))
	{	
		return ;
	}
	else
	{
	}*/
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

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->print);
		printf("%lld %d is thinking\n", get_time(philo->params->start_program), philo->id + 1);
	pthread_mutex_unlock(&philo->params->print);
}
int	check_philo_died(t_philo *philo)
{
	int i;
	int	since_last_meal;
	
	i = 0;
	since_last_meal = 0;
	since_last_meal = (get_time(philo->params->start_program) - philo->time_lst_meal);
	
	if (since_last_meal >= philo->params->n_time_to_die)
	{
		printf("\n%d %d morreu\n", since_last_meal, philo->id + 1);
		return (1);
	}
	/*while (i < philo->params->n_philo)
	{
		if (since_last_meal >= philo->params->n_time_to_die)
		{	
			printf("%d %d died\n\n", philo->time_lst_meal, philo->params->philos[i]->id + 1);
			philo->params->philos[i]->died = 1;
			return (1);
		}
		i++;
	}*/
	return (0);
}
void	*routine(void *arg)
{
	t_philo	*philo;
	//int		i;

	//i = 0;
	philo = (t_philo *)arg;
	
	if(philo->params->n_philo == 1)
	{
		pthread_mutex_lock(&philo->params->print);
			printf("%d %d has take a fork\n", philo->time_lst_meal, philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
		printf("%lld %d died\n", get_time(philo->params->start_program), philo->id + 1);
		return (0);
	}

	while(1)
	{
		
		if(philo->id % 2 != 0)
		usleep(90);
		if(check_philo_died(philo))
			break;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}
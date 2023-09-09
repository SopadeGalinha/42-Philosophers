#include "../philo.h"

void	sleeping(t_philo *philo)
{		
		pthread_mutex_lock(&philo->params->finish_lock);
			int finish = philo->params->finish;
		pthread_mutex_unlock(&philo->params->finish_lock);

		pthread_mutex_lock(&philo->params->print);
			if (finish == 0)
				printf("%lld %d is sleeping\n", get_time(philo->params->start_program), philo->id + 1);
		pthread_mutex_unlock(&philo->params->print);
		
		
		usleep(philo->params->n_time_to_sleep * 1000);

}

void	eating(t_philo *philo)
{

	pthread_mutex_lock(&philo->params->finish_lock);
			int finish = philo->params->finish;
	pthread_mutex_unlock(&philo->params->finish_lock);
	if(philo->id % 2 == 0)
	{
			pthread_mutex_lock(&philo->params->forks[philo->id_fork_right]);

			pthread_mutex_lock(&philo->params->finish_lock);
				finish = philo->params->finish;
			pthread_mutex_unlock(&philo->params->finish_lock);

			pthread_mutex_lock(&philo->params->print);
				if (finish == 0)
					printf("%lld %d has taken a fork\n", get_time(philo->params->start_program), philo->id + 1);
			pthread_mutex_unlock(&philo->params->print);
			pthread_mutex_lock(&philo->params->forks[philo->id_fork_left]);
				pthread_mutex_lock(&philo->params->finish_lock);
					finish = philo->params->finish;
				pthread_mutex_unlock(&philo->params->finish_lock);

				pthread_mutex_lock(&philo->params->print);
				if (finish == 0)
				{
					printf("%lld %d has taken a fork\n", get_time(philo->params->start_program), philo->id + 1);
					printf("%lld %d is eating\n", get_time(philo->params->start_program), philo->id + 1);
				}
				if (philo->params->n_meals != -1)
				{
					pthread_mutex_lock(&philo->meal_count_lock);
						philo->meals_count++;
					pthread_mutex_unlock(&philo->meal_count_lock);
				}
				pthread_mutex_unlock(&philo->params->print);
				pthread_mutex_lock(&philo->lst_meal_lock);
					philo->time_lst_meal = get_time(philo->params->start_program);
				pthread_mutex_unlock(&philo->lst_meal_lock);
			pthread_mutex_unlock(&philo->params->forks[philo->id_fork_left]);
			usleep(philo->params->n_time_to_eat * 1000);
		
		pthread_mutex_unlock(&philo->params->forks[philo->id_fork_right]);
	}
	else
	{
			pthread_mutex_lock(&philo->params->forks[philo->id_fork_left]);

			pthread_mutex_lock(&philo->params->finish_lock);
				finish = philo->params->finish;
			pthread_mutex_unlock(&philo->params->finish_lock);

			if (finish == 0)
			pthread_mutex_lock(&philo->params->print);
				printf("%lld %d has taken a fork\n", get_time(philo->params->start_program), philo->id + 1);
			pthread_mutex_unlock(&philo->params->print);
			pthread_mutex_lock(&philo->params->forks[philo->id_fork_right]);
				pthread_mutex_lock(&philo->params->finish_lock);
					finish = philo->params->finish;
				pthread_mutex_unlock(&philo->params->finish_lock);

				pthread_mutex_lock(&philo->params->print);
				if (finish == 0)
				{
					printf("%lld %d has taken a fork\n", get_time(philo->params->start_program), philo->id + 1);
					printf("%lld %d is eating\n", get_time(philo->params->start_program), philo->id + 1);
				}
				if (philo->params->n_meals != -1)
				{
					pthread_mutex_lock(&philo->meal_count_lock);
						philo->meals_count++;
					pthread_mutex_unlock(&philo->meal_count_lock);
				}

				pthread_mutex_unlock(&philo->params->print);
				pthread_mutex_lock(&philo->lst_meal_lock);
					philo->time_lst_meal = get_time(philo->params->start_program);
				pthread_mutex_unlock(&philo->lst_meal_lock);
			pthread_mutex_unlock(&philo->params->forks[philo->id_fork_right]);
			usleep(philo->params->n_time_to_eat * 1000);
		
		pthread_mutex_unlock(&philo->params->forks[philo->id_fork_left]);
	}
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->finish_lock);
			int finish = philo->params->finish;
	pthread_mutex_unlock(&philo->params->finish_lock);

	pthread_mutex_lock(&philo->params->print);
		if (finish == 0)
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
		pthread_mutex_lock(&params->philos[i]->lst_meal_lock);
			since_last_meal = get_time(params->start_program) - params->philos[i]->time_lst_meal;
		pthread_mutex_unlock(&params->philos[i]->lst_meal_lock);
		if (since_last_meal >= params->n_time_to_die)
		{
			if (params->n_philo == 1)
				return(1);
			printf("%lld %d died\n", get_time(params->start_program), params->philos[i]->id + 1);
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
		printf("%d %d died\n", philo->params->n_time_to_die + philo->time_lst_meal, philo->id + 1);
		pthread_mutex_lock(&philo->params->finish_lock);
			philo->params->finish = 1;
		pthread_mutex_unlock(&philo->params->finish_lock);
		return (0);
	}
	int finish = 0;

	while (finish == 0)
	{
		pthread_mutex_lock(&philo->params->finish_lock);
			finish = philo->params->finish;
		pthread_mutex_unlock(&philo->params->finish_lock);
		if (finish == 1)
			return (NULL);
		if(philo->id % 2 != 0)
			usleep(100);

		if(finish == 0)
			eating(philo);
		if(finish == 0)
			sleeping(philo);
		if(finish == 0)
			thinking(philo);
	}
	return (0);
}

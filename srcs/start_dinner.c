/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:04:58 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/26 09:04:58 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	all_done(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->is_done_lock);
		if (!table->philos[i]->is_done)
		{
			pthread_mutex_unlock(&table->philos[i]->is_done_lock);
			return (false);
		}
		pthread_mutex_unlock(&table->philos[i]->is_done_lock);
	}
	return (true);
}

static bool	any_dead(t_table *table)
{
	int		i;
	long	time_now;

	i = -1;
	time_now = get_time(table);
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_lock);
		pthread_mutex_lock(&table->philos[i]->is_done_lock);
		pthread_mutex_unlock(&table->philos[i]->is_done_lock);
		pthread_mutex_unlock(&table->philos[i]->last_meal_lock);
		if (time_now - table->philos[i]->last_meal > table->args.time_die)
		{
			pthread_mutex_lock(&table->is_over_lock);
			table->is_over = true;
			pthread_mutex_unlock(&table->is_over_lock);
			log_message(table->philos[i], table, "died", ESC_BOLD_RED);
			return (true);
		}
	}
	return (false);
}

static void	*dine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->args.nb_philo == 1)
	{
		pthread_mutex_lock(philo->fork[RIGHT]);
		log_message(philo, philo->table, "has taken a fork", ESC_BOLD_ORANGE);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		log_message(philo, philo->table, "can't eat alone", ESC_BOLD_RED);
		return (NULL);
	}
	while (!is_meal_over(philo))
	{
		philo->ft[EAT](philo, philo->table);
		if (is_meal_over(philo))
			break ;
		philo->ft[SLEEP](philo, philo->table);
		if (is_meal_over(philo))
			break ;
		philo->ft[THINK](philo, philo->table);
	}
	return (NULL);
}

static void	*reaper(void *table_ptr)
{
	t_table	*table;
	bool	is_over;

	table = (t_table *)table_ptr;
	pthread_mutex_lock(&table->is_over_lock);
	is_over = table->is_over;
	pthread_mutex_unlock(&table->is_over_lock);
	if (is_over)
		return (NULL);
	while (!all_done(table))
	{
		if (any_dead(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL, \
			dine, table->philos[i]) != 0)
			return (printf("Error creating thread for philo %d\n", i + 1));
	}
	if (pthread_create(&table->reaper, NULL, reaper, table) != 0)
		return (printf("Error creating reaper thread\n"));
	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_join(table->philos[i]->thread_id, NULL) != 0)
			return (printf("Error joining thread for philo %d\n", i + 1));
	return (0);
}

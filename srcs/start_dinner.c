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
	int		i;
	bool	is_done;

	i = -1;
	if (table->args.nb_meals == -1)
		return (false);
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->is_done_lock);
		is_done = table->philos[i]->is_done;
		pthread_mutex_unlock(&table->philos[i]->is_done_lock);
		if (!is_done)
			return (false);
	}
	pthread_mutex_lock(&table->is_over_lock);
	table->is_over = true;
	pthread_mutex_unlock(&table->is_over_lock);
	return (true);
}

static bool	any_dead(t_table *table)
{
	int		i;
	int		since_last_meal;
	bool	is_done;

	i = -1;
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_lock);
		pthread_mutex_lock(&table->philos[i]->is_done_lock);
		is_done = table->philos[i]->is_done;
		since_last_meal = get_time(table->args.start) \
			- table->philos[i]->last_meal;
		pthread_mutex_unlock(&table->philos[i]->last_meal_lock);
		pthread_mutex_unlock(&table->philos[i]->is_done_lock);
		if (!is_done && since_last_meal >= table->args.time_die)
		{
			pthread_mutex_lock(&table->is_over_lock);
			table->is_over = true;
			pthread_mutex_unlock(&table->is_over_lock);
			log_message(table->philos[i], "died", ESC_BOLD_RED);
			return (true);
		}
	}
	return (false);
}

static void	*dinning(void *philo_ptr)
{
	t_philo			*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->args.nb_philo == 1)
	{
		pthread_mutex_lock(philo->fork[RIGHT]);
		log_message(philo, "has taken a fork", ESC_BOLD_ORANGE);
		log_message(philo, "can't eat alone", ESC_BOLD_RED);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		return (NULL);
	}
	while (!meal_over(philo))
	{
		philo->ft[EAT](philo);
		if (!meal_over(philo))
			philo->ft[SLEEP](philo);
		if (!meal_over(philo))
			philo->ft[THINK](philo);
	}
	return (NULL);
}

static void	*checkdeath(void *table_ptr)
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
		usleep(table->args.time_die / 2 * 500);
	}
	return (NULL);
}

bool	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_create(&table->philos[i]->thread_id, NULL, dinning, \
			table->philos[i]))
			return (false);
	if (pthread_create(&table->dead, NULL, checkdeath, table))
		return (false);
	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_join(table->philos[i]->thread_id, NULL))
			return (false);
	if (pthread_join(table->dead, NULL))
		return (false);
	return (true);
}

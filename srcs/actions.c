/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:21:46 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/26 13:21:46 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	get_two_forks(t_philo *philo);

void	ft_eat(t_philo *philo, t_table *table)
{
	if (!get_two_forks(philo))
		return ;
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time(table);
	pthread_mutex_unlock(&philo->last_meal_lock);
	log_message(philo, table, "is eating", ESC_BOLD_GREEN);
	philo->meal_count++;
	usleep((table->args.time_eat * 1000));
	pthread_mutex_unlock(philo->fork[RIGHT]);
	pthread_mutex_unlock(philo->fork[LEFT]);
	if (philo->meal_count == philo->args.nb_meals)
	{
		log_message(philo, table, "is done eating", ESC_BOLD_GREY);
		pthread_mutex_lock(&philo->is_done_lock);
		philo->is_done = true;
		pthread_mutex_unlock(&philo->is_done_lock);
	}
}

static bool	get_fork(t_philo *philo, int fork)
{
	bool	is_over;

	pthread_mutex_lock(philo->fork[fork]);
	pthread_mutex_lock(philo->is_over_lock);
	is_over = *philo->is_over;
	pthread_mutex_unlock(philo->is_over_lock);
	if (is_over)
	{
		pthread_mutex_unlock(philo->fork[fork]);
		return (false);
	}
	log_message(philo, philo->table, "has taken a fork", ESC_BOLD_ORANGE);
	return (true);
}

static bool	get_two_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!get_fork(philo, RIGHT))
			return (false);
		if (!get_fork(philo, LEFT))
		{
			pthread_mutex_unlock(philo->fork[RIGHT]);
			return (false);
		}
		return (true);
	}
	if (!get_fork(philo, LEFT))
		return (false);
	if (!get_fork(philo, RIGHT))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	return (true);		
}

void	ft_think(t_philo *philo, t_table *table)
{
	log_message(philo, table, "is thinking", ESC_BOLD_PURPLE);
}

void	ft_sleep(t_philo *philo, t_table *table)
{
	log_message(philo, table, "is sleeping", ESC_BOLD_CYAN);
	usleep((table->args.time_sleep * 1000));
}

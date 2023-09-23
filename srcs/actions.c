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
static bool	get_a_fork(t_philo *philo, int fork);

void	ft_eat(t_philo *philo)
{		
	if (!get_two_forks(philo))
		return ;
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time(philo->args.start);
	pthread_mutex_unlock(&philo->last_meal_lock);
	log_message(philo, "is eating", ESC_BOLD_GREEN);
	philo->meal_count++;
	usleep(philo->args.time_eat * 1000);
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	if (philo->meal_count == philo->args.nb_meals)
	{		
		log_message(philo, "has finished eating", ESC_BOLD_WHITE);
		pthread_mutex_lock(&philo->is_done_lock);
		philo->is_done = true;
		pthread_mutex_unlock(&philo->is_done_lock);
	}
}

static bool	get_two_forks(t_philo *philo)
{
	int	first;
	int	second;

	first = LEFT;
	second = RIGHT;
	if (philo->id % 2 == 0)
	{
		first = RIGHT;
		second = LEFT;
	}
	if (!get_a_fork(philo, first))
		return (false);
	if (!get_a_fork(philo, second))
	{
		pthread_mutex_unlock(philo->fork[first]);
		return (false);
	}
	return (true);
}

static bool	get_a_fork(t_philo *philo, int fork)
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
	log_message(philo, "has taken a fork", ESC_BOLD_ORANGE);
	return (true);
}

void	ft_sleep(t_philo *philo)
{
	log_message(philo, "is sleeping", ESC_BOLD_CYAN);
	usleep(philo->args.time_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	log_message(philo, "is thinking", ESC_BOLD_PURPLE);
}

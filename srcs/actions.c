/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:01:01 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/24 12:01:01 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_message(philo, philo->table, "has taken a fork", ESC_GREEN);
	pthread_mutex_lock(philo->right_fork);
	log_message(philo, philo->table, "has taken a fork", ESC_GREEN);
	log_message(philo, philo->table, "is eating", ESC_GREEN);
	philo->last_meal = get_time(philo->table);
	ft_usleep(philo->table->args.time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	log_message(philo, philo->table, "is sleeping", ESC_YELLOW);
	ft_usleep(philo->table->args.time_sleep);
}

void	ft_think(t_philo *philo)
{
	log_message(philo, philo->table, "is thinking", ESC_MAGENTA);
}
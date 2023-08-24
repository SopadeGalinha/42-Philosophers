/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:58:56 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/20 20:58:56 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void set_philo_env(int i, t_philo *philo, t_table *table);
void    ft_think(t_philo *philo, t_table *table);

int	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (printf("Error creating philo: malloc failed\n"));
	table->philos[i]->id = i + 1;
	table->philos[i]->thread_id = 0;
	table->philos[i]->meal_count = 0;
	table->philos[i]->is_done = false;
	set_philo_env(i, table->philos[i], table);
	pthread_mutex_init(&table->philos[i]->is_done_lock, NULL);
	pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL);
	table->philos[i]->ft[EAT] = ft_eat;
	table->philos[i]->ft[SLEEP] = ft_sleep;
	table->philos[i]->ft[THINK] = ft_think;
	table->philos[i]->last_meal = get_time(table);
	log_message(table->philos[i], table, "has joined the table", ESC_BOLD_WHITE);
	return (0);
}

static void set_philo_env(int i, t_philo *philo, t_table *table)
{
	philo->args.nb_philo = table->args.nb_philo;
	philo->args.time_die = table->args.time_die;
	philo->args.time_eat = table->args.time_eat;
	philo->args.time_sleep = table->args.time_sleep;
	philo->args.nb_meals = table->args.nb_meals;
	philo->print_zone = &table->printzone;
	philo->fork[0] = &table->forks[i];
	philo->fork[1] = &table->forks[(i + 1) % table->args.nb_philo];
	philo->is_over = &table->is_over;
	philo->is_over_lock = &table->is_over_lock;
}

void	ft_think(t_philo *philo, t_table *table)
{
	log_message(philo, table, "is thinking", ESC_BOLD_MAGENTA);
}

void	ft_sleep(t_philo *philo, t_table *table)
{
	log_message(philo, table, "is sleeping", ESC_BOLD_BLUE);
	usleep(table->args.time_sleep);
}

void	ft_eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->fork[0]);
	log_message(philo, table, "has taken a fork", ESC_BOLD_GREEN);
	pthread_mutex_lock(philo->fork[1]);
	log_message(philo, table, "has taken a fork", ESC_BOLD_GREEN);
	log_message(philo, table, "is eating", ESC_BOLD_GREEN);
	philo->last_meal = get_time(table);
	usleep(table->args.time_eat);
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:58:23 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/20 14:58:23 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	get_args(int ac, char **av, t_table *table);
static int	get_forks(t_table *table);
static int	get_philos(t_table *table);

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	if (check_args(ac, av))
		return (NULL);
 	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	get_args(ac, av, table);
	table->is_over = false;
	if (table->args.nb_philo == 1)
		table->is_over = true;
	pthread_mutex_init(&table->printzone, NULL);
	pthread_mutex_init(&table->is_over_lock, NULL);
	table->start_time.tv_sec = get_time(table);
	if (get_forks(table) || get_philos(table))
		return (NULL);
	return (table);
}

static void	get_args(int ac, char **av, t_table *table)
{
	table->args.nb_philo = ft_atoi(av[1]);
	table->args.time_die = ft_atoi(av[2]);
	table->args.time_eat = ft_atoi(av[3]);
	table->args.time_sleep = ft_atoi(av[4]);
	table->args.nb_meals = -1;
	if (ac == 6)
		table->args.nb_meals = ft_atoi(av[5]);
}

static int	get_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args.nb_philo);
	if (!table->forks)
		return (printf("Error getting forks: malloc failed\n"));
	i = -1;
	while (++i < table->args.nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	return (0);
}

static int	get_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->args.nb_philo);
	if (!table->philos)
		return (printf("Error getting philos: malloc failed\n"));
	i = -1;
	while (++i < table->args.nb_philo)
		if (create_philo(i, table))
			return (1);
	return (0);
}

int	get_time(t_table *table)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000)\
		+ (time.tv_usec / 1000) - (table->start_time.tv_sec));
}
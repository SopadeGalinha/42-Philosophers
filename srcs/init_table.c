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
static int	get_forks_and_philos(t_table *table);

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	if (check_args(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->start_time.tv_sec = 0;
	if (pthread_mutex_init(&table->printzone, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&table->is_over_lock, NULL) != 0)
		return (NULL);
	get_args(ac, av, table);
	table->start_time.tv_sec = get_time(table);
	if (get_forks_and_philos(table))
		return (NULL);
	table->is_over = false;
	if (table->args.nb_philo == 1)
		table->is_over = true;
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

static void	set_env(int i, t_philo *philo, t_table *table)
{
	philo->args.nb_philo = table->args.nb_philo;
	philo->args.time_die = table->args.time_die;
	philo->args.time_eat = table->args.time_eat;
	philo->args.time_sleep = table->args.time_sleep;
	philo->args.nb_meals = table->args.nb_meals;
	philo->print_zone = &table->printzone;
	philo->fork[LEFT] = &table->forks[i];
	philo->fork[RIGHT] = &table->forks[(i + 1) % table->args.nb_philo];
	philo->is_over = &table->is_over;
	philo->is_over_lock = &table->is_over_lock;
}

static int	create_philo(int i, t_table *table)
{
	table->philos[i] = malloc(sizeof(t_philo));
	if (!table->philos[i])
		return (printf("Error creating philo: malloc failed\n"));
	table->philos[i]->id = i + 1;
	table->philos[i]->thread_id = 0;
	table->philos[i]->meal_count = 0;
	table->philos[i]->is_done = false;
	if (pthread_mutex_init(&table->philos[i]->is_done_lock, NULL) != 0)
		return (printf("Error creating philo: mutex init failed\n"));
	set_env(i, table->philos[i], table);
	if (pthread_mutex_init(&table->philos[i]->last_meal_lock, NULL) != 0)
		return (printf("Error creating philo: mutex init failed\n"));
	table->philos[i]->ft[EAT] = ft_eat;
	table->philos[i]->ft[SLEEP] = ft_sleep;
	table->philos[i]->ft[THINK] = ft_think;
	table->philos[i]->last_meal = get_time(table);
	table->philos[i]->table = table;
	log_message(table->philos[i], \
		table->philos[i]->table, "joined the table", ESC_BOLD_WHITE);
	return (0);
}

static int	get_forks_and_philos(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->args.nb_philo);
	if (!table->forks)
		return (printf("Error getting forks: malloc failed\n"));
	i = -1;
	while (++i < table->args.nb_philo)
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf("Error getting forks: mutex init failed\n"));
	table->philos = malloc(sizeof(t_philo) * table->args.nb_philo);
	if (!table->philos)
		return (printf("Error getting philos: malloc failed\n"));
	i = -1;
	while (++i < table->args.nb_philo)
		if (create_philo(i, table))
			return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:35:47 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/26 12:42:09 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_data(int ac, char	**av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else 
		data->nb_meals = -1;
		printf("DEBUG: nb_philo=%d, time_to_die=%ld, time_to_eat=%ld, time_to_sleep=%ld, nb_meals=%d\n",
    data->nb_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->nb_meals);

	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat  <= 0 || data->time_to_sleep <= 0)
		return (EXIT_FAILURE);
	data->start_time = timestamp();
	data->dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	return (EXIT_SUCCESS);
}

static int	start_thread(t_philo *philo, t_data *data)
{
	int i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].last_meal = timestamp() - philo->data->start_time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, philo))
		return (EXIT_FAILURE);
	pthread_join(monitor_thread, NULL);
	return (EXIT_SUCCESS);
}

static void	clean(t_philo *philo, t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].meal_mutex);
	}
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->fork);
	free(philo);
}

int main(int ac, char **av)
{
	t_philo *philo;
	t_data	data;
	
	if (ac != 5 && ac != 6)
	{
		write (2, "ERROR\nWrong number of arguments\n", 32);
		return (EXIT_FAILURE);
	}
	if (init_data(ac, av, &data))
		return (EXIT_FAILURE);
	if (init_fork(&data))
		return (EXIT_FAILURE);
	philo = init_philo(&data);
	if (!philo)
		return (EXIT_FAILURE);
	if (start_thread(philo, &data))
		return (EXIT_FAILURE);
	clean(philo, &data);
	return (EXIT_SUCCESS);
}


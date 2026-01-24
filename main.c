/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:35:47 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/24 14:47:28 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	init_data(int ac, char	**av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (EXIT_FAILURE);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else 
		data->nb_meals = -1;
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat  <= 0 || data->time_to_sleep <= 0)
		return (EXIT_FAILURE);
	data->start_time = timestamp();
	pthread_mutex_init(&data->print_mutex, NULL);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_data	data;
	t_philo *philo;
	if (init_data(ac, av, &data))
	{
		printf("Error: Wrong number of arguments !\n");
		return (EXIT_FAILURE);
	}
	if (init_fork(&data))
	{
		printf("Error: Init fork failed\n");
		return (EXIT_FAILURE);
	}
	philo = init_philo(&data);
	if (!philo)
	{
		printf("Error: Malloc philo failed\n");
		return (EXIT_FAILURE);
	}
	int i;

	i = 0;
	while (i < data.nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}


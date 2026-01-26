/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:09:24 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/26 11:47:01 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int init_fork(t_data *data)
{
    int i;
    data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if  (!data->fork)
        return (EXIT_FAILURE);
    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_init(&data->fork[i], NULL);
        i++;
    }
    return (EXIT_SUCCESS);
}

t_philo *init_philo(t_data *data)
{
    int i;
    t_philo *philo;
    
    philo = malloc(sizeof(t_philo) * data->nb_philo);
    if (!philo)
        return (NULL);
    i = 0;
    while (i < data->nb_philo)
    {
        philo[i].id = i + 1;
        philo[i].meals_eaten = 0;
        philo[i].last_meal = data->start_time;
        pthread_mutex_init(&philo[i].meal_mutex, NULL);
        philo[i].left_fork = &data->fork[i];
        philo[i].right_fork = &data->fork[(i + 1) % data->nb_philo];
        philo[i].data = data;
        i++;
    }
    return (philo);
}
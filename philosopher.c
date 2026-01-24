/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:28 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/24 14:36:31 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    *routine(void *ac)
{
    t_philo *philo;
    philo = (t_philo *)ac;
    while (1)
    {
        printf("The cake %d is Alive\n", philo->id);
        usleep(500000);
    }
    return (NULL);
    
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/12 12:56:36 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		write(1, "1", 1);
	}
	else if (signum == SIGUSR2)
	{
		write(1, "1", 1);
	}
}

int	main()
{
	pid_t	pid;

	pid = getpid();
	printf ("%d\n", pid);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1);
		sleep(1);
	return (0);
}
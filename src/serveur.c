/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/21 13:27:18 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

void	sig_handler(int signal)
{
	static char c = 0;
	static	int bit = 7;

	if (signal == SIGUSR1)
		c |= 1 << bit;
	else if (signal == SIGUSR2)
		c &= ~(1 << bit);
	if (bit == 0)
	{
		write(1,&c, 1);
		bit = 7;
		c = 0;
	}
	else
		bit--;
}

int	main()
{
	pid_t	pid;

	pid = getpid();
	ft_putendl_fd("PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putendl_fd("\n\nMessage : ", 1);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		pause();
	return (0);
}

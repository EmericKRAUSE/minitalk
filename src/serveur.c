/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/26 14:12:45 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

int		p = 0;
char	pid[8];

void	sig_handler(int signal)
{
	static char c = 0;
	static	int bit = -1;

	if (bit < 0)
		bit = 7;
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else if (signal == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c && p >= 7)
		ft_putchar_fd(c, 1);
	else if (!bit && !c && p >= 7)
		kill(atoi(pid), SIGUSR2);
	if (!bit && p < 7)
	{
		pid[p] = c;
		p++;
		if (p == 7)
		{
			pid[p] = '\0';
			c = 0;
		}
	}
	if (p >= 7)
		kill(atoi(pid), SIGUSR1);
	bit--;
}

int	main(void)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/03/22 13:41:27 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

void	sig_handler(int signal, siginfo_t *info, void *context)
{
	static char c = 0;
	static	int bit = -1;

	if (bit < 0)
		bit = 7;
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else if (signal == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit)
		ft_putchar_fd(c, 1);
	bit--;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putendl_fd("PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putendl_fd("\n\nMessage : ", 1);
	sigaction(SIGUSR1, sig_handler);
	sigaction(SIGUSR2, sig_handler);
	while (1)
		sleep(1);
	return (0);
}

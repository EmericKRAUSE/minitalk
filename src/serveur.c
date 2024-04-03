/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/04/03 11:11:46 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../libft/libft.h"

char	pid[8];
char	*message;

char *add_char(char *str, char c)
{
	char	*result;
	int		i;

	if (!str || !c)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	free(str);
	return (result);
}

void	sig_handler(int signal)
{
	static char c = 0;
	static	int bit = -1;
	static int p = 0;

	if (!message)
		message = ft_strdup("");
	if (bit < 0)
		bit = 7;
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else if (signal == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c && p >= 7)
		message = add_char(message, c);
	else if (!bit && !c && p >= 7)
	{
		p = 0;
		c = 0;
		bit = -1;
		ft_putendl_fd(message, 1);
		free(message);
		message = NULL;
		kill(atoi(pid), SIGUSR2);
	}
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
		sleep(1);
	return (0);
}

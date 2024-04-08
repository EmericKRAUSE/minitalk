/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:31:26 by ekrause           #+#    #+#             */
/*   Updated: 2024/04/08 15:10:47 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

char	*g_message;

char	*add_char(char *str, char c)
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

void	end_of_message(char	*c, int *bit, int *p, char pid[8])
{
	(*c) = 0;
	(*bit) = -1;
	(*p) = 0;
	ft_putendl_fd(g_message, 1);
	free(g_message);
	g_message = NULL;
	kill(ft_atoi(pid), SIGUSR2);
}

void	fill_pid(char pid[8], int *p, char *c)
{
	pid[(*p)++] = *c;
	if ((*p) == 7)
	{
		pid[*p] = '\0';
		(*c) = 0;
	}
}

void	sig_handler(int signal)
{
	static char	c = 0;
	static int	bit = -1;
	static int	p = 0;
	static char	pid[8];

	if (bit < 0 && !c && p >= 7)
		ft_putendl_fd("\033[36mClient say:\033[0m", 1);
	if (!g_message)
		g_message = ft_strdup("");
	if (bit < 0)
		bit = 7;
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else if (signal == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c && p >= 7)
		g_message = add_char(g_message, c);
	else if (!bit && !c && p >= 7)
		end_of_message(&c, &bit, &p, pid);
	if (!bit-- && p < 7)
		fill_pid(pid, &p, &c);
	if (p >= 7)
		kill(ft_atoi(pid), SIGUSR1);
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

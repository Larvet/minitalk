/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:12:49 by locharve          #+#    #+#             */
/*   Updated: 2024/03/03 15:58:20 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_buff
{
	unsigned char	buff[1000];
	struct s_byte	*nxt;
}	t_buff;

static void	answer_client(int pid, int *pow, unsigned char *byte)
{
	int	sig;

	sig = SIGUSR2;
	if (*pow < 0)
	{
		*pow = 7;
		if (*byte)
			ft_putchar_fd(*byte, 1);
		else
		{
			ft_putchar_fd('\n', 1);
			sig = SIGUSR1;
		}
		*byte = 0;
	}
	usleep(200);
	kill(pid, sig);
	return ;
}

static void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	byte = 0;
	static int				pow = 7;
	int						pid;	

	(void) ucontext;
	pid = info->si_pid;
	if (sig == SIGUSR1)
		byte += 1 << pow;
	else
		byte += 0 << pow;
	pow--;
	answer_client(pid, &pow, &byte);
	return ;
}

int	main(void)
{
	struct sigaction	sa1;
	int					pid;

	ft_memset(&sa1, 0, sizeof(sa1));
	sa1.sa_sigaction = &handle_sigusr;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	pid = getpid();
	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}

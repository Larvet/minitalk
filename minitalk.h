/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locharve <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:00 by locharve          #+#    #+#             */
/*   Updated: 2024/03/01 14:05:55 by locharve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

///////////////////////////////////////////////////////////////////// ALL

/***/// ft_memset.c
void	*ft_memset(void *s, int c, size_t n);

/***/// ft_putstr_fd.c
void	ft_putstr_fd(char *s, int fd);

///////////////////////////////////////////////////////////////////// SERVER

/***/// server.c

/***/// ft_putchar_fd.c
void	ft_putchar_fd(char c, int fd);

/***/// ft_putnbr_fd.c
void	ft_putnbr_fd(int n, int fd);

///////////////////////////////////////////////////////////////////// CLIENT

/***/// client.c

/***/// ft_atoi.c
int		ft_atoi(const char *nptr);

#endif

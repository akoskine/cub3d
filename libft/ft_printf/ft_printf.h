/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:28:21 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/02 22:28:45 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_format_pf(va_list args, const char format);
int		ft_putchar_pf(int c);
int		ft_putstr_pf(char *s);
int		ft_putptr_pf(unsigned long long ptr);
int		ft_putnbr_pf(int n);
int		ft_putunsigned_pf(unsigned int n);
int		ft_puthex_pf(unsigned int hex, const char format);
int		ft_writecheck_pf(int val);

#endif

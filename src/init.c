/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/17 17:30:13 by alelievr          #+#    #+#             */
/*   Updated: 2020/03/02 13:04:10 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char			*current_fun_name = "";
int				current_fun_visibility = 0;
int				current_protected = 0;
int				current_test_id = 0;
int				current_subtest_id = 0;
int				current_benchtype = 0;
int				current_benchiter = 1;
int				current_part = -1;
int				total_subtest = 0;
char			*current_test = "";
char			*current_explication = "";
char			*current_test_code = "";
pid_t			g_pid = 0;
int				g_log_fd = 0;
int				g_diff_fd = 0;
int				g_ret;
t_tdiff			g_time;
t_map			*g_shared_mem;
char			g_nospeed = 0;
char			g_bench = 0;
char			g_nobenchlog = 0;
char			g_help = 0;
char			*g_versus = NULL;
t_libft_subtest	fun_subtest_table[SUBTEST_SIZE];
t_libft_subbench fun_subbench_table[SUBTEST_SIZE];
t_libft_test	fun_test_table[] = {
	{"ft_putstr", test_ft_putstr, 1, 1},
	{"ft_putnbr", test_ft_putnbr, 1, 1},
	{"ft_atoi", test_ft_atoi, 1, 1},
	{"ft_strcpy", test_ft_strcpy, 1, 1},
	{"ft_strncpy", test_ft_strncpy, 1, 1},
	{"ft_strstr", test_ft_strstr, 1, 1},
	{"ft_strcmp", test_ft_strcmp, 1, 1},
	{"ft_strncmp", test_ft_strncmp, 1, 1},
	// {"ft_strupcase", test_ft_strupcase, 1, 1},
	// {"ft_strlowcase", test_ft_strlowcase, 1, 1},
	{"ft_strcapitalize", test_ft_strcapitalize, 1, 1},
	// {"ft_str_is_alpha", test_ft_str_is_alpha, 1, 1},
	// {"ft_str_is_numeric", test_ft_str_is_numeric, 1, 1},
	// {"ft_str_is_lowercase", test_ft_str_is_lowercase, 1, 1},
	// {"ft_str_is_uppercase", test_ft_str_is_uppercase, 1, 1},
	// {"ft_str_is_printable", test_ft_str_is_printable, 1, 1},
	{"ft_strcat", test_ft_strcat, 1, 1},
	{"ft_strncat", test_ft_strncat, 1, 1},
	{"ft_strlcat", test_ft_strlcat, 1, 1},
	{"ft_strlcpy", test_ft_strlcpy, 1, 1},

	{"ft_memset", test_ft_memset, 3, 0},
	{"ft_bzero", test_ft_bzero, 3, 0},
	{"ft_memcpy", test_ft_memcpy, 3, 0},
	{"ft_memccpy", test_ft_memccpy, 3, 0},
	{"ft_memmove", test_ft_memmove, 3, 0},
	{"ft_memchr", test_ft_memchr, 3, 0},
	{"ft_memcmp", test_ft_memcmp, 3, 0},
	{"ft_strlen", test_ft_strlen, 3, 0},
	{"ft_strdup", test_ft_strdup, 3, 0},
	{"ft_strchr", test_ft_strchr, 3, 0},
	{"ft_strrchr", test_ft_strrchr, 3, 0},
	{"ft_strnstr", test_ft_strnstr, 3, 0},
	{"ft_isalpha", test_ft_isalpha, 3, 0},
	{"ft_isdigit", test_ft_isdigit, 3, 0},
	{"ft_isalnum", test_ft_isalnum, 3, 0},
	{"ft_isascii", test_ft_isascii, 3, 0},
	{"ft_isprint", test_ft_isprint, 3, 0},
	{"ft_toupper", test_ft_toupper, 3, 0},
	{"ft_tolower", test_ft_tolower, 3, 0},

	{"ft_memalloc", test_ft_memalloc, 3, 0},
	{"ft_memdel", test_ft_memdel, 3, 0},
	{"ft_strnew", test_ft_strnew, 3, 0},
	{"ft_strdel", test_ft_strdel, 3, 0},
	{"ft_strclr", test_ft_strclr, 3, 0},
	{"ft_striter", test_ft_striter, 3, 0},
	{"ft_striteri", test_ft_striteri, 3, 0},
	{"ft_strmap", test_ft_strmap, 3, 0},
	{"ft_strmapi", test_ft_strmapi, 3, 0},
	{"ft_strequ", test_ft_strequ, 3, 0},
	{"ft_strnequ", test_ft_strnequ, 3, 0},
	{"ft_strsub", test_ft_strsub, 3, 0},
	{"ft_strjoin", test_ft_strjoin, 3, 0},
	{"ft_strtrim", test_ft_strtrim, 3, 0},
	{"ft_strsplit", test_ft_strsplit, 3, 0},
	{"ft_itoa", test_ft_itoa, 3, 0},
	{"ft_putchar", test_ft_putchar, 3, 0},
	{"ft_putendl", test_ft_putendl, 3, 0},
	{"ft_putchar_fd", test_ft_putchar_fd, 3, 0},
	{"ft_putstr_fd", test_ft_putstr_fd, 3, 0},
	{"ft_putendl_fd", test_ft_putendl_fd, 3, 0},
	{"ft_putnbr_fd", test_ft_putnbr_fd, 3, 0},

	{"ft_lstnew", test_ft_lstnew, 3, 0},
	{"ft_lstdelone", test_ft_lstdelone, 3, 0},
	{"ft_lstdel", test_ft_lstdel, 3, 0},
	{"ft_lstadd", test_ft_lstadd, 3, 0},
	{"ft_lstiter", test_ft_lstiter, 3, 0},
	{"ft_lstmap", test_ft_lstmap, 3, 0},

	{"ft_islower", test_ft_islower, 3, 0},
	{"ft_isupper", test_ft_isupper, 3, 0},
	{"ft_isnumber", test_ft_isnumber, 3, 0},
	{"ft_isblank", test_ft_isblank, 3, 0},
	{"ft_strtrimc", test_ft_strtrimc, 3, 0},
	{"ft_strndup", test_ft_strndup, 3, 0},
	{"ft_atof", test_ft_atof, 3, 0},

	{NULL, NULL, 4, 0}
};

t_libft_bench	fun_bench_table[] = {
	{"ft_memset", bench_ft_memset, 1},
	{"ft_bzero", bench_ft_bzero, 1},
	{"ft_memcpy", bench_ft_memcpy, 1},
	{"ft_memccpy", bench_ft_memccpy, 1},
	{"ft_memmove", bench_ft_memmove, 1},
	{"ft_memchr", bench_ft_memchr, 1},
	{"ft_memcmp", bench_ft_memcmp, 1},
	{"ft_strlen", bench_ft_strlen, 1},
	{"ft_strdup", bench_ft_strdup, 1},
	{"ft_strcpy", bench_ft_strcpy, 1},
	{"ft_strncpy", bench_ft_strncpy, 1},
	{"ft_strcat", bench_ft_strcat, 1},
	{"ft_strncat", bench_ft_strncat, 1},
	{"ft_strlcat", bench_ft_strlcat, 1},
	{"ft_strchr", bench_ft_strchr, 1},
	{"ft_strrchr", bench_ft_strrchr, 1},
	{"ft_strstr", bench_ft_strstr, 1},
	{"ft_strnstr", bench_ft_strnstr, 1},
	{"ft_strcmp", bench_ft_strcmp, 1},
	{"ft_strncmp", bench_ft_strncmp, 1},
	{"ft_atoi", bench_ft_atoi, 1},

	{NULL, NULL, 0}
};

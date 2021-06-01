# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/08 16:38:19 by tmatis            #+#    #+#              #
#    Updated: 2021/05/29 22:04:34 by jmazoyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS_ASSERT		= assert.c assert_utils.c

SRCS_CHAR		= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
				  ft_islower.c ft_isprint.c ft_isupper.c ft_toupper.c \
				  ft_utf8_encode.c ft_isspace.c

SRCS_LST		= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
				  ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
				  ft_lstsize.c ft_lstlast.c ft_lstremove_one_if_bonus.c

SRCS_MEMORY		= ft_bzero.c ft_memccpy.c ft_memcmp.c ft_memmove.c \
				  ft_realloc.c ft_calloc.c ft_memchr.c ft_memcpy.c ft_memset.c

SRCS_MISC		= ft_atoi.c ft_itoa.c

SRCS_PUT		= ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
				  ft_putendl_fd.c ft_putstr.c ft_putwstr_fd.c

SRCS_STRING		= ft_christr.c ft_split.c ft_str_is_alpha.c \
				  ft_str_is_lowercase.c ft_str_is_uppercase.c ft_strcat.c \
				  ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strequ.c \
				  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				  ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
				  ft_strnlen.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				  ft_substr.c

SRCS_GNL		= ft_gnl.c ft_gnl_utils.c ft_strjoin_del_bonus.c \
				  ft_strnjoin_del_bonus.c get_next_line_bonus.c \
				  ft_min_size_t_bonus.c

SRCS_WSTRING	= ft_wstr_strlen.c ft_wstrlen.c ft_wstrnlen.c ft_wstrtostr.c

SRCS_LOG		= ft_log.c

SRCS_MATHS		= maths.c

OBJS_ASSERT		= $(addprefix assert/, ${SRCS_ASSERT:.c=.o})
OBJS_CHAR		= $(addprefix char/, ${SRCS_CHAR:.c=.o})
OBJS_LST		= $(addprefix lst/, ${SRCS_LST:.c=.o})
OBJS_MEMORY		= $(addprefix memory/, ${SRCS_MEMORY:.c=.o})
OBJS_MISC		= $(addprefix misc/, ${SRCS_MISC:.c=.o})
OBJS_PUT		= $(addprefix put/, ${SRCS_PUT:.c=.o})
OBJS_STRING		= $(addprefix string/, ${SRCS_STRING:.c=.o})
OBJS_WSTRING	= $(addprefix wstring/, ${SRCS_WSTRING:.c=.o})
OBJS_GNL		= $(addprefix gnl/, ${SRCS_GNL:.c=.o})
OBJS_PRINTF 	= $(addprefix printf/, ${SRCS_PRINTF:.c=.o})
OBJS_LOG	 	= $(addprefix log/, ${SRCS_LOG:.c=.o})
OBJS_MATHS	 	= $(addprefix maths/, ${SRCS_MATHS:.c=.o})
NAME			= libft.a

.c.o:
			@clang -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

$(NAME):	${OBJS_ASSERT} ${OBJS_CHAR} ${OBJS_LST} ${OBJS_MEMORY} \
			${OBJS_MISC} ${OBJS_PUT} ${OBJS_STRING} ${OBJS_WSTRING} \
			${OBJS_GNL} ${OBJS_PRINTF} ${OBJS_LOG} ${OBJS_MATHS}
			@ar -rcs  $@ $^

all:		${NAME}

clean:
			@rm -f ${OBJS_ASSERT} ${OBJS_CHAR} ${OBJS_LST} ${OBJS_MEMORY} \
			${OBJS_MISC} ${OBJS_PUT} ${OBJS_STRING} ${OBJS_WSTRING} \
			${OBJS_GNL} ${OBJS_PRINTF} ${OBJS_LOG} ${OBJS_MATHS}

fclean:		clean
			@rm -f ${NAME}

re:			fclean all


.PHONY:		all clean fclean re

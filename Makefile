SRCS	=	get_next_line.c \
			get_next_line_utils.c 
			
OBJS	= ${SRCS:.c=.o}
NAME	= get_next_line.a
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -D BUFFER_SIZE=42

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re, bonus

#fullgcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
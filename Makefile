##
## EPITECH PROJECT, 2023
## MyTeams
## File description:
## Makefile
##

CC = gcc
RM = rm -rf

SERV_SRC = app/server.c \
	src/server/database_loading.c \
	src/server/database_management.c \
	src/server/generate_server.c \
	src/server/prompt_misc_utils.c \
	src/server/server_main_functions.c \
	src/server/server_runtime_functions.c \
	src/server/server_data_clearing.c \

CLI_SRC = app/client.c

SRC_TEST = ./test/main.c

SERV_C_OBJ = $(SERV_SRC:.c=.o)

CLI_C_OBJ = $(CLI_SRC:.c=.o)

C_OBJ_TEST = $(SRC_TEST:.c=.o)

SERV_BINARY = myteams_server

CLI_BINARY = myteams_cli

CFLAGS = -Wall -Wextra -Werror -I./include/ -lmyteams -L./libs/myteams

DEBUG_FLAGS = -g3 -Wpedantic

SHUFFLE := $(shell shuf -i1024-65535 -n1)

PWD := $(shell pwd)

SERV_VALGRIND_PARAMS = --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--log-file=$(PWD)/serv_valgrind.out

CLI_VALGRIND_PARAMS = --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--log-file=$(PWD)/cli_valgrind.out

SERV_TEST_PARAMS = $(SHUFFLE)

CLI_TEST_PARAMS = 127.0.0.1 $(SHUFFLE)

.PHONY: all clean fclean re debug

%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)
	@echo -e '[OK] Pre-compiled' $< '->' $@ ''

all: $(SERV_BINARY) $(CLI_BINARY)

$(SERV_BINARY): $(SERV_C_OBJ)
	@$(CC) -o $(SERV_BINARY) $(SERV_C_OBJ) $(CFLAGS)
	@echo -e '[Finish]' $(SERV_BINARY) 'compiled'

$(CLI_BINARY): $(CLI_C_OBJ)
	@$(CC) -o $(CLI_BINARY) $(CLI_C_OBJ) $(CFLAGS)
	@echo -e '[Finish]' $(CLI_BINARY) 'compiled'

clean:
	@$(RM) $(SERV_C_OBJ)
	@$(RM) $(CLI_C_OBJ)
	@$(RM) #*#
	@$(RM) ~*
	@echo -e '[Cleaner] clean success'

fclean: clean
	@$(RM) $(SERV_BINARY)
	@$(RM) $(CLI_BINARY)
	@echo -e '[Cleaner] fclean success'

re: fclean all

serv_debug: $(SERV_C_OBJ)
	@$(CC) -o $(SERV_BINARY) $(SERV_C_OBJ) $(CFLAGS) $(DEBUG_FLAGS)
	@echo -e '[Finish]' $(SERV_BINARY) 'compiled'

cli_debug: $(CLI_C_OBJ)
	@$(CC) -o $(CLI_BINARY) $(CLI_C_OBJ) $(CFLAGS) $(DEBUG_FLAGS)
	@echo -e '[Finish]' $(CLI_BINARY) 'compiled'

serv_valgrind: serv_debug
	valgrind $(SERV_VALGRIND_PARAMS)  ./$(SERV_BINARY) $(SERV_TEST_PARAMS) &
	@echo -e '[INFO] Valgrind log file created at' $(PWD)/serv_valgrind.out''
	@echo -e '[INFO] Valgrind is running in background'
	@echo -e '[INFO] Current program parameters are' $(SERV_TEST_PARAMS)''

cli_valgrind: cli_debug
	valgrind $(CLI_VALGRIND_PARAMS)  ./$(CLI_BINARY) $(CLI_TEST_PARAMS)
	@echo -e '[INFO] Valgrind log file created at' $(PWD)/cli_valgrind.out''
	@echo -e '[INFO] Valgrind is running in background'
	@echo -e '[INFO] Current program parameters are' $(CLI_TEST_PARAMS)''

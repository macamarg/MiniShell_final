NAME = minishell

SRC_DIR = ./src

OBJ_DIR = ./obj

LIBFT = libft/libft.a

LIBFT_FLAGS = -Llibft -lft

SRC = $(SRC_DIR)/minishell_main.c\
	$(SRC_DIR)/minishell_readline.c\
	$(SRC_DIR)/minishell_parse.c\
	$(SRC_DIR)/minishell_call.c\
	$(SRC_DIR)/minishell_tokenlst.c\
	$(SRC_DIR)/minishell_classtoken.c\
	$(SRC_DIR)/minishell_exptoken.c\
	$(SRC_DIR)/minishell_cmdstruc.c\
	$(SRC_DIR)/minishell_cmd_utils.c\
	$(SRC_DIR)/minishell_pathfill.c\
	$(SRC_DIR)/minishell_expand.c\
	$(SRC_DIR)/minishell_expandutils.c\
	$(SRC_DIR)/minishell_redir.c\
	$(SRC_DIR)/minishell_redir_utils.c\
	$(SRC_DIR)/minishell_cpy_envp.c\
	$(SRC_DIR)/minishell_exec.c\
	$(SRC_DIR)/exec_get_path.c\
	$(SRC_DIR)/exec_get_path_utils.c\
	$(SRC_DIR)/exec_builtin.c\
	$(SRC_DIR)/builtin_pwd.c\
	$(SRC_DIR)/builtin_echo.c\
	$(SRC_DIR)/builtin_cd.c\
	$(SRC_DIR)/builtin_cd_utils.c\
	$(SRC_DIR)/builtin_env.c\
	$(SRC_DIR)/builtin_unset.c\
	$(SRC_DIR)/builtin_export.c\
	$(SRC_DIR)/builtin_export_utils.c\
	$(SRC_DIR)/builtin_exit.c\
	$(SRC_DIR)/heredoc.c\
	$(SRC_DIR)/heredoc_utils.c\
	$(SRC_DIR)/sort_env.c\
	$(SRC_DIR)/exec_other.c\
	$(SRC_DIR)/exec_pipeline.c\
	$(SRC_DIR)/exec_pipeline_utils.c\
	$(SRC_DIR)/shell_level.c\
	$(SRC_DIR)/minishell_clean.c\
	$(SRC_DIR)/minishell_free.c\
	$(SRC_DIR)/minishell_signals.c\
	$(SRC_DIR)/minishell_signhadle.c\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#DEP = $(OBJ:.o=.d)

WFLAGS = -Wall -Wextra -Werror

OPT = -g

CC = cc

.PHONY: all bonus clean fclean re valgrind

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(WFLAGS) $(LIBFT_FLAGS) $(OPT) $^ $(LIBFT) -lreadline -lncurses -o $@
	@echo "Compilation finished! Executable '$(NAME)' is ready."

libft/libft.a:
	@$(MAKE) -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

#-MMD includes all #include dependencies but excludes system headers.

# Include dependencies
#-include $(DEP)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "*.o were cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable '$(NAME)' was removed."

re: fclean all

valgrind:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --track-fds=yes ./$(NAME)
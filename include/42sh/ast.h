/*
** EPITECH PROJECT, 2026
** ast.h
** File description:
** ast
*/

#ifndef AST_H_
    #define AST_H_
    #include "job_control.h"
typedef enum node_type_e {
    NODE_CMD,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_SEMI,
    NODE_SUBSHELL,
    NODE_REDIR_OUT,
    NODE_REDIR_APPEND,
    NODE_REDIR_IN,
    NODE_REDIR_HEREDOC,
    NODE_FILE
} node_type_t;

typedef struct ast_node_s {
    node_type_t type;
    char *cmd;
    struct ast_node_s *left;
    struct ast_node_s *right;
} ast_node_t;

typedef struct job_list_s job_list_t;

ast_node_t *create_node(node_type_t type, char *cmd);
void free_ast(ast_node_t *node);
char *my_strndup(char *str, int n);
int match_op(char *s, int i, char *op);
int find_op(char *str, char *op);
char *trim_spaces(char *str);
ast_node_t *split_node(char *str, int idx, int oplen, node_type_t type);
ast_node_t *parse_expr(char *str);
ast_node_t *parse_and_or(char *str);
ast_node_t *parse_pipe(char *str);
ast_node_t *parse_redir(char *str);
ast_node_t *parse_cmd(char *str);
int exec_ast(ast_node_t *node, char ***env, job_list_t *jobs);
int exec_pipe_node(ast_node_t *node, char ***env, job_list_t *jobs);
int exec_and_or(ast_node_t *node, char ***env, job_list_t *jobs);
int process_ast_line(char *line, char ***env, job_list_t *jobs);
int exec_redir_out(ast_node_t *node, char ***env, job_list_t *jobs);
int exec_redir_append(ast_node_t *node, char ***env, job_list_t *jobs);
int exec_redir_in(ast_node_t *node, char ***env, job_list_t *jobs);
int exec_redir_heredoc(ast_node_t *node, char ***env, job_list_t *jobs);

#endif /* !AST_H_ */

#include "minishell.h"

static char *init_cwd()
{
    char *cwd = getcwd(NULL, 0);
    cwd = basename(cwd);

    return (cwd);
}

static char *init_hostname()
{
    char *hostname = malloc(BUFFER_SIZE);

    gethostname(hostname, BUFFER_SIZE);
    return (hostname);
}

static char *init_input()
{
    char *input =  malloc(BUFFER_SIZE);

    ft_bzero(input, BUFFER_SIZE);
    return (input);
}

static t_hist *init_history()
{
    t_hist *history = malloc(sizeof(t_hist));

    ft_bzero(history, sizeof(t_hist));
    return (history);
}

static char **init_bin_path()
{
    char *env_path = getenv("PATH");
    char **path = ft_split(env_path, ':');

    return (path);
}

static t_table_cmd *init_table_cmd()
{
    t_table_cmd *table = (t_table_cmd *) malloc(sizeof(t_table_cmd));

    table->tokens = NULL;
    table->ast = new_cmd();
    table->background = false;

    return table;
}

void    init(t_shell *SHELL)
{
    SHELL->cwd = init_cwd();
    SHELL->user = getenv("USER");
    SHELL->hostname = init_hostname();
    SHELL->input = init_input();
    SHELL->history = init_history();
    SHELL->bin_paths = init_bin_path();
    SHELL->table = init_table_cmd();
    SHELL->exitstatus = 0;
    tcgetattr(STDIN_FILENO, SHELL->termios);
}

t_tokens    *new_token()
{
    t_tokens *token = (t_tokens *) malloc(sizeof(t_tokens));

    if (token == NULL)
        return (NULL);
        
    ft_memset(token, 0, sizeof(t_tokens));
    token->arg = NULL;
    token->next = NULL;

    return (token);
}

t_cmd    *new_cmd()
{
    t_cmd *cmd = (t_cmd *) malloc(sizeof(t_cmd));

    if (cmd == NULL)
    {
        perror("new_cmd:");
        return (NULL);
    }

    ft_memset(cmd, 0, sizeof(t_cmd));

    cmd->bin_path = NULL;
    cmd->args = NULL;
    cmd->output = NULL;
    cmd->status = 0;
    cmd->pipe = NULL;
    cmd->is_builtin = false;
    cmd->lst_args = NULL;
    cmd->outputs = NULL;
    cmd->inputs = NULL;
    cmd->errs = NULL;
    cmd->prev = NULL;
    cmd->next = NULL;

    return (cmd);
}

t_redir *new_redir()
{
    t_redir *redir = (t_redir *) malloc( sizeof(t_redir) );

    if (redir == NULL)
    {
        perror("new_cmd:");
        return (NULL);
    }

    ft_memset( redir, 0, sizeof(t_redir) );

    redir->file_path = NULL;
    redir->fd = -1;
    return( redir );
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:43:12 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/13 20:26:25 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function to get env variable value by its name
char *get_env_value(const char *name) {
    for (char **current = g_vars.envp; *current; current++) {
        char *key = strtok(*current, "=");
        char *value = strtok(NULL, "=");

        if (strcmp(key, name) == 0) {
            return value;
        }
    }
    return NULL;
}

// The cd function
int cd(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "cd: too many arguments\n");
        return -1;
    }

    char *path;
    if (argc == 1) {
        path = get_env_value("HOME");
        if (!path) {
            fprintf(stderr, "cd: HOME not set\n");
            return -1;
        }
    } else {
        path = argv[1];
    }

    if (chdir(path) != 0) {
        perror("cd");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[], char *envp[]) {
    g_vars.envp = envp;
    
    // Example usage of cd function:
    // cd(argc, argv);
    
    return 0;
}
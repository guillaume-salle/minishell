#include "tests.h"

static int pipefd[2];
static int saved_fd;

int redirect_fd_to_buffer(int fd) {
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    saved_fd = dup(fd);
    if (saved_fd == -1) {
        perror("dup");
        return -1;
    }
    if (dup2(pipefd[1], fd) == -1) {
        perror("dup2");
        return -1;
    }
    return 0;
}

ssize_t restore_fd_and_read_buffer(int fd, char* buffer, size_t size) {
    if (close(pipefd[1]) == -1) {
        perror("close");
        return -1;
    }

    ssize_t len = read(pipefd[0], buffer, size - 1);
    if (len == -1) {
        perror("read");
        return -1;
    }

    buffer[len] = '\0';

    if (close(pipefd[0]) == -1) {
        perror("close");
        return -1;
    }

    if (dup2(saved_fd, fd) == -1) {
        perror("dup2");
        return -1;
    }

    return len;
}

t_list* new_node(char* name, char* content) {
    t_list* node = (t_list*)malloc(sizeof(t_list));
    node->name = strdup(name); // Make a copy of the string
    node->content = strdup(content); // Make a copy of the string
    node->next = NULL;
    return node;
}


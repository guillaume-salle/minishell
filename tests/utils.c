#include "tests.h"

int pipefd[2];
int saved_stdout;

int redirect_stdout_to_buffer() {
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1) {
        perror("dup");
        return -1;
    }
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        return -1;
    }
    return 0;
}

ssize_t restore_stdout_and_read_buffer(char* buffer, size_t size) {
    // Add this check to ensure STDOUT is restored even if an error occurs later
    if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
        perror("dup2");
        return -1;
    }

    if (close(pipefd[1]) == -1) {
        perror("close");
        return -1;
    }

    ssize_t len = read(pipefd[0], buffer, size - 1);
    if (len == -1) {
        perror("read");
        return -1;
    }

    buffer[len] = '\0';  // Ensure the buffer is null-terminated

    if (close(pipefd[0]) == -1) {
        perror("close");
        return -1;
    }

    return len;
}


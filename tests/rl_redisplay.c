#include <readline/readline.h>
#include <readline/history.h>

int main() {
    // Initialize Readline and History
    using_history();

    // Add some commands to history
    add_history("ls -l");
    add_history("cd /home/user");

    // Modify the input buffer
    rl_insert_text("echo Hello, World!");

    // Redisplay the current line
    rl_redisplay();

    return 0;
}


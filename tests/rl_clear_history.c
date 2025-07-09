   #include <readline/readline.h>
    #include <readline/history.h>

    int main() {
        // Initialize Readline and History
        using_history();

        // Add some commands to history
        add_history("ls -l");
        add_history("cd /home/user");

        // Clear the history
        rl_clear_history();

        // Verify history is cleared
        if (history_length == 0) {
            printf("History cleared successfully.\n");
        } else {
            printf("History still contains %d entries.\n", history_length);
        }

        return 0;
    }


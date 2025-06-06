#include <stdio.h>
#include "larkspur.h"

int main() {
    // sets up configuration for the larkspur cache
    LarkspurConfig config = {
        .port = 8024,
        .log_directory = "logs.txt",
        .max_items = 8
    };
    
    // creates an instance of the larkspur cache
    Larkspur *larkspur = init_larkspur(config);

    // this runs the larkspur cache server/cli
    LarkspurResult result = run(larkspur);

    // checks for process errors
    if (result != SUCCESS) {
        log_error(larkspur->logger, "larkspur encountered an error during exection");
    }

    // frees any allocated memory used by larkspur
    free_larkspur(larkspur);

    // output the process result of the program
    log_info(larkspur->logger, "larkspur exited process happily %s", result != SUCCESS ? "(with errors)" : "");
    return 0;
}
#include <stdio.h>
#include "larkspur.h"

int main(int argc, char *argv[]) {
    // sets up configuration for the larkspur cache
    LarkspurConfig config = {
        .port = 8024,
        .log_dir = "logs.txt",
        .max_items = 16
    };
    
    // creates an instance of the larkspur cache
    Larkspur *larkspur = init_larkspur(config);

    // this runs the larkspur cache server/cli
    LarkspurResult result = run_cli(larkspur);

    // checks for process errors
    if (result != SUCCESS) {
        log_error(larkspur->logger, "larkspur encountered an error during exection");
    }

    // frees any allocated memory used by larkspur
    free_larkspur(larkspur);

    log_info(larkspur->logger, "larkspur exited process happily %s", result != SUCCESS ? "(with errors)" : "");
    return 0;
}
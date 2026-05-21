/* SPDX-License-Identifier: AGPL-3.0-or-later */
#include <stdio.h>
#include <string.h>

#define LATTICRA_CLI_VERSION "0.0.0"

static void latticra_cli_print_status(void) {
    puts("LATTICRA STATUS REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("runtime_behavior=disabled");
    puts("host_mutation=0");
    puts("network=0");
    puts("kernel_operation=0");
    puts("service_operation=0");
    puts("package_manager_operation=0");
    puts("boot_operation=0");
    puts("selinux_policy_operation=0");
    puts("effect_authority=denied");
}

static void latticra_cli_print_version(void) {
    puts("latticra " LATTICRA_CLI_VERSION);
    puts("mode=no-effect");
    puts("runtime_behavior=disabled");
}

static void latticra_cli_print_usage(void) {
    fputs("usage: latticra [--status|--version|--report]\n", stderr);
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--status") == 0) {
        latticra_cli_print_status();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--report") == 0) {
        latticra_cli_print_status();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        latticra_cli_print_version();
        return 0;
    }

    latticra_cli_print_usage();
    return 2;
}

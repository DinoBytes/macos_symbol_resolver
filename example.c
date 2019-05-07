#include <stdio.h>
#include "symbol_resolver.h"


// LaunchServices example
int (*LSServerMain_loc)();



int main() {
    printf("[+] Resolving symbols...");

    void *handle_LaunchServices = dlopen(
        "/System/Library/Frameworks/CoreServices.framework/Frameworks/LaunchServices.framework/LaunchServices",
        RTLD_GLOBAL | RTLD_NOW
    );

    // This should work for both private and public symbols. LSServerMain used as an example
    LSServerMain_loc = resolve_symbol("LaunchServices", "__LSServerMain");

    dlclose(handle_LaunchServices);

    printf(" Done\n");

    printf("Symbol resides at:  %p\n", LSServerMain_loc);

    return LSServerMain_loc();
}

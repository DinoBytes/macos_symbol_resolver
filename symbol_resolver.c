#import <dlfcn.h>
#import <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach/mach.h>
#include <mach/task.h>

#include "CoreSymbolication.h"


void *resolve_symbol(const char *owner, const char *symbol)
{
    if (!owner || !symbol) {
        fprintf(stderr, "Invalid owner or symbol provided.");
        return NULL;
    }

    task_t targetTask;
    if (task_for_pid(mach_task_self(), getpid(), &targetTask)) {
        fprintf(stderr, "Unable to get target task.\n");
        return NULL;
    }

    CSSymbolicatorRef symbolicator = CSSymbolicatorCreateWithTask(targetTask);
    if(CSIsNull(symbolicator)) {
        fprintf(stderr, "Unable to create symbolicator.\n");
        return NULL;
    }

    __block CSSymbolOwnerRef ownerRef = kCSNull;
    CSSymbolicatorForeachSymbolOwnerWithNameAtTime(symbolicator,
                                                   owner,
                                                   kCSNow,
                                                   ^(CSSymbolOwnerRef x) { ownerRef = x; });

    if (CSIsNull(ownerRef)) {
        CSRelease(symbolicator);
        fprintf(stderr, "Unable to find symol owner.\n");
        return NULL;
    }

    __block void *result = NULL;

    CSSymbolIterator iterator = ^(CSSymbolRef symbolRef) {
        const char *symbol_name = CSSymbolGetMangledName(symbolRef);
        if (strcmp(symbol_name, symbol) == 0) {
            result = (void *) CSSymbolGetRange(symbolRef).location;
        }
    };

    CSSymbolOwnerForeachSymbol(ownerRef, iterator);

    CSRelease(symbolicator);
    
    return (result);
}

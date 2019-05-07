#import <dlfcn.h>
#import <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach/mach.h>
#include <mach/task.h>


#include "CoreSymbolication.h"


void *resolve_symbol(const char *owner, const char *symbol);

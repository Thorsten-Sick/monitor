/*
Cuckoo Sandbox - Automated Malware Analysis.
Copyright (C) 2010-2014 Cuckoo Foundation.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MONITOR_HOOKING_H
#define MONITOR_HOOKING_H

#include <stdint.h>
#include <windows.h>
#include "slist.h"

/** Info structure for hooking
**/
typedef struct _hook_info_t {
    uint32_t hook_count;
    uint32_t last_error;

    slist_t retaddr;         // List of return addresses
} hook_info_t;

/** Machine Code structure for hook
**/
typedef struct _hook_data_t {
    uint8_t *trampoline;      // points to the trampoline code
    uint8_t *guide;           // points to the guide code (wrapper around calling original stub)
    uint8_t *func_stub;       // points to the function stub
    uint8_t *clean;           // points cleanup code

    uint8_t *_mem;            // Full memory containing all parts above
} hook_data_t;

/** High level data for hook
**/
typedef struct _hook_t {
    const char *library;  // Library name
    const char *funcname; // Function name
    FARPROC handler;      // pointer to handler function
    FARPROC *orig;        // pointer to original function
    int special;          // 1 if special function

    uint8_t *addr;        // The addr. of the original worker-code. Can be at the end of a chain of jumps

    hook_data_t *data;    // hook_data for that hook
} hook_t;

hook_info_t *hook_alloc();
hook_info_t *hook_info();

void hook_disable();
void hook_enable();

uintptr_t hook_retaddr_get(uint32_t index);

int hook(const char *library, const char *funcname,
    FARPROC handler, FARPROC *orig, int special);

int hook2(hook_t *h);

int hook_is_spoofed_return_address(uintptr_t addr);

#define DISASM_BUFSIZ 128

int disasm(const void *addr, char *str);

extern const hook_t g_hooks[];

#endif

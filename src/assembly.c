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

#include <stdint.h>
#include <string.h>
#include "assembly.h"

#if __x86_64__

/** Create assembly to push addr onto the stack
*
* stub: Code area to write assembly to
* addr: Address to push
**/
int asm_push_addr(uint8_t *stub, const uint8_t *addr)
{
    // Push the lower 32-bits of the address onto the stack. The 32-bit
    // value will be zero-extended to 64-bits.
    stub[0] = 0x68;
    *(uint32_t *)(stub + 1) = (uint32_t) (uintptr_t) addr;

    // Move higher 32-bits of the address into the stack.
    // mov dword [rsp+4], 32-bit
    stub[5] = 0xc7;
    stub[6] = 0x44;
    stub[7] = 0x24;
    stub[8] = 0x04;
    *(uint32_t *)(stub + 9) = (uint32_t) ((uintptr_t) addr >> 32);
    return 13;
}

#else

/** Create assembly to push addr onto the stack
*
* stub: Code area to write assembly to
* addr: Address to push
**/
int asm_push_addr(uint8_t *stub, const uint8_t *addr)
{
    // Push the address onto the stack.
    stub[0] = 0x68; // PUSH
    *(const uint8_t **)(stub + 1) = addr;
    return 5;
}

#endif

/** Create assembly to jump to address
*
* stub: memory to modify
* addr: Addr to jump to
**/
int asm_jump_32bit(uint8_t *stub, const uint8_t *addr)
{
    stub[0] = 0xe9; // JMP
    *(uint32_t *)(stub + 1) = addr - stub - 5;
    return 5;
}

/** Create assembly push addr and return
*
* stub: Memory area to write assembly to
* addr: addr to jump to
**/
int asm_jump_addr(uint8_t *stub, const uint8_t *addr)
{
    uint8_t *base = stub;

    // Push the address on the stack.
    stub += asm_push_addr(stub, addr);

    // Pop the address into the instruction pointer.
    *stub++ = 0xc3; // RET

    return stub - base;
}

/** Create assembly code to jump to address
*
* stub: stub to modify
* addr: Addr to call
**/
int asm_call_addr(uint8_t *stub, const uint8_t *addr)
{
    uint8_t *base = stub;

    // We push the return address onto the stack and then jump into the target
    // address. This way both 32-bit and 64-bit are supported at once. The
    // return address is 8-byte aligned as required in 64-bit mode.
    uint8_t *return_address = stub + ASM_PUSH_ADDR_SIZE + ASM_JUMP_ADDR_SIZE;
    return_address += 8 - ((uintptr_t) return_address & 7);

    stub += asm_push_addr(stub, return_address);
    stub += asm_jump_addr(stub, addr);

    // Pad with a couple of int3's.
    memset(stub, 0xcc, return_address - stub);

    return return_address - base;
}

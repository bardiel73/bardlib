#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep

#define WIN32_LEAN_AND_MEAN
#include "windows.h" // IWYU pragma: keep

int user_main();

__attribute__((used))
void* memset(void* dest, int c, uint64_t n) {
    uint8_t* p = (uint8_t*)dest;
    while (n--) *p++ = (uint8_t)c;
    return dest;
}

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point(void)
{
    int result = user_main();
    ExitProcess(result);
}

#include "windef.h" // IWYU pragma: keep
#include "winuser.h" // IWYU pragma: keep

int user_main();

__attribute__((used))
void* memset(void* dest, int c, unsigned long long n) {
    unsigned char* p = (unsigned char*)dest;
    while (n--) *p++ = (unsigned char)c;
    return dest;
}

__attribute__((noreturn, dllimport))
void __stdcall ExitProcess(int uExitCode);

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point(void)
{
    int result = user_main();
    ExitProcess(result);
}
#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep

#define WIN32_LEAN_AND_MEAN
#include "windows.h" // IWYU pragma: keep

typedef void*  (__cdecl *PNtRtlCopyMemory)(void*, const void*, size_t);
typedef void*  (__cdecl *PNtRtlMoveMemory)(void*, const void*, size_t);
typedef void*  (__cdecl *PNtRtlFillMemory)(void*, size_t, int);
typedef size_t (__cdecl *PNtRtlCompareMemory)(const void*, const void*, size_t);

struct {
    PNtRtlCopyMemory copy;
    PNtRtlMoveMemory move;
    PNtRtlFillMemory fill;
    PNtRtlCompareMemory cmp;
} ntdll_funcs = {0};

void load_ntdll_funcs(void)
{
    if (ntdll_funcs.copy) return;
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
    ntdll_funcs.copy = (PNtRtlCopyMemory)  GetProcAddress(hNtdll, "RtlCopyMemory");
    ntdll_funcs.move = (PNtRtlMoveMemory)  GetProcAddress(hNtdll, "RtlMoveMemory");
    ntdll_funcs.fill = (PNtRtlFillMemory)  GetProcAddress(hNtdll, "RtlFillMemory");
    ntdll_funcs.cmp  = (PNtRtlCompareMemory)GetProcAddress(hNtdll, "RtlCompareMemory");
}

inline void* memcpy(void* dst, const void* src, size_t n) { return ntdll_funcs.copy(dst, src, n);}
inline void* memmove(void* dst, const void* src, size_t n) {return ntdll_funcs.move(dst, src, n);}
inline void* memset(void* dst, int c, size_t n) { return ntdll_funcs.fill(dst, n, c);}
inline int memcmp(const void* p1, const void* p2, size_t n)
{
    size_t same = ntdll_funcs.cmp(p1, p2, n);
    if (same == n) return 0;
    const unsigned char *a = (const unsigned char*)p1 + same;
    const unsigned char *b = (const unsigned char*)p2 + same;
    return (*a > *b) - (*a < *b);
}

int user_main();

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point(void)
{
    load_ntdll_funcs();
    int result = user_main();
    ExitProcess(result);
}
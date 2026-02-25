#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep

#define WIN32_LEAN_AND_MEAN
#include "windows.h" // IWYU pragma: keep

typedef void* (__cdecl *PTR_RtlCopyMemory)(void*, const void*, size_t);
typedef void* (__cdecl *PTR_RtlMoveMemory)(void*, const void*, size_t);
typedef void* (__cdecl *PTR_RtlFillMemory)(void*, size_t, int);
typedef size_t (__cdecl *PTR_RtlCompareMemory)(const void*, const void*, size_t);

struct {
    PTR_RtlCopyMemory copy;
    PTR_RtlMoveMemory move;
    PTR_RtlFillMemory fill;
    PTR_RtlCompareMemory cmp;
} ntdll_funcs = {0};

void load_ntdll_funcs(void)
{
    if (ntdll_funcs.copy) return;
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
    *(FARPROC*)&ntdll_funcs.copy = GetProcAddress(hNtdll, "RtlCopyMemory");
    *(FARPROC*)&ntdll_funcs.move = GetProcAddress(hNtdll, "RtlMoveMemory");
    *(FARPROC*)&ntdll_funcs.fill = GetProcAddress(hNtdll, "RtlFillMemory");
    *(FARPROC*)&ntdll_funcs.cmp  = GetProcAddress(hNtdll, "RtlCompareMemory");
}

inline void* memcpy(void* dst, const void* src, size_t n) {return ntdll_funcs.copy(dst, src, n);}
inline void* memmove(void* dst, const void* src, size_t n) {return ntdll_funcs.move(dst, src, n);}
inline void* memset(void* dst, int c, size_t n) {return ntdll_funcs.fill(dst, n, c);}
inline int memcmp(const void* p1, const void* p2, size_t n)
{
    size_t same = ntdll_funcs.cmp(p1, p2, n);
    if (same == n) return 0;
    const uint8_t *a = (const uint8_t*)p1 + same;
    const uint8_t *b = (const uint8_t*)p2 + same;
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
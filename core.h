#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep

#define WIN32_LEAN_AND_MEAN
#include "windows.h" // IWYU pragma: keep

// builtin mem*
typedef void* (__cdecl *PTR_RtlCopyMemory)(void*, const void*, size_t);
typedef void* (__cdecl *PTR_RtlMoveMemory)(void*, const void*, size_t);
typedef void* (__cdecl *PTR_RtlFillMemory)(void*, size_t, int);
typedef size_t (__cdecl *PTR_RtlCompareMemory)(const void*, const void*, size_t);

// time
typedef int (__cdecl *PTR_RtlQueryPerformanceFrequency)(uint64_t*);
typedef int (__cdecl *PTR_RtlQueryPerformanceCounter)(uint64_t*);

// GLOBAL
struct {
    PTR_RtlCopyMemory copy;
    PTR_RtlMoveMemory move;
    PTR_RtlFillMemory set;
    PTR_RtlCompareMemory cmp;

    PTR_RtlQueryPerformanceFrequency qpc_freq;
    PTR_RtlQueryPerformanceCounter qpc_count;
} ntdll_funcs = {0};

static void load_ntdll_funcs(void)
{
    if (ntdll_funcs.copy) return;
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
    *(FARPROC*)&ntdll_funcs.copy = GetProcAddress(hNtdll, "RtlCopyMemory");
    *(FARPROC*)&ntdll_funcs.move = GetProcAddress(hNtdll, "RtlMoveMemory");
    *(FARPROC*)&ntdll_funcs.set = GetProcAddress(hNtdll, "RtlFillMemory");
    *(FARPROC*)&ntdll_funcs.cmp  = GetProcAddress(hNtdll, "RtlCompareMemory");

    *(FARPROC*)&ntdll_funcs.qpc_freq  = GetProcAddress(hNtdll, "RtlQueryPerformanceFrequency");
    *(FARPROC*)&ntdll_funcs.qpc_count  = GetProcAddress(hNtdll, "RtlQueryPerformanceCounter");
}

inline void* memcpy(void* dst, const void* src, size_t n) {return ntdll_funcs.copy(dst, src, n);}
inline void* memmove(void* dst, const void* src, size_t n) {return ntdll_funcs.move(dst, src, n);}
inline void* memset(void* dst, int c, size_t n) {return ntdll_funcs.set(dst, n, c);}
inline int memcmp(const void* p1, const void* p2, size_t n)
{
    size_t same = ntdll_funcs.cmp(p1, p2, n);
    if (same == n) return 0;
    const uint8_t *a = (const uint8_t*)p1 + same;
    const uint8_t *b = (const uint8_t*)p2 + same;
    return (*a > *b) - (*a < *b);
}

typedef struct global_time {
    uint64_t freq;
    uint64_t previous_count;
    uint64_t current_count;
} global_time;

// GLOBAL
global_time time = {0}; // TODO: might move this to bardlib.h to keep this clean?

static inline void time_init(void)
{
    ntdll_funcs.qpc_count((void*)&time.previous_count);
    ntdll_funcs.qpc_freq((void*)&time.freq);
}

double time_in_seconds(void)
{
    ntdll_funcs.qpc_count((void*)&time.current_count);
    double ret = (double)((time.current_count - time.previous_count) / (double)time.freq);
    time.previous_count = time.current_count;
    return ret;
}

int user_main();

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point(void)
{
    load_ntdll_funcs();
    time_init();
    int result = user_main();
    ExitProcess(result);
}
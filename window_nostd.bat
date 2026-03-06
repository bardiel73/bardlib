@echo off

set NOCRT=^
-nostdlib -ffreestanding -fno-builtin ^
-mno-stack-arg-probe -fno-asynchronous-unwind-tables ^
-Wl,--entry,entry_point -Wl,--gc-sections -Wl,--subsystem,windows -Xlinker --stack=0x200000,0x200000

set CFLAGS= -Wall -Wextra -Og -gdwarf-5 -gstrict-dwarf -g3
set LFLAGS= -lntdll -lkernel32 -luser32 -lgdi32

@echo on
gcc %NOCRT% %CFLAGS% -o window_nostd.exe window_nostd.c %LFLAGS% && .\window_nostd.exe
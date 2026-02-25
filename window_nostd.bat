@echo off

set CFLAGS=^
-Wall -Wextra ^
-nostdlib -ffreestanding -fno-builtin ^
-mno-stack-arg-probe -fno-asynchronous-unwind-tables ^
-Wl,--entry,entry_point -Wl,--gc-sections -Wl,--subsystem,windows -Xlinker --stack=0x200000,0x200000

set CFLAGS2= -Og
:: set linking= -lkernel32 -luser32 -lgdi32 -lntdll
set linking= -lntdll -lkernel32 -luser32 -lgdi32

@echo on
gcc %CFLAGS% %CFLAGS2% -o window_nostd.exe window_nostd.c %linking% && .\window_nostd.exe
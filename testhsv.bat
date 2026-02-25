@echo off
set CFLAGS=^
-Wall -Wextra ^
-Og -ggdb3

set linking=

@echo on
gcc %CFLAGS% -o testhsv.exe testhsv.c %linking% && .\testhsv.exe
@echo off
rem gcc %CFLAGS% -o testhsv.exe testhsv.c %linking% && .\testhsv.exe && del .\testhsv.exe

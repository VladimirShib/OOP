@echo off
rem %1 - value of the first command line argument of the bat-file (as it is)
rem %~1 - value of the first command line argument of the bat-file, removing framing quotes (if any)

rem the PROGRAM variable will store the first command line argument enclosed in quotes
set PROGRAM="%~1"

rem A non-zero return code is expected when running without parameters
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 16 10 > nul
if NOT ERRORLEVEL 1 goto err

rem A zero return code is expected when running with correct parameters
%PROGRAM% "" 15 2 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\empty-argument.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 16 - > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\empty-argument.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 40 15 2 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-notation.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% -15 15 2 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-notation.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 2 10 22 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-arguments.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 20 1A > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-arguments.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 36 0 > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\0-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 36 2 -0 > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\0-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 2 36 1111111111111111 > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\2-36-1111111111111111-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 36 10 -HELLO > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\36-10-(-HELLO)-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 36 10 HELLOWORLD > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\overflow-error.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 36 2147483647 > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\10-36-2147483647-correct-output.txt > nul
if ERRORLEVEL 1 goto err

echo Unit tests succeeded
exit 0

:err
echo Unit tests failed
exit 1
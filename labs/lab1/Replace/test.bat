@echo off
rem %1 - value of the first command line argument of the bat-file (as it is)
rem %~1 - value of the first command line argument of the bat-file, removing framing quotes (if any)

rem the PROGRAM variable will store the first command line argument enclosed in quotes
set PROGRAM="%~1"

rem A non-zero return code is expected when running without parameters
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem A zero return code is expected when running with correct parameters
%PROGRAM% test-data\fox.txt test-data\output.txt bird cat
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\fox.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\fox.txt test-data\output.txt dog cat
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\fox-replace-dog-with-cat.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\1231234.txt test-data\output.txt 1231234 666
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\1231234-replace-with-666.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\ma.txt test-data\output.txt ma mama
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\ma-replace-with-mama.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\empty-string.txt test-data\output.txt "" hello
if ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\empty-string-replace-with-hello.txt > nul
if ERRORLEVEL 1 goto err

echo Unit tests succeeded
exit 0

:err
echo Unit tests failed
exit 1
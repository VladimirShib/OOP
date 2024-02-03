@echo off
rem %1 - value of the first command line argument of the bat-file (as it is)
rem %~1 - value of the first command line argument of the bat-file, removing framing quotes (if any)

rem the PROGRAM variable will store the first command line argument enclosed in quotes
set PROGRAM="%~1"

rem A non-zero return code is expected when running without parameters
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem A zero return code is expected when running with correct parameters
%PROGRAM% test-data\nonexistent-file.txt > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\couldnt-open-file.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\matrix-with-char.txt > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-matrix-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\not-3x3-matrix.txt > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-matrix-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\matrix-with-zero-determinant.txt > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\matrix-with-zero-determinant-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\matrix.txt > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\matrix-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\matrix2.txt > test-data\output.txt
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\matrix2-output.txt > nul
if ERRORLEVEL 1 goto err

echo Unit tests succeeded
exit 0

:err
echo Unit tests failed
exit 1
@echo off
rem %1 - value of the first command line argument of the bat-file (as it is)
rem %~1 - value of the first command line argument of the bat-file, removing framing quotes (if any)

rem the PROGRAM variable will store the first command line argument enclosed in quotes
set PROGRAM="%~1"

rem A non-zero return code is expected when running without parameters
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem A zero return code is expected when running with correct parameters
%PROGRAM% test-data\invalid-char.txt test-data\output.txt > test-data\error-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\error-output.txt test-data\invalid-char-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\two-starting-points.txt test-data\output.txt > test-data\error-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\error-output.txt test-data\two-starting-points-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\two-destination-points.txt test-data\output.txt > test-data\error-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\error-output.txt test-data\two-destination-points-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\no-starting-or-destination-point.txt test-data\output.txt > test-data\error-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\error-output.txt test-data\no-starting-or-destination-point-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\labyrinth1.txt test-data\output.txt > test-data\error-output.txt
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\labyrinth1-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\labyrinth2.txt test-data\output.txt > test-data\error-output.txt
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\labyrinth2-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\labyrinth3.txt test-data\output.txt > test-data\error-output.txt
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\labyrinth3-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% test-data\non-enclosed-labyrinth.txt test-data\output.txt > test-data\error-output.txt
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\non-enclosed-labyrinth-output.txt > nul
if ERRORLEVEL 1 goto err

echo Unit tests succeeded
exit 0

:err
echo Unit tests failed
exit 1
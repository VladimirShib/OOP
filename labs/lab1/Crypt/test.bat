@echo off
rem %1 - value of the first command line argument of the bat-file (as it is)
rem %~1 - value of the first command line argument of the bat-file, removing framing quotes (if any)

rem the PROGRAM variable will store the first command line argument enclosed in quotes
set PROGRAM="%~1"

rem A non-zero return code is expected when running without parameters
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem A zero return code is expected when running with correct parameters
%PROGRAM% hello test-data\little-star.txt test-data\encrypted-output.txt 20 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe test-data\output.txt test-data\invalid-operation.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% crypt test-data\little-star.txt test-data\encrypted-output.txt "" > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-key.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% crypt test-data\little-star.txt test-data\encrypted-output.txt -5 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\invalid-key.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% crypt test-data\little-star.txt test-data\encrypted-output.txt 300 > test-data\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\too-large-key-value.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% crypt test-data\little-star.txt test-data\encrypted-output.txt 13
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt test-data\encrypted-output.txt test-data\output.txt 13
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\little-star.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% crypt test-data\little-star.txt test-data\encrypted-output.txt 13
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt test-data\encrypted-output.txt test-data\output.txt 14
if ERRORLEVEL 1 goto err
fc.exe /w test-data\output.txt test-data\little-star.txt > nul
if NOT ERRORLEVEL 1 goto err

echo Unit tests succeeded
exit 0

:err
echo Unit tests failed
exit 1
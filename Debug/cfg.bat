@echo off

if "%1"=="_chk_" shift

rem --- Konfiguracja ocen.bat ---
rem W przypadku opracowania wlasnego zestawu testow nalezy zmienic
rem zawartosc zmiennej TESTS a testy zabpiowac do kataloguw IN\, OUT\
rem nazwy testow powinny analogiczne do przykladowych

if "%1"=="NMKSolver" goto NMKSolver
if "%1"=="SHIPS" goto NMKSolver



set T=%1
goto end

:NMKSolver
set I=NMKSolver
set T=0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
set C=bin\cmp.exe
goto end


rem --- Koniec konfiguracji

:end

if "%C%"=="" goto def_chk
goto new_chk
:def_chk
set C=bin\cmp.exe
:new_chk

:real_end

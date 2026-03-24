@echo off
color 2
setlocal enabledelayedexpansion

windres resources.rc -O coff -o resources.res

set APPNAME=LevelEditor
set DEFAULT_SDL3=C:/Dependencies/SDL3
echo SDL3 Folder: %DEFAULT_SDL3%

set "SOURCES="
set "OBJECTS="
set "INCLUDES="

:: Buscar todos los archivos .cpp en ./Source
for /R ./Source %%f in (*.cpp) do (
    set "SOURCES=!SOURCES! %%f"
    set "OBJECTS=!OBJECTS! %%~nf.o"
)

:: Buscar todas las carpetas de inclusion dentro de ./Headers
for /R ./Headers /D %%d in (*) do (
    set "INCLUDES=!INCLUDES! -I%%d"
)

:: Compilar
for %%f in (%SOURCES%) do (
    g++ -std=c++17 -c %%f ^
    -I ./Headers/ %INCLUDES% ^
    -I %DEFAULT_SDL3%/include ^
    -o %%~nf.o

    if errorlevel 1 (
        echo Error compiling %%f.
        pause
        exit /b 1
    )
)

:: Linking (IMPORTANTE: SDL3 cambia libs)
g++ %OBJECTS% ^
-L %DEFAULT_SDL3%/lib ^
-o ./Bin/%APPNAME%.exe ^
resources.res ^
-static-libgcc -static-libstdc++ ^
-lmingw32 ^
-lSDL3 ^
-lSDL3_image ^
-lSDL3_mixer ^
-lSDL3_ttf

if errorlevel 1 (
    echo Linker error.
    pause
    exit /b 1
)

pause
echo Compilation succeeded. Running the app...
start ./Bin/%APPNAME%.exe

endlocal
exit
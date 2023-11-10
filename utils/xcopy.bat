@echo off

echo copiando carpeta res en la carpeta release

cd %1
mkdir res
xcopy %2 %3 /s /i /y

echo Copiado correctamente

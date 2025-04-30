@echo off
setlocal

:: Caminho de instalação
set SNASK_DIR=C:\Snask

:: Cria a pasta C:\Snask, se não existir
if not exist "%SNASK_DIR%" (
    mkdir "%SNASK_DIR%"
)

:: Copia os arquivos principais para C:\Snask
copy /Y "main.py" "%SNASK_DIR%\main.py"
copy /Y "Snask_Interpreter.py" "%SNASK_DIR%\Snask_Interpreter.py"
copy /Y "grammar.lark" "%SNASK_DIR%\grammar.lark"

:: Cria o snask.bat para execução global
(
    echo @echo off
    echo python "%%~dp0main.py" %%*
    echo echo.
    echo pause
) > "%SNASK_DIR%\snask.bat"

:: Adiciona C:\Snask ao PATH do sistema, se ainda não estiver
echo %PATH% | find /I "%SNASK_DIR%" >nul
if errorlevel 1 (
    setx PATH "%PATH%;%SNASK_DIR%" /M
)

echo.
echo ✅ Snask instalado com sucesso em %SNASK_DIR%
echo 🔁 Agora você pode executar: snask arquivo.snask de qualquer lugar
pause

@echo off
:: Verificar se o script está rodando como administrador
openfiles >nul 2>nul
if %errorlevel% neq 0 (
    echo O script nao esta rodando como administrador. Tentando novamente...
    powershell -Command "Start-Process cmd -ArgumentList '/c %~s0' -Verb runAs"
    exit /b
)

:: Baixar Python 3.8.0
echo Baixando Python 3.8.0...
curl -o "%USERPROFILE%\Downloads\python-3.8.0-amd64.exe" https://www.python.org/ftp/python/3.8.0/python-3.8.0-amd64.exe

:: Instalar Python 3.8.0
echo Instalando Python 3.8.0...
start /wait %USERPROFILE%\Downloads\python-3.8.0-amd64.exe /quiet InstallAllUsers=1 PrependPath=1

:: Remover o instalador
echo Removendo o instalador...
del %USERPROFILE%\Downloads\python-3.8.0-amd64.exe

echo Updating..
python -m pip install --upgrade pip

:: Baixar e instalar Lark
echo Instalando Lark...
pip install lark-parser

echo Python 3.8.0 e Lark foram instalados com sucesso.
pause

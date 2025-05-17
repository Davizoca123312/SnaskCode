import os
import shutil
import requests
import zipfile
import ctypes
import sys
from pathlib import Path

DESTINO = Path("C:/Snask")
SCRIPT_NAME = "Atualizar.py"  # nome do script que não deve ser apagado

def remove_old_files_except_script():
    print("Removendo arquivos e pastas antigos, exceto o script...")
    for item in DESTINO.iterdir():
        # Se for o próprio script, pula
        if item.name == SCRIPT_NAME:
            continue
        try:
            if item.is_file():
                item.unlink()
                print(f"Arquivo removido: {item.name}")
            elif item.is_dir():
                shutil.rmtree(item)
                print(f"Pasta removida: {item.name}")
        except Exception as e:
            print(f"Erro removendo {item}: {e}")

def download_zip():
    url = "https://github.com/Davizoca123312/SnaskCode/raw/main/SnaskOfficial.zip"
    zip_path = DESTINO / "SnaskOfficial.zip"
    print("Baixando SnaskOfficial.zip...")
    try:
        import requests
        r = requests.get(url, stream=True)
        r.raise_for_status()
        with open(zip_path, "wb") as f:
            for chunk in r.iter_content(chunk_size=8192):
                f.write(chunk)
        print("Download concluído.")
        return zip_path
    except Exception as e:
        print(f"Erro ao baixar arquivo: {e}")
        return None

def extract_zip(zip_path):
    print("Extraindo arquivos...")
    try:
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(DESTINO)
        print("Extração concluída.")
    except Exception as e:
        print(f"Erro ao extrair arquivos: {e}")

def add_path_to_user_env():
    print(f"Adicionando {DESTINO} ao PATH do usuário...")
    try:
        import winreg as reg
        key = reg.OpenKey(reg.HKEY_CURRENT_USER,
                          r"Environment",
                          0, reg.KEY_READ)
        current_path, _ = reg.QueryValueEx(key, "Path")
        reg.CloseKey(key)

        path_str = str(DESTINO)
        if path_str.lower() in current_path.lower():
            print("Caminho já está no PATH do usuário.")
            return

        new_path = current_path + ";" + path_str

        key = reg.OpenKey(reg.HKEY_CURRENT_USER,
                          r"Environment",
                          0, reg.KEY_WRITE)
        reg.SetValueEx(key, "Path", 0, reg.REG_EXPAND_SZ, new_path)
        reg.CloseKey(key)

        HWND_BROADCAST = 0xFFFF
        WM_SETTINGCHANGE = 0x1A
        SMTO_ABORTIFHUNG = 0x0002
        ctypes.windll.user32.SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, "Environment", SMTO_ABORTIFHUNG, 5000, None)
        print("PATH atualizado com sucesso!")
    except Exception as e:
        print(f"Erro ao adicionar PATH: {e}")

def main():
    if not DESTINO.exists():
        print(f"Criando diretório {DESTINO}...")
        DESTINO.mkdir(parents=True, exist_ok=True)
    
    remove_old_files_except_script()
    zip_path = download_zip()
    if not zip_path:
        print("Falha no download, abortando.")
        sys.exit(1)
    extract_zip(zip_path)
    zip_path.unlink(missing_ok=True)

    add_path_to_user_env()

    print("\n✅ Atualização concluída com sucesso!")

if __name__ == "__main__":
    main()

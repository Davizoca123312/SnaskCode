import os
import shutil
import requests
import re

SNASK_PACKAGES_DIR = "snask_packages"
SNASKHUB_URL = "http://127.0.0.1:5000" # URL do seu SnaskHub local

def install_package(package_name):
    print(f"Tentando instalar o pacote '{package_name}' do SnaskHub...")
    package_path = os.path.join(SNASK_PACKAGES_DIR, package_name)
    
    if os.path.exists(package_path):
        print(f"Pacote '{package_name}' já existe localmente. Pulando instalação.")
        return

    os.makedirs(package_path, exist_ok=True)
    
    download_url = f"{SNASKHUB_URL}/api/packages/{package_name}/download"
    try:
        response = requests.get(download_url, stream=True)
        response.raise_for_status() # Levanta um HTTPError para status de erro (4xx ou 5xx)

        filename = package_name + ".snask"
        if "Content-Disposition" in response.headers:
            cd = response.headers["Content-Disposition"]
            fname_match = re.findall(r"filename=\"(.+)\"", cd)
            if fname_match:
                filename = fname_match[0]

        file_path = os.path.join(package_path, filename)

        with open(file_path, "wb") as f:
            for chunk in response.iter_content(chunk_size=8192):
                f.write(chunk)
        
        with open(os.path.join(package_path, "snaskpack.json"), "w", encoding="utf-8") as f:
            f.write(f'{{"name": "{package_name}", "version": "1.0.0", "description": "Pacote baixado do SnaskHub."}}')
        
        print(f"Pacote '{package_name}' instalado com sucesso em '{package_path}'.")

    except requests.exceptions.RequestException as e:
        print(f"ERRO ao baixar o pacote '{package_name}' do SnaskHub: {e}")
        shutil.rmtree(package_path)
    except Exception as e:
        print(f"Ocorreu um erro inesperado durante a instalação: {e}")
        shutil.rmtree(package_path)

if __name__ == "__main__":
    import sys
    import re
    if len(sys.argv) > 2 and sys.argv[1] == "install":
        install_package(sys.argv[2])
    else:
        print("Uso: python snaskpack.py install <nome_do_pacote>")

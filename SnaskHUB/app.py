from flask import Flask, render_template_string, request, jsonify, send_from_directory
import sqlite3
import os

app = Flask(__name__)

DATABASE = 'snaskhub.db'
PACKAGES_DIR = 'packages_data'

# Garante que o diretório de pacotes exista
if not os.path.exists(PACKAGES_DIR):
    os.makedirs(PACKAGES_DIR)

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row # Permite acessar colunas como dicionário
    return conn

def init_db():
    with get_db_connection() as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS packages (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                version TEXT NOT NULL,
                description TEXT,
                filename TEXT NOT NULL,
                UNIQUE(name, version)
            )
        ''')
        conn.commit()

# Inicializa o banco de dados ao iniciar a aplicação
with app.app_context():
    init_db()

HTML_CONTENT = """
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SnaskHub</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f4f4f4;
            color: #333;
        }
        header {
            background-color: #333;
            color: #fff;
            padding: 1em 0;
            text-align: center;
        }
        nav {
            background-color: #444;
            color: #fff;
            padding: 0.5em 0;
            text-align: center;
        }
        nav a {
            color: #fff;
            text-decoration: none;
            padding: 0.5em 1em;
        }
        nav a:hover {
            background-color: #555;
        }
        .container {
            width: 80%;
            margin: 2em auto;
            background-color: #fff;
            padding: 2em;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
        }
        .package-card {
            border: 1px solid #ddd;
            padding: 1em;
            margin-bottom: 1em;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .package-card h3 {
            margin-top: 0;
            color: #007bff;
        }
        .package-card p {
            margin-bottom: 0.5em;
        }
        .install-command {
            background-color: #e9e9e9;
            padding: 0.5em;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
            font-size: 0.9em;
            color: #c0392b;
        }
        footer {
            text-align: center;
            padding: 1em 0;
            color: #777;
            font-size: 0.8em;
        }
    </style>
</head>
<body>
    <header>
        <h1>SnaskHub</h1>
        <p>O seu repositório de pacotes Snask!</p>
    </header>
    <nav>
        <a href="#" onclick="loadPackages()">Pacotes</a>
        <a href="#" onclick="showUploadForm()">Publicar</a>
    </nav>
    <div class="container">
        <div id="content">
            <h2>Pacotes Disponíveis</h2>
            <div id="package-list">
                <!-- Pacotes serão carregados aqui pelo JavaScript -->
            </div>
        </div>
    </div>
    <footer>
        <p>&copy; 2025 SnaskHub. Todos os direitos reservados.</p>
    </footer>

    <script>
        async function loadPackages() {
            const packageListDiv = document.getElementById('package-list');
            packageListDiv.innerHTML = ''; // Limpa a lista existente
            document.getElementById('content').innerHTML = '<h2>Pacotes Disponíveis</h2><div id="package-list"></div>';

            try {
                const response = await fetch('/api/packages');
                const packages = await response.json();

                if (packages.length === 0) {
                    packageListDiv.innerHTML = '<p>Nenhum pacote disponível ainda. Que tal publicar um?</p>';
                    return;
                }

                packages.forEach(pkg => {
                    const card = document.createElement('div');
                    card.className = 'package-card';
                    card.innerHTML = `
                        <h3>${pkg.name} <small>v${pkg.version}</small></h3>
                        <p>${pkg.description}</p>
                        <p>Comando de instalação: <span class="install-command">snaskpack install ${pkg.name}</span></p>
                    `;
                    packageListDiv.appendChild(card);
                });
            } catch (error) {
                console.error('Erro ao carregar pacotes:', error);
                packageListDiv.innerHTML = '<p>Erro ao carregar pacotes. Tente novamente mais tarde.</p>';
            }
        }

        function showUploadForm() {
            const contentDiv = document.getElementById('content');
            contentDiv.innerHTML = `
                <h2>Publicar Novo Pacote</h2>
                <form id="upload-form">
                    <label for="packageName">Nome do Pacote:</label><br>
                    <input type="text" id="packageName" name="packageName" required><br><br>
                    
                    <label for="packageVersion">Versão:</label><br>
                    <input type="text" id="packageVersion" name="packageVersion" required><br><br>
                    
                    <label for="packageDescription">Descrição:</label><br>
                    <textarea id="packageDescription" name="packageDescription" rows="4" required></textarea><br><br>
                    
                    <label for="packageFile">Arquivo do Pacote (.zip ou .snask):</label><br>
                    <input type="file" id="packageFile" name="packageFile" accept=".zip,.snask" required><br><br>
                    
                    <button type="submit">Publicar Pacote</button>
                </form>
                <p id="upload-status"></p>
            `;

            document.getElementById('upload-form').addEventListener('submit', async function(event) {
                event.preventDefault();
                const statusParagraph = document.getElementById('upload-status');
                statusParagraph.textContent = 'Publicando...';
                statusParagraph.style.color = 'black';

                const formData = new FormData(this);

                try {
                    const response = await fetch('/api/upload', {
                        method: 'POST',
                        body: formData
                    });
                    const result = await response.json();

                    if (response.ok) {
                        statusParagraph.textContent = result.message;
                        statusParagraph.style.color = 'green';
                        loadPackages(); // Recarrega a lista de pacotes
                    } else {
                        statusParagraph.textContent = `Erro: ${result.message}`;
                        statusParagraph.style.color = 'red';
                    }
                } catch (error) {
                    console.error('Erro no upload:', error);
                    statusParagraph.textContent = 'Erro de conexão ou servidor.';
                    statusParagraph.style.color = 'red';
                }
            });
        }

        // Carrega os pacotes ao carregar a página
        window.onload = loadPackages;
    </script>
</body>
</html>
"""

@app.route('/')
def home():
    return render_template_string(HTML_CONTENT)

@app.route('/api/packages', methods=['GET'])
def get_packages():
    conn = get_db_connection()
    packages = conn.execute('SELECT name, version, description FROM packages').fetchall()
    conn.close()
    return jsonify([dict(row) for row in packages])

@app.route('/api/upload', methods=['POST'])
def upload_package():
    package_name = request.form.get('packageName')
    package_version = request.form.get('packageVersion')
    package_description = request.form.get('packageDescription')
    package_file = request.files.get('packageFile')

    if not all([package_name, package_version, package_description, package_file]):
        return jsonify({"status": "error", "message": "Todos os campos são obrigatórios."}), 400

    # Salva o arquivo do pacote
    filename = f"{package_name}-{package_version}{os.path.splitext(package_file.filename)[1]}"
    file_path = os.path.join(PACKAGES_DIR, filename)
    package_file.save(file_path)

    conn = get_db_connection()
    try:
        conn.execute('''
            INSERT INTO packages (name, version, description, filename)
            VALUES (?, ?, ?, ?)
        ''', (package_name, package_version, package_description, filename))
        conn.commit()
    except sqlite3.IntegrityError:
        conn.close()
        return jsonify({"status": "error", "message": "Pacote com este nome e versão já existe."}), 409
    except Exception as e:
        conn.close()
        os.remove(file_path) # Remove o arquivo se a inserção no DB falhar
        return jsonify({"status": "error", "message": f"Erro ao salvar no banco de dados: {e}"}), 500
    finally:
        conn.close()

    return jsonify({"status": "success", "message": "Pacote publicado com sucesso!"})

@app.route('/api/packages/<package_name>/download', methods=['GET'])
def download_package(package_name):
    conn = get_db_connection()
    package_info = conn.execute('SELECT filename FROM packages WHERE name = ? ORDER BY version DESC LIMIT 1', (package_name,)).fetchone()
    conn.close()

    if package_info:
        filename = package_info['filename']
        return send_from_directory(PACKAGES_DIR, filename, as_attachment=True)
    else:
        return jsonify({"status": "error", "message": "Pacote não encontrado."}), 404

if __name__ == '__main__':
    app.run(debug=True)
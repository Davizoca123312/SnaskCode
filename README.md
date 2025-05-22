Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML``   # Linguagem Snask  Snask é uma linguagem de script de tipagem dinâmica, projetada para simplicidade e facilidade de uso. Ela possui uma sintaxe direta para declaração de variáveis, controle de fluxo, definição de funções e operações básicas de I/O. Este documento detalha as construções da linguagem e fornece exemplos para cada uma.  ## Sumário  * [1. Primeiros Passos](#1-primeiros-passos)  * [2. Fundamentos da Linguagem](#2-fundamentos-da-linguagem)      * [2.1. Comentários](#21-comentários)      * [2.2. Tipos de Dados](#22-tipos-de-dados)  * [3. Variáveis e Constantes](#3-variáveis-e-constantes)      * [3.1. Declaração de Variável (`make`)](#31-declaração-de-variável-make)      * [3.2. Atribuição de Variável (`set`)](#32-atribuição-de-variável-set)      * [3.3. Excluindo Variáveis (`zap`)](#33-excluindo-variáveis-zap)      * [3.4. Declaração de Constante (`keep`)](#34-declaração-de-constante-keep)  * [4. Entrada e Saída](#4-entrada-e-saída)      * [4.1. Imprimindo Saída (`shoo`)](#41-imprimindo-saída-shoo)      * [4.2. Entrada do Usuário (`grab`, `grabnum`, `grabtxt`)](#42-entrada-do-usuário-grab-grabnum-grabtxt)  * [5. Funções](#5-funções)      * [5.1. Declaração de Função (`craft`)](#51-declaração-de-função-craft)      * [5.2. Chamada de Função](#52-chamada-de-função)      * [5.3. Retornando de Funções (`back`)](#53-retornando-de-funções-back)  * [6. Controle de Fluxo](#6-controle-de-fluxo)      * [6.1. Condicionais (`when`)](#61-condicionais-when)      * [6.2. Laços de Repetição (`spin`, `loopy`)](#62-laços-de-repetição-spin-loopy)      * [6.3. Controle de Laço (`breaky`, `skipit`)](#63-controle-de-laço-breaky-skipit)  * [7. Coleções](#7-coleções)      * [7.1. Listas (packs)](#71-listas-packs)          * [7.1.1. Declaração de Lista (`pack`)](#711-declaração-de-lista-pack)          * [7.1.2. Adicionando Elementos a uma Lista (`packadd`)](#712-adicionando-elementos-a-uma-lista-packadd)          * [7.1.3. Acessando Elementos da Lista](#713-acessando-elementos-da-lista)      * [7.2. Dicionários (boxes)](#72-dicionários-boxes)          * [7.2.1. Declaração de Dicionário (`box`)](#721-declaração-de-dicionário-box)          * [7.2.2. Adicionando/Atualizando Elementos do Dicionário (`boxput`)](#722-adicionandoatualizando-elementos-do-dicionário-boxput)          * [7.2.3. Acessando Elementos do Dicionário](#723-acessando-elementos-do-dicionário)  * [8. Operações de Tempo](#8-operações-de-tempo)      * [8.1. Espera (`snooze`)](#81-espera-snooze)  * [9. Conversão de Tipo (`convert`)](#9-conversão-de-tipo-convert)  * [10. Interações Externas](#10-interações-externas)      * [10.1. Usando Bibliotecas (`to use`)](#101-usando-bibliotecas-to-use)      * [10.2. Operações de Arquivo (`readfile`, `writefile`)](#102-operações-de-arquivo-readfile-writefile)      * [10.3. Requisições HTTP (`httpget`)](#103-requisições-http-httpget)      * [10.4. Análise de JSON (`jsonparse`)](#104-análise-de-json-jsonparse)  * [11. Funções Incorporadas e Expressões](#11-funções-incorporadas-e-expressões)      * [11.1. Operadores Aritméticos](#111-operadores-aritméticos)      * [11.2. Operadores de Comparação](#112-operadores-de-comparação)      * [11.3. Funções de String](#113-funções-de-string)      * [11.4. `lenof`](#114-lenof)      * [11.5. `typeis`](#115-typeis)  * [12. Detalhes do Intérprete](#12-detalhes-do-intérprete)  ---  ## 1. Primeiros Passos  Para executar o código Snask, você precisa do `SnaskInterpreter` e de um parser Lark configurado com a gramática Snask. O interpretador processa a Árvore de Sintaxe Abstrata (AST) gerada pelo Lark.  **Pré-requisitos:**  * Python 3.x  * Biblioteca `lark` (`pip install lark`)  * Biblioteca `requests` (`pip install requests`)  ## 2. Fundamentos da Linguagem  ### 2.1. Comentários  Comentários em Snask começam com `#` e continuam até o final da linha.  ```snask  # Este é um comentário de linha única  make myVar: int = 10; # Isso também funciona   ``

### 2.2. Tipos de Dados

Snask suporta os seguintes tipos de dados básicos:

*   int: Números inteiros.
    
*   str: Cadeias de caracteres.
    
*   float: Números de ponto flutuante.
    
*   bool: Valores booleanos (true ou false).
    
*   list: Coleções ordenadas de itens (packs).
    
*   dict: Pares chave-valor (boxes).
    
*   void: Representa a ausência de um valor, tipicamente para funções que não retornam nada.
    
*   any: Um tipo curinga que pode corresponder a qualquer outro tipo.
    
*   module: Usado para bibliotecas Python ou Snask importadas.
    

3\. Variáveis e Constantes
--------------------------

### 3.1. Declaração de Variável (make)

Declara e inicializa uma variável mutável com um tipo especificado.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make meuNumero: int = 123;  make meuTexto: str = "Olá Snask!";  make ehVerdadeiro: bool = true;   `

### 3.2. Atribuição de Variável (set)

Atribui um novo valor a uma variável já declarada.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make contador: int = 0;  set contador = 1;  shoo(contador); # Saída: 1   `

### 3.3. Excluindo Variáveis (zap)

Remove uma variável do ambiente atual.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make varTemporaria: str = "temporário";  shoo(varTemporaria); # Saída: temporário  zap varTemporaria;  # Tentar usar varTemporaria depois disso resultará em um erro   `

### 3.4. Declaração de Constante (keep)

Declara e inicializa uma variável constante. Seu valor não pode ser alterado após a declaração.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   keep PI: float = 3.14159;  # set PI = 3.0; # Isso causaria um TypeError   `

4\. Entrada e Saída
-------------------

### 4.1. Imprimindo Saída (shoo)

Imprime valores no console. Suporta múltiplos argumentos e formatação de string usando placeholders {}.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo("Olá, Mundo!"); # Saída: Olá, Mundo!  make nome: str = "Alice";  shoo("Meu nome é {}", nome); # Saída: Meu nome é Alice  shoo("Número um: {}, Número dois: {}", 1, 2); # Saída: Número um: 1, Número dois: 2   `

### 4.2. Entrada do Usuário (grab, grabnum, grabtxt)

Lê a entrada do usuário e a atribui a uma variável.

*   grab NAME : type: Lê a entrada e tenta convertê-la para o type especificado.
    
*   grabnum NAME : type: Especificamente para entrada numérica (int ou float).
    
*   grabtxt NAME : type: Especificamente para entrada de string.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   grab nomeUsuario: str; # Solicita entrada de string  shoo("Olá, {}", nomeUsuario);  grabnum idadeUsuario: int; # Solicita entrada de inteiro  shoo("Você tem {} anos.", idadeUsuario);  grabtxt cidade: str; # Solicita entrada de string  shoo("Você mora em {}", cidade);   `

5\. Funções
-----------

### 5.1. Declaração de Função (craft)

Define um bloco de código reutilizável. Funções podem receber parâmetros com tipos e devem especificar um tipo de retorno.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   craft somarNumeros(a: int, b: int) -> int:      make soma: int = a + b;      back soma;  done  craft saudar(nome: str) -> void:      shoo("Saudações, {}!", nome);  done   `

### 5.2. Chamada de Função

Executa uma função definida. Chamadas de função podem ser usadas como instruções ou dentro de expressões.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML``   make resultado: int = somarNumeros(5, 3);  shoo(resultado); # Saída: 8  # A gramática fornecida não mostra "call", mas o interpretador a implementa como `func_call_stmt`.  # Se "call" for um token explícito na sua gramática para chamadas de função como instrução:  # call saudar("Bob"); # Saída: Saudações, Bob!  # Caso contrário, apenas o nome da função seguido de parênteses é a chamada de função (expressão).  # Para usar como instrução sem retorno:  saudar("Bob"); # Saída: Saudações, Bob!   ``

### 5.3. Retornando de Funções (back)

Especifica o valor que uma função deve retornar. Funções declaradas com void retornam None.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   craft calcularArea(comprimento: float, largura: float) -> float:      back comprimento * largura;  done  make area: float = calcularArea(10.5, 5.0);  shoo("Área: {}", area); # Saída: Área: 52.5   `

6\. Controle de Fluxo
---------------------

### 6.1. Condicionais (when)

Executa um bloco de código se uma dada condição for verdadeira.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make temperatura: int = 25;  when temperatura over 20 {      shoo("Está um dia quente!");  }   `

### 6.2. Laços de Repetição (spin, loopy)

*   spin expr : stmt+: Um laço while que continua enquanto a expr (condição) for avaliada como verdadeira.
    
*   loopy : stmt+: Um laço infinito que continua indefinidamente até ser explicitamente interrompido.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   # laço spin (laço while)  make contagem: int = 0;  spin contagem undereq 5 :      shoo("Contagem: {}", contagem);      set contagem = contagem + 1;  done  # laço loopy (laço infinito)  make x: int = 0;  loopy :      shoo("Looping...");      set x = x + 1;      when x over 2 {          breaky; # Sai do laço loopy      }  done   `

### 6.3. Controle de Laço (breaky, skipit)

*   breaky: Termina imediatamente o laço mais interno.
    
*   skipit: Pula o restante da iteração atual do laço mais interno e prossegue para a próxima iteração.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   spin true:      make i: int = 0;      loopy :          shoo("Laço interno: {}", i);          set i = i + 1;          when i overeq 2 {              skipit; # Pula para a próxima iteração do laço 'loopy'          }          when i overeq 4 {              breaky; # Sai do laço 'loopy'          }      done      breaky; # Sai do laço 'spin' depois que o laço interno termina  done   `

7\. Coleções
------------

### 7.1. Listas (packs)

Coleções ordenadas e mutáveis de itens.

#### 7.1.1. Declaração de Lista (pack)

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   pack minhaLista: list = [1, 2, 3];  pack listaVazia: list = [];   `

#### 7.1.2. Adicionando Elementos a uma Lista (packadd)

Adiciona um elemento ao final de uma lista.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   pack minhaLista: list = [10];  packadd minhaLista, 20;  shoo(minhaLista); # Saída: [10, 20]   `

#### 7.1.3. Acessando Elementos da Lista

Elementos são acessados usando indexação baseada em zero (usando a sintaxe NOME\[expr\]).

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   pack meusNomes: list = ["Alice", "Bob", "Charlie"];  shoo(meusNomes[0]); # Saída: Alice  shoo(meusNomes[1]); # Saída: Bob   `

### 7.2. Dicionários (boxes)

Coleções não ordenadas e mutáveis de pares chave-valor. As chaves são tipicamente strings.

#### 7.2.1. Declaração de Dicionário (box)

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   box meuDicionario: dict = {"nome": "Snask", "versao": "1.0"};  box dicionarioVazio: dict = {};   `

#### 7.2.2. Adicionando/Atualizando Elementos do Dicionário (boxput)

Adiciona um novo par chave-valor ou atualiza uma chave existente.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   box infoUsuario: dict = {"id": 1};  boxput infoUsuario, "nome", "João Silva";  shoo(infoUsuario); # Saída: {"id": 1, "nome": "João Silva"}   `

#### 7.2.3. Acessando Elementos do Dicionário

Elementos são acessados usando suas chaves (usando a sintaxe NOME\[expr\]).

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   box configuracao: dict = {"tema": "escuro", "idioma": "pt"};  shoo(configuracao["tema"]); # Saída: escuro   `

8\. Operações de Tempo
----------------------

### 8.1. Espera (snooze)

Pausa a execução por uma duração especificada em segundos.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo("Esperando por 2 segundos...");  snooze 2; # Pausa por 2 segundos  shoo("Terminei de esperar.");   `

9\. Conversão de Tipo (convert)
-------------------------------

Converte o valor de uma variável para um tipo diferente, se possível.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make numStr: str = "123";  convert numStr to int;  shoo(numStr); # Saída: 123 (agora um inteiro)  make meuBool: bool = true;  convert meuBool to str;  shoo(meuBool); # Saída: "True" (agora uma string)   `

10\. Interações Externas
------------------------

### 10.1. Usando Bibliotecas (to use)

Importa funcionalidades externas. Pode importar módulos Python ou outros arquivos Snask.

*   Se libname for um nome de módulo Python válido, ele tenta importá-lo.
    
*   Caso contrário, ele procura por libname.snask em ./libs/ ou no diretório atual e executa seu código.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   to use "minha_lib_python"; # Tenta importar o módulo Python 'minha_lib_python'  to use "minha_lib_snask"; # Tenta carregar 'minha_lib_snask.snask'   `

### 10.2. Operações de Arquivo (readfile, writefile)

*   readfile FILEPATH\_EXPR to VAR\_NAME: Lê o conteúdo de um arquivo para uma variável de string.
    
*   writefile FILEPATH\_EXPR with CONTENT\_EXPR: Escreve um conteúdo de string em um arquivo especificado.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   # Escrever em um arquivo  writefile "saida.txt" with "Este é algum texto.";  # Ler de um arquivo  readfile "saida.txt" to conteudoArquivo;  shoo(conteudoArquivo); # Saída: Este é algum texto.   `

### 10.3. Requisições HTTP (httpget)

Realiza uma requisição GET para uma URL fornecida e retorna o corpo da resposta como uma string.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make url: str = "[https://www.example.com](https://www.example.com)";  make resposta: str = httpget(url);  shoo("Comprimento da Resposta HTTP: {}", lenof(resposta));   `

### 10.4. Análise de JSON (jsonparse)

Analisa uma string JSON em um dicionário ou lista Snask (dict/list Python).

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   make stringJson: str = "{\"nome\": \"João\", \"idade\": 30}";  make objetoJson: dict = jsonparse(stringJson);  shoo(objetoJson["nome"]); # Saída: João   `

11\. Funções Incorporadas e Expressões
--------------------------------------

Snask suporta operações aritméticas padrão, operadores de comparação e várias funções incorporadas para manipulação de strings e verificação de tipo.

### 11.1. Operadores Aritméticos

*   \+ (add): Adição, concatenação de strings, concatenação de listas.
    
*   \- (sub): Subtração.
    
*   \* (mul): Multiplicação, repetição de string/lista.
    
*   / (div): Divisão (retorna float).
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo(10 + 5);      # Saída: 15  shoo("Olá" + "Mundo"); # Saída: OláMundo  shoo([1,2] + [3,4]); # Saída: [1, 2, 3, 4]  shoo(10 - 5);      # Saída: 5  shoo(10 * 5);      # Saída: 50  shoo("abc" * 3);  # Saída: abcabcabc  shoo(10 / 3);      # Saída: 3.3333333333333335   `

### 11.2. Operadores de Comparação

*   is (==): Igual a.
    
*   aint (!=): Diferente de.
    
*   over (>): Maior que.
    
*   under (<): Menor que.
    
*   overeq (>=): Maior ou igual a.
    
*   undereq (<=): Menor ou igual a.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo(5 is 5);      # Saída: True  shoo(5 aint 10);    # Saída: True  shoo(10 over 5);    # Saída: True  shoo(5 under 10);    # Saída: True  shoo(10 overeq 10); # Saída: True  shoo(5 undereq 5); # Saída: True   `

### 11.3. Funções de String

*   toupper(expr): Converte uma string para maiúsculas.
    
*   tolower(expr): Converte uma string para minúsculas.
    
*   startswith(expr, prefix\_expr): Verifica se uma string começa com um dado prefixo.
    
*   endswith(expr, suffix\_expr): Verifica se uma string termina com um dado sufixo.
    

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo(toupper("olá")); # Saída: OLÁ  shoo(tolower("MUNDO")); # Saída: mundo  shoo(startswith("maçã", "ma")); # Saída: True  shoo(endswith("banana", "ana")); # Saída: True   `

### 11.4. lenof

Retorna o comprimento de uma string, lista ou dicionário.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo(lenof("Snask")); # Saída: 5  shoo(lenof([1, 2, 3])); # Saída: 3  shoo(lenof({"a": 1, "b": 2})); # Saída: 2   `

### 11.5. typeis

Retorna o tipo Snask (como uma string) de um dado valor.

Snippet de código

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   shoo(typeis(123)); # Saída: int  shoo(typeis("olá")); # Saída: str  shoo(typeis(true)); # Saída: bool  shoo(typeis([1,2])); # Saída: list   `

12\. Detalhes do Intérprete
---------------------------

A classe SnaskInterpreter estende o Transformer do Lark e é responsável por avaliar a AST gerada pela gramática Snask.

*   **\_\_init\_\_(self, parser=None)**: Inicializa o ambiente do interpretador, armazenamento de funções e flags de controle.
    
    *   self.env: Um dicionário que armazena variáveis e suas propriedades (tipo, valor, status de constante).
        
    *   self.functions: Um dicionário que armazena funções declaradas (parâmetros, tipo de retorno, nó AST do corpo).
        
    *   self.returning: Uma flag para gerenciar o 'return' de função e 'breaky' de laço.
        
    *   self.return\_value: Armazena o valor retornado por uma função.
        
    *   self.\_is\_break\_signal, self.\_is\_skip\_signal: Flags internas para breaky e skipit respectivamente.
        
*   **\_resolve(self, val)**: Resolve recursivamente um nó AST ou token em seu valor Python correspondente. Ele lida com literais, busca de variáveis e avaliação de expressões.
    
*   **\_execute(self, stmt\_node)**: Executa um único nó de instrução, despachando para o método transformador apropriado com base no atributo data do nó.
    
*   **\_execute\_tree(self, tree)**: Itera e executa todas as instruções dentro de uma dada tree AST.
    
*   **\_check\_type(self, value, expected\_str\_type)**: Função auxiliar interna para validar se um value Python corresponde a um expected\_str\_type (ex: "int", "str", "list").
    
*   **\_execute\_function\_body(self, func\_name, func\_def, resolved\_args)**: Gerencia a execução do corpo de uma função, incluindo a configuração de seu escopo local para parâmetros, a execução de instruções e o tratamento de retornos. Ele cria uma cópia do ambiente para variáveis e parâmetros locais.

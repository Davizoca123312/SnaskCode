# Documentação da Linguagem Snask

Snask é uma linguagem de programação **simples e expressiva**, projetada para **clareza e facilidade de uso**. Este documento descreve sua sintaxe, recursos e fornece exemplos para cada tipo de declaração e expressão.

## Sumário

1. Visão Geral da Linguagem
2. Tipos de Dados
3. Variáveis e Constantes
   * Declaração de Variável (**make**)
   * Atribuição de Variável (**set**)
   * Exclusão de Variável (**zap**)
   * Declaração de Constante (**keep**)
4. Entrada e Saída
   * Impressão de Saída (**shoo**)
   * Entrada Geral (**grab**)
   * Entrada Numérica (**grabnum**)
   * Entrada de Texto (**grabtxt**)
5. Controle de Fluxo
   * Declarações Condicionais (**when**)
   * Loop Condicional (**spin**)
   * Loop Infinito (**loopy**)
   * Quebrar Loop (**breaky**)
   * Pular Iteração (**skipit**)
6. Funções
   * Declaração de Função (**craft**)
   * Chamada de Função
   * Retorno de Valor (**back**)
7. Coleções
   * Listas (Packs)
     * Declaração de Lista (**pack**)
     * Adicionar Elementos (**packadd**)
     * Acessar Elementos (Acesso por Índice)
   * Dicionários (Boxes)
     * Declaração de Dicionário (**box**)
     * Adicionar/Atualizar Elementos (**boxput**)
     * Acessar Elementos (Acesso por Chave)
8. Operações de Tempo
   * Pausar Execução (**snooze**)
9. Conversão de Tipo
   * Converter Tipo de Variável (**convert**)
10. Operações de Arquivo
  * Ler Arquivo (**readfile**)
  * Escrever Arquivo (**writefile**)
11. Importação de Módulos
  * Usar Bibliotecas (**to use**)
12. Expressões e Operadores
  * Operadores Aritméticos
  * Operadores de Comparação
  * Funções de String Embutidas
  * Outras Funções Embutidas
  * Operações HTTP

---

## 1\. Visão Geral da Linguagem

Snask é uma linguagem **dinamicamente tipada** com uma sintaxe clara para construções de programação comuns. Ela suporta variáveis, constantes, I/O básico, controle de fluxo, funções, listas (**packs**), dicionários (**boxes**), operações de arquivo e importação de bibliotecas externas.

---

## 2\. Tipos de Dados

Snask suporta os seguintes tipos de dados fundamentais:

* **int**: Inteiros (ex: 10, -5)
* **str**: Strings (ex: "olá", "Snask é legal")
* **float**: Números de ponto flutuante (ex: 3.14, 0.5)
* **bool**: Valores booleanos (**true**, **false**)
* **list**: Coleções ordenadas de itens (ex: `[1, 2, 3]`)
* **dict**: Coleções não ordenadas de pares chave-valor (ex: `{"nome": "Alice", "idade": 30}`)
* **void**: Representa a ausência de um valor (similar a `None` em Python). Usado para funções que não retornam nada.
* **any**: Um tipo curinga que pode conter qualquer valor.
* **module**: Representa uma biblioteca externa importada.

---

## 3\. Variáveis e Constantes

### Declaração de Variável (**make**)

Declara uma nova variável com um tipo especificado e um valor inicial.

**Sintaxe**: `make <nome_variavel>: <tipo> = <valor_inicial>`

**Exemplo**:
<response-element><code-block>```
make idade: int = 25
make saudacao: str = "Olá, Snask!"
make esta_ativo: bool = true
```</code-block></response-element>
### Atribuição de Variável (**set**)

Atribui um novo valor a uma variável já declarada.

**Sintaxe**: `set <nome_variavel> = <novo_valor>`

**Exemplo**:
<response-element><code-block>```
make contador: int = 0
set contador = contador + 1 # contador agora é 1
set saudacao = "Bem-vindo!"
```</code-block></response-element>
### Exclusão de Variável (**zap**)

Remove uma variável do escopo atual.

**Sintaxe**: `zap <nome_variavel>`

**Exemplo**:
<response-element><code-block>```
make dados_temp: str = "temporário"
shoo(dados_temp) # Imprime "temporário"
zap dados_temp
# shoo(dados_temp) # Isso causaria um erro, pois dados_temp não existe mais
```</code-block></response-element>
### Declaração de Constante (**keep**)

Declara uma constante, similar a uma variável, mas seu valor não pode ser alterado após a inicialização.

**Sintaxe**: `keep <nome_constante>: <tipo> = <valor_inicial>`

**Exemplo**:
<response-element><code-block>```
keep PI: float = 3.14159
# set PI = 3.0 # Isso causaria um TypeError
```</code-block></response-element>
---

## 4\. Entrada e Saída

### Impressão de Saída (**shoo**)

Imprime o valor de uma expressão no console. Suporta formatação básica de string usando placeholders `{}`.

**Sintaxe**: `shoo(<expressao>) [.cdr {<arg1>, <arg2>, ...}]`

**Exemplo**:
<response-element><code-block>```
shoo("Olá, mundo!")
make nome: str = "Snask"
make versao: int = 1
shoo("Bem-vindo, {}! Versão {}.", .cdr {nome, versao})
```</code-block></response-element>
### Entrada Geral (**grab**)

Solicita uma entrada do usuário e a armazena em uma variável de um tipo especificado. O interpretador tenta converter a entrada para o tipo de destino.

**Sintaxe**: `grab <nome_variavel>: <tipo>`

**Exemplo**:
<response-element><code-block>```
grab idade_usuario: int
shoo("Você digitou a idade: {}", .cdr {idade_usuario})
```</code-block></response-element>
### Entrada Numérica (**grabnum**)

Especificamente solicita uma entrada numérica (inteiro).

**Sintaxe**: `grabnum <nome_variavel>: <tipo_numerico>`

**Exemplo**:
<response-element><code-block>```
grabnum quantidade: int
shoo("Quantidade: {}", .cdr {quantidade})
```</code-block></response-element>
### Entrada de Texto (**grabtxt**)

Especificamente solicita uma entrada de texto (string).

**Sintaxe**: `grabtxt <nome_variavel>: <tipo_texto>`

**Exemplo**:
<response-element><code-block>```
grabtxt nome_usuario: str
shoo("Olá, {}", .cdr {nome_usuario})
```</code-block></response-element>
---

## 5\. Controle de Fluxo

### Declarações Condicionais (**when**)

Executa um bloco de código se uma dada condição for verdadeira.

**Sintaxe**: `when <condição> { <bloco_de_codigo> }`

**Exemplo**:
<response-element><code-block>```
make pontuacao: int = 95
when pontuacao over 90 {
    shoo("Pontuação excelente!")
}
when pontuacao undereq 70 {
    shoo("Precisa melhorar.")
}
```</code-block></response-element>
### Loop Condicional (**spin**)

Repete um bloco de código enquanto uma condição especificada permanecer verdadeira.

**Sintaxe**: `spin <condição> : <bloco_de_codigo>`

**Exemplo**:
<response-element><code-block>```
make contador: int = 0
spin contador under 5 :
    shoo("Contador é: {}", .cdr {contador})
    set contador = contador + 1
```</code-block></response-element>
### Loop Infinito (**loopy**)

Executa um bloco de código repetidamente sem uma condição específica. Este loop deve ser encerrado usando **breaky**.

**Sintaxe**: `loopy : <bloco_de_codigo>`

**Exemplo**:
<response-element><code-block>```
loopy :
    shoo("Isso será impresso para sempre, a menos que seja parado.")
    make continuar_loop: bool = true
    grabtxt valor_entrada: str
    when valor_entrada is "parar" {
        breaky
    }
```</code-block></response-element>
### Quebrar Loop (**breaky**)

Sai do loop **spin** ou **loopy** mais interno.

**Sintaxe**: `breaky`

**Exemplo**:
<response-element><code-block>```
loopy :
    shoo("Digite 'sair' para parar:")
    grabtxt comando: str
    when comando is "sair" {
        breaky
    }
```</code-block></response-element>
### Pular Iteração (**skipit**)

Pula o restante da iteração atual do loop mais interno e prossegue para a próxima iteração.

**Sintaxe**: `skipit`

**Exemplo**:
<response-element><code-block>```
make i: int = 0
spin i under 5 :
    set i = i + 1
    when i is 3 {
        shoo("Pulando o 3...")
        skipit
    }
    shoo("Valor atual: {}", .cdr {i})
```</code-block></response-element>
---

## 6\. Funções

### Declaração de Função (**craft**)

Define um bloco de código reutilizável. As funções podem receber parâmetros e retornar um valor.

**Sintaxe**: `craft <nome_funcao>(<param1>: <tipo1>, <param2>: <tipo2>, ...) -> <tipo_retorno> : <bloco_de_codigo> done`

**Exemplo**:
<response-element><code-block>```
craft somar_numeros(a: int, b: int) -> int :
    make soma: int = a + b
    back soma
done

craft saudar(nome: str) -> void :
    shoo("Olá, {}!", .cdr {nome})
done
```</code-block></response-element>
### Chamada de Função

Executa uma função definida.

**Sintaxe**: `<nome_funcao>(<arg1>, <arg2>, ...)`

**Exemplo**:
<response-element><code-block>```
make resultado: int = somar_numeros(10, 20)
shoo("Soma: {}", .cdr {resultado}) # Imprime "Soma: 30"
saudar("Mundo") # Imprime "Olá, Mundo!"
```</code-block></response-element>
### Retorno de Valor (**back**)

Especifica o valor que uma função irá retornar.

**Sintaxe**: `back <valor>`

**Exemplo**:
<response-element><code-block>```
craft multiplicar(x: int, y: int) -> int :
    back x * y
done
make produto: int = multiplicar(5, 6)
shoo("Produto: {}", .cdr {produto}) # Imprime "Produto: 30"
```</code-block></response-element>
---

## 7\. Coleções

### Listas (Packs)

Coleções ordenadas e mutáveis de itens.

#### Declaração de Lista (**pack**)

Cria uma nova lista, opcionalmente inicializada com elementos.

**Sintaxe**: `pack <nome_lista>: list = [<elem1>, <elem2>, ...]`

**Exemplo**:
<response-element><code-block>```
pack meus_numeros: list = [1, 2, 3]
pack lista_vazia: list = []
```</code-block></response-element>
#### Adicionar Elementos (**packadd**)

Adiciona um elemento ao final de uma lista.

**Sintaxe**: `packadd <nome_lista> <elemento>`

**Exemplo**:
<response-element><code-block>```
pack minha_lista: list = ["maçã", "banana"]
packadd minha_lista "cereja"
shoo(minha_lista) # Imprime ["maçã", "banana", "cereja"]
```</code-block></response-element>
#### Acessar Elementos (Acesso por Índice)

Recupera um elemento de uma lista usando seu índice baseado em zero. Também usado para acessar valores em dicionários.

**Sintaxe**: `<colecao>[<indice_ou_chave>]`

**Exemplo**:
<response-element><code-block>```
pack frutas: list = ["maçã", "banana", "laranja"]
shoo(frutas[0]) # Imprime "maçã"
shoo(frutas[lenof(frutas) - 1]) # Imprime "laranja"
```</code-block></response-element>
### Dicionários (Boxes)

Coleções não ordenadas e mutáveis de pares chave-valor. As chaves são tipicamente strings.

#### Declaração de Dicionário (**box**)

Cria um novo dicionário, opcionalmente inicializado com pares chave-valor.

**Sintaxe**: `box <nome_dicionario>: dict = {<chave1>: <valor1>, <chave2>: <valor2>, ...}`

**Exemplo**:
<response-element><code-block>```
box perfil_usuario: dict = {"nome": "Alice", "idade": 30}
box caixa_vazia: dict = {}
```</code-block></response-element>
#### Adicionar/Atualizar Elementos (**boxput**)

Adiciona um novo par chave-valor a um dicionário ou atualiza o valor para uma chave existente.

**Sintaxe**: `boxput <nome_dicionario> <chave> <valor>`

**Exemplo**:
<response-element><code-block>```
box configuracoes: dict = {"tema": "escuro"}
boxput configuracoes "tamanho_fonte" 14
boxput configuracoes "tema" "claro" # Atualiza o tema
shoo(configuracoes) # Imprime {"tema": "claro", "tamanho_fonte": 14}
```</code-block></response-element>
#### Acessar Elementos (Acesso por Chave)

Recupera um valor de um dicionário usando sua chave.

**Sintaxe**: `<colecao>[<indice_ou_chave>]`

**Exemplo**:
<response-element><code-block>```
box estudante: dict = {"id": 101, "nota": "A"}
shoo(estudante["nota"]) # Imprime "A"
```</code-block></response-element>
---

## 8\. Operações de Tempo

### Pausar Execução (**snooze**)

Pausa a execução do programa por um número especificado de segundos.

**Sintaxe**: `snooze <segundos>`

**Exemplo**:
<response-element><code-block>```
shoo("Esperando por 2 segundos...")
snooze 2
shoo("Terminei de esperar.")
```</code-block></response-element>
---

## 9\. Conversão de Tipo

### Converter Tipo de Variável (**convert**)

Tenta converter o valor de uma variável para um tipo especificado.

**Sintaxe**: `convert <variavel> to <novo_tipo>`

**Exemplo**:
<response-element><code-block>```
make num_str: str = "123"
shoo(typeis(num_str)) # Imprime "str"
convert num_str to int
shoo(typeis(num_str)) # Imprime "int"
shoo(num_str + 1) # Imprime 124 (agora realiza adição de inteiros)

make valor_bool: bool = true
shoo(typeis(valor_bool)) # Imprime "bool"
convert valor_bool to str
shoo(typeis(valor_bool)) # Imprime "str"
shoo(valor_bool) # Imprime "True"
```</code-block></response-element>
---

## 10\. Operações de Arquivo

### Ler Arquivo (**readfile**)

Lê todo o conteúdo de um arquivo especificado e o armazena como uma string em uma variável.

**Sintaxe**: `readfile "<caminho_arquivo>" to <variavel_destino>`

**Exemplo**:
<response-element><code-block>```
# Assumindo que um arquivo chamado "meus_dados.txt" existe com o conteúdo "Olá Arquivo!"
make conteudo_arquivo: str = ""
readfile "meus_dados.txt" to conteudo_arquivo
shoo(conteudo_arquivo) # Imprime "Olá Arquivo!"
```</code-block></response-element>
### Escrever Arquivo (**writefile**)

Escreve o conteúdo de uma expressão em um arquivo especificado. Se o arquivo não existir, ele será criado. Se existir, seu conteúdo será sobrescrito.

**Sintaxe**: `writefile "<caminho_arquivo>" with <expressao>`

**Exemplo**:
<response-element><code-block>```
writefile "saida.txt" with "Este é um texto escrito do Snask."
shoo("Conteúdo escrito em saida.txt")
```</code-block></response-element>
---

## 11\. Importação de Módulos

### Usar Bibliotecas (**to use**)

Importa módulos externos, que podem ser módulos Python ou outros arquivos Snask (`.snask`).

**Sintaxe**: `to use "<nome_modulo_ou_caminho_arquivo>"`

**Exemplo**:
<response-element><code-block>```
# Para usar um módulo Python (ex: 'math')
to use "math"
# Você pode então acessar funções/variáveis do módulo 'math' se o interpretador as expuser.
# (Nota: A implementação atual do interpretador pode não expor diretamente o conteúdo do módulo como variáveis Snask.)

# Para usar outro arquivo Snask (ex: 'minhas_utilidades.snask' em uma pasta 'libs' ou no diretório atual)
# libs/minhas_utilidades.snask:
#    craft dizer_oi() -> void :
#        shoo("Oi das minhas_utilidades!")
#    done
to use "minhas_utilidades"
dizer_oi() # Chama a função do arquivo Snask importado
```</code-block></response-element>
---

## 12\. Expressões e Operadores

Expressões avaliam para um valor e podem ser usadas em várias declarações (ex: atribuições de variáveis, declarações de impressão, condições).

### Operadores Aritméticos

<response-element><table-block>|||||
|:---|:---|:---|:---|
|Operador|Descrição|Exemplo|Resultado|
|**+**|Adição|`10 + 5`|`15`|
|**+**|Concatenação|`"Olá" + "Mundo"`|`"OláMundo"`|
|**\-**|Subtração|`10 - 5`|`5`|
|**\***|Multiplicação|`10 * 5`|`50`|
|**\***|Repetição de String/Lista|`"abc" * 3`|`"abcabcabc"`|
|**/**|Divisão|`10 / 2`|`5.0`|

<button>Exportar para as Planilhas</button></table-block></response-element>

### Operadores de Comparação

<response-element><table-block>|||||
|:---|:---|:---|:---|
|Operador|Descrição|Exemplo|Resultado|
|**is**|Igual a|`10 is 10`|`true`|
|**aint**|Diferente de|`10 aint 5`|`true`|
|**over**|Maior que|`10 over 5`|`true`|
|**under**|Menor que|`10 under 5`|`false`|
|**overeq**|Maior ou igual a|`10 overeq 10`|`true`|
|**undereq**|Menor ou igual a|`10 undereq 5`|`false`|
|**\==**|Igualdade Direta (mesmo que **is**)|`10 == 10`|`true`|

<button>Exportar para as Planilhas</button></table-block></response-element>

### Funções de String Embutidas

Estas funções operam em expressões de string.

* **lenof**(`<string_ou_colecao>`): Retorna o comprimento de uma string (ou lista/dicionário). **Exemplo**: `shoo(lenof("Snask"))` # Imprime `5`
* **toupper**(`<string>`): Converte uma string para maiúsculas. **Exemplo**: `shoo(toupper("olá"))` # Imprime `"OLÁ"`
* **tolower**(`<string>`): Converte uma string para minúsculas. **Exemplo**: `shoo(tolower("MUNDO"))` # Imprime `"mundo"`
* **startswith**(`<string_principal>`, `<prefixo>`): Verifica se uma string começa com um dado prefixo. **Exemplo**: `shoo(startswith("maçã", "ma"))` # Imprime `true`
* **endswith**(`<string_principal>`, `<sufixo>`): Verifica se uma string termina com um dado sufixo. **Exemplo**: `shoo(endswith("banana", "ana"))` # Imprime `true`

### Outras Funções Embutidas

* **typeis**(`<expressao>`): Retorna o nome do tipo Snask do valor da expressão. **Exemplo**: `shoo(typeis(123))` # Imprime `"int"`**Exemplo**: `shoo(typeis("olá"))` # Imprime `"str"`

### Operações HTTP

* <response-element><code-block>```
  make url_api: str = "https://jsonplaceholder.typicode.com/todos/1"
  make texto_resposta: str = httpget(url_api)
  shoo(texto_resposta) # Imprime a resposta JSON da API
```</code-block></response-element>

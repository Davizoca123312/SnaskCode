Documentação da Linguagem Snask
Snask é uma linguagem de programação simples e expressiva, projetada para clareza e facilidade de uso. Este documento descreve sua sintaxe, recursos e fornece exemplos para cada tipo de declaração e expressão.

Sumário
Visão Geral da Linguagem

Tipos de Dados

Variáveis e Constantes

Declaração de Variável (make)

Atribuição de Variável (set)

Exclusão de Variável (zap)

Declaração de Constante (keep)

Entrada e Saída

Impressão de Saída (shoo)

Entrada Geral (grab)

Entrada Numérica (grabnum)

Entrada de Texto (grabtxt)

Controle de Fluxo

Declarações Condicionais (when)

Loop Condicional (spin)

Loop Infinito (loopy)

Quebrar Loop (breaky)

Pular Iteração (skipit)

Funções

Declaração de Função (craft)

Chamada de Função

Retorno de Valor (back)

Coleções

Listas (Packs)

Declaração de Lista (pack)

Adicionar Elementos (packadd)

Acessar Elementos (Acesso por Índice)

Dicionários (Boxes)

Declaração de Dicionário (box)

Adicionar/Atualizar Elementos (boxput)

Acessar Elementos (Acesso por Chave)

Operações de Tempo

Pausar Execução (snooze)

Conversão de Tipo

Converter Tipo de Variável (convert)

Operações de Arquivo

Ler Arquivo (readfile)

Escrever Arquivo (writefile)

Importação de Módulos

Usar Bibliotecas (to use)

Expressões e Operadores

Operadores Aritméticos

Operadores de Comparação

Funções de String Embutidas

Outras Funções Embutidas

Operações HTTP

1. Visão Geral da Linguagem
Snask é uma linguagem dinamicamente tipada com uma sintaxe clara para construções de programação comuns. Ela suporta variáveis, constantes, I/O básico, controle de fluxo, funções, listas (packs), dicionários (boxes), operações de arquivo e importação de bibliotecas externas.

2. Tipos de Dados
Snask suporta os seguintes tipos de dados fundamentais:

int: Inteiros (ex: 10, -5)

str: Strings (ex: "olá", "Snask é legal")

float: Números de ponto flutuante (ex: 3.14, 0.5)

bool: Valores booleanos (true, false)

list: Coleções ordenadas de itens (ex: [1, 2, 3])

dict: Coleções não ordenadas de pares chave-valor (ex: {"nome": "Alice", "idade": 30})

void: Representa a ausência de um valor (similar a None em Python). Usado para funções que não retornam nada.

any: Um tipo curinga que pode conter qualquer valor.

module: Representa uma biblioteca externa importada.

3. Variáveis e Constantes
Declaração de Variável (make)
Declara uma nova variável com um tipo especificado e um valor inicial.

Sintaxe: make <nome>: <tipo> = <expressão>

Exemplo:

make idade: int = 25;
make saudacao: str = "Olá, Snask!";
make esta_ativo: bool = true;

Atribuição de Variável (set)
Atribui um novo valor a uma variável já declarada.

Sintaxe: set <nome> = <expressão>

Exemplo:

make contador: int = 0;
set contador = contador + 1; # contador agora é 1
set saudacao = "Bem-vindo!";

Exclusão de Variável (zap)
Remove uma variável do escopo atual.

Sintaxe: zap <nome>

Exemplo:

make dados_temp: str = "temporário";
shoo(dados_temp); # Imprime "temporário"
zap dados_temp;
# shoo(dados_temp); # Isso causaria um erro, pois dados_temp não existe mais

Declaração de Constante (keep)
Declara uma constante, similar a uma variável, mas seu valor não pode ser alterado após a inicialização.

Sintaxe: keep <nome>: <tipo> = <expressão>

Exemplo:

keep PI: float = 3.14159;
# set PI = 3.0; # Isso causaria um TypeError

4. Entrada e Saída
Impressão de Saída (shoo)
Imprime o valor de uma expressão no console. Suporta formatação básica de string usando placeholders {}.

Sintaxe: shoo(<expressão>) [.cdr {<expressão>, <expressão>, ...}]

Exemplo:

shoo("Olá, mundo!");
make nome: str = "Snask";
make versao: int = 1;
shoo("Bem-vindo, {}! Versão {}.", .cdr {nome, versao});

Entrada Geral (grab)
Solicita uma entrada do usuário e a armazena em uma variável de um tipo especificado. O interpretador tenta converter a entrada para o tipo de destino.

Sintaxe: grab <nome>: <tipo>

Exemplo:

grab idade_usuario: int;
shoo("Você digitou a idade: {}", .cdr {idade_usuario});

Entrada Numérica (grabnum)
Especificamente solicita uma entrada numérica (inteiro).

Sintaxe: grabnum <nome>: <tipo>

Exemplo:

grabnum quantidade: int;
shoo("Quantidade: {}", .cdr {quantidade});

Entrada de Texto (grabtxt)
Especificamente solicita uma entrada de texto (string).

Sintaxe: grabtxt <nome>: <tipo>

Exemplo:

grabtxt nome_usuario: str;
shoo("Olá, {}", .cdr {nome_usuario});

5. Controle de Fluxo
Declarações Condicionais (when)
Executa um bloco de código se uma dada condição for verdadeira.

Sintaxe: when <expressão> { <declarações> }

Exemplo:

make pontuacao: int = 95;
when pontuacao over 90 {
    shoo("Pontuação excelente!");
}
when pontuacao undereq 70 {
    shoo("Precisa melhorar.");
}

Loop Condicional (spin)
Repete um bloco de código enquanto uma condição especificada permanecer verdadeira.

Sintaxe: spin <expressão> : <declarações>

Exemplo:

make contador: int = 0;
spin contador under 5 :
    shoo("Contador é: {}", .cdr {contador});
    set contador = contador + 1;

Loop Infinito (loopy)
Executa um bloco de código repetidamente sem uma condição específica. Este loop deve ser encerrado usando breaky.

Sintaxe: loopy : <declarações>

Exemplo:

loopy :
    shoo("Isso será impresso para sempre, a menos que seja parado.");
    make continuar_loop: bool = true;
    grabtxt valor_entrada: str;
    when valor_entrada is "parar" {
        breaky;
    }

Quebrar Loop (breaky)
Sai do loop spin ou loopy mais interno.

Sintaxe: breaky

Exemplo:

loopy :
    shoo("Digite 'sair' para parar:");
    grabtxt comando: str;
    when comando is "sair" {
        breaky;
    }

Pular Iteração (skipit)
Pula o restante da iteração atual do loop mais interno e prossegue para a próxima iteração.

Sintaxe: skipit

Exemplo:

make i: int = 0;
spin i under 5 :
    set i = i + 1;
    when i is 3 {
        shoo("Pulando o 3...");
        skipit;
    }
    shoo("Valor atual: {}", .cdr {i});

6. Funções
Declaração de Função (craft)
Define um bloco de código reutilizável. As funções podem receber parâmetros e retornar um valor.

Sintaxe: craft <nome>([<nome_param>: <tipo_param>, ...]) -> <tipo_retorno> : <declarações> done

Exemplo:

craft somar_numeros(a: int, b: int) -> int :
    make soma: int = a + b;
    back soma;
done

craft saudar(nome: str) -> void :
    shoo("Olá, {}!", .cdr {nome});
done

Chamada de Função
Executa uma função definida.

Sintaxe: <nome>([<expressão_arg>, ...])

Exemplo:

make resultado: int = somar_numeros(10, 20);
shoo("Soma: {}", .cdr {resultado}); # Imprime "Soma: 30"

saudar("Mundo"); # Imprime "Olá, Mundo!"

Retorno de Valor (back)
Especifica o valor que uma função irá retornar.

Sintaxe: back <expressão>

Exemplo:

craft multiplicar(x: int, y: int) -> int :
    back x * y;
done

make produto: int = multiplicar(5, 6);
shoo("Produto: {}", .cdr {produto}); # Imprime "Produto: 30"

7. Coleções
Listas (Packs)
Coleções ordenadas e mutáveis de itens.

Declaração de Lista (pack)
Cria uma nova lista, opcionalmente inicializada com elementos.

Sintaxe: pack <nome>: list = [<expressão>, <expressão>, ...]

Exemplo:

pack meus_numeros: list = [1, 2, 3];
pack lista_vazia: list = [];

Adicionar Elementos (packadd)
Adiciona um elemento ao final de uma lista.

Sintaxe: packadd <nome_lista> <expressão>

Exemplo:

pack minha_lista: list = ["maçã", "banana"];
packadd minha_lista "cereja";
shoo(minha_lista); # Imprime ["maçã", "banana", "cereja"]

Acessar Elementos (Acesso por Índice)
Recupera um elemento de uma lista usando seu índice baseado em zero. Também usado para acessar valores em dicionários.

Sintaxe: <nome_colecao>[<expressão_indice>]

Exemplo:

pack frutas: list = ["maçã", "banana", "laranja"];
shoo(frutas[0]); # Imprime "maçã"
shoo(frutas[lenof(frutas) - 1]); # Imprime "laranja"

Dicionários (Boxes)
Coleções não ordenadas e mutáveis de pares chave-valor. As chaves são tipicamente strings.

Declaração de Dicionário (box)
Cria um novo dicionário, opcionalmente inicializado com pares chave-valor.

Sintaxe: box <nome>: dict = {<nome_chave>: <expressão>, ...}

Exemplo:

box perfil_usuario: dict = {"nome": "Alice", "idade": 30};
box caixa_vazia: dict = {};

Adicionar/Atualizar Elementos (boxput)
Adiciona um novo par chave-valor a um dicionário ou atualiza o valor para uma chave existente.

Sintaxe: boxput <nome_dicionario> <expressão_chave> <expressão_valor>

Exemplo:

box configuracoes: dict = {"tema": "escuro"};
boxput configuracoes "tamanho_fonte" 14;
boxput configuracoes "tema" "claro"; # Atualiza o tema
shoo(configuracoes); # Imprime {"tema": "claro", "tamanho_fonte": 14}

Acessar Elementos (Acesso por Chave)
Recupera um valor de um dicionário usando sua chave.

Sintaxe: <nome_colecao>[<expressão_chave>]

Exemplo:

box estudante: dict = {"id": 101, "nota": "A"};
shoo(estudante["nota"]); # Imprime "A"

8. Operações de Tempo
Pausar Execução (snooze)
Pausa a execução do programa por um número especificado de segundos.

Sintaxe: snooze <expressão_duracao>

Exemplo:

shoo("Esperando por 2 segundos...");
snooze 2;
shoo("Terminei de esperar.");

9. Conversão de Tipo
Converter Tipo de Variável (convert)
Tenta converter o valor de uma variável para um tipo especificado.

Sintaxe: convert <nome_variavel> to <tipo>

Exemplo:

make num_str: str = "123";
shoo(typeis(num_str)); # Imprime "str"
convert num_str to int;
shoo(typeis(num_str)); # Imprime "int"
shoo(num_str + 1); # Imprime 124 (agora realiza adição de inteiros)

make valor_bool: bool = true;
shoo(typeis(valor_bool)); # Imprime "bool"
convert valor_bool to str;
shoo(typeis(valor_bool)); # Imprime "str"
shoo(valor_bool); # Imprime "True"

10. Operações de Arquivo
Ler Arquivo (readfile)
Lê todo o conteúdo de um arquivo especificado e o armazena como uma string em uma variável.

Sintaxe: readfile <expressão_caminho_arquivo> to <nome_variavel>

Exemplo:

# Assumindo que um arquivo chamado "meus_dados.txt" existe com o conteúdo "Olá Arquivo!"
make conteudo_arquivo: str = "";
readfile "meus_dados.txt" to conteudo_arquivo;
shoo(conteudo_arquivo); # Imprime "Olá Arquivo!"

Escrever Arquivo (writefile)
Escreve o conteúdo de uma expressão em um arquivo especificado. Se o arquivo não existir, ele será criado. Se existir, seu conteúdo será sobrescrito.

Sintaxe: writefile <expressão_caminho_arquivo> with <expressão_conteudo>

Exemplo:

writefile "saida.txt" with "Este é um texto escrito do Snask.";
shoo("Conteúdo escrito em saida.txt");

11. Importação de Módulos
Usar Bibliotecas (to use)
Importa módulos externos, que podem ser módulos Python ou outros arquivos Snask (.snask).

Sintaxe: to use <expressão_nome_biblioteca>

Exemplo:

# Para usar um módulo Python (ex: 'math')
to use "math";
# Você pode então acessar funções/variáveis do módulo 'math' se o interpretador as expuser.
# (Nota: A implementação atual do interpretador pode não expor diretamente o conteúdo do módulo como variáveis Snask.)

# Para usar outro arquivo Snask (ex: 'minhas_utilidades.snask' em uma pasta 'libs' ou no diretório atual)
# libs/minhas_utilidades.snask:
#   craft dizer_oi() -> void :
#       shoo("Oi das minhas_utilidades!");
#   done
to use "minhas_utilidades";
dizer_oi(); # Chama a função do arquivo Snask importado

12. Expressões e Operadores
Expressões avaliam para um valor e podem ser usadas em várias declarações (ex: atribuições de variáveis, declarações de impressão, condições).

Operadores Aritméticos
Operador

Descrição

Exemplo

Resultado

+

Adição

10 + 5

15

+

Concatenação

"Olá" + "Mundo"

"OláMundo"

-

Subtração

10 - 5

5

*

Multiplicação

10 * 5

50

*

Repetição de String/Lista

"abc" * 3

"abcabcabc"

/

Divisão

10 / 2

5.0

Operadores de Comparação
Operador

Descrição

Exemplo

Resultado

is

Igual a

10 is 10

true

aint

Diferente de

10 aint 5

true

over

Maior que

10 over 5

true

under

Menor que

10 under 5

false

overeq

Maior ou igual a

10 overeq 10

true

undereq

Menor ou igual a

10 undereq 5

false

==

Igualdade Direta (mesmo que is)

10 == 10

true

Funções de String Embutidas
Estas funções operam em expressões de string.

lenof(<expressão_string>): Retorna o comprimento de uma string (ou lista/dicionário).
Exemplo: shoo(lenof("Snask")); # Imprime 5

toupper(<expressão_string>): Converte uma string para maiúsculas.
Exemplo: shoo(toupper("olá")); # Imprime "OLÁ"

tolower(<expressão_string>): Converte uma string para minúsculas.
Exemplo: shoo(tolower("MUNDO")); # Imprime "mundo"

startswith(<expressão_string>, <expressão_string_prefixo>): Verifica se uma string começa com um dado prefixo.
Exemplo: shoo(startswith("maçã", "ma")); # Imprime true

endswith(<expressão_string>, <expressão_string_sufixo>): Verifica se uma string termina com um dado sufixo.
Exemplo: shoo(endswith("banana", "ana")); # Imprime true

Outras Funções Embutidas
typeis(<expressão>): Retorna o nome do tipo Snask do valor da expressão.
Exemplo: shoo(typeis(123)); # Imprime "int"
Exemplo: shoo(typeis("olá")); # Imprime "str"

Operações HTTP
httpget(<expressão_string_url>): Realiza uma requisição HTTP GET para a URL especificada e retorna o corpo da resposta como uma string.
Exemplo:

make url_api: str = "https://jsonplaceholder.typicode.com/todos/1";
make texto_resposta: str = httpget(url_api);
shoo(texto_resposta); # Imprime a resposta JSON da API

# 📘 SnaskLang: Manual de Referência

Bem-vindo à documentação oficial da linguagem Snask, uma linguagem divertida de alto nível que combina simplicidade com poder expressivo!

---

## 📚 Sumário
- [Introdução](#introdução)
- [Fundamentos da Linguagem](#fundamentos-da-linguagem)
  - [Comentários](#comentários)
  - [Tipos de Dados](#tipos-de-dados)
  - [Variáveis e Constantes](#variáveis-e-constantes)
    - [make](#make)
    - [keep](#keep)
    - [set](#set)
    - [zap](#zap)
- [Entrada e Saída](#entrada-e-saída)
  - [shoo](#shoo)
  - [grab](#grab)
  - [grabnum](#grabnum)
  - [grabtxt](#grabtxt)
- [Funções](#funções)
  - [function](#function)
  - [back](#back)
  - [Chamadas de Função](#chamadas-de-função)
- [Controle de Fluxo](#controle-de-fluxo)
  - [when](#when)
  - [whenn](#whenn)
  - [whenem](#whenem)
  - [spin](#spin)
  - [loopy](#loopy)
  - [breaky e skipit](#breaky-e-skipit)
  - [for](#for)
- [Coleções](#coleções)
  - [pack (listas)](#pack-listas)
  - [packadd](#packadd)
  - [packget](#packget)
  - [box (dicionários)](#box-dicionários)
  - [boxput](#boxput)
  - [boxget](#boxget)
- [Operações de Tempo](#operações-de-tempo)
  - [snooze](#snooze)
- [Conversões](#conversões)
  - [convert](#convert)
- [Arquivos e Bibliotecas](#arquivos-e-bibliotecas)
  - [readfile e writefile](#readfile-e-writefile)
  - [to use](#to-use)
- [Interface Gráfica (GUI)](#interface-gráfica-gui)
  - [create_window](#create_window)
  - [create_button](#create_button)
  - [create_label](#create_label)
  - [create_entry](#create_entry)
  - [start_gui_loop](#start_gui_loop)
- [Funções Embutidas](#funções-embutidas)
  - [lenof e typeis](#lenof-e-typeis)
  - [toupper, tolower, startswith, endswith](#toupper-tolower-startswith-endswith)
  - [jsonparse e httpget](#jsonparse-e-httpget)
  - [Funções de Memória](#funções-de-memória)

## Introdução
Snask é uma linguagem de alto nível projetada para o **Desenvolvimento Rápido de Aplicações Interativas e Ferramentas de Automação, com Ênfase na Facilidade de Uso e Prototipagem.**

Com uma sintaxe expressiva e legível, Snask abstrai complexidades e permite que desenvolvedores e entusiastas transformem ideias em protótipos e ferramentas funcionais de forma ágil. Sua capacidade de integrar interfaces gráficas (GUI) de maneira intuitiva a torna ideal para democratizar a criação de software, permitindo que usuários com diferentes níveis de experiência construam suas próprias soluções para automatizar tarefas cotidianas e otimizar fluxos de trabalho.

## Fundamentos da Linguagem

### Comentários
Use `#` para escrever comentários de linha única.

### Tipos de Dados
Suporta `int`, `float`, `str`, `bool`, `list`, `dict`, `void`, `any`.

### Variáveis e Constantes

#### make
Declara uma variável:
```snask
make x i = 10
```

#### keep
Declara uma constante:
```snask
keep pi f = 3.14
```

#### set
Altera valor de variável:
```snask
set x = 42
```

#### zap
Remove variável do ambiente:
```snask
zap x
```

## Entrada e Saída

### shoo
Imprime na tela:
```snask
shoo("Olá, mundo!")
shoo(minhaVariavel)
```

### grab
Recebe entrada genérica e armazena na variável especificada no ambiente global:
```snask
grab nome s
```

### grabnum
Recebe um número do usuário e armazena na variável especificada no ambiente global:
```snask
grabnum idade i
```

### grabtxt
Recebe texto do usuário e armazena na variável especificada no ambiente global:
```snask
grabtxt frase s
```

## Funções

### function
Define uma função.

**Sintaxe:**
```snask
function <tipo_de_retorno> <nome_da_funcao>(<tipo_param1> <nome_param1>, <tipo_param2> <nome_param2>, ...) {
    // corpo da função
    back <valor_de_retorno>
}
```

**Exemplo:**
```snask
function int somar(int a, int b) {
    back a + b
}
```

### back
Retorna um valor de dentro de uma função.

**Exemplo:**
```snask
function bool eh_maior_que_dez(int numero) {
    when numero > 10 {
        back true
    }
    back false
}
```

### Chamadas de Função
Para chamar uma função, use o nome da função seguido por parênteses com os argumentos.

**Exemplo:**
```snask
// Chamando a função 'somar' que definimos acima
make resultado int = somar(5, 3)
shoo(resultado) // Irá imprimir 8
```

## Controle de Fluxo

### when
Condicional (como `if`):
```snask
when x > 5 {
  shoo("Maior que 5")
}
```

### whenn
Condicional "else if". Executa se a condição for verdadeira e nenhum `when` ou `whenn` anterior na mesma estrutura condicional tiver sido executado:
```snask
when x > 5 {
  shoo("Maior que 5")
}
whenn x == 5 {
  shoo("Igual a 5")
}
```

### whenem
Condicional "else". Executa se nenhum `when` ou `whenn` anterior na mesma estrutura condicional tiver sido executado:
```snask
when x > 5 {
  shoo("Maior que 5")
}
whenn x == 5 {
  shoo("Igual a 5")
}
whenem {
  shoo("Menor que 5")
}
```

### spin
Loop com condição:
```snask
spin x < 10 {
  set x = x + 1
}
```

### loopy
Loop infinito:
```snask
loopy {
  shoo("pra sempre")
}
```

### breaky e skipit
Interrompe ou pula iteração:
```snask
breaky
skipit
```

### for
Itera sobre os elementos de uma lista ou os caracteres de uma string. A cada iteração, o elemento atual é atribuído à variável especificada.
```snask
pack minha_lista: list = ["maçã", "banana", "cereja"]
for fruta in minha_lista:
  shoo("Fruta: ", fruta)

make minha_string: str = "Snask"
for char in minha_string:
  shoo("Caractere: ", char)
```

## Coleções

### pack (listas)
```snask
pack numeros l = [1, 2, 3]
```

### packadd
Adiciona item:
```snask
packadd numeros, 4
```

### packget
Acessa item:
```snask
numeros[0]
```

### box (dicionários)
```snask
box dados = {"nome": "João", "idade": 30}
```

### boxput
Insere item:
```snask
boxput dados, "cidade", "SP"
```

### boxget
Acessa valor:
```snask
dados["idade"]
```

## Operações de Tempo

### snooze
(dormir por N segundos — a ser implementado)

## Conversões

### convert
(converter tipos — a ser documentado se implementado)

## Arquivos e Bibliotecas

### readfile e writefile
(leitura e escrita de arquivos — a ser documentado)

### to use
Importa bibliotecas Snask (`.snask`). Ao importar um módulo Snask, ele é executado em um escopo isolado, e suas funções e variáveis declaradas ficam acessíveis através do nome do módulo.

```snask
to use "minha_bib"
```

**Acesso a Membros de Módulos:**
Após importar um módulo, você pode acessar suas funções e variáveis usando a sintaxe `nome_do_modulo.membro`.

**Exemplo com Módulo Snask (`minha_bib.snask`):**

`minha_bib.snask`:
```snask
craft saudacao(nome s) -> void
  shoo("Olá do módulo: {}", .cdr{nome})
done

make versao s = "1.0"
```

Seu código principal:
```snask
to use "minha_bib"

call minha_bib.saudacao("Snasker")
shoo("Versão do módulo: {}", .cdr{minha_bib.versao})
```

**Exemplo com Módulo Python (`math`):**
```snask
to use "math"

make raiz f = call math.sqrt(25)
shoo("Raiz quadrada: {}", .cdr{raiz})
```

## Arquivos e Bibliotecas

### readfile e writefile
(leitura e escrita de arquivos — a ser documentado)

### to use
Importa bibliotecas Snask (`.snask`). Ao importar um módulo Snask, ele é executado em um escopo isolado, e suas funções e variáveis declaradas ficam acessíveis através do nome do módulo.

```snask
to use "minha_bib"
```

**Acesso a Membros de Módulos:**
Após importar um módulo, você pode acessar suas funções e variáveis usando a sintaxe `nome_do_modulo.membro`.

**Exemplo com Módulo Snask (`minha_bib.snask`):**

`minha_bib.snask`:
```snask
craft saudacao(nome s) -> void
  shoo("Olá do módulo: {}", .cdr{nome})
done

make versao s = "1.0"
```

Seu código principal:
```snask
to use "minha_bib"

call minha_bib.saudacao("Snasker")
shoo("Versão do módulo: {}", .cdr{minha_bib.versao})
```

**Exemplo com Módulo Python (`math`):**
```snask
to use "math"

make raiz f = call math.sqrt(25)
shoo("Raiz quadrada: {}", .cdr{raiz})
```

## Interface Gráfica (GUI)

A biblioteca `snask_gui` permite criar interfaces gráficas simples usando o Tkinter do Python. Para usá-la, importe-a com `to use "snask_gui"`.

### create_window
Cria uma nova janela.
```snask
call snask_gui.create_window("Minha Janela", 400, 300)
```

### create_button
Cria um botão na janela. O `callback_func_name` é o nome de uma função Snask que será "chamada" (simulada por enquanto) quando o botão for clicado.
```snask
craft minha_acao() -> void:
  shoo("Botão clicado!")
done

call snask_gui.create_button("Clique Aqui", "minha_acao")
```

### create_label
Cria um rótulo de texto na janela.
```snask
call snask_gui.create_label("Olá, GUI Snask!")
```

### create_entry
Cria um campo de entrada de texto na janela.
```snask
call snask_gui.create_entry()
```

### start_gui_loop
Inicia o loop principal da interface gráfica. Esta função deve ser chamada no final do seu script GUI Snask.
```snask
call snask_gui.start_gui_loop()
```

## SnaskPack: Gerenciador de Pacotes Snask

SnaskPack é o gerenciador de pacotes oficial do Snask, permitindo que você instale e gerencie bibliotecas Snask de forma fácil.

### Instalando Pacotes

Para instalar um pacote Snask, use o script `snaskpack.py` na raiz do seu projeto:

```bash
python snaskpack.py install <nome_do_pacote>
```

Isso simulará o download e a instalação do pacote no diretório `snask_packages/`.

### Estrutura de um Pacote Snask

Um pacote Snask é uma pasta com a seguinte estrutura:

```
nome_do_pacote/
├── main.snask          # Arquivo principal da biblioteca
├── snaskpack.json      # Metadados do pacote (nome, versão, descrição, dependências)
└── src/                # Outros arquivos .snask da biblioteca (opcional)
```

Você pode então importar o pacote em seu código Snask usando o comando `to use`:

```snask
to use "nome_do_pacote"
```

---

## Funções Embutidas

### lenof e typeis
```snask
lenof minhaLista
typeis minhaVar
```

### toupper, tolower, startswith, endswith, chop, glue, swap, snip, finds
```snask
toupper("oi")
tolower("OI")
startswith("banana", "ba")
endswith("banana", "na")
chop("um,dois,tres", ",") # Divide uma string em uma lista de substrings
glue(["um", "dois", "tres"], "-") # Une elementos de uma lista em uma string
swap("hello world", "world", "Snask") # Substitui ocorrências de uma substring
snip("   espacos   ") # Remove espaços em branco do início e fim da string
finds("abacate", "baca") # Verifica se uma string contém uma substring
```

### Coleções (Funções Adicionais)
- `toss(list, element)`: Joga fora a primeira ocorrência de um elemento da lista.
- `pluck(list, index)`: Arranca um elemento da lista em um índice específico.
- `tuck(list, index, element)`: Enfia um elemento na lista em um índice específico.
- `order(list)`: Coloca os elementos da lista em ordem.
- `locks(dict)`: Retorna uma lista com as chaves (fechaduras) de um dicionário.
- `treasures(dict)`: Retorna uma lista com os valores (tesouros) de um dicionário.

### Operações Matemáticas (Funções Adicionais)
- `straighten(number)`: Endireita um número (retorna o valor absoluto).
- `smooth(number)`: Suaviza um número (arredonda).


### jsonparse e httpget
```snask
jsonparse("{\"a\": 1}")
httpget("https://api.exemplo.com")
```



---

🚀 Desenvolvido com 🧠 e 💥 em SnaskLang.

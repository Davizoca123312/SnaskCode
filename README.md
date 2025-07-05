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
  - [craft](#craft)
  - [back](#back)
  - [Chamadas de Função](#chamadas-de-função)
- [Controle de Fluxo](#controle-de-fluxo)
  - [when](#when)
  - [spin](#spin)
  - [loopy](#loopy)
  - [breaky e skipit](#breaky-e-skipit)
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
- [Funções Embutidas](#funções-embutidas)
  - [lenof e typeis](#lenof-e-typeis)
  - [toupper, tolower, startswith, endswith](#toupper-tolower-startswith-endswith)
  - [jsonparse e httpget](#jsonparse-e-httpget)
  - [Funções de Memória](#funções-de-memória)

## Introdução
Snask é uma linguagem criada para ser ao mesmo tempo divertida e poderosa. Ideal para programadores que querem a leveza de Python.

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
shoo("Resultado: {} {}", .cdr{x, y})
```

### grab
Recebe entrada genérica:
```snask
grab nome s
```

### grabnum
Recebe número do usuário:
```snask
grabnum idade i
```

### grabtxt
Recebe texto:
```snask
grabtxt frase s
```

## Funções

### craft
Define uma função:
```snask
craft soma(a i, b i) -> i
  back a + b
done
```

### back
Retorna valor de função:
```snask
back resultado
```

### Chamadas de Função
```snask
call soma(2, 3)
```

## Controle de Fluxo

### when
Condicional (como `if`):
```snask
when x > 5 {
  shoo("Maior que 5")
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

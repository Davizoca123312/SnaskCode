# 📘 SnaskLang: Manual de Referência

Bem-vindo à documentação oficial da linguagem Snask, uma linguagem divertida de médio a baixo nível que combina simplicidade com poder expressivo — e acesso direto à memória!

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
Snask é uma linguagem criada para ser ao mesmo tempo divertida e poderosa. Ideal para programadores que querem o controle de C com a leveza de Python... e um pouco de caos.

## Fundamentos da Linguagem

### Comentários
Use `#` para escrever comentários de linha única.

### Tipos de Dados
Suporta `int`, `float`, `str`, `bool`, `list`, `dict`, `void`, `any` e `module`.

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
Importa biblioteca externa:
```snask
to use "minha_bib.snask"
```

## Funções Embutidas

### lenof e typeis
```snask
lenof minhaLista
typeis minhaVar
```

### toupper, tolower, startswith, endswith
```snask
toupper("oi")
tolower("OI")
startswith("banana", "ba")
endswith("banana", "na")
```

### jsonparse e httpget
```snask
jsonparse("{\"a\": 1}")
httpget("https://api.exemplo.com")
```

### Funções de Memória
- `grabbox`, `letgo`, `reshuffle`
- `dropbyte`, `peekbyte`, `dropword`, `peekword`
- `write_c_string`, `read_c_string`
- `clonemem`, `paintmem`, `matchmem`
- `manual_grabbox`, `allocsize`
```snask
grabbox buffer = grabbox 16
dropbyte buffer, 0, 65
letgo buffer
```

---

🚀 Desenvolvido com 🧠 e 💥 em SnaskLang.

# Linguagem Lang (Snask)

Lang é uma linguagem de script interpretada, de tipagem dinâmica e sintaxe simplificada, feita com Lark + Python. Esta documentação cobre todas as suas construções, com exemplos funcionais para cada recurso.

## 📚 Sumário

* [1. Introdução](#1-introdução)
* [2. Fundamentos da Linguagem](#2-fundamentos-da-linguagem)

  * [2.1. Comentários](#21-comentários)
  * [2.2. Tipos de Dados](#22-tipos-de-dados)
* [3. Variáveis e Constantes](#3-variáveis-e-constantes)

  * [3.1. make](#31-make)
  * [3.2. const](#32-const)
  * [3.3. zap](#33-zap)
* [4. Entrada e Saída](#4-entrada-e-saída)

  * [4.1. shoo](#41-shoo)
  * [4.2. inpt, inpttxt, inptnum](#42-inpt-inpttxt-inptnum)
* [5. Funções](#5-funções)

  * [5.1. func](#51-func)
  * [5.2. return](#52-return)
  * [5.3. call](#53-call)
* [6. Controle de Fluxo](#6-controle-de-fluxo)

  * [6.1. when](#61-when)
  * [6.2. spin](#62-spin)
  * [6.3. loopy, breaky, skipit](#63-loopy-breaky-skipit)
* [7. Coleções](#7-coleções)

  * [7.1. pack (Listas)](#71-pack-listas)
  * [7.2. box (Dicionários)](#72-box-dicionários)
* [8. Operações de Tempo](#8-operações-de-tempo)

  * [8.1. snooze](#81-snooze)
* [9. Conversões](#9-conversões)

  * [9.1. convert](#91-convert)
* [10. Arquivos e Bibliotecas](#10-arquivos-e-bibliotecas)

  * [10.1. readfile / writefile](#101-readfile--writefile)
  * [10.2. use](#102-use)
* [11. Funções Embutidas](#11-funções-embutidas)

  * [11.1. lenof, typeis](#111-lenof-typeis)
  * [11.2. toupper, tolower, startswith, endswith](#112-toupper-tolower-startswith-endswith)
  * [11.3. jsonparse, httpget](#113-jsonparse-httpget)

---

## 1. Introdução

Lang usa sintaxe simples e direta para manipulação de dados, entrada/saída, controle de fluxo e funções. É interpretada com Python e definida por uma gramática Lark.

## 2. Fundamentos da Linguagem

### 2.1. Comentários

```snask
# Este é um comentário
make idade: int = 20;  # Comentário após instrução
```

### 2.2. Tipos de Dados

* `int`, `float`, `str`, `bool`, `void`, `list`, `dict`, `module`, `any`

---

## 3. Variáveis e Constantes

### 3.1. `make`

```snask
make x: int = 10;
make nome: str = "Lang";
```

### 3.2. `const`

```snask
const PI: float = 3.1415;
```

### 3.3. `zap`

```snask
zap x;
```

---

## 4. Entrada e Saída

### 4.1. `shoo`

```snask
shoo("Olá, {}!", "mundo");
```

### 4.2. `inpt`, `inpttxt`, `inptnum`

```snask
inpt idade: int = "Qual sua idade? ";
inpttxt nome = "Seu nome? ";
inptnum valor = "Informe um número: ";
```

---

## 5. Funções

### 5.1. `func`

```snask
func saudacao(nome: str) -> void {
  shoo("Olá, {}!", nome);
}
```

### 5.2. `return`

```snask
func soma(a: int, b: int) -> int {
  return a + b;
}
```

### 5.3. `call`

```snask
call saudacao("Lang");
make resultado = soma(2, 3);
```

---

## 6. Controle de Fluxo

### 6.1. `when`

```snask
when idade over 18 {
  shoo("Maior de idade");
}
```

### 6.2. `spin`

```snask
spin i under 3 {
  shoo(i);
  i = i + 1;
}
```

### 6.3. `loopy`, `breaky`, `skipit`

```snask
loopy {
  shoo("infinito");
  breaky;
}
```

---

## 7. Coleções

### 7.1. `pack` (Listas)

```snask
pack lista: list = [1, 2];
pack_add lista, 3;
shoo(lista[0]);
```

### 7.2. `box` (Dicionários)

```snask
box dados: dict = {"nome": "Lang"};
box_put dados, "versao", "1.0";
shoo(dados["nome"]);
```

---

## 8. Operações de Tempo

### 8.1. `snooze`

```snask
shoo("Aguarde...");
snooze 2;
shoo("Fim da espera.");
```

---

## 9. Conversões

### 9.1. `convert`

```snask
make idade: str = "30";
convert idade to int;
```

---

## 10. Arquivos e Bibliotecas

### 10.1. `readfile` / `writefile`

```snask
writefile "saida.txt" with "Oi arquivo!";
readfile "saida.txt" into conteudo;
shoo(conteudo);
```

### 10.2. `use`

```snask
use "math";       # Módulo Python
use "libcustom";  # Biblioteca Snask
```

---

## 11. Funções Embutidas

### 11.1. `lenof`, `typeis`

```snask
shoo(lenof("abc"));      # Saída: 3
shoo(typeis(123));       # Saída: int
```

### 11.2. `toupper`, `tolower`, `startswith`, `endswith`

```snask
shoo(toupper("lang"));      # Saída: LANG
shoo(tolower("LANG"));      # Saída: lang
shoo(startswith("lang", "la")); # Saída: True
shoo(endswith("lang", "ng"));   # Saída: True
```

### 11.3. `jsonparse`, `httpget`

```snask
make dados: dict = jsonparse("{\"nome\": \"Lang\"}");
shoo(dados["nome"]);

make html: str = httpget("https://example.com");
shoo(lenof(html));
```

---

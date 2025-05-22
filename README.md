# Linguagem Lang (Snask)

Lang é uma linguagem de script interpretada, de tipagem dinâmica e sintaxe simplificada, feita com Lark + Python. Esta documentação cobre todas as suas construções, com exemplos funcionais para cada recurso.

## 📚 Sumário

* [1. Introdução](#1-introdução)
* [2. Fundamentos da Linguagem](#2-fundamentos-da-linguagem)

  * [2.1. Comentários](#21-comentários)
  * [2.2. Tipos de Dados](#22-tipos-de-dados)
* [3. Variáveis e Constantes](#3-variáveis-e-constantes)

  * [3.1. make](#31-make)
  * [3.2. keep](#32-keep)
  * [3.3. zap](#33-zap)
* [4. Entrada e Saída](#4-entrada-e-saída)

  * [4.1. shoo](#41-shoo)
  * [4.2. grab, grabnum, grabtxt](#42-grab-grabnum-grabtxt)
* [5. Funções](#5-funções)

  * [5.1. craft](#51-craft)
  * [5.2. back](#52-back)
  * [5.3. chamadas](#53-chamadas)
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
  * [10.2. to use](#102-to-use)
* [11. Funções Embutidas](#11-funções-embutidas)

  * [11.1. lenof, typeis](#111-lenof-typeis)
  * [11.2. toupper, tolower, startswith, endswith](#112-toupper-tolower-startswith-endswith)
  * [11.3. jsonparse, httpget](#113-jsonparse-httpget)

---

## 4. Entrada e Saída

### 4.1. `shoo`

```snask
shoo("Olá, {}!", "mundo");
```

### 4.2. `grab`, `grabnum`, `grabtxt`

```snask
grab idade: int;
grabtxt nome: str;
grabnum valor: int;
```

---

## 5. Funções

### 5.1. `craft`

```snask
craft saudacao(nome: str) -> void:
  shoo("Olá, {}!", nome);
done
```

### 5.2. `back`

```snask
craft soma(a: int, b: int) -> int:
  back a + b;
done
```

### 5.3. Chamadas

```snask
saudacao("Lang");
make resultado = soma(2, 3);
```

---

## 10. Arquivos e Bibliotecas

### 10.1. `readfile` / `writefile`

```snask
writefile "saida.txt" with "Oi arquivo!";
readfile "saida.txt" to conteudo;
shoo(conteudo);
```

### 10.2. `to use`

```snask
to use "math";       # Módulo Python
to use "libcustom";  # Biblioteca Snask
```

# Linguagem Lang (Snask)

Lang é uma linguagem de script interpretada, de tipagem dinâmica e sintaxe simplificada, feita com Lark + Python. Esta documentação cobre **todas** as construções da linguagem com explicações claras e exemplos práticos.

---

## 📚 Sumário

1. [Introdução](#introdução)
2. [Fundamentos da Linguagem](#fundamentos-da-linguagem)

   * [Comentários](#comentários)
   * [Tipos de Dados](#tipos-de-dados)
3. [Variáveis e Constantes](#variáveis-e-constantes)

   * [make](#make)
   * [keep](#keep)
   * [set](#set)
   * [zap](#zap)
4. [Entrada e Saída](#entrada-e-saída)

   * [shoo](#shoo)
   * [grab](#grab)
   * [grabnum](#grabnum)
   * [grabtxt](#grabtxt)
5. [Funções](#funções)

   * [craft](#craft)
   * [back](#back)
   * [Chamadas de Função](#chamadas-de-função)
6. [Controle de Fluxo](#controle-de-fluxo)

   * [when](#when)
   * [spin](#spin)
   * [loopy](#loopy)
   * [breaky e skipit](#breaky-e-skipit)
7. [Coleções](#coleções)

   * [pack (listas)](#pack-listas)
   * [packadd](#packadd)
   * [packget](#packget)
   * [box (dicionários)](#box-dicionários)
   * [boxput](#boxput)
   * [boxget](#boxget)
8. [Operações de Tempo](#operações-de-tempo)

   * [snooze](#snooze)
9. [Conversões](#conversões)

   * [convert](#convert)
10. [Arquivos e Bibliotecas](#arquivos-e-bibliotecas)

    * [readfile e writefile](#readfile-e-writefile)
    * [to use](#to-use)
11. [Funções Embutidas](#funções-embutidas)

    * [lenof e typeis](#lenof-e-typeis)
    * [toupper, tolower, startswith, endswith](#toupper-tolower-startswith-endswith)
    * [jsonparse e httpget](#jsonparse-e-httpget)

---

## Introdução

Lang combina simplicidade com poder. Sua sintaxe se inspira em linguagens modernas, com foco na clareza.

## Fundamentos da Linguagem

### Comentários

Comentários começam com `#` e vão até o fim da linha:

```snask
# Isso é um comentário
```

### Tipos de Dados

* `int`, `float`, `str`, `bool`
* `list`, `dict`, `any`, `void`, `module`

## Variáveis e Constantes

### make

Declara uma variável mutável:

```snask
make idade: int = 20;
```

### keep

Declara uma constante (imutável):

```snask
keep pi: float = 3.14;
```

### set

Atribui novo valor a uma variável:

```snask
set idade = 21;
```

### zap

Remove uma variável:

```snask
zap idade: int;
```

## Entrada e Saída

### shoo

Exibe valores no terminal:

```snask
shoo("Olá, {}!", "mundo");
```

### grab

Entrada genérica com tipo:

```snask
grab idade: int;
```

### grabnum

Entrada numérica:

```snask
grabnum valor: int;
```

### grabtxt

Entrada textual:

```snask
grabtxt nome: str;
```

## Funções

### craft

Define uma função:

```snask
craft saudacao(nome: str) -> void:
  shoo("Oi, {}!", nome);
done
```

### back

Retorna valor em uma função:

```snask
craft soma(a: int, b: int) -> int:
  back a + b;
done
```

### Chamadas de Função

```snask
saudacao("Lang");
make resultado = soma(2, 3);
```

## Controle de Fluxo

### when

Executa código se condição for verdadeira:

```snask
when idade over 18 {
  shoo("Maior de idade");
}
```

### spin

Laço enquanto:

```snask
make i: int = 0;
spin i under 5:
  shoo(i);
  set i = i + 1;
done
```

### loopy

Laço infinito:

```snask
loopy:
  shoo("Executando...");
  breaky;
done
```

### breaky e skipit

```snask
spin true:
  make i: int = 0;
  loopy:
    set i = i + 1;
    when i is 2 {
      skipit;
    }
    when i over 3 {
      breaky;
    }
  done
  breaky;
done
```

## Coleções

### pack (listas)

```snask
pack lista: list = [1, 2];
```

### packadd

```snask
packadd lista 3;
```

### packget

```snask
make item = packget lista 0;
```

### box (dicionários)

```snask
box pessoa: dict = {nome: "João"};
```

### boxput

```snask
boxput pessoa idade 30;
```

### boxget

```snask
make nome = boxget pessoa nome;
```

## Operações de Tempo

### snooze

```snask
snooze 2;  # Espera 2 segundos
```

## Conversões

### convert

```snask
convert idade to str;
```

## Arquivos e Bibliotecas

### readfile e writefile

```snask
writefile "arquivo.txt" with "Olá";
readfile "arquivo.txt" to conteudo;
shoo(conteudo);
```

### to use

```snask
to use "math";
to use "minha_lib";
```

## Funções Embutidas

### lenof e typeis

```snask
shoo(lenof("abc"));
shoo(typeis(123));
```

### toupper, tolower, startswith, endswith

```snask
shoo(toupper("abc"));
shoo(tolower("DEF"));
shoo(startswith("lang", "la"));
shoo(endswith("lang", "ng"));
```

### jsonparse e httpget

```snask
make obj = jsonparse("{\"nome\": \"João\"}");
shoo(obj["nome"]);
make html = httpget("https://example.com");
```

---

Essa é a documentação **completa** da linguagem Lang. Se quiser gerar uma versão HTML interativa ou um PDF formatado, posso ajudar com isso também!

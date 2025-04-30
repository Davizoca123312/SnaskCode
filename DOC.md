
# 📘 Snask Language Documentation

Este documento descreve a sintaxe e as regras da linguagem de programação **Snask**, com base na gramática `grammar.lark` e no interpretador `Snask_Interpreter.py`.

---

## 📌 Tipos suportados

A linguagem Snask reconhece os seguintes tipos:

- `int` → Número inteiro
- `str` → Texto (string)
- `bool` → Verdadeiro ou falso (`true` ou `false`)
- `float` → Número decimal
- `list` → Lista de valores
- `dict` → Dicionário (chave:valor)
- `void` → Usado em funções que não retornam valor

---

## 🟦 Declaração de variáveis

```snask
make nome_da_variavel :tipo = expressao
```

Exemplo:
```snask
make idade :int = 25
make nome :str = "Maria"
make ativo :bool = true
```

---

## 🟧 Entrada de dados

- `grab nome :str` → Pede ao usuário uma string.
- `grabnum nome :int` → Pede um número inteiro.
- `grabtxt nome :str` → Também lê uma string.

---

## 🟨 Impressão de dados

```snask
shoo("Texto com {}").cdr{variavel}
```

Exemplo:
```snask
make nome :str = "João"
shoo("Olá, {}!").cdr{nome}
```

---

## 🔁 Controle de fluxo

- `when condição : ...` → Condicional
- `spin condição : ...` → Loop com condição
- `loopy : ...` → Loop infinito
- `breaky` → Interrompe o laço
- `skipit` → Pula para a próxima iteração

---

## 🔧 Funções

```snask
craft nome(param1:tipo, param2:tipo) -> tipo_retorno:
    ...bloco de código...
    back valor
done
```

---

## 📦 Listas (packs)

```snask
pack lista :list = [1, 2, 3]
packadd lista 4
packget lista 2
```

---

## 🗃️ Dicionários (boxes)

```snask
box config :dict = {porta: 8080, ativo: true}
boxput config porta 9090
boxget config porta
```

---

## ⏱️ Espera

```snask
snooze 2  # Espera 2 segundos
```

---

## 🔁 Conversão de tipos

```snask
convert variavel to int
convert variavel to float
convert variavel to str
```

---

## 📁 Arquivos

```snask
readfile "entrada.txt" to variavel
writefile "saida.txt" with conteudo
```

---

## 📚 Bibliotecas

```snask
to use NomeDaBiblioteca
```

As bibliotecas devem estar na pasta `libs/` com extensão `.snask`.

---

## 🌐 Requisições e JSON (implementadas no interpretador)

```snask
make dados :str = httpget("https://api.exemplo.com")
make json :dict = jsonparse(dados)
```

---

## 🧪 Funções internas úteis

- `lenof(valor)` → Retorna o tamanho
- `typeis(valor)` → Retorna o tipo
- `toupper(valor)` / `tolower(valor)` → Manipula texto
- `startswith(txt, prefix)` / `endswith(txt, sufix)` → Testa prefixo/sufixo

---


from snask_interpreter.utils.debug import debug_print
from lark import Token
from lark.tree import Tree

class CollectionHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self.env = interpreter.env
        self._resolve = interpreter._resolve
        self._check_type = interpreter._check_type
        self.typeis = interpreter.typeis

    def list_literal(self, items):
     resolved = []
     for item in items:
        val = self._resolve(item)
        if isinstance(val, str):
            if val.startswith('"') and val.endswith('"'):
                inner = val[1:-1]
                if '"' in inner or "'" in inner:
                    raise ValueError(f"String inválida com aspas extras: {val!r}")
                val = inner
            elif val.count('"') > 0:
                raise ValueError(f"String malformada: {val!r} — use aspas apenas ao redor da palavra")
        resolved.append(val)
     return resolved

    def pack_decl(self, items):
        name_token = items[0]
        type_node = items[1]
        list_literal_node = items[2]

        name = str(name_token.value)
        declared_type = self.interpreter.type(type_node.children) if isinstance(type_node, Tree) else str(type_node)
        resolved_list = self._resolve(list_literal_node)

        if not isinstance(resolved_list, list):
            raise TypeError(f"A declaração de pacote para '{name}' esperava uma lista, mas recebeu {self.interpreter.typeis([resolved_list])}.")
        
        if declared_type != "list":
            raise TypeError(f"O tipo declarado para '{name}' é '{declared_type}', mas o valor é uma lista.")

        self.interpreter.env[-1][name] = {"type": declared_type, "value": resolved_list, "constant": False}
        debug_print(f"pack_decl: Lista '{name}' definida no ambiente: {self.interpreter.env[-1][name]}")
    
    def pack_get(self, items):
     name_token = items[0]
     index_node = items[1]

     name = str(name_token.value)
     index = self._resolve(index_node)

     if name not in self.env:
        raise NameError(f"A lista '{name}' não foi declarada.")
     lista = self.env[name]["value"]

     if not isinstance(lista, list):
        raise TypeError(f"'{name}' não é uma lista.")
     if not isinstance(index, int):
        raise TypeError(f"O índice fornecido deve ser um número inteiro.")

     if index < 0 or index >= len(lista):
        raise IndexError(f"Índice {index} fora dos limites para a lista '{name}'.")

     return lista[index]

    def pack_add(self, items):
        name_token = items[0]
        element_node = items[1]
        name = str(name_token.value)

        list_var = None
        for scope in reversed(self.interpreter.env):
            if name in scope:
                list_var = scope[name]
                break
        
        if list_var is None or list_var.get("type") != "list":
            raise NameError(f"'{name}' não é uma lista declarada para packadd.")
        
        element_value = self._resolve(element_node)
        list_var["value"].append(element_value)
        debug_print(f"pack_add: Elemento '{element_value}' adicionado à lista '{name}'. Novo valor: {list_var['value']}")

    def dict_literal(self, items):
        d = {}
        for i in range(0, len(items), 2):
            key = self._resolve(items[i])
            value = self._resolve(items[i+1])
            d[key] = value
        return d

    def dict_declaration(self, items):
        name_token = items[0]
        dict_expr_node = items[1]
        name = str(name_token.value)
        value = self._resolve(dict_expr_node)
        if not isinstance(value, dict):
            raise TypeError(f"A declaração de dicionário para '{name}' esperava um dicionário, mas recebeu {self.typeis([value])}.")
        self.env[-1][name] = {"type": "dict", "value": value, "constant": False}

    def set_dictionary_value(self, items):
        dict_name_token = items[0]
        key = items[1]
        value = items[2]

        dict_name = str(dict_name_token.value)

        debug_print(f"set_dictionary_value: dict_name: {dict_name!r}, key: {key!r}, value: {value!r}")

        resolved_dict_var = self._resolve(dict_name_token)
        debug_print(f"set_dictionary_value: resolved_dict_var: {resolved_dict_var!r}")

        if not isinstance(resolved_dict_var, dict) or resolved_dict_var.get("type") != "dict":
            raise TypeError(f"'{dict_name}' não é um dicionário declarado.")

        actual_dict = resolved_dict_var["value"]
        actual_dict[str(key)] = value

    def get_dictionary_value(self, items):
        dict_name_token = items[0]
        key = items[1]

        dict_name = str(dict_name_token.value)

        debug_print(f"get_dictionary_value: dict_name: {dict_name!r}, key: {key!r}")

        resolved_dict_var = self._resolve(dict_name_token)
        debug_print(f"get_dictionary_value: resolved_dict_var: {resolved_dict_var!r}")

        if not isinstance(resolved_dict_var, dict) or resolved_dict_var.get("type") != "dict":
            raise TypeError(f"'{dict_name}' não é um dicionário declarado.")

        actual_dict = resolved_dict_var["value"]

        try:
            return actual_dict[str(key)]
        except KeyError:
            raise KeyError(f"Chave '{key}' não encontrada no dicionário '{dict_name}'.")

    def index_access(self, items):
        collection = self._resolve(items[0])
        index_val = self._resolve(items[1])
        try:
            return collection[index_val]
        except (KeyError, IndexError) as e:
            raise type(e)(f"Erro ao acessar índice/chave '{index_val}' em '{collection!r}': {e}")
        except TypeError:
            actual_collection_type = self.typeis([collection])
            raise TypeError(f"Objeto do tipo '{actual_collection_type}' não suporta indexação (valor: {collection!r}).")

    def toss(self, items):
        lst = self._resolve(items[0])
        element = self._resolve(items[1])
        if not isinstance(lst, list):
            raise TypeError("toss espera uma lista como primeiro argumento.")
        try:
            lst.remove(element)
        except ValueError:
            raise ValueError(f"Elemento '{element}' não encontrado na lista.")

    def pop(self, items):
        lst = self._resolve(items[0])
        index = self._resolve(items[1])
        if not isinstance(lst, list):
            raise TypeError("pop espera uma lista como primeiro argumento.")
        if not isinstance(index, int):
            raise TypeError("pop espera um índice inteiro como segundo argumento.")
        try:
            return lst.pop(index)
        except IndexError:
            raise IndexError(f"Índice {index} fora do limite da lista para pop.")

    def insert(self, items):
        lst = self._resolve(items[0])
        index = self._resolve(items[1])
        element = self._resolve(items[2])
        if not isinstance(lst, list):
            raise TypeError("insert espera uma lista como primeiro argumento.")
        if not isinstance(index, int):
            raise TypeError("insert espera um índice inteiro como segundo argumento.")
        lst.insert(index, element)

    def sort(self, items):
        lst = self._resolve(items[0])
        if not isinstance(lst, list):
            raise TypeError("sort espera uma lista.")
        try:
            lst.sort()
        except TypeError:
            raise TypeError("Os elementos na lista não são comparáveis para ordenação.")

    def keys(self, items):
        d = self._resolve(items[0])
        if not isinstance(d, dict):
            raise TypeError("keys espera um dicionário.")
        return list(d.keys())

    def treasures(self, items):
        d = self._resolve(items[0])
        if not isinstance(d, dict):
            raise TypeError("treasures espera um dicionário.")
        return list(d.values())
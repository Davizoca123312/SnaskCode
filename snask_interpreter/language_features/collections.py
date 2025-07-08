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
            raise TypeError(f"pack_decl para '{name}' espera uma lista, mas recebeu {self.interpreter.typeis([resolved_list])}.")
        
        # Verifica se o tipo declarado é 'list'
        if declared_type != "list":
            raise TypeError(f"Tipo declarado para '{name}' é '{declared_type}', mas o valor é uma lista.")

        self.interpreter.env[-1][name] = {"type": declared_type, "value": resolved_list, "constant": False}
        debug_print(f"pack_decl: Lista '{name}' definida no ambiente: {self.interpreter.env[-1][name]}")
    
    def pack_get(self, items):
     name_token = items[0]
     index_node = items[1]

     name = str(name_token.value)
     index = self._resolve(index_node)

     if name not in self.env:
        raise NameError(f"Lista '{name}' não foi declarada.")
     lista = self.env[name]["value"]

     if not isinstance(lista, list):
        raise TypeError(f"'{name}' não é uma lista.")
     if not isinstance(index, int):
        raise TypeError(f"O índice fornecido deve ser inteiro.")

     if index < 0 or index >= len(lista):
        raise IndexError(f"Índice {index} fora do limite da lista '{name}'.")

     return lista[index]

    def pack_add(self, items):
        name_token = items[0]
        element_node = items[1]
        name = str(name_token.value)
        
        if name not in self.env or self.env[name]["type"] != "list":
            raise NameError(f"'{name}' não é uma lista declarada para pack_add.")
        
        element_value = self._resolve(element_node)
        self.env[name]["value"].append(element_value)

    def dict_literal(self, items):
        d = {}
        for i in range(0, len(items), 2):
            key_item = items[i]
            if isinstance(key_item, Token) and key_item.type == "NAME":
                key = str(key_item.value)
            elif isinstance(key_item, Token) and key_item.type == "ESCAPED_STRING":
                key = key_item.value
            else:
                key = str(self._resolve(key_item))
            
            value = self._resolve(items[i+1])
            d[key] = value
        return d

    def box_decl(self, items):
        name_token = items[0]
        dict_expr_node = items[1]
        name = str(name_token.value)
        value = self._resolve(dict_expr_node)
        if not isinstance(value, dict):
            raise TypeError(f"box_decl para '{name}' espera um dicionário, recebeu {self.typeis([value])}.")
        self.env[name] = {"type": "dict", "value": value, "constant": False}

    def box_put(self, items):
        name_token = items[0]
        key_node = items[1]
        value_node = items[2]
        name = str(name_token.value)

        if name not in self.env or self.env[name]["type"] != "dict":
            raise NameError(f"'{name}' não é um dicionário declarado para box_put.")
        
        key = self._resolve(key_node)
        val = self._resolve(value_node)
        self.env[name]["value"][str(key)] = val

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

    def remove(self, items):
        lst = self._resolve(items[0])
        element = self._resolve(items[1])
        if not isinstance(lst, list):
            raise TypeError("remove espera uma lista como primeiro argumento.")
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
            raise TypeError("Elementos na lista não são comparáveis para ordenação.")

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
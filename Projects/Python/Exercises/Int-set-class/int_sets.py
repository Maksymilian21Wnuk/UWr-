class Number(object):
    def __init__(self, num):
        self.num = int(num)
    def get_num(self):
        return self.num

class Variable(object):
    def __init__(self, var):
        self.scalar = int(var[:-1])
        self.name = var[-1]
    def get_scalar(self):
        return self.scalar;
    def get_name(self):
        return self.name

class VariableContainer(object):
    def __init__(self):
        self.var_dict = {}
    def __str__(self):
        s = "";
        for tup in self.var_dict.items():
            s += tup[0] + tup[1] + " "
        return s;
    def append_var(self, var_name, var_value):
        if var_name not in self.var_dict.keys():
            self.var_dict[var_name] = var_value
            return
        raise ValueError("Variable already in container")
    def remove_var(self, var_name):
        if var_name in self.var_dict.keys():
            self.var_dict.pop(var_name)
            return
        raise ValueError("Variable not present in container")
    def get_value(self, var_name):
        if var_name  in self.var_dict.keys():
            return self.var_dict[var_name]
        else:
            return var_name
    def get_container(self):
        return self.var_dict;
    def in_container(self, name):
        if name in self.var_dict.keys():
            return True
        return False
            
            

class IntSet(object):
    var_container = VariableContainer()
    def __init__(self, var = "0x"):         # useless variable
        self.set = []
        if var == "0x":
            return
        elif not isinstance(var, list):
            if isinstance(var, Number) or isinstance(var, Variable):
                self.set.append(var)
            raise ValueError("Wrong item")
        else:
            for instance in var:
                self.set.append(instance)

    def __str__(self):
        s = "<"
        for item in self.set:
            if isinstance(item, Number):
                s += str(item.get_num()) + ","
            elif isinstance(item, Variable):
                s += str(item.get_scalar()) + str(item.get_name()) + ","
        s = s[:-1]
        s += ">"
        return s

    @staticmethod
    def append_eval(name, value):
        IntSet.var_container.append_var(name, value)

    @staticmethod
    def remove_eval(name):
        IntSet.var_container.remove_var(name)

    def evaluate(self):
        ret_set = set()
        for item in self.set:
            if isinstance(item, Number):
                ret_set.add(item.get_num())
            elif isinstance(item, Variable):
                if self.var_container.in_container(item.get_name()):
                    ret_set.add(self.var_container.get_value(item.get_name()) * item.get_scalar())
                else:
                    ret_set.add(self.var_container.get_value(item.get_name()) + str(item.get_scalar()))
        return ret_set

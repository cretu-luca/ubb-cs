class FunctionCall:
    def __init__(self, function_name, *function_params):
        self.__function_name = function_name
        self.__function_params = function_params

    def call(self):
        return self.__function_name(*self.__function_params)

    def __call__(self, *args, **kwargs):
        return self.call()


class Operation:
    def __init__(self, function_undo: FunctionCall, function_redo: FunctionCall):
        self.__undo = function_undo
        self.__redo = function_redo

    def undo(self):
        return self.__undo()

    def redo(self):
        return self.__redo()


class CascadedOperation:
    def __init__(self, *operations):
        self.__operations = operations

    def undo(self):
        for operation in self.__operations:
            operation.undo()

    def redo(self):
        for operation in self.__operations:
            operation.redo()


class UndoRedoError(Exception):
    def __init__(self, message):
        self.__message = message

    def __str__(self):
        return self.__message


class UndoRedo:
    def __init__(self):
        self.__undo_operation_stack = []
        self.__redo_operation_stack = []

    def record(self, operation: Operation):
        self.__undo_operation_stack.append(operation)

    def undo(self):
        if not self.__undo_operation_stack:
            raise UndoRedoError("No mo undos!")

        undo_operation = self.__undo_operation_stack.pop()
        self.__redo_operation_stack.append(undo_operation)
        undo_operation.undo()

    def redo(self):
        if not self.__redo_operation_stack:
            raise UndoRedoError("No more redos!")

        redo_operation = self.__redo_operation_stack.pop()
        self.__undo_operation_stack.append(redo_operation)
        redo_operation.redo()


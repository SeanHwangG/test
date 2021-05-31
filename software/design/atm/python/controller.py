def create_conroller(type_):
  if type_ == "CONSOLE":
    return ConsoleBankController()


class ConsoleBankController:
  def __init__(self, _model):
    self._model = _model

  def run(self, command):
    pass

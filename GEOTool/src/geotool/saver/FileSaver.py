from abc import ABC


# Interface FileSaver
class FileSaver(ABC):

    def save(self, file_name, data):
        raise NotImplementedError

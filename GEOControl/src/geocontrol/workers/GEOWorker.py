from geocontrol.observer.Observer import Observer
from abc import ABC
from numpy import genfromtxt


def conv(x):
    return x.replace(',', '.').encode()


class GEOWorker(Observer, ABC):

    def __init__(self, client, csv_file):
        Observer.__init__(self)
        self.client = client
        self.data = genfromtxt((conv(x) for x in open(csv_file)), delimiter=';', skip_header=1)

    def notify(self, event):
        pass

    def is_finish(self):
        pass

from geocontrol.observer.Observer import Observer
from abc import ABC


class GEOWorker(Observer, ABC):

	def __init__(self, client):
		Observer.__init__(self)
		self.client = client

	def notify(self, event):
		pass

	def is_finish(self):
		pass

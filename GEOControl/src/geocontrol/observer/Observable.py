from abc import ABC


class Observable(ABC):

	def __init__(self):
		self.observers = []

	def register(self, listener):
		self.observers.append(listener)

	def unregister(self, listener):
		self.observers.remove(listener)

	def notify_listeners(self, event):
		for observer in self.observers:
			observer.notify(event)


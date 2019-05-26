from geocontrol.observer.Observable import Observable
import time


class GEOClock(Observable):

	def __init__(self):
		Observable.__init__(self)
		self.running = False
		self.time = 0

	def start(self):
		self.running = True
		self.worker()

	def stop(self):
		self.running = False

	def worker(self):
		while self.running:
			time.sleep(1 / 1000)
			self.notify_listeners(self.time)
			self.running = not self.all_finish()
			self.time = self.time + 1

	def all_finish(self):

		for worker in self.observers:
			if not worker.is_finish():
				return False

		return True

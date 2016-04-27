import threading  
import random  
import time  

class SemaphoreThread(threading.Thread):
	"""class using semaphore"""

	availableBuckets = ['A', 'B', 'C']
	volumn = 0

	def __init__(self, threadName, bonze, mutex1, mutex2, empty, full, count):
		"""initialize thread"""

		threading.Thread.__init__(self, name = threadName)
		self.sleepTime = random.randrange(1, 4)
		self.bonze = bonze
		self.mutex1 = mutex1
		self.mutex2 = mutex2
		self.empty = empty
		self.full = full
		self.count = count

	def fetch(self):
		self.empty.acquire()
		self.count.acquire()
		bucket = self.availableBuckets.pop()
		print "%s get bucket %s, available = %s" % (self.getName(), bucket, self.availableBuckets)
		self.mutex1.acquire()
		time.sleep(self.sleepTime)
		print "%s get water with bucket %s." % (self.getName(), bucket)
		self.mutex1.release()
		self.mutex2.acquire()
		time.sleep(self.sleepTime)
		SemaphoreThread.volumn = SemaphoreThread.volumn + 1
		print "%s pure water into the jar with bucket %s, volumn = %d." % (self.getName(), bucket, SemaphoreThread.volumn)
		self.mutex2.release()
		self.availableBuckets.append(bucket)
		print "%s release bucket %s, available = %s" % (self.getName(), bucket, self.availableBuckets)
		self.count.release()
		self.full.release()

	def drink(self):
		self.full.acquire()
		self.count.acquire()
		bucket = self.availableBuckets.pop()
		print "%s get bucket %s, available = %s" % (self.getName(), bucket, self.availableBuckets)
		self.mutex2.acquire()
		time.sleep(self.sleepTime)
		SemaphoreThread.volumn = SemaphoreThread.volumn - 1
		print "%s get water and drink water with bucket %s, volumn = %d." %(self.getName(), bucket, SemaphoreThread.volumn)
		self.mutex2.release()
		self.availableBuckets.append(bucket)
		self.empty.release()
		self.count.release()

	def run(self):
		if self.bonze == 1:
			self.fetch()
		else:
			self.drink()

threads = [] # list of threads

mutex1 = threading.Semaphore(1)
mutex2 = threading.Semaphore(1)
empty = threading.Semaphore(10)
full = threading.Semaphore(0)
count = threading.Semaphore(len(SemaphoreThread.availableBuckets))

# create threads
for i in range(1, 21):
	threads.append(SemaphoreThread("Young monk " + str(i), 1, mutex1, mutex2, empty, full, count))

for i in range(1, 21):
	threads.append(SemaphoreThread("Old monk " + str(i), 2, mutex1, mutex2, empty, full, count))

volumn = 0
# start each thread  
for thread in threads:
	thread.start()

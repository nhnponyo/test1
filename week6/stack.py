class Stack:
	def __init__ (self):
		self.items = []

	def isEmpty(self):
		return self.itmes == []

	def push(self,item):
		self.items.append(item)
	
	def pop(self):
		return self.items.pop()
	
	def peek(self):
		return self.items[len(self.items)-1]

	def size(self):
		return len(self.items)

s=Stack()
s.push(3)
s.push(5)
print s.pop()
print s.pop()

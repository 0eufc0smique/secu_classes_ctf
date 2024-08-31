class Shoes:
	def __init__(self, name, price):
		self.name = name
		self.price = float(price)
		
	
	def input_check(self, budget):
		# looks for specific(s) type(s) and return something we choose:
		if isinstance(budget, (int, float)):
			return True		
		else:
			return False
			print("Invalid entry, please enter a number")
			exit()
	
	def budget_check(self, budget):
		self.input_check(budget)
		if self.input_check(budget) and budget >= self.price:
			return True
		else:
			return False
		
	
	def change(self, budget):
		# determine the final change:
		return (budget - self.price)
	
	
	def buy(self, budget):
		self.budget_check(budget)
		if budget >= self.price:
			print(f"You can have some {self.name}")
			if budget == self.price:					
				print("You just have enough for them!")		
			else:
				print(f"You can even buy them, and have ${self.change(budget)} left!")
			exit("Thanks for using our shoe budget app!")
		else:				
			exit("Not enough budget, put more aside ;)")

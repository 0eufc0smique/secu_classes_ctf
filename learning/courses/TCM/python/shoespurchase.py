#!/bin/python3

from shoes import Shoes
from sys import exit

low = Shoes("And 1s", 30)
medium = Shoes("Air Force 1s", 120)
high = Shoes("Off Whites", 400)

try:
	shoe_budget = float(input("What is your shoe budget? "))
except ValueError:
	exit("Please enter a number.")
	
for shoes in [high, medium, low]:
	# checking for budget for each shoes mentionned in the list:
	shoes.buy(shoe_budget)

#!/bin/python3

from Employees import Employees

e1 = Employees("bob", "sales", "director", 100000, 20)
e2 = Employees("linda", "executive", "CEO", 150000, 10)

print(e1.name + e1.role) 
print(f"{e2.name} >>> {e2.role} >>> Eligible for retirement: {e2.eligible_for_retirement()}")

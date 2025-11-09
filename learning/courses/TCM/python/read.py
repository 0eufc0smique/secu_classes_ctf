#!/bin/python3

months = open("months.txt")

# To get months file infos:
#print(months)

# To get months mode:
#print(months.mode)

# To get a boolean telling us if its readable or not:
#print(months.readable())

# read the file:
#print(months.read())

# to read the first line:
# NB: WE CANT DO READ AND READLINE AT THE SAME TIME
#print(months.readline())

# to read the second line, we add the same stuff:
#print(months.readline())

# to read all lines at once, and output a list:
#print(months.readlines())

# if we do it a second time, it returns an empty list:
#print(months.readlines())

# in order to counter that, we need to add a seek method on the file, to seek again the context, and output it one more time:
# if we wanna go back to the first line, we pass it the argument 0:
#months.seek(0)
# now we use readlines again, and it returns the same list one more time:
#print(months.readlines())

# we can also use a for loop:
for month in months:
	print(month.strip())
	# same result with "print(months.read().strip())"



months.close()

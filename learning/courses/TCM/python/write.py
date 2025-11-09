#!/bin/python3

# if doc doesn't exist, create it and add content to it:
# when "w" is selected, everything we'll add using .write() method will overwrite content, except if we use write each time with different content to input into the file:
#days = open("days.txt", "w")

# if we want to append content, we use "a"
days = open("days.txt", "a")

print(days)
print(days.mode)

#days.write("\nmonday")

#days.write("\ntuesday")

days.write("\nwednesday")

days.close()

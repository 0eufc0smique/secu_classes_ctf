#!/bin/python3

import sys
import socket
from datetime import datetime


#Define our target
if len(sys.argv) == 2:
	target = socket.gethostbyname(sys.argv[1]) #Translate hostname to IPV4 if address entered isn't formatted to IPV4
	#Output text:
	print("\n" + ("#" * 50) + "\n")
	print(f"Scanning target: {target}")
	print(f"Time started: {str(datetime.now())}")
	print("\n" + ("#" * 50) + "\n")

	#try except thing:
	try:
		for port in range(50,85):
			# AF_INET is for IPV4, SOCK_STREAM is for the port we trynna connect to:
			sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			# if it takes more than 1 sec, we out:
			socket.setdefaulttimeout(1)
			# target will be supplied by us using argv[1], and port will b between 50 and 85
			# s.connect_ex is an error indicator, if port is open, result returns 0, if closed it returns a 1 and going to close using s.close() 
			result = sock.connect_ex((target,port))
			if result == 0:
				print(f"Port {port} is opened.")
			sock.close()
		
	except KeyboardInterrupt:
		print("\nExiting program.")
		sys.exit()
	
	except socket.gaierror:
		print("Hostname couldn't be resolved.")
		sys.exit()
		
	except socket.error:
		print("Couldn't connect to server.")
else:
	print("\nInvalid amount of arguments")
	print("Syntax: python3 scanner.py <ip address>")

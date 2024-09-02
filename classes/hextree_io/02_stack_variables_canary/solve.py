#!/usr/bin/python3

# we create a BYTEARRAY so we can iterate through it:
data = bytearray(b'\xf3\xe3\xef\xc0\xfc\xd3\xd2\xdf\xc9\xda\xe8\xcf\xda\xd8\xd0\xfa\xd5\xdf\xf3\xde\xda\xcb\xe4\xf3\xd2\xcb\x89\xd4\xc6')

for i in range(len(data)):
	data[i] = data[i] ^ 0xbb

print(data.decode())
#outputs: HXT{GhidraStackAndHeap_Hip2o}

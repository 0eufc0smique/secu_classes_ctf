#!/usr/bin/python3

obfuscated_flag = bytearray(b'\x01\x08\x69\x4a\x7c\x52\x5d\x44\x4b\x54\x71\x62\x24\x1d\x07\x17\x49\x44\x41\x56\x68\x06\x03\x0a\x06\x1a\x08\x03\x02\x62\x43\x0d\x5e\x41\x68\x1c\x00')
#print(type(obfuscated_flag))

config_buffer = bytearray("IP=127.0.0.1Port=1337Username=rootPassword=toor".encode())
#hex_config_buffer = hex(int(config_buffer, 16))
#config_buffer = '49503d3132372e302e302e31506f72743d31333337557365726e616d653d726f6f7450617373776f72643d746f6f72'
#print(type(config_buffer))

for i in range(len(obfuscated_flag) - 1):
    #print(type(config_buffer[i]), type(obfuscated_flag[i]))
    obfuscated_flag[i] = config_buffer[i] ^ obfuscated_flag[i]

print(obfuscated_flag.decode())

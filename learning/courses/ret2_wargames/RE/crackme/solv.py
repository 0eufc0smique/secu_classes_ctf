#!/usr/bin/python3

s = 'ycbwkgyucbgfajd'
s_encoded = s.encode()
s_hexed = s_encoded.hex()
print(f"string hexed: {s_hexed}")
key = ''

# iterate over pairs of hex digits, convert to int, xor it, convert back to hex
# and store in key
for i in range(0, len(s_hexed), 2):
    #print(f"s_hexed[i:i+2]: {s_hexed[i:i+2]}") # str type

    int_s_hexed = int(s_hexed[i:i+2], 16)
    #print('int_s_hexed: ', int_s_hexed)

    int_xored_i = int_s_hexed ^ int(0x21)
    #print('int_xored_i: ', int_xored_i)

    hex_xored_i = hex(int_xored_i)
    #print(f"hex_xored_i: {hex_xored_i}")

    int_char = int((hex_xored_i), 16)
    char = chr(int_char)
    #print(f"char: {char}")

    key += char

print(f"key: {key}")
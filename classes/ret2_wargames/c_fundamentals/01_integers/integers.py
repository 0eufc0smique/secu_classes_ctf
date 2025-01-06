import interact
import re


values = {
        'int8_t': (-128, 127),
        'int16_t': (-32768, 32767),
        'int32_t': (-2147483648, 2147483647),
        'int64_t': (-9223372036854775808, 9223372036854775807),
        'int': (-2147483648, 2147483647),
        'uint8_t':(0, 255),
        'uint16_t':(0, 65535),
        'uint32_t':(0, 4294967295),
        'uint64_t':(0, 18446744073709551615),
        'unsigned int':(0, 4294967295)
}

""" def str_to_hex(string):
    bytes_data = bytes(string, "utf-8")
    hex_part = ' '.join(f'{byte:02X}' for byte in bytes_data)
    print(f'string: {string}\nhex: {hex_part.ljust(47)}')

def remove_ansi_escape_sequences_start_end(data):
    ansi_escape_start = re.compile(r'^\x1b[@-_][0-?]*[ -/]*[@-~]')
    ansi_escape_end = re.compile(r'\x1b[@-_][0-?]*[ -/]*[@-~]$')

    data = ansi_escape_start.sub('', data)
    data = ansi_escape_end.sub('', data)
    return data

def left_ansi_escape_stuff(data):
    ansi_escape_start = re.search('^\x1b[@-_][0-?]*[ -/]*[@-~]', data)
    print(f"ansi_escape_start value: {ansi_escape_start}")
    ansi_escape_end = re.search(r'\x1b[@-_][0-?]*[ -/]*[@-~]$', data)
    print(f"ansi_escape_end value: {ansi_escape_end}") """

p = interact.Process()
    
def clean_data(data):
    data_decoded = data.decode('utf-8')                         # create a raw string to parse
    data_cleaned = re.sub(r'\x1b\[[0-9;]*m', '', data_decoded)  # remove ANSI escape code
    return data_cleaned

def arithmetic(data):
    data = p.readuntil('\n\n')
    data_cleaned = clean_data(data)
    
    first_num = int(data_cleaned.split(';')[0])
    operator = data_cleaned.split('=')[0].split(' ')[-1]
    second_num = int(data_cleaned.split(';')[1].split('= ')[-1])
    print(f"firstnum: {first_num} operator: {operator} secondnum: {second_num}")

    if operator == '+':
        result = str(first_num + second_num)
    elif operator == '-':
        result = str(first_num - second_num)
    else:
        print('error')
    return result

def send_choice(choice):
    p.readuntil("Enter Choice:")
    p.sendline(str(choice))
    p.sendline('')
    p.sendline('')

def quizz_choice(choice):
    if choice == 1:
        send_choice(choice)
        unsigned_int_quizz()
    elif choice == 2:
        send_choice(choice)
        signed_int_quizz()
    elif choice == 3:
        send_choice(choice)
        max_int_limit_quizz()
        min_int_limit_quizz()
        max_int_limit_quizz()
        min_int_limit_quizz()
    elif choice == 4:
        send_choice(choice)
        p.sendline('')
        p.sendline('')
        uint_overflow_quizz()
        int_overflow_quizz()
    elif choice == 5:
        send_choice(choice)
    else:
        print("[!] wrong choice")

def unsigned_int_quizz():
    pass

def signed_int_quizz():
    pass


def max_int_limit_quizz():
    p.readuntil(' a ')
    valuetomax = p.readuntil('?\n').strip()[8:-5].decode()
    valuetomax = valuetomax[:-1].strip()
    maxed_value = ''
    
    if valuetomax in values:
        value = values[valuetomax]
        maxed_value = value[1]
        maxed_value = str(maxed_value)
    else:
        print(f'{valuetomax} not found in values')
        
    p.sendline(maxed_value)
    print(f"Max value sent: (repr) {repr(valuetomax)} maxed to {repr(maxed_value)}")
    p.flush()


def min_int_limit_quizz():
    p.readuntil(' a ')
    valuetomin = p.readuntil('?\n').strip()[8:-5].decode()
    valuetomin = valuetomin[:-1].strip()
    lessened_value = ''
    
    if valuetomin in values:
        value = values[valuetomin]
        lessened_value = value[0]
        lessened_value = str(lessened_value)
    else:
        print(f'{valuetomin} not found in values')
    
    p.sendline(lessened_value)
    print(f"Min value sent: (repr) {repr(valuetomin)} lessened to {repr(lessened_value)}")
    p.flush()


def uint_overflow_quizz():
    data = p.readuntil('bar = ').strip().decode('utf-8')
    result = arithmetic(data)
    p.sendline(result)
    print(f"uint_overflow_quizz result sent: {result}")
    p.flush()

   
def int_overflow_quizz():
    data = p.readuntil('foo = ').strip().decode('utf-8')
    result = arithmetic(data)
    p.sendline(result)
    print(f"int_overflow_quizz result sent {result}")
    
    
quizz_choice(4)
p.interactive()
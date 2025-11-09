// this source code was extracted by me using Ghidra (i just copy pasted all the functions
// here so i could have an easier time trying to figure out the whole thing **


void goodbye(void) {
  puts("Goodbye !");
  return;
}

void list_available_actions(void) {
  puts("0 - Add a new page");
  puts("1 - Read the last page");
  puts("2 - Write on the last page");
  puts("3 - Leave");
  return;
}

ulong choose_action(void) {
  int *piVar1;
  long in_FS_OFFSET;
  char *endptr;
  ulong result;
  char buffer [8];
  long canary;

  canary = *(long *)(in_FS_OFFSET + 0x28);
  list_available_actions();
  fgets(buffer,8,stdin);
  result = strtoul(buffer,&endptr,0);
  piVar1 = __errno_location();
  if ((*piVar1 == 0x22) && (result == 0xffffffffffffffff)) {
    puts("Failed to interpret provided action");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  if (canary != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return result;
}

void FUN_004011e0(void) {
  __ctype_b_loc();
  return;
}

ulong get_offset_from_title(void) {
  long *plVar1;
  int i;
  ulong res;
  ulong tmp;

  res = 0;
  tmp = 0;
  i = 0;
  do {
    if (0xff < i) {
LAB_0040153d:
      printf("Offset: 0x%lx\n",(res ^ tmp) << 0xc);
      return (res ^ tmp) << 0xc;
    }
    if (book.title[i] == '\0') {
LAB_004014c1:
      if (book.title[i] == '\n') {
         tmp = tmp >> 8;
         goto LAB_0040153d;
      }
      if (book.title[i] != '\0') {
         puts("No one understand gibberish !");
                      /* WARNING: Subroutine does not return */
         exit(1);
      }
    }
    else {
      plVar1 = (long *)FUN_004011e0();
      if ((*(ushort *)((long)book.title[i] * 2 + *plVar1) & 8) == 0) goto LAB_004014c1;
      tmp = tmp | (long)((int)(book.title[i] * i + ((int)book.title[i] & 0xfU) * 0x10 +
                                  (int)(book.title[i] >> 4)) % 0x100);
    }
    if ((i & 7U) == 7) {
      res = res ^ tmp;
      tmp = 0;
    }
    tmp = tmp << 8;
    i = i + 1;
  } while( true );
}

void * get_wanted_addr(void) {
  ulong uVar1;

  uVar1 = get_offset_from_title();
  return (void *)(uVar1 + 0x4000);
}

void allocate_first_page(void) {
  uint8_t *__addr;
  uint8_t *puVar1;
  void *wanted_addr;
  void *addr;

  __addr = (uint8_t *)get_wanted_addr();
  puVar1 = (uint8_t *)mmap(__addr,0x1000,3,0x22,-1,0);
  if ((puVar1 != (uint8_t *)0xffffffffffffffff) && (puVar1 == __addr)) {
    book.content = puVar1;
    book.nb_pages = book.nb_pages + 1;
    return;
  }
  puts("Failed to allocate the first page");
  printf("%p\n",puVar1);
                /* WARNING: Subroutine does not return */
  exit(1);
}

void get_book_title(void) {
  puts("How do you want to name your book ?");
  fgets(book.title,0x100,stdin);
  return;
}

void welcome(void) {
  puts("Welcome to the book writer assistant !");
  return;
}

int main(int argc,char **argv) {
  ulong choix;
  char **argv_local;
  int argc_local;
  uint32_t choice;

  welcome();
  get_book_title();
  allocate_first_page();
  while( true ) {
    choix = choose_action();
    if (3 < (uint)choix) break;
    (*actions[choix & 0xffffffff])();
  }
  goodbye();
  return 0;
}

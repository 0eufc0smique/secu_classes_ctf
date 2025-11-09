#include <stdio.h>
#include <string.h>


void do_vuln(void *buf, size_t sz_buf);


int main (void)
{
    char buf[1000] = { 0 };
    memset(buf, '\x41', 28);          // padding
    memset(buf+28, '\x42', 4);        // saved ebp
    memset(buf+32, '\x43', 4);        // eip

    do_vuln(buf, 36);

    return 0;
}


void do_vuln(void *buf, size_t sz_buf)
{
    char dst[28];
    memcpy(dst, buf, sz_buf);
    return;
}


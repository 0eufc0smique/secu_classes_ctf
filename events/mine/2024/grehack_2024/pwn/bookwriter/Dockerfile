FROM ubuntu:24.04

RUN apt update
RUN apt install -y socat

RUN mkdir /chall
# COPY Makefile /chall/
# COPY main.c /chall/

COPY data/book-writer /chall/
COPY data/flag.txt /chall/
WORKDIR /chall

RUN chmod 444 /chall/flag.txt
RUN chmod 555 /chall/book-writer

# RUN make

RUN useradd -s /bin/bash -d /home/author -m author

# RUN sysctl -w vm.max_map_count=512

USER author

CMD socat tcp-l:4242,fork system:"/chall/book-writer",pty,stderr,setsid,sigint,sane



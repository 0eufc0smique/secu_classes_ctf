#!/bin/sh

exec socat TCP-LISTEN:1337,reuseaddr,fork EXEC:'timeout -k 61 60 /chall/run.sh,stderr'

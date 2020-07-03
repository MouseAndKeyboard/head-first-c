##
# Encrypt
#
# @file
# @version 0.1

message_hider.o: message_hider.c encrypt.h
	gcc -c message_hider.c

encypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c

message_hide: message_hider.o encrypt.o
	gcc encrypt.o message_hider.o -o message_hide

# end

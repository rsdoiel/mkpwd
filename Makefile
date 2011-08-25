#################################################
# Makefile for mkpwd
#################################################

# where the binary should be installed
DIR_INSTALL	= /usr/bin
# where the manpage goes
MAN_INSTALL	= /usr/man/man1

PRG		= mkpwd
SRC		= mkpwd.c
OBJ		= mkpwd.o
MAN		= mkpwd.1

CC		= gcc
# FLAGS		= -g
LDFLAGS		= -lcrypt

$(PRG):		$(OBJ)
		$(CC) -o $(PRG) $(OBJ) $(LDFLAGS)
		strip --strip-all $(PRG)
		
$(OBJ):		$(SRC)
		$(CC) $(FLAGS) -c $(SRC)

install:	$(PRG)
		cp $(PRG) $(DIR_INSTALL)
		cp $(MAN) $(MAN_INSTALL)
		chmod 555 $(DIR_INSTALL)/$(PRG)

uninstall:
	-rm $(DIR_INSTALL)/$(PRG)
	-rm $(MAN_INSTALL)/$(MAN)
deinstall:
	-rm $(DIR_INSTALL)/$(PRG)
	-rm $(MAN_INSTALL)/$(MAN)
un-install:
	-rm $(DIR_INSTALL)/$(PRG)
	-rm $(MAN_INSTALL)/$(MAN)
de-install:
	-rm $(DIR_INSTALL)/$(PRG)
	-rm $(MAN_INSTALL)/$(MAN)

clean:
	-rm $(OBJ) $(PRG) core

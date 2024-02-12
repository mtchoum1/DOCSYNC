#Libraries
LIBS := -lbfd

#Objects
OBJS := objsect.o objsym.o
GETSECTIONS_OBJS := getsections.o
GETSYMS_OBJS := getsyms.o

all: static_libs getsections getsyms 

objsect.o: objsect.c
	gcc -c objsect.c -o objsect.o
objsym.o: objsym.c
	gcc -c objsym.c -o objsym.o
getsections.o: getsections.c
	gcc -c getsections.c -o getsections.o
getsyms.o: getsyms.c
	gcc -c getsyms.c -o getsyms.o
static_libs: ${OBJS}
	ar rcs libobjdata.a ${OBJS}
getsections: ${GETSECTIONS_OBJS} static_libs
	gcc ${GETSECTIONS_OBJS} ./libobjdata.a -o getsections ${LIBS}
getsyms: ${GETSYMS_OBJS} static_libs
	gcc ${GETSYMS_OBJS} ./libobjdata.a -o getsyms ${LIBS}
clean:
	rm -f empty.o ${OBJS} ${GETSECTIONS_OBJS} ${GETSYMS_OBJS} libobjdata.a
empty: empty.o
	ld -g empty.o -o empty

empty.o: empty.s
	as -g empty.s -o empty.o

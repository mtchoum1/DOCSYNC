#Libraries
LIBS := -lbfd

#Objects
OBJS := objsect.o objsym.o objcopy.o
GETSECTIONS_OBJS := getsections.o
GETSYMS_OBJS := getsyms.o

all: static_libs getsections getsyms 

objsect.o: objsect.c
	gcc -fPIC -c objsect.c -o objsect.o
objsym.o: objsym.c
	gcc -fPIC -c objsym.c -o objsym.o
objcopy.o: objcopy.c
	gcc -fPIC -c objcopy.c -o objcopy.o
getsections.o: getsections.c
	gcc -c getsections.c -o getsections.o
getsections_dl.o: getsections_dl.c
	gcc -c getsections_dl.c -o getsections_dl.o
getsyms.o: getsyms.c
	gcc -c getsyms.c -o getsyms.o
static_libs: ${OBJS}
	ar rcs libobjdata.a ${OBJS}
share_libs: ${OBJS}
	gcc -shared -o libobjdata.so ${OBJS}
getsections: ${GETSECTIONS_OBJS} static_libs
	gcc ${GETSECTIONS_OBJS} ./libobjdata.a -o getsections ${LIBS}
getsyms: ${GETSYMS_OBJS} static_libs
	gcc ${GETSYMS_OBJS} ./libobjdata.a -o getsyms ${LIBS}
objcopy: $ static_libs
	gcc ./libobjdata.a -o objcopy ${LIBS}
getsections_dl: getsections_dl.o share_libs
	gcc getsections_dl.o  -L. -o getsections_dl ${LIBS}
clean:
	rm -f empty.o getsections_dl.o ${OBJS} ${GETSECTIONS_OBJS} ${GETSYMS_OBJS} libobjdata.a
empty: empty.o
	ld -g empty.o -o empty

empty.o: empty.s
	as -g empty.s -o empty.o

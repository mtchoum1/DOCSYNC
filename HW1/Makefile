OBJS := objfile.o

objfile.o: objfile.c
	gcc -c objfile.c -o objfile.o

static_libs: ${OBJS}
	ar rcs libobjdata.a ${OBJS}

finds.o: finds.c
	gcc -c finds.c -o finds.o
finds: finds.o static_libs
	gcc finds.o ./libobjdata.a -o finds
clean:
	rm -f finds.o finds ${OBJS} libobjdata.a

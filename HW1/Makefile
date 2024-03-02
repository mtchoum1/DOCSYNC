OBJS := objdir.o objfile.o objdot.o objast.o objque.o

objdir.o: objdir.c
	gcc -c objdir.c -o objdir.o
objfile.o: objfile.c
	gcc -c objfile.c -o objfile.o
objdot.o: objdot.c
	gcc -c objdot.c -o objdot.o
objast.o: objast.c
	gcc -c objast.c -o objast.o
objque.o: objque.c
	gcc -c objque.c -o objque.o

static_libs: ${OBJS}
	ar rcs libobjdata.a ${OBJS}

finds.o: finds.c
	gcc -c finds.c -o finds.o
finds: finds.o static_libs
	gcc finds.o ./libobjdata.a -o finds
clean:
	rm -f finds.o finds ${OBJS} libobjdata.a

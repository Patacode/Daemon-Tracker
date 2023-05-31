app.name=dtrack
app.obj=obj/
app.src=src/
app.head=headers/

app: dtrack
	./$(app.name)

clean:
	@rm $(app.obj)* -r
	@echo "Application cleaned up !"

dtrack: $(app.obj)error.o \
		$(app.obj)predicate.o \
		$(app.obj)linked_list.o \
		$(app.obj)env.o \
		$(app.obj)util.o \
		$(app.obj)hashmap.o \
		$(app.obj)graph.o \
		$(app.obj)notify.o \
		$(app.obj)lifecycle.o \
		$(app.obj)main.o
	@gcc $^ -o $(app.name)
	@echo "Object files linked !"

$(app.obj)error.o: $(app.src)error.c $(app.head)error.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "error.c compiled"

$(app.obj)predicate.o: $(app.src)predicate.c $(app.head)predicate.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "predicate.c compiled"

$(app.obj)linked_list.o: $(app.src)linked_list.c $(app.head)linked_list.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "linked_list.c compiled"

$(app.obj)env.o: $(app.src)env.c $(app.head)env.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "env.c compiled"

$(app.obj)util.o: $(app.src)util.c $(app.head)util.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "util.c compiled"

$(app.obj)hashmap.o: $(app.src)hashmap.c $(app.head)hashmap.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "hashmap.c compiled"

$(app.obj)graph.o: $(app.src)graph.c $(app.head)graph.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "graph.c compiled"

$(app.obj)notify.o: $(app.src)notify.c $(app.head)notify.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "notify.c compiled"

$(app.obj)lifecycle.o: $(app.src)lifecycle.c $(app.head)lifecycle.h
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "lifecycle.c compiled"

$(app.obj)main.o: $(app.src)main.c
	@gcc -c $< -I $(app.head)
	@mv *.o $(app.obj)
	@echo "main.c compiled"


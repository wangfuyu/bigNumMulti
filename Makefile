
APP_NAME=bigNumMulti
OBJ_NAME=bigNumMulti.o

$(APP_NAME):$(OBJ_NAME)
	gcc $^ -o $(APP_NAME)

%.o:%.c
	gcc -c $^ -o $@

clean:
	rm *.o $(APP_NAME)

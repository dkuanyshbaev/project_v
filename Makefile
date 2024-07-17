bin/project_v: src/main.c
	mkdir -p bin
	cc -o bin/project_v src/main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

default: src/main.c src/interp_engine.c src/ie_string.c
	clang -fsanitize=address -fsanitize=leak -fsanitize=undefined -g src/main.c src/interp_engine.c src/ie_string.c -o strings -I ./include/

test: src/tests.c src/interp_engine.c src/ie_string.c
	clang -fsanitize=address -fsanitize=leak -fsanitize=undefined -g src/tests.c src/interp_engine.c src/ie_string.c -o tests -I ./include/
	./tests

clean:
	rm tests strings
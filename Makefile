build/football: build src/football.c
	gcc src/football.c -o build/football

build:
	mkdir build

clean:
	rm -rf build
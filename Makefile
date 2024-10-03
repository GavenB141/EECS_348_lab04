all: football temperature

football: src/football.c
	gcc src/football.c -o football

temperature: src/temperature.c
	gcc src/temperature.c -o temperature

clean:
	rm football temperature

all:
	make encrypt
	make decrypt
	make crack

clean:
	rm -f encrypt
	rm -f decrypt
	rm -f crack

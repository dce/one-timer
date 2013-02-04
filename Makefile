all:
	make encrypt
	make decrypt
	make crack
	make crypto-quiz

clean:
	rm -f encrypt
	rm -f decrypt
	rm -f crack
	rm -f crypto-quiz

.PHONY: all clean input output

all: input output check zip

input:
	# Put any data generation commands here
	python3 gen/bootstrap.py
	# No sample cases
	# cp handmade/* .

output: input
	# Ummmm ok what do we do here?
	bash ./make-blank-outputs.sh

check: input

zip: input output check
	zip data.zip *.in *.out

clean:
	-rm *.in *.out
	-rm data.zip

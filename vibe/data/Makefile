.PHONY: all clean input output check

all: input output check zip

input:
	# Put any data generation commands here
	python3 gen/bootstrap.py
	cp handmade/* .

output: input
	bash ./make-output.sh

check: input
	bash ./run-validator.sh

zip: input output check
	zip data.zip *.in *.out

clean:
	-rm *.in *.out
	-rm data.zip

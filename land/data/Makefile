.PHONY: all clean input output

all: input output check zip

input:
	# Put any data generation commands here
	mkdir -p gen_specs
	g++ -std=c++14 -o generator gen/generator.cpp
	python3 gen/makecaselist.py
	python3 gen/bootstrap.py
	cp handmade/* .

output: input
	bash ./make-output.sh

check: input

zip: input output check
	zip data.zip *.in *.out

clean:
	-rm generator
	-rm *.in *.out
	-rm gen_specs/*-auto.in
	-rm data.zip

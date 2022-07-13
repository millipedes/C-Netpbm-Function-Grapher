CC=gcc -g -Wall -Wextra -std=c99
OCFILES=$(wildcard src/*/*.c)
OHFILES=$(wildcard src/*/include/*.h)
TCFILES=$(wildcard src/*/*/*.c)
THFILES=$(wildcard src/*/*/include/*.h)
RCFILES=$(wildcard src/*/*/*/*.c)
RHFILES=$(wildcard src/*/*/*/include/*.h)
OOBJFILES=$(OCFILES:.c=.o)
TOBJFILES=$(TCFILES:.c=.o)
ROBJFILES=$(RCFILES:.c=.o)

EXEFILE=bin/main
INFILE=docs/example_graph_set/example_graph.txt

all:$(OOBJFILES) $(TOBJFILES) $(ROBJFILES)
	$(CC) $(OOBJFILES) $(TOBJFILES) $(ROBJFILES) -o $(EXEFILE) -lm

%.o: %.c $(THFILES)%.h $(OHFILES)%.h $(RHFILES)%.h
	$(CC) -c $(TCFILES) $(OCFILES) $(RCFILES) $< -o $@ -lm

vim:
	nvim $(OCFILES) $(TCFILES) $(RCFILES)

vimh:
	nvim $(OHFILES) $(THFILES) $(RHFILES)

run:
	$(EXEFILE) $(INFILE)

memcheck:
	valgrind $(EXEFILE) $(INFILE) --leak-check=full --read-var-info

debug:
	gdb -q $(EXEFILE)

feh:
	feh docs/uml.png&

plant:
	plantuml docs/uml.txt
	convert docs/uml.png -channel RGB -negate docs/uml.png

test:
	feh test.ppm&

git-update:
	git add Makefile README.md src/ docs/
	git commit -m "update commit"
	git push origin main

clean:
	rm $(OOBJFILES) $(TOBJFILES) $(ROBJFILES)

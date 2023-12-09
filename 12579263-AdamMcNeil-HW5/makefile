all:hw5

run:main.c
	make hw5
	./hw5

hw5:main.c
	gcc main.c -o  hw5 -lm

doc: main.tex
	pdflatex -shell-escape main.tex -o main.pdf

clean:
	rm *.pdf
	rm *.dot
	rm hw5

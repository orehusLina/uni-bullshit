TARGET=referat
SOURCE=main
FLAGS=-shell-escape -jobname="$(TARGET)"

all: $(TARGET)

$(TARGET): $(SOURCE).tex $(wildcard *.tex) SCWorks.cls preamble.sty
	pdflatex $(FLAGS) $(SOURCE)
	bibtex "$(TARGET)"
	pdflatex $(FLAGS) $(SOURCE)
	pdflatex $(FLAGS) $(SOURCE)

.PHONY=clean

clean:
ifeq ($(OS),Windows_NT)
	del /F /S /Q $(TARGET).pdf $(wildcard *.pyg) $(wildcard *.toc) $(wildcard *.synctex.gz) $(wildcard *.out) \
	$(wildcard *.log) $(wildcard *.bbl) $(wildcard *.blg) $(wildcard _minted-*) \
	$(wildcard *.aux)
	rmdir $(wildcard _minted-*)
else
	rm -rf $(TARGET).pdf $(wildcard *.pyg) $(wildcard *.toc) $(wildcard *.synctex.gz) $(wildcard *.out) \
	$(wildcard *.log) $(wildcard *.bbl) $(wildcard *.blg) $(wildcard _minted-*) \
	$(wildcard *.aux)
endif
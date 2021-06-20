# You may want to change your pdf file name
DOCNAME="Design and Implementation of a Low Cost Embedded System for Localization of Drones Flying in Swarms"

SUBDIRS=./ Appendices Chapters

TEXNAME=main

DIR=$(PWD)
FLAGS=-synctex=1 -interaction=nonstopmode -file-line-error -recorder
CLEAN_EXTS=*.blg *.bbl *.aux *.log *.fls *.loa *.toc *.fdb_latexmk *.lof *.out *.run.xml main.synctex.gz *.lot main-blx.bib

# Help menu
USAGE = Usage: make [OPTION]
DESCRIPTION = 
HELPMENU = $(USAGE)\n$(DESCRIPTION)\nOPTIONS:

#  -------------------------------

all: report	rename clean view ## Build pdf file, clean auxiliary files and open pdf 

.PHONY: clean

report: ## Only build pdf file
	pdflatex $(FLAGS) -output-directory=$(DIR) -job-name=$(TEXNAME).pdf $(TEXNAME).tex
	bibtex $(TEXNAME).aux
	pdflatex $(FLAGS) -output-directory=$(DIR) -job-name=$(TEXNAME).pdf $(TEXNAME).tex
	pdflatex $(FLAGS) -output-directory=$(DIR) -job-name=$(TEXNAME).pdf $(TEXNAME).tex
	
rename:	## Rename main.pdf to desired pdf file name
	mv $(TEXNAME).pdf $(DOCNAME).pdf

view:	## Open pdf file with a pdf viewer
	xdg-open $(DOCNAME).pdf
	
clean:	## Clean auto generated files
	$(RM) $(TEXNAME).pdf
	$(RM) $(CLEAN_EXTS)
	cd $(DIR)/Appendices && $(RM) *.aux
	cd $(DIR)/Chapters && $(RM) *.aux
	cd $(DIR)/Misc && $(RM) *.aux

help:	## Print this help message and exit
	@echo "$(HELPMENU)" ; grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "   %-30s %s\n", $$1, $$2}'

	
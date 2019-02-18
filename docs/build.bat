@echo off
pdfLatex %1
bibtex %1
pdfLatex %1
del *.aux
del *.log
del *.out
%1.pdf
pandoc -s --mathml %~n1.md -o %~n1.html
pandoc %~n1.html -o %~n1.pdf --template=main --latex-engine=xelatex
::example.pdf
pause
set FILENAME=veysick-mate-manual
pandoc --standalone %FILENAME%.md -o %FILENAME%.html
pandoc %FILENAME%.md -o %FILENAME%.pdf --pdf-engine=lualatex -V documentclass=ltjsarticle -V luatexjapresetoptions=ipa
pandoc -t epub3 %FILENAME%.md -o %FILENAME%.epub --pdf-engine=lualatex -V documentclass=ltjsarticle -V luatexjapresetoptions=ms
pause

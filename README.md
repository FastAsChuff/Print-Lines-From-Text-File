# Print-Lines-From-Text-File
Prints a range of lines from a text file. Line numbers can be included.

This program prints lines from a text file. The line number can be prepended to the output with the switch below.

Usage:- ./flines.bin filename linenum1 [linenum2] [--linenumbers]

e.g. ./flines.bin myfilename.txt 10 20 ...prints lines 10 to 20 of myfilename.txt.

Use with grep to search a file for text. e.g. famous-person.txt from https://github.com/bsansouci/fuzzbeed/blob/master/wordlists/famous-person.txt

./flines.bin Downloads/famous-person.txt 0 500 --linenumbers | grep "Walt Disney"

206 Walt Disney

Then you can see the lines before and after easily with 

./flines.bin Downloads/famous-person.txt 202 210

Vanessa Hudgens

Vanessa Minnillo

Vanessa Williams

Vincent Van Gogh

Walt Disney

Whitney Port

Whoopi Goldberg

Will Arnett

Winston Churchill


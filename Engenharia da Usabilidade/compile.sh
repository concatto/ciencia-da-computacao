echo "Compiling $1..."
OUTFILE="$1.pdf"
pandoc $1 --pdf-engine=xelatex -o $OUTFILE -V documentclass=article -V geometry:margin=3cm -t latex 
echo "Output written to $OUTFILE."

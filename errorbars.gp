#!/usr/bin/gnuplot -persist

set title "Average temperature per Station" 
unset errorbars
set linetype 7 linecolor 6 
set grid xtics mxtics ytics mytics
set xrange [ 6000 : 100000 ] noreverse writeback
set logscale x 10
set xlabel "ID Station"
set ylabel "Average Temperature (°C)"
unset key
Shadecolor = "#80E0A080"
plot "data.dat" using 1:($2+$3):($2-$3) with filledcurve fc rgb Shadecolor, '' using 1:2 smooth mcspline lw 2 
#!/usr/local/bin/gnuplot -persist

set title "Diagramme multi-ligne des valeurs mesurées"
set xlabel "Jours"
set ylabel "Valeurs mesurées"
set key outside
set style line 1 linewidth 3
set style line 2 linewidth 3



plot 'data.dat' using 1:2 with lines ls 1 title "Station 1 - Heure 17h", \
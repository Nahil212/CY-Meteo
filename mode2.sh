#!/usr/local/bin/gnuplot -persist

set title "Diagramme de ligne simple des moyennes"
set xlabel "Jour et heure des mesures"
set ylabel "Moyenne des mesures"
set timefmt "%d/%m/%y %H:%M"
set xdata time
set format x "%d/%m\n%H:%M"

plot 'data.dat' using 1:5 with lines title "Moyenne"
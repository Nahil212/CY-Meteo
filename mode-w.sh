#!/usr/local/bin/gnuplot -persist

set title "Diagramme de vecteurs"
set xlabel "Longitude (Ouest-Est)"
set ylabel "Latitude (Sud-Nord)"

plot 'data.dat' using 1:2:($3-$1):($4-$2) with vectors title "Vecteurs"
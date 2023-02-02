#!/usr/local/bin/gnuplot -persist
set title "Diagramme de carte interpolée et colorée"
set xlabel "Longitude (Ouest-Est)"
set ylabel "Latitude (Sud-Nord)"

set pm3d map
set palette defined (0 "blue", 1 "green", 2 "red")

splot 'data.dat' using 1:2:3 with pm3d title "Carte interpolée et colorée"
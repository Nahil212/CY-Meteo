#!/usr/bin/gnuplot -persist
#This heatmap is for moisture
set view map
set dgrid3d 75,100
set palette rgb 23,28,33
set title "Humidité en fonction des coordonnées"
set xlabel "Longitude (Ouest-Est)"
set ylabel "Latitude (Nord-Sud)"
set cblabel "Humidité en %"
set xrange [-63:130]
set yrange[-62:51]
splot "data.dat" using 2:1:3 with pm3d
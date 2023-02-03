#!/usr/bin/gnuplot -persist
#This heatmap is for height
set view map
set dgrid3d 75,100
set palette defined (0 "blue", 1 "cyan", 2 "white")
set title "Altitude en fonction des coordonnées"
set xlabel "Longitude (Ouest-Est)"
set ylabel "Latitude (Nord-Sud)"
set cblabel "Altitude"
set xrange [-63:130]
set yrange[-62:51]
splot "data.dat" using 2:1:3 with pm3d
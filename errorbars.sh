#!/usr/bin/gnuplot -persist

unset errorbars
set linetype 7 linecolor 6 
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
 nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set grid layerdefault   lt 0 linecolor 0 linewidth 0.500,  lt 0 linecolor 0 linewidth 0.500

set xrange [ 6000 : 100000 ] noreverse writeback
set style data lines
set xlabel "ID Station"
set ytics  norangelimit logscale autofreq
set ylabel "Température Moyenne (°C)"
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback
n(x)=1.53**2*x/(5.67+x)**2
NO_ANIMATION = 1
unset key 
Shadecolor = "#80E0A080"
plot 'data.dat' using 1:($3):($4) with filledcurve fc rgb Shadecolor title "Température moyenne par station", '' using 1:3 with lines title "Moyenne"
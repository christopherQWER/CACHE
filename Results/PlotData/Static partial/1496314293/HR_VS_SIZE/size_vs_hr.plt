set terminal  png size 512,512 font 'Verdana, 10'
set title "Static Partial"
set output '//home//cat//Documents//CACHE//Results//PlotData//Static partial//1496314293//HR_VS_SIZE//size_vs_hr.png'
set ylabel "Hit rate"
set yrange [0:1]
set xlabel "Cache size"
set xrange [0:1]
set grid xtics ytics
plot '//home//cat//Documents//CACHE//Results//PlotData//Static partial//1496314293//HR_VS_SIZE//App_1.txt' using 1:2 with lines title 'Ap_1'

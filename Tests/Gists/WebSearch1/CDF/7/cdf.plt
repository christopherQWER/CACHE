set terminal  png size 512,512 font 'Verdana, 10'
set nokey
set title "WebSearch_1 CDF"
set output '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//cdf.png'
set ylabel "Cdf"
set yrange [0:1]
set xlabel "Stack distance"
set xrange [2.000000:455065.000000]
set grid xtics ytics
plot '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//0.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//1.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//2.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//3.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//4.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7//5.txt' using 1:2 with lines

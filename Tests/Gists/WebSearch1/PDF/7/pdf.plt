set terminal  png size 512,512 font 'Verdana, 10'
set nokey
set title "WebSearch_1 PDF"
set output '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//pdf.png'
set ylabel "Pdf"
set yrange [0:1]
set xlabel "Stack distance"
set xrange [2.000000:151688.333333]
set grid xtics ytics
plot '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//0.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//1.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//2.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//3.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//4.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//7//5.txt' using 1:2 with lines

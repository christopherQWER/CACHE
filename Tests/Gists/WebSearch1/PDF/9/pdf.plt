set terminal  png size 512,512 font 'Verdana, 10'
set nokey
set title "WebSearch_1 PDF"
set output '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//pdf.png'
set ylabel "Pdf"
set yrange [0:1]
set xlabel "Stack distance"
set xrange [2.000000:174763.000000]
set grid xtics ytics
plot '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//0.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//1.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//2.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//3.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//4.txt' using 1:2 with lines,\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//PDF//9//5.txt' using 1:2 with lines

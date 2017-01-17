set terminal  png size 512,512 font 'Verdana, 10'
set nokey
set title "WebSearch_1 CDF"
set output '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//WebSearch1_CDFs.png'
set ylabel "CDF"
set yrange [0:1]
set xlabel "Stack distance"
set xrange [2:100000]
set xtics 20000
set grid xtics ytics
plot '//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//0.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//1.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//2.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//3.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//4.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//5.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//6.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//7.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//8.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//9.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//10.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//11.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//12.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//13.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//14.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//15.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//16.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//17.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//18.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//19.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//20.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//21.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//22.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//23.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//24.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//25.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//26.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//27.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//28.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//29.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//30.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//31.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//32.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//33.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//34.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//35.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//36.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//37.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//38.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//39.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//40.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//41.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//42.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//43.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//44.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//45.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//46.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//47.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//48.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//49.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//50.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//51.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//52.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//53.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//54.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//55.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//56.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//57.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//58.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//59.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//60.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//61.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//62.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//63.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//64.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//65.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//66.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//67.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//68.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//69.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//70.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//71.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//72.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//73.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//74.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//75.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//76.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//77.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//78.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//79.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//80.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//81.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//82.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//83.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//84.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//85.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//86.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//87.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//88.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//89.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//90.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//91.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//92.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//93.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//94.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//95.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//96.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//97.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//98.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//99.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//100.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//101.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//102.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//103.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//104.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//105.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//106.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//107.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//108.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//109.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//110.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//111.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//112.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//113.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//114.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//115.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//116.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//117.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//118.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//119.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//120.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//121.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//122.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//123.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//124.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//125.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//126.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//127.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//128.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//129.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//130.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//131.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//132.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//133.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//134.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//135.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//136.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//137.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//138.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//139.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//140.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//141.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//142.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//143.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//144.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//145.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//146.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//147.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//148.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//149.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//150.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//151.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//152.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//153.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//154.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//155.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//156.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//157.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//158.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//159.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//160.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//161.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//162.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//163.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//164.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//165.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//166.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//167.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//168.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//169.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//170.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//171.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//172.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//173.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//174.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//175.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//176.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//177.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//178.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//179.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//180.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//181.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//182.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//183.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//184.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//185.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//186.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//187.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//188.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//189.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//190.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//191.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//192.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//193.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//194.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//195.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//196.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//197.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//198.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//199.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//200.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//201.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//202.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//203.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//204.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//205.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//206.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//207.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//208.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//209.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//210.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//211.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//212.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//213.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//214.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//215.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//216.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//217.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//218.txt' using 1:2 lw 2 lt rgb 'red',\
'//home//cat//Documents//CACHE//Tests//Gists//WebSearch1//CDF//219.txt' using 1:2 lw 2 lt rgb 'red'

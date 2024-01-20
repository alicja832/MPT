set term png size 2000, 2000 lw 5 font "Helvetica,40"
set size square
set out "report2.png"

set xlabel "Thread count"
set ylabel "Speedup"

plot "test500.dat" using 2:3 w l title "N=500", "test1500.dat" using 2:3 w l title "N=1500", "test2500.dat" using 2:3 w l title "N=2500", "test3500.dat" using 2:3 w l title "N=3500", "test4500.dat" using 2:3 w l title "N=4500"
set size ratio -1
unset key
set xrange [-5:5]
set yrange [-5:5]
f(x)=-tan(20*pi/180)*x
set title "Solid Fraction"
plot "avv.dat" u 1:2:3 w image,f(x) lc rgb "white" lw 2#,"prf.dat" u 15:16 lc rgb "yellow"
pause -1
set title "Velocity v_x"
plot "avv.dat" u 1:2:4 w image
pause -1
set title "Velocity v_y"
plot "avv.dat" u 1:2:5 w image
pause -1
set title "Omega"
plot "avv.dat" u 1:2:7 w image
pause -1

#set title "Fluctuation velocity u_x"
#plot "avv.dat" u 1:2:7 w image
#pause -1
#set title "Normal stress sigma_{zz}"
#plot "avv.dat" u 1:2:12 w image
#pause -1
#set title "Shear stress \sigma_{xz}"
#plot "avv.dat" u 1:2:13 w image
#pause -1
#set title "Shear rate gamma-dot"
#plot "avv.dat" u 1:2:14 w image,f(x) lc rgb "white" lw 2,"prf.dat" u 15:16 lc rgb "yellow"
#pause -1

unset key
set title "Solid Fraction"
set xrange [0.3:0.7]
plot "prf.dat" u 2:1
pause -1
unset xrange
set title "Velocities v_x,v_y"
plot "prf.dat" u 3:1,"prf.dat" u 4:1
pause -1
#set title "Fluctuation velocities u_x,u_y,u_z"
#plot "prf.dat" u 5:1,"prf.dat" u 6:1,"prf.dat" u 7:1
#pause -1
#set title "Stresses s_{xx},s_{zz},s_{xz}"
#plot "prf.dat" u 8:1,"prf.dat" u 9:1,"prf.dat" u 10:1
#pause -1
#set xrange [0:20]
#set title "Shear rate gamma-dot"
#plot "prf.dat" u 11:1
#pause -1
#set xrange [0:3]
#set title "Stress ratio, K"
#plot "prf.dat" u 14:1
#pause -1

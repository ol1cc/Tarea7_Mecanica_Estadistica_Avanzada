reset session

set terminal pngcairo size 800,600 font "Times New Roman, 18"
set xlabel "Intensity"
set ylabel "Probability Density p𝘀𝙩(I)"
set output "probability_density.png"
unset title

k = 1e-4
b = 0.2

set xrange[0:0.025]
set yrange [0:2]

f(x,g) = exp(((g-1)*x**2 - (2 * b * x**3)/3)/k)

plot f(x,0.5) w l lw 2 title "g = 0.5", f(x,1) w l lw 2 title "g = 1", f(x,1.5) w l lw 2 title "g = 1.5"
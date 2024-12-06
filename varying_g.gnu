reset session

set terminal pngcairo size 800,600 font "Times New Roman, 18"
set xlabel "g"
set ylabel "Average Intensity〈I〉(g)"
set output "plots/avr_intensity.png"
unset title
unset key

plot "data/gvar/gvar.txt" using 1:2 w l lw 2

set ylabel "Intensity Fluctuations"
set output "plots/avr_intensity_fluct.png"
plot "data/gvar/gvar.txt" using 1:3 w l lw 2
reset session

set terminal pngcairo size 800,600 font "Times New Roman, 18"
set output 'noise_histogram.png'

set style data boxes
set style fill solid border -1
set xlabel "ξ"
set ylabel "Normalized Frequency"
unset title

# Define bin width
bin_width = 0.01
bin(x, width) = width * floor(x / width) + width / 2.0


# Gaussian 
dt = 0.01
k = 1e-4
s = sqrt(k / dt)
f(x) = exp(-0.5 * (x / s) ** 2) / (sqrt(2 * pi) * s)

# Compute the total number of data points
stats 'noise_counts.txt' nooutput
total_points = STATS_records

# Normalize by dividing by total_points * bin_width
plot 'noise_counts.txt' using (bin($2, bin_width)):(1.0 / (total_points * bin_width)) smooth freq with boxes lc "turquoise" title "Noise Counts", f(x) w l lw 4 lc "dark-blue" title "Gaussian Curve"

unset output
unset key

set xlabel "Time"
set ylabel "ξ"
set output 'noise_time.png'
plot 'noise_counts.txt' using 1:2 w l lw 2
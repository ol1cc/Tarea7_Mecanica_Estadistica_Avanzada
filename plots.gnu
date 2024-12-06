reset session

set terminal pngcairo size 800,600 font "Times New Roman, 18"
set xlabel "Time"
set ylabel "Intensity I(t)"
set output "plots/noise_different_g.png"
set title "Intensity Curves for Different g Values"

# Configure the key (legend)
set key at screen 0.5, 0.9 # Position the key in normalized coordinates
set key box opaque # Add a white background box behind the legend
set key inside # Place the key inside the plot area

plot_files = "int_n=true_g=0.5.txt int_n=true_g=0.75.txt int_n=true_g=1.txt int_n=true_g=1.25.txt int_n=true_g=1.5.txt"
plot_colors = "red, blue, #006400, orange, purple"

# Initialize plot command
plot for [i=0:4] sprintf("data/intensity/%s", word(plot_files, i+1)) using 1:2 with lines lw 2 lc rgb word(plot_colors, i+1) title sprintf("g = %.2f", 0.5 + i*0.25)
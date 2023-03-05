cat > temperature_profile.p << EOF
set title "Temperature profile for nodes"
set xlabel "nodes"
set ylabel "temperature in Celsius"
set term png
set output "temperature_profile_u_0.png"
plot "temperature_profile.txt"
EOF

gnuplot temperature_profile.p

open temperature_profile_u_0.png

cat > temperature_node0.p << EOF
set title "Temperature profile with time"
set xlabel "time steps"
set ylabel "temperature in Celsius"
set term png
set output "temperature_node0_u_0.png"
plot "temperature_node0.txt" with lines
EOF

gnuplot temperature_node0.p

open temperature_node0_u_0.png


cat > temperature_node_last.p << EOF
set title "Temperature profile with time"
set xlabel "time"
set ylabel "temperature in Celsius"
set term png
set output "temperature_node_last_u_0.png"
plot "temperature_node_last.txt" with lines
EOF

gnuplot temperature_node_last.p

open temperature_node_last_u_0.png

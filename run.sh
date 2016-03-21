cd ./Build
echo "Started execution @ $(date)"
./Rasterize && xdg-open ../Images/
echo "Ended execution @ $(date)"
cd ./Build
BEGIN=$(date +"%S")
./Rasterize 
xdg-open ../Images/none.ppm

END=$(date +"%S")
TIME=$((END-BEGIN))
ABS=${TIME#-}
echo -e "Total Runtime \e[41m $ABS seconds \e[49m"
echo "Pictures can be found in ./Images"
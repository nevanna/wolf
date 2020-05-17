clear
echo "\033[32mmake\033[0m"
echo " "
make
echo "\033[32mmake clean\033[0m"
echo " "
make clean
echo "\033[32mmake fclean\033[0m"
echo " "
make fclean
echo "\033[32mmake re\033[0m"
echo " "
make re
echo "\033[32mmake\033[0m"
echo " "
make
echo "\033[35;5;5mvalidation wrong map \033[0m"
echo "-------------------------------------------------------------"
echo "\033[32mno file\033[0m"
./wolf3d ahsjdhkajsd
echo " "
echo "\033[32mmultiple maps\033[0m"
./wolf3d map1 map2
echo " "
echo "\033[32mmap 0:empty map \033[0m"
./wolf3d maps/map0
echo " "
echo "\033[32mmap 1:no sp\033[0m"
./wolf3d maps/map1
echo " "
echo "\033[32mmap 2:dif len\033[0m"
./wolf3d maps/map2
echo " "
echo "\033[32mmap 3:with liter\033[0m"
./wolf3d maps/map3

make fclean

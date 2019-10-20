
#Read folder list
j=0
for i in `ls -F | grep "/$" `
do
    folder_list[j]=$i
    j=`expr $j + 1`
done


read -p "Enter your choice(install or uninstall),please:" input

case $input in
	[install]*)
		for((i=0;i<j;i++))
		do
		    cd ${folder_list[i]}  && make && sudo make install && cd ..
		done
		;;
	[uninstall]*)
		for((i=0;i<j;i++))
		do
		    cd ${folder_list[i]}  && make && sudo make uninstall && cd ..
		done
		;;
	*)
		echo "Input install or uninstall"
		exit
		;;
esac


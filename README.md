# Запуск
./client -a 127.0.0.1 -p 33333 -i ../input.bin -o ../output.bin -c ../vclient.conf
./server_static -T float -H SHA1 -S client

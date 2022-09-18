Перед запуском надо установить библиотеку для работы с json:
sudo apt-get install libjsoncpp-dev

пример запуска:
./log_reader --concurrency 4 --path ~/logs --file_count 10

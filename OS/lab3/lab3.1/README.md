# Лабораторная работа 3, Задача 1

Запуск: gcc main.c  
./a.out

Реализуйте клиент-серверное приложение на очередях сообщений System V. Данными,
которыми посредством очереди сообщений обмениваются клиентский и серверный
процессы, являются переменные структурного типа с полями текст (статический
массив значений типа char) и приоритет (целое неотрицательное число). Серверное
приложение, получив сообщение, обрабатывает его, заменяя все подряд идущие
символы-разделители (символы пробела, табуляции) одним символом пробела, и
возвращает обработанный текст клиентскому приложению. Разработайте систему
приоритетов для ускорения обработки некоторых сообщений. Каждый клиентский
процесс имеет набор текстовых файлов. Каждый текстовый файл имеет следующий
формат:  
prior=0 text=“Hello World!!”  
prior=0 text=“Python is my favorite language!!!...”  
prior=5 text=“Where is my greatest Lab’’’ work???”  
prior=2 text=“ Yes!”  
prior=3 text=“No……”  
prior=3 text=“2,,,9\”99\” .”  
prior=2 text=“12,,,4 6”  
Предусмотрите возможность отправки сообщения с наивысшим приоритетом, которое
предназначается для завершения взаимодействия с сервером  
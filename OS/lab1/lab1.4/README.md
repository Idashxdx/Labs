# Лабораторная работа 1, Задача 4

Запуск: gcc main.c 
./a.out file flag  
flag: xor8, xor32, mask (number in 16n.s)


Реализуйте консольное приложение для побайтовой обработки файлов. Аргументы в
Ваше приложение передаются как аргументы командной строки: первый параметр —
путь ко входному файлу, второй параметр – это флаг, который определяет действие,
которое необходимо выполнить с файлом:  
● xor8 - сложение по модулю 2 всех байтов файла;  
● xor32 - сложение по модулю 2 групп четырехбайтовых значений из файла (если
размер последней группы байтов файла != 4 байтам, недостающие байты
заполняются значением ;0016  
● mask <hex> - подсчет четырёхбайтовых целых чисел из файла, которые
соответствуют маске <hex>, которая задана в системе счисления с основанием
16.  

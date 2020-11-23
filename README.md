# ILab2

ILab2 homework

## [Cache](https://github.com/Tako-San/ILab2/tree/master/1_Cache)

Мой LFU кэш, на ```std::unordered_map``` и ```std::list```.

Имя файла с тестовыми данными передается в агрументах командной строки (Но можно вводить и в консоли). 
Расширение файла с входными данными - ``` *.dat ```, выходными - ``` *.ans ``` .


## [Triangle intersect](https://github.com/Tako-San/ILab2/tree/master/2_TrigonCross)

Ищем пересекающиеся в пространстве треугольники.
Для оптимизации поиска пересечений используется **октодерево**.

**Входные данные**: число треугольников, затем координаты их вершин.

## [Search Tree](https://github.com/Tako-San/ILab2/tree/master/3_SrchTree)

Поисковое дерево с сохранением **AVL**-инварианта.
В ```main.cc``` сравнение скорости с ```std::set```.

**Входные данные**: количество сортируемых элементов, сами элементы, 
затем количество интервалов, в которых будем искать элементы,
и сами интервалы (конец и начало).

**Выходные данные**: элементы дерева, лежащие в интервалах и время исполнения.


## [Matrix](https://github.com/Tako-San/ILab2/tree/master/4_Matrix)

Шаблонный класс матрицы различными операциями. 

Некоторые операции:
* Транспонирование.
* Поиск детерминанта (методом Гаусса).
* Перемножение матриц.
* Элементарные операции.
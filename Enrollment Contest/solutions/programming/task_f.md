# Definition

В этом задании необходимо найти номер строки, содержащей ошибку.
Ниже приведен псевдокод решения следующей задачи.
Даны *m* заказов на доставку. Каждый заказа описывается двумя моментами времени: *start*, *finish* (в формате HH:MM:SS). Как только курьер начинает выполнение заказа, курьер не может выполнять никакой другой заказ в интервале между *start* и *finish*. 

Определите минимальное количество курьеров, которые потребуются для выполнения всех *m* заказов.

Рассмотрим пример:
Если m=4 и 
start1=08:00:00, finish1=11:00:00,
start2=09:00:00, finish2=10:00:00,
start3=10:00:00, finish3=11:10:00,
start4=10:59:59, finish4=13:00:00.

Один курьер может выполнить 2 заказа (2-й и 3-й или 2-й и 4-й), два курьера могут доставить 3 заказа, а три курьера могут доставить все 4 заказа.
Обратите внимание, что курьер может взять новый заказ сразу после окончания выполнения предыдущего.

 
    # read input:  
    # read number of orders to deliver from first row of the input into m  
    # read start and finish timestamps from each next row in input  
    # and store them in an m*2 array called orders  
    # orders[i][0] - start of order i, orders[i][1] - finish of order i  
    # it is known that for each order i that: orders[i][0] < orders[i][1]  
    
    1.  available_at - [0..m-1] array of timestamps, initialized with 00:00:00  
    2.  sort orders in increasing order of start timestamps  
    3.  
    4.  used_couriers = 0  // count of couriers delivering at least one order  
    5.  
    6.  for order_id from 0 to m - 1:  
    7.    available_courier = -1  
    8.  
    9.    for courier_id from 0 to m - 1:  
    10.      if available_at[courier_id] <= orders[order_id][0]:  
    11.        available_courier = courier_id  // save available courier found  
    12.       break  
    13.  
    14.   if available_at[available_courier] == ’00:00:00’:  
    15.     used_couriers += 1 // assign order to a new courier  
    16.  
    17.   available_at[available_courier] = orders[order_id][0] // update time of availability  
    18.  
    19. return used_couriers


Замечание: ’Ошибка’ может соответствовать любой ситуации, когда программа (алгоритм) выдает неверный ответ, псевдокод может быть исправлен изменением, удалением или добавлением нескольких символов в одной строке.
Подсказка: Ошибка не синтаксическая, а в корректности алгоритма.

# Answer

17
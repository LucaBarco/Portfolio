# Project Estimation  

Authors:<br />
Barco Luca<br />Di Vincenzo Alessandro<br />Pappalardo Marco Giulio Lorenzo<br />Petruzzi Rocco Luigi<br />

Date:<br />01/05/2020

Version:

# Contents



- [Estimate by product decomposition]
- [Estimate by activity decomposition ]



# Estimation approach

# Estimate by product decomposition



### 

|             | Estimate                        |             
| ----------- | ------------------------------- |  
| NC =  Estimated number of classes to be developed   | 35 |             
| A = Estimated average size per class, in LOC    | 250| 
| S = Estimated size of project, in LOC (= NC * A) | 8750 |
| E = Estimated effort, in person hours  | 487 |   
| C = Estimated cost, in euro (here use 1 person hour cost = 30 euro) | 14.610 | 
| Estimated calendar time, in calendar weeks (Assume team of 4 people, 8 hours per day, 5 days per week ) | ~ 12|               


# Estimate by activity decomposition



### 

|         Activity name    | Estimated effort (person hours)   |             
| ----------- | ------------------------------- | 
| requirements | 130 |
| design | 70 |
| coding | 70 |
| documentation | 34 |
| test plan | 70 |
| test data | 34 |
| test unit | 70 |
| system test | 9 |

###
Insert here Gantt chart with above activities

```plantuml
@startuml
-- Requirements --
[Requirements] as [TASK1] lasts 4 days
-- Design --
[Design] as [TASK2] lasts 2 days
-- Coding --
[Coding] as [TASK3] lasts 2 days
[Documentation] as [TASK6] lasts 1 days
-- Testing --
[Test Plan] as [TASK7] lasts 2 days
[Test Data] as [TASK4] lasts 1 days
[Test Unit] as [TASK5] lasts 2 days
[System Test] as [TASK8] lasts 1 days
[TASK1]->[TASK2]
[TASK2]->[TASK3]
[TASK2]->[TASK7]
[TASK3]->[TASK6]
[TASK7]->[TASK4]
[TASK4]->[TASK5]
[TASK5]->[TASK8]
[TASK3] is colored in Coral/LightBlue
[TASK6] is colored in Coral/LightBlue
[TASK4] is colored in Yellow/LightBlue
[TASK5] is colored in Yellow/LightBlue
[TASK7] is colored in Yellow/LightBlue
[TASK8] is colored in Yellow/LightBlue
@enduml
```


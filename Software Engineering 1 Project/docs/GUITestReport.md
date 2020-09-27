# GUI  Testing Documentation 

Authors:<br />
Barco Luca<br />Di Vincenzo Alessandro<br />Pappalardo Marco Giulio Lorenzo<br />Petruzzi Rocco Luigi<br />

Date:<br />01/06/2020

Version:

# GUI testing

This part of the document reports about testing at the GUI level. Tests are end to end, so they should cover the Use Cases, and corresponding scenarios.

## Coverage of Scenarios and FR


### 

| Scenario ID | Functional Requirements covered |GUI Test(s) | 
| ----------- | ------------------------------- | ----------- | 
| UC1.1       |   FR1.1, FR1.4                   | testUC1_1.py|
| UC1.2       |   FR1.1, FR1.4                   |testUC1_2.py |
| UC1.3       |   FR1.1, FR1.4           |testUC1_3.py |
| UC1.4       |   FR1.1, FR1.4           |testUC1_4.py |
| UC2.1       |   FR1.1                         |testUC2_1.py |
| UC2.2       |   FR1.1, FR1.3, FR1.4           |testUC2_2.py |
| UC3.1       |   FR1.2, FR1.3                         |https://git-softeng.polito.it/se-2020/ezgas/-/issues/27|
| UC3.2       |   FR1.2, FR1.3, FR1.4           |testUC3_2.py |
| UC4.1 | FR3.1, FR4 |testUC4_1.py|
| UC5.1| FR3.1, FR4 |testUC5_1.py|
| UC6.1| FR3.2, FR3.3 |testUC6_1.py |
| UC7.1| FR1.4 FR3.1 FR5.1| testUC7_1.py|
| UC7.2| FR1.4 FR3.1 FR5.1|testUC7_2.py |
| UC7.3| FR1.4 FR3.1 FR5.1|testUC7_3.py |
| UC7.4| FR1.4 FR3.1 FR5.1|testUC7_4.py |
| UC8.1| FR4.2 |testUC8_1.py |
| UC8.2| FR4.5|testUC8_2.py|
| UC8.3 | FR4.3, FR4.4|testUC8_3.py |
| UC9.1| FR5.2|testUC9_1.py  |
| UC10.1| FR4, FR5.3 |testUC10_1.py |
| UC10.2| FR4, FR5.3 |testUC10_2.py|          


# REST  API  Testing

This part of the document reports about testing the REST APIs of the back end. The REST APIs are implemented by classes in the Controller package of the back end. 
Tests should cover each function of classes in the Controller package

## Coverage of Controller methods



| class.method name | Functional Requirements covered |REST  API Test(s) | 
| ----------- | ------------------------------- | ----------- | 
|  GasStationController.saveGasStation                   | FR3.1         |  TC01_TestsaveGasStation                   |     
|  GasStationController.getAllGasStations                | FR3.3         |  TC02_TestgetAllGasStations                |
|  GasStationController.getGasStationById                | FR4           |  TC03_TestgetGasStationById                |
|  GasStationController.getGasStationByProximity         | FR4.1         |  TC04_TestgetGasStationByProximity         |
|  GasStationController.searchGasStationByNeighborhood   | FR4.2         |  TC05_TestsearchGasStationsByNeighborhood  |
|  GasStationController.searchGasStationsByGasolineType  | FR4.3 - FR4.5 |  TC06_TestsearchGasStationsByGasolineType  |
|  GasStationController.getGasStationsWithCoordinates    | FR4.5         |  TC07_TestgetGasStationsWithCoordinates    |
|  GasStationController.setReport                        | FR5.1 - FR5.2 |  TC09_TestsetReport                        |
|  GasStationController.deleteGasStation                 | FR3.2         |  TC10_TestdeleteGasStation                 |
|  UserController.saveUser                               | FR1.1         |  TC11_TestsaveUser                         |
|  UserController.getUserById                            | FR1.4         |  TC12_TestgetUserById                      |
|  UserController.getAllUsers                            | FR1.3         |  TC13_TestgetAllUsers                      |
|  UserController.increaseUserReputation                 | FR5.3         |  TC14_TestincreaseUserReputation           |
|  UserController.decreaseUserReputation                 | FR5.3         |  TC15_TestdecreaseUserReputation           |
|  UserController.login                                  | FR2           |  TC16_Testlogin                            |
|  UserController.deleteUser                             | FR1.2         |  TC17_TestdeleteUser                       |
<!--
|  GasStationController.getGasStationWithoutCoordinates  | FR  |  TC08_TestgetGasStationsWithoutCoordinates | 

check FR for TC04 -->
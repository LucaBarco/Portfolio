# Requirements Document 

Authors:<br />
Barco Luca<br />Di Vincenzo Alessandro<br />Pappalardo Marco Giulio Lorenzo<br />Petruzzi Rocco Luigi<br />

Date:<br />16/04/2020

Version:

# Contents

- [Abstract](#abstract)
- [Stakeholders](#stakeholders)
- [Context Diagram and interfaces](#context-diagram-and-interfaces)
	+ [Context Diagram](#context-diagram)
	+ [Interfaces](#interfaces) 
	
- [Requirements Document](#requirements-document)
- [Contents](#contents)
- [Abstract](#abstract)
- [Stakeholders](#stakeholders)
- [Context Diagram and interfaces](#context-diagram-and-interfaces)
	- [Context Diagram](#context-diagram)
	- [Interfaces](#interfaces)
- [Stories and personas](#stories-and-personas)
- [Functional and non functional requirements](#functional-and-non-functional-requirements)
	- [Functional Requirements](#functional-requirements)
	- [Non Functional Requirements](#non-functional-requirements)
- [Use case diagram and use cases](#use-case-diagram-and-use-cases)
	- [Use case diagram](#use-case-diagram)
		- [Use case 1, UC1](#use-case-1-uc1)
				- [Scenario 1.1](#scenario-11)
				- [Scenario 1.2](#scenario-12)
				- [Scenario 1.3](#scenario-13)
		- [Use case 2, UC2](#use-case-2-uc2)
				- [Scenario 2.1](#scenario-21)
				- [Scenario 2.2](#scenario-22)
		- [Use case 3, UC3](#use-case-3-uc3)
				- [Scenario 3.1](#scenario-31)
		- [Use case 4, UC4](#use-case-4-uc4)
				- [Scenario 4.1](#scenario-41)
		- [Use case 5, UC5](#use-case-5-uc5)
				- [Scenario 5.1](#scenario-51)
		- [Use case 6, UC6](#use-case-6-uc6)
			- [Scenario 6.1](#scenario-61)
		- [Use case 7, UC7](#use-case-7-uc7)
			- [Scenario 7.1](#scenario-71)
		- [Use case 8, UC8](#use-case-8-uc8)
			- [Scenario 8.1](#scenario-81)
		- [Use case 9, UC9](#use-case-9-uc9)
			- [Scenario 9.1](#scenario-91)
		- [Use case 10, UC10](#use-case-10-uc10)
			- [Scenario 10.1](#scenario-101)
		- [Use case 11, UC11](#use-case-11-uc11)
			- [Scenario 11.1](#scenario-111)
		- [Use case 12, UC12](#use-case-12-uc12)
			- [Scenario 12.1](#scenario-121)
- [Glossary](#glossary)
- [System Design](#system-design)
- [Deployment Diagram](#deployment-diagram)

# Abstract

Since cars have been invented, car owners have had the need to refill the fuel tank in order to make them move. Sometimes you know where you're going to refuel, sometimes you don't. If you're travelling a long distance it will happen that you need to find a gas station, and probably you want to find the cheapest or the closest one. Car drivers need to know the different prices and precise position of gas stations in their neighboring area or anywherelse. In order to do this, they use EZGas that allows to:

1 - collect prices of fuels in different gas stations;<br />
2 - locate gas stations in an area.

Each user can use the app also to send a feedback about reliability of information of a specific gas station. If a user has a registered account, he can also update the price for a specific fuel type for a certain gas station and, possibly, its location. By doing this, the registered user can collect points to obtain coupons. Moreover, a registered user can have a list of its favourite gas stations and receive notifications if changes occur to those gas stations.


# Stakeholders


| Stakeholder name  | Description | 
| ----------------- |:-----------:|
| Unregistered User	|Can find a gas station based on its location or prices; can send a feedback about correctness of gas station data; can signal a gas station closure| 
| Registered User 	| Can insert a gas station and insert/modify fuel price. By doing this, it collects points to obtain coupon| 
| GoogleMaps	    |External service used to map user and gas stations|


# Context Diagram and interfaces

## Context Diagram


```plantuml
left to right direction
actor "Unregistered User" as uu
actor "Registered User" as ru
actor GoogleMaps as gm
uu -- (EZGas) 
ru -- (EZGas)
gm <=> (EZGas)
```

## Interfaces

| Actor | Logical Interface | Physical Interface  |
| ------------- |:-------------:| -----:|
| User (both types)	| GUI |Touchscreen     |
| GoogleMaps	    | API |Internet        |

# Stories and personas
\<A Persona is a realistic impersonation of an actor. Define here a few personas and describe in plain text how a persona interacts with the system>

\<Persona is-an-instance-of actor>

\<stories will be formalized later as use cases>

Tom is a bank worker who has been transferred in a office pretty far from his house. The bank has not provided Tom with a company car, so he must use his own vehicle. He would like to know what are the gas stations along the road between his house and the bank and which are the ones with the lower prices. He also would like to communicate this information to his colleagues and friends, in an efficient way. He discovers a new app, EZGas, where he can find gas stations located around his position and check their prices. He can also leave a positive/negative feedback about the gas station. Moreover, he decides to register an account. By doing so, he can also update fuels prices or insert a new gas station. In this way he obtains points that can be converted in coupons to get free fuel. 

Jess is a car driver that just wants to save some money on fuel. She uses EZGas to choose the cheapest gas station in the area where she is, but she is not interested in supporting this system. Therefore, she has not an account and can't update prices or notify the presence of a new gas station; however, she can signal any kind of error about information of a gas station, for example if it's closed.

# Functional and non functional requirements

## Functional Requirements

<In the form DO SOMETHING, or VERB NOUN, describe high level capabilities of the system>

<will match to high level use cases>

| ID        | Description  |
| ------------- |:-------------:| 
|  FR1      |Manage operations of registration, log in and log out|  
|  FR2      |Every user can visualize information of a gas station|
|  FR3      |Every user can visualize the list of the closest gas stations|
|  FR4     |Every user can search gas stations located in an area selected by the user itself directly on the map  |             
|  FR5      |Every user can visualize the list of the cheapest gas stations|
|  FR6      |Every user can get from GoogleMaps the route to the selected gas station|
|  FR7      |Every user can send a feedback about data of a specific gas station (price, location, ...)|
|  FR8      |Registered user can insert a fuel type price for a gas station|
|  FR9     |Registered user can add a new gas station|
|  FR10     |Every user can signal a gas station closure|
|  FR11     |Registered user can see the points he collected and their equivalent money value in his wallet|
|  FR12     |Registered user can print the coupon|
|  FR13     |Registered user can delete his account|
|  FR14     |Registered user can update its profile and settings|
|  FR15     |Registered user can insert a gas station into a favourite list|
|  FR16     |Send a notification to registered user when one of his favourites gas stations' price is updated |
|  FR17     | Every user can view the list of gas stations along a specific route |

## Non Functional Requirements

<Describe constraints on functional requirements>

| ID        | Type (efficiency, reliability, ..)           | Description  | Refers to |
| ------------- |:-------------:| :-----:| -----:|
|  NFR1     | Performance   | All functions should be completed in < 0.5 sec  			                                           | All FR   |
|  NFR2     | Portability   | The application must be available on every OS 						                               | All FR   |
|  NFR3     | Functionality | Every user can send one feedback a day for each gas station                                          | FR7      |
|  NFR4     | Functionality | A feedback can be sent only if the user is located at most 3 km from the selected gas station        | FR7      |
|  NFR5  | Localisation |Prices are expressed in EUR, USD,GBP (according to user's location)  | FR2, FR5, FR7, FR8, FR9, FR11, FR12 |
|  NFR6     | Usability | When an user notifies a closure  or a registered user inserts a new gas station, it's necessary to attach a photo of the gas station and check if his location is around 500m|FR9, FR10|
|  NFR7	   | Localisation | Points are integer values |FR7, FR8, FR9, FR10, FR11|
|  NFR8     | Usability |Registered user receives points when he insert a new price. Points are computing according to this time parameter:  p= (timestamp_lastupdate-timestamp_now). The older the last update , the higher the number of points (p=24h -> 10 points; p=48h->15 points; ...) |FR8 |
|  NFR9     | Usability |Registered user receives 50 points when the insert of a gas station or the signal of errors about it is correctly verified. |FR7, FR9, FR10|
| NFR10    | Usability | When a specific route is defined, the ' information of the gas stations is about those located within a range of 1 km from the route | FR17 |


# Use case diagram and use cases


## Use case diagram
\<define here UML Use case diagram UCD summarizing all use cases, and their relationships>

```plantuml
left to right direction
actor "Registered user" as ru
actor "Unregistered user" as uu
actor GoogleMaps as gm
uu -- (FR3 Visualize the closest gas stations)
uu -- (FR4 Visualize the gas stations in a specific area)
uu -- (FR5 Visualize the cheapest gas stations)
(FR3 Visualize the closest gas stations) --> (FR2 Visualize gas station info)
(FR4 Visualize the gas stations in a specific area) --> (FR2 Visualize gas station info)
(FR5 Visualize the cheapest gas stations) --> (FR2 Visualize gas station info)
(FR2 Visualize gas station info) --> (FR6 Get from GoogleMaps the route)
(gm) --> (FR6 Get from GoogleMaps the route)
uu -- (FR7 Send a feedback)
uu -- (FR10 Signal a gas station closure)
(FR10 Signal a gas station closure) --> (gm)
uu -- (FR17 View gas stations along a specific route)
(gm) --> (FR17 View gas stations along a specific route)
ru --> uu
ru -- (FR8 Insert a fuel type price)
ru -- (FR9 Add a gas station)
(FR9 Add a gas station) --> (gm)
ru -- (FR11 See the points collected)
(FR11 See the points collected) --> (FR12 Print a coupon)
ru -- (FR13 Delete account)
ru -- (FR14 Update profile)
ru -- (FR15 Insert a gas station into a favourite list)
```

\<next describe here each use case in the UCD>
### Use case 1, UC1
Registration, login, logout

| Actors Involved        | Registered user |
| ------------- |:-------------:| 
|  Precondition     | |  
|  Post condition     | |
|  Nominal Scenario     | |
|  Variants     |in case of registration errors or login errors issue a warning |

##### Scenario 1.1 

Registration

| Scenario 1.1 | |
| ------------- |:-------------:| 
|  Precondition     | Account does not exist |
|  Post condition     | Account exists |
| Step#        | Description  |
|  1     | The user clicks to the registration button  |  
|  2     | He fills a form with all required information |
|  3     |  He has an account |

##### Scenario 1.2

Login

| Scenario 1.2 | |
| ------------- |:-------------:| 
|  Precondition     | User is not logged in|
|  Post condition     | User is logged in |
| Step#        | Description  |
|  1     | The  user clicks to the login button  |  
|  2     | He inserts username and password |
|  3     |  He is logged |

##### Scenario 1.3

Logout

| Scenario 1.3 | |
| ------------- |:-------------:| 
|  Precondition     | User logged in|
|  Post condition     | User is not logged in |
| Step#        | Description  |
|  1     | The user clicks to the logout button  |  
|  3     |  He is not logged anymore |

### Use case 2, UC2

Visualize the list of gas stations

| Actors Involved        | User, Google Maps |
| ------------- |:-------------:| 
|  Precondition     | Map M exists |  
|  Post condition     |  Gas stations' positions are in a specific area |
|  Nominal Scenario     |The user opens the app, the map is retrieved by the map system and the gas stations (with their prices) are list on the map. |
|  Variants     | The area can be retrieved automatically (based on user's GPS location) or it can be defined by the user  |

##### Scenario 2.1

Visualize the list of gas stations around user's GPS location

| Scenario 2.1 | |
| ------------- |:-------------:| 
|  Precondition     | User GPS should be activated|
|  Post condition     | All the gas stations are in a range of 10 km around the user position |
| Step#        | Description  |
|  1     | The  user opens the app  |  
|  2     | The GPS signal is captured |
|  3     | The map is retrieved by GoogleMaps |
|  4     | The gas stations are selected and listed with their prices on the map|
|  5     | The cheapest and the most expensive gas stations are highlighted|

##### Scenario 2.2

Visualize the list of gas stations in a user-defined area

| Scenario 2.2 | |
| ------------- |:-------------:| 
|  Precondition     | User GPS should be activated|
|  Post condition     | All the gas stations are in a range defined by user |
| Step#        | Description  |
|  1     | The  user opens the app  |  
|  2     | The map is retrieved by GoogleMaps |
|  3     | The user defines an area of the map he is interested in |
|  4     | The gas stations are selected and listed with their prices on the map|
|  5     | The cheapest and the most expensive gas stations are highlighted|

### Use case 3, UC3

Get the route 

| Actors Involved        | User, Google Maps |
| ------------- |:-------------:| 
|  Precondition     | Map M exists, Gas station G exists |  
|  Post condition     | User's location <= G's location + 500mt |
|  Nominal Scenario     |The user chooses a gas station on the list and the GoogleMaps system gets a route for it. |
|  Variants     | |

##### Scenario 3.1

| Scenario 3.1 | |
| ------------- |:-------------:| 
|  Precondition     | User GPS should be activated|
|  Post condition     | User's position <= G's position + 500mt |
| Step#        | Description  |
|  1     | The  user chooses a gas station G  |  
|  2     | The user presses the route button |
|  3     | User's location and G's location are sent to GoogleMaps  |
|  4     | GoogleMaps provides a route|
|  5     | User follows this route and he reaches the gas station G|

### Use case 4, UC4

Manage Feedback about prices

| Actors Involved        | User |
| ------------- |:-------------:| 
|  Precondition     | Map M exists, Gas station G exists, User's location < G's location + 3 km, User has not already expressed a feedback for G on that day |  
|  Post condition     |User can no longer express a feedback for G on that day |
|  Nominal Scenario     |The user chooses a gas station in a range of 3km around him and he send a feedback (positive/negative) about the correctness of prices. |
|  Variants     | If the user is a registered user, he receives points|

##### Scenario 4.1

| Scenario 4.1 | |
| ------------- |:-------------:| 
|  Precondition     |Map M exists, Gas station G exists, User's location < G's location + 3 km, User has not already expressed a feedback for G on that day|
|  Post condition     | User can no longer express a feedback for G on that day |
| Step#        | Description  |
|  1     | The  user chooses a gas station G  |  
|  2     | The user presses one of the feedback's buttons (up/down) |
|  3     | If the user is a registered user, he receives points|

### Use case 5, UC5

Manage Feedback about gas station's information (location, ...)

| Actors Involved        | User |
| ------------- |:-------------:| 
|  Precondition     | Map M exists, Gas station G exists, User's location < G's location + 3 km |  
|  Post condition     | |
|  Nominal Scenario     |The user chooses a gas station in a range of 3km around him and he notify an error about gas station's information |
|  Variants     | If the user is a registered user, he receives points|

##### Scenario 5.1

| Scenario 5.1 | |
| ------------- |:-------------:| 
|  Precondition     |Map M exists, Gas station G exists |
|  Post condition     | |
| Step#        | Description  |
|  1     | The  user choices a gas station G  |
|  2     | The user presses a button to signal an error |
|  3     | The user inserts all the information required about the error|
|  3     | If the user is a registered user, he receives points|

### Use case 6, UC6

Insert/modify a fuel type price for a gas station

| Actors Involved        | Registered User |
| ------------- |:-------------:| 
|  Precondition     | Log-in successful, User's location < G's location + 3 km |  
|  Post condition     | Gas station updated |
|  Nominal Scenario     |The registered user chooses a gas station in a range of 3km around him and inserts a fuel type price |
|  Variants     | Error message if log-in fails |

#### Scenario 6.1

| Scenario 6.1 | |
| ------------- |:-------------:| 
|  Precondition     |User has an account, Gas station G exists |
|  Post condition     | Data recorded |
| Step#        | Description  |
|  1     | The  user choices a gas station G  |
|  2     | The user presses a button to insert/modify a fuel type price |
|  3     | The user inserts all the information needed |
|  4	 | New information is now available to every other user |
|  5	 | The registered user receives an amount of points base on rule in NFR10 | 

### Use case 7, UC7

Add a new gas station

| Actors Involved        | Registered User |
| ------------- |:-------------:| 
|  Precondition     | Log-in successful, User's location < Selected location + 500 m |  
|  Post condition     | Gas station inserted |
|  Nominal Scenario     | The registered user inserts a new gas station with as many information as possible, providing also a photo |
|  Variants     | Error message if log-in fails |

#### Scenario 7.1

| Scenario 7.1 | |
| ------------- |:-------------:| 
|  Precondition     |User has an account|
|  Post condition     | Data recorded |
| Step#        | Description  |
|  1     | The  user selects a point in the map where there should be a gas station  |
|  2     | The user presses a button to insert the gas station |
|  3     | The user inserts all the information needed, together with a photo |
|  4	 | New gas station now appears in the map to every other user |
|  5	 | Once existence of the gas station will be correctly verified, the user will receive 50 points |

### Use case 8, UC8

Signal a gas station closure

| Actors Involved        | User |
| ------------- |:-------------:| 
|  Precondition     |Gas Station G exists,  User's location < G' location + 500 m |  
|  Post condition     | Gas station signaled as closed |
|  Nominal Scenario     | The user signals a gas station closure, providing also a photo |
|  Variants     |If the user is a registered user, he receives points |

#### Scenario 8.1

| Scenario 8.1 | |
| ------------- |:-------------:| 
|  Precondition     |Gas Station G exists|
|  Post condition     | |
| Step#        | Description  |
|  1     | The  user selects a gas station in the map |
|  2     | The user presses a button to signal the closure of the gas station |
|  3     | The user provides also a photo |
|  4	 | If correctly verified, the gas station disappears from the map
|  5     | If the user is a registered user, he receives 50 points|

### Use case 9, UC9

Delete an account

| Actors Involved        | Registered User |
| ------------- |:-------------:| 
|  Precondition     | Log-in successful |  
|  Post condition     | Account deleted |
|  Nominal Scenario     | The user selects delete option |
|  Variants     | Error message if log-in fails |

#### Scenario 9.1

| Scenario 9.1 | |
| ------------- |:-------------:| 
|  Precondition     |User has an account|
|  Post condition     | |
| Step#        | Description  |
|  1     | The  user selects setting and option |
|  2     | The user presses a button to delete his account |
|  3     | The user will no longer be able to log with the deleted profile |

### Use case 10, UC10

Update profile

| Actors Involved        | Registered User |
| ------------- |:-------------:| 
|  Precondition     | Log-in successful |  
|  Post condition     | Profile updated |
|  Nominal Scenario     | The user can modify different information like username, password, email, telephone number, date of birth |
|  Variants     | Error message if log-in fails |

#### Scenario 10.1

| Scenario 10.1 | |
| ------------- |:-------------:| 
|  Precondition     |User has an account|
|  Post condition     | |
| Step#        | Description  |
|  1     | The  user selects setting and option |
|  2     | The user presses a button to modify his profile information |
|  3     | Information updated |

### Use case 11, UC11

Insert gas station in the favourite list

| Actors Involved        | Registered User |
| ------------- |:-------------:| 
|  Precondition     | Log-in successful |  
|  Post condition     | Gas station appears in the favourite list |
|  Nominal Scenario     | The user selects a gas station and press the option 'add to favourite' |
|  Variants     | Error message if log-in fails |

#### Scenario 11.1

| Scenario 11.1 | |
| ------------- |:-------------:| 
|  Precondition     |User has an account, Gas station G exists |
|  Post condition     | List updated |
| Step#        | Description  |
|  1     | The  user selects a gas station from the map |
|  2     | The user presses a button to insert the gas station in the list of the favourite ones |
|  3     | The gas station will appear in the list |

### Use case 12, UC12

View the list of gas stations along a specif route

| Actors Involved        |  User |
| ------------- |:-------------:| 
|  Precondition     | Map M exists |  
|  Post condition     |Route and list of gas stations are generated |
|  Nominal Scenario     | The user selects a destination, a route is generated with a list of gas stations along it |
|  Variants     |  |

#### Scenario 12.1

| Scenario 12.1 | |
| ------------- |:-------------:| 
|  Precondition     |Map M exists |
|  Post condition     | Route and list of gas stations are generated|
| Step#        | Description  |
|  1     | The  user selects the destination |
|  2     | The route is generated by GoogleMaps|
|  3     | Select the gas stations located within a range of 1 km from the route |
|  4     | The route and the list of gas stations are displayed|


# Glossary
```plantuml
@startuml
Class EZGas{}
Class GoogleMaps{}
note top of GoogleMaps : "System that provides\n maps to EZGas"
Class UnregisteredUser{
ID
GPS Location
}
note top of UnregisteredUser : "User that uses the application\n without an account"
Class RegisteredUser{
Fiscal Code
Name
Surname
Date of birth
Email
Telephone Number
}
note top of RegisteredUser : "User that uses the application\n with an account"
Class Account{
Username
Password
OverallPoints
}

Class GasStation{
ID
Brand
Name
Location
}
note top of GasStation : "Place where car drivers\n can refuel their car"
Class FuelType{
Name
}
note top of FuelType : "i.e. GPL, Diesel ,..."

Class PriceLog{
Amount
Date
Points
}
note bottom of PriceLog : "It is the price specification\n for a specific fuel type\n for a certain gas station"

Class PriceFeedback{
value
date
}
note top of PriceFeedback : "It is a feedback about\n a PriceLog correctness"


Class RegisteredPriceFeedback{
points
}
note top of RegisteredPriceFeedback : "It gives points to the registered user"
Class ErrorLog{
Type
Date
Value
Photo
}
note top of ErrorLog : "It is a feedback about correctness\n of the information of a gas station\n (location error, closure,...).\n (the attribute "photo" is optional)"
Class RegisteredErrorLog{
Points
}
note bottom of RegisteredErrorLog: "It gives points only to registered user"
Class NewStationLog{
Date
Photo
Points
}
note top of NewStationLog : "It contains the information\n about the new gas station \nsignaled by the user.\n It gives points to user"
EZGas -- GoogleMaps
EZGas -- "*" UnregisteredUser : uses
EZGas -- "*" GasStation : recorded into
UnregisteredUser <|-- RegisteredUser
RegisteredUser -- Account : has
Account -- "0..*" PriceLog : records
PriceLog "0..*" -- FuelType : for a
PriceLog "0..*" -- GasStation : for a
FuelType "1..*" --  "0..*" GasStation : provides

Account -- "0..*" RegisteredErrorLog : sends
UnregisteredUser -- "0..*" ErrorLog : sends
ErrorLog "0..*" -- GasStation : for a
ErrorLog <|-- RegisteredErrorLog
Account -- "0..*" NewStationLog : sends
NewStationLog "0..1" -- GasStation : for a
NewStationLog o-- "*" PriceLog
UnregisteredUser --  PriceFeedback : sends
PriceFeedback "0..*"-- PriceLog : for a
PriceFeedback <|-- RegisteredPriceFeedback

Account --  RegisteredPriceFeedback : sends


RegisteredPriceFeedback "0..*"-- PriceLog : for a
@enduml
```
# System Design


```plantuml
@startuml
Class EZGas 
Class Database 
 
Class ApplicationServer
EZGas *-- Database

EZGas *-- ApplicationServer
@enduml
```

# Deployment Diagram 

```plantuml
@startuml
node "Application Server" as as{
artifact "EZGas"
}
node "Smartphone/PC client" as sc{
artifact "EZGas Client"
}
node "Map System" as m
node "Database" as d
d--as : internet
m--as : internet
as -- "*" sc : internet
@enduml
```
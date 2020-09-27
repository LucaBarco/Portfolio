# Design Document 

Authors:<br />
Barco Luca<br />Di Vincenzo Alessandro<br />Pappalardo Marco Giulio Lorenzo<br />Petruzzi Rocco Luigi<br />

Date:<br />03/05/2020

Version:


# Contents

- [High level design](#package-diagram)
- [Low level design](#class-diagram)
- [Verification traceability matrix](#verification-traceability-matrix)
- [Verification sequence diagrams](#verification-sequence-diagrams)

# Instructions

The design must satisfy the Official Requirements document (see EZGas Official Requirements.md ). <br>
The design must comply with interfaces defined in package it.polito.ezgas.service (see folder ServicePackage ) <br>
UML diagrams **MUST** be written using plantuml notation.

# High level design 

The style selected is client - server. Clients can be smartphones, tablets, PCs.
The choice is to avoid any development client side. The clients will access the server using only a browser. 

The server has two components: the frontend, which is developed with web technologies (JavaScript, HTML, Css) and is in charge of collecting user inputs to send requests to the backend; the backend, which is developed using the Spring Framework and exposes API to the front-end.
Together, they implement a layered style: Presentation layer (front end), Application logic and data layer (back end). 
Together, they implement also an MVC pattern, with the V on the front end and the MC on the back end.



```plantuml
@startuml
package "Backend" {

}

package "Frontend" {

}


Frontend -> Backend
@enduml


```


## Front End

The Frontend component is made of: 

Views: the package contains the .html pages that are rendered on the browser and that provide the GUI to the user. 

Styles: the package contains .css style sheets that are used to render the GUI.

Controller: the package contains the JavaScript files that catch the user's inputs. Based on the user's inputs and on the status of the GUI widgets, the JavaScript controller creates REST API calls that are sent to the Java Controller implemented in the back-end.


```plantuml
@startuml
package "Frontend" {

    package "it.polito.ezgas.resources.views" {

    }


package "it.polito.ezgas.resources.controller" {

    }


package "it.polito.ezgas.resources.styles" {

    }



it.polito.ezgas.resources.styles -down-> it.polito.ezgas.resources.views

it.polito.ezgas.resources.views -right-> it.polito.ezgas.resources.controller


}
@enduml

```

## Back End

The backend  uses a MC style, combined with a layered style (application logic, data). 
The back end is implemented using the Spring framework for developing Java Entrerprise applications.

Spring was selected for its popularity and relative simplicity: persistency (M and data layer) and interactions are pre-implemented, the programmer needs only to add the specific parts.

See in the package diagram below the project structure of Spring.

For more information about the Spring design guidelines and naming conventions:  https://medium.com/the-resonant-web/spring-boot-2-0-project-structure-and-best-practices-part-2-7137bdcba7d3



```plantuml
@startuml
package "Backend" {

package "it.polito.ezgas.service"  as ps {
   interface "GasStationService"
   interface "UserService"
} 


package "it.polito.ezgas.controller" {

}

package "it.polito.ezgas.converter" {

}

package "it.polito.ezgas.dto" {

}

package "it.polito.ezgas.entity" {

}

package "it.polito.ezgas.repository" {

}

    
}
note "see folder ServicePackage" as n
n -- ps
```



The Spring framework implements the MC of the MVC pattern. The M is implemented in the packages Entity and Repository. The C is implemented in the packages Service, ServiceImpl and Controller. The packages Dto and Converter contain classes for translation services.



**Entity Package**

Each Model class should have a corresponding class in this package. Model classes contain the data that the application must handle.
The various models of the application are organised under the model package, their Dtos(data transfer objects) are present under the dto package.

In the Entity package all the Entities of the system are provided. Entities classes provide the model of the application, and represent all the data that the application must handle.




**Repository Package**

This package implements persistency for each Model class using an internal database. 

For each Entity class, a Repository class is created (in a 1:1 mapping) to allow the management of the database where the objects are stored. For Spring to be able to map the association at runtime, the Repository class associated to class "XClass" has to be exactly named "XClassRepository".

Extending class JpaRepository provides a lot of CRUD operations by inheritance. The programmer can also overload or modify them. 



**Dto package**

The Dto package contains all the Dto classes. Dto classes are used to transfer only the data that we need to share with the user interface and not the entire model object that we may have aggregated using several sub-objects and persisted in the database.

For each Entity class, a Dto class is created (in a 1:1 mapping).  For Spring the Dto class associated to class "XClass" must be called "XClassDto".  This allows Spring to find automatically the Dto class having the corresponding Entity class, and viceversa. 




**Converter Package**

The Converter Package contains all the Converter classes of the project.

For each Entity class, a Converter class is created (in a 1:1 mapping) to allow conversion from Entity class to Dto class and viceversa.

For Spring to be able to map the association at runtime, the Converter class associated to class "XClass" has to be exactly named "XClassConverter".




**Controller Package**

The controller package is in charge of handling the calls to the REST API that are generated by the user's interaction with the GUI. The Controller package contains methods in 1:1 correspondance to the REST API calls. Each Controller can be wired to a Service (related to a specific entity) and call its methods.
Services are in packages Service (interfaces of services) and ServiceImpl (classes that implement the interfaces)

The controller layer interacts with the service layer (packages Service and ServieImpl) 
 to get a job done whenever it receives a request from the view or api layer, when it does it should not have access to the model objects and should always exchange neutral Dtos.

The service layer never accepts a model as input and never ever returns one either. This is another best practice that Spring enforces to implement  a layered architecture.



**Service Package**


The service package provides interfaces, that collect the calls related to the management of a specific entity in the project.
The Java interfaces are already defined (see file ServicePackage.zip) and the low level design must comply with these interfaces.


**ServiceImpl Package**

Contains Service classes that implement the Service Interfaces in the Service package.










# Low level design

```plantuml
@startuml
left to right direction
skinparam linetype ortho
skinparam nodesep 5
skinparam ranksep 10
Package it.polito.ezgas.controller{
Class UserController{
    UserDto getUserById()
    List<UserDto> getAllUsers()
    UserDto saveUser()
    Boolean deleteUser()
    Integer increaseUserReputation() 
    Integer decreaseUserReputation()
    LoginDto login()

}
Class GasStationController{
   GasStationDto getGasStationById()
   List<GasStationDto> getAllGasStations()
   void saveGasStation()
   void deleteGasStation()
   List<GasStationDto> getGasStationsByGasolineType()
   List<GasStationDto> getGasStationsByProximity()
   List<GasStationDto> getGasStationsWithCoordinates()
   void setGasStationReport()


}
}

package it.polito.ezgas.entity{


class User {
 Integer userId
 String userName
 String password
 String email
 Integer reputation
 Boolean admin

void setUserId()
void setUserName()
void setPassword()
void setEmail()
void setReputation()
void setAdmin()
Integer getUserId()
String getUserName()
String getPassword()
String getEmail()
Integer getReputation()
Boolean getAdmin()
}

class GasStation {
 Integer gasStationId
 String gasStationName
 String gasStationAddress
 String carSharing
 boolean hasDiesel
 boolean hasSuper
 boolean hasSuperPlus
 boolean hasGas
 boolean hasMethane
 boolean hasDieselPremium
 double lat
 double lon
 double dieselPrice
 double superPrice
 double superPlusPrice
 double gasPrice
 double methanePrice
 double dieselPremiumPrice
 double reportDependability
 String reportTimestamp
 Integer reportUser 
 User user

 void setGasStationId()
 void setGasStationName()
 void setGasStationAddress()
 void setReportDependability()
 void setReportUser()
 void setReportTimestamp()
 void setHasDiesel()
 void setHasSuper()
 void setHasSuperPlus()
 void setHasGas()
 void setLat()
 void setLon()
 void setDieselPrice()
 void setSuperPrice()
 void setSuperPlusPrice()
 void setGasPrice()
 void setUser()
 void setHasMethane() 
 void setMethanePrice()
 void setHasDieselPremium()
 void setdieselPremiumPrice()
 void setCarSharing()
 String getGasStationId()
 String getGasStationName()
 String getGasStationAddress()
 double getReportDependability()
 Integer getReportUser()
 String getReportTimestamp()
 boolean getHasDiesel()
 boolean getHasSuper()
 boolean getHasSuperPlus()
 boolean getHasGas()
 double getLat()
 double getLon()
 double getDieselPrice()
 double getSuperPrice()
 double getSuperPlusPrice()
 double getGasPrice()
 User getUser()
 boolean getHasMethane()
 double getMethanePrice()
 boolean getHasDieselPremium()
 double getdieselPremiumPrice()
 String getCarSharing()
}

User"0..1"--GasStation

}

Package it.polito.ezgas.repository{
class UserRepository{ 
User findOne()
User findByEmail()
List<User> findAll()
User saveAndFlush()
User delete()

}
class GasStationRepository{
GasStation findOne()
List<GasStation> findAll()
void delete()
GasStation saveAndFLush()
GasStation findBygasStationName()
List<GasStation> findBylatBetweenAndLonBetween()
List<GasStation> findByhasDiesel()
List<GasStation> findByhasSuper()
List<GasStation> findByhasGas()
List<GasStation> findByhasSuperPlus()
List<GasStation> findByhasMethane()
List<GasStation> findByhasDieselAndCarSharing()
List<GasStation> findByhasSuperAndCarSharing()
List<GasStation> findByhasGasAndCarSharing()
List<GasStation> findByhasSuperPlusAndCarSharing()
List<GasStation> findByhasMethaneAndCarSharing()
List<GasStation> findByCarSharing()
}



}

Package it.polito.ezgas.converter{
class UserConverter{
    UserDto toUserDto()
    User toUser()
    List<User> toUserList()
    List<UserDto> toUserDtoList()
}
class GasStationConverter{
   GasStationDto toGasStationDto()
   GasStation toGasStation()
   List<GasStation> toGasStationDtoList()
   List<GasStationDto> toGasStationList()
}

}

Package it.polito.ezgas.dto{
    class IdPw{
    String user
    String psw
    
	void setUser()
    void setPw()
    String getUser() 
	String getPw()
	
}
Class LoginDto{
    Integer userId
    String userName
    String token
    String email
    Integer reputation
    Boolean admin
    
	void setUserId()
    void setUserName()
    void setToken()
    void setEmail()
    void setReputation()
    void setAdmin()
    Integer getUserId() 
	String getUserName() 
	String getToken() 
	String getEmail() 
	Integer getReputation() 
    Boolean getAdmin()
    

}
Class UserDto{
    Integer userId
    String userName
    String password
    String email
    Integer reputation
    Boolean admin
    void setUserId()
    void setUserName()
    void setPassword()
    void setEmail()
    void setReputation()
    void setAdmin()
    Integer getUserId()
    String getUserName()
    String getPassword()
    String getEmail()
    Integer getReputation()
    Boolean getAdmin()
}
Class GasStationDto{
 Integer gasStationId
 String gasStationName
 String gasStationAddress
 boolean hasDiesel
 boolean hasSuper
 boolean hasSuperPlus
 boolean hasGas
 boolean hasMethane
 boolean hasPremiumDiesel
 String carSharing
 double lat
 double lon
 double dieselPrice
 double superPrice
 double superPlusPrice
 double gasPrice
 double methanePrice
 double premiumDieselPrice
 Integer reportUser
 UserDto userDto
 String reportTimestamp
 double reportDependability
 
 void setReportDependability()
 void setGasStationId()
 void setGasStationName()
 void setGasStationAddress()
 void setHasDiesel()
 void setDieselPrice()
 void setHasSuper()
 void setSuperPrice()
 void setHasSuperPlus()
 void setSuperPlusPrice()
 void setHasGas()
 void setGasPrice()
 void setHasMethane()
 void setMethanePrice()
 void setHasDieselPremium()
 void setDieselPremiumPrice()
 void setReportUser()
 void setReportTimestamp()
 void setLat()
 void setLon()
 void setUserDto()
 void setCarSharing()
 double getReportDependability()
 Integer getGasStationId()
 String getGasStationName()
 String getGasStationAddress()
 boolean getHasDiesel()
 double getDieselPrice()
 boolean getHasSuper() 
 double getSuperPrice()
 Boolean getHasSuperPlus()
 double getSuperPlusPrice()
 Boolean getHasGas()
 double getGasPrice()
 boolean getHasMethane()
 double getMethanePrice()
 boolean getHasDieselPremium()
 double getDieselPremium()
 Integer getReportUser()
 String getReportTimestamp()
 UserDto getUserDto()
 double getLat()
 double getLon() 
 String getCarSharing()
}
Class PriceReportDto{
 Integer gasStationId
 double dieselPrice
 double superPrice
 double superPlusPrice
 double gasPrice
 double methanePrice
 double premiumDieselPrice
 Integer userId
 
 
 void setGasStationId()
 void setDieselPrice()
 void setSuperPrice()
 void setSuperPlusPrice()
 void setGasPrice()
 void setMethanePrice()
 void setDieselPremiumPrice()
 void setUserId()
 Integer getGasStationId()
 double getDieselPrice()
 double getSuperPrice()
 double getSuperPlusPrice()
 double getGasPrice()
 double getMethanePrice()
 double getDieselPremium()
 Integer getUserID()

}
}

Package it.polito.ezgas.service{
Interface GasStationService{
}
Interface UserService{
}
}

Package it.polito.ezgas.serviceimpl {
 Class GasStationServiceImp{
    GasStationRepository gasStationRepository
    GasStationConverter gasStationConverter
    UserRepository UserRepository
    boolean updateDependability 

    GasStationDto getGasStationById()
    List<GasStationDto> getAllGasStations()
    List<GasStationDto> getGasStationsByGasolinType()
    List<GasStationDto> getGasStationsByProximity()
    List<GasStationDto> getGasStationsByProximity()
    List<GasStationDto> getGasStationsWithCoordinates()
    List<GasStationDto> getGasStationsWithoutCoordinates()
    List<GasStationDto> getGasStationByCarSharing()
    GasStationDto saveGasStation()
    boolean deleteGasStation()
    void setReport()
    void checkCarSharing()
    void checkPriceList()
    void checkCoordinates()
    void calculateDependability()
 }
 Class UserServiceImp{
    UserRepository userRepository
    UserConverter userConverter

    UserDto getUserById()
    UserDto saveUser()
    List<UserDto> getAllUsers()
    Boolean deleteUser()
    LogiDto login()
    Integer increaseUserReputation()
    Integer decreaseUserReputation()
 }
}


UserService <|-- UserServiceImp
GasStationService <|-- GasStationServiceImp

UserServiceImp -- User
UserServiceImp -- UserConverter


UserConverter -- User
GasStationConverter-- GasStation


UserConverter -- UserDto
GasStationConverter-- GasStationDto

GasStationRepository --"*" GasStation
UserRepository --"*" User

UserDto "*"-- UserServiceImp

GasStationServiceImp --"*" GasStation
GasStationServiceImp -- GasStationConverter

GasStationDto "*"- GasStationServiceImp


UserController -- UserService
GasStationController -- GasStationService

@enduml
```



# Verification traceability matrix


|   | UserController | GasStationController | User  | GasStation | UserRepository | GasStationRepository | UserConverter | GasStationConverter | IdPw | LoginDto | UserDto | GasStationDto | GasStationServiceImp | UserServiceImp |
|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
| FR1.1  |  X  |     |  X  |     |  X  |     |  X  |     |  X  |  X  |  X  |     |     |  X  |  
| FR1.2  |  X  |     |  X  |     |  X  |     |  X  |     |  X  |  X  |  X  |     |     |  X  |
| FR1.3  |  X  |     |  X  |     |  X  |     |  X  |     |  X  |  X  |  X  |     |     |  X  |
| FR1.4  |  X  |     |  X  |     |  X  |     |  X  |     |  X  |  X  |  X  |     |     |  X  |
| FR2    |  X  |     |     |     |     |     |     |     |  X  |  X  |  X  |     |     |  X  |
| FR3.1  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR3.2  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR3.3  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR4.1  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR4.2  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR4.3  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR4.4  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR4.5  |     |  X  |     |  X  |     |  X  |     |  X  |     |     |     |  X  |  X  |     |
| FR5.1  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |     |     |  X  |  X  |  X  |  X  |
| FR5.2  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |     |     |  X  |  X  |  X  |  X  |
| FR5.3  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |     |     |  X  |  X  |  X  |  X  |

# Verification sequence diagrams 

## UC1 - Create User Account
```plantuml
@startuml
        FrontEnd --> UserController : createUser(userDto)
        UserController -> UserService : saveUser(userDto)
        UserService -> UserConverter : toUser(userDto)
        UserConverter -> User: new(...)
        User -> UserConverter: user
        UserConverter -> UserService : user
        UserService -> UserRepository: save(user)
        UserService -> UserController: userDto
        UserController -> FrontEnd: userDto
@enduml
```
## UC2 - Modify user account
```plantuml
@startuml
    FrontEnd --> UserController : modifyUser(userDto)
    UserController -> UserService: saveUser(userDto)
    UserService -> UserConverter: toUser(userDto)
    UserConverter -> User: new(...)
    User -> UserConverter: user
    UserConverter -> UserService : user
    UserService -> UserRepository: save(user)
    UserService -> UserConverter: toDto(user)
    UserConverter -> UserDto: new(...)
    UserDto -> UserConverter: userDto
    UserService -> UserController: userDto
    UserController -> FrontEnd: userDto
@enduml
```
## UC3 - Delete user account
```plantuml
@startuml
    @startuml
    FrontEnd -> UserController: deleteUser(userId)
    UserController -> UserService: deleteUser(userId)
    UserService -> UserRepository: delete(userId)
    UserController -> FrontEnd: booleanResult
    @enduml
@enduml
```
## UC4 - Create Gas Station 
```plantuml
@startuml
     @startuml
        FrontEnd --> GasStationController : saveGasStation(gasStationDto)
        GasStationController -> GasStationService : saveGasStation(gasStationDto)
        GasStationService -> GasStationConverter : toGasStation(gasStationDto)
        GasStationConverter -> GasStation: new(...)
        GasStation -> GasStationConverter: gasStation
        GasStationConverter -> GasStationService: gasStation
        GasStationService -> GasStationRepository: save(gasStation)
        GasStationService -> GasStationController: gasStationDto
        GasStationController -> FrontEnd: booleanResult
@enduml
```
## UC5 - Modify Gas Station information
```plantuml
@startuml
     @startuml
    FrontEnd -> GasStationController : modifyGasStation(gasStationDto)
    GasStationController ->GasStationService: saveGasStation(gasStationDto)
    GasStationService -> GasStationConverter: toGasStation(gasStationDto)
    GasStationConverter -> GasStation: new(...)
    GasStation -> GasStationConverter: gasStation
    GasStationConverter -> GasStationService: gasStation
    GasStationService -> GasStationRepository: save(gasStation)
    GasStationService -> GasStationConverter: toDto(gasStation)
    GasStationConverter -> GasStationDto: new(...)
    GasStationDto -> GasStationConverter: gasStationDto
    GasStationService -> GasStation: gasStationDto
    GasStationController -> FrontEnd: booleanResult
@enduml
```
## UC6 - Delete Gas Station
```plantuml
 @startuml
    FrontEnd -> GasStationController: deleteGasStation(gasStationId) 
    GasStationController -> GasStationService: deleteGasStation(gasStationId)
    GasStationService -> GasStationRepository: delete(gasStationId)
    GasStationController -> FrontEnd: booleanResult
@enduml
```
## UC7 - Report fuel price for a gas station
```plantuml
@startuml
    FrontEnd -> GasStationController : setGasStationReport(gasStationId,dieselPrice,superPrice,superPlusPrice,gasPrice,methanePrice,userId)
    GasStationController -> GasStationService: setReport(gasStationId,dieselPrice,superPrice,superPlusPrice,gasPrice,methanePrice,userId)
    GasStationService -> GasStationRepository: find(gasStationId)
    GasStationRepository -> GasStationService: gasStation
    GasStationService -> GasStation: gasStation.setPriceReport(gasStationId,dieselPrice,superPrice,superPlusPrice,gasPrice,methanePrice,userId)
    GasStationService -> GasStationRepository: save(GasStation)
    GasStationController -> FrontEnd: booleanResult
@enduml
```
## UC8 - Obtain price of fuel for gas stations in a certain geographic area
```plantuml
@startuml
    FrontEnd -> GasStationController : getGasStationswithCoordinates(lat,lon,gasolinetype,carsharing)
    GasStationController -> GasStationService: getGasStationsWithCoordinates(lat,lon,gasolinetype,carsharing)
    GasStationService -> GasStationRepository : findLatBetweenAndLonBetween(lat1,lat2,lon1,lon2)
    GasStationRepository -> GasStationService: List<GasStation>
    GasStationService -> GasStationConverter: toGasStationDtoList(List<GasStation>)
    GasStationConverter -> GasStationService: List<GasStatioDto>
    GasStationService -> GasStationController: List<GasStatioDto>
    GasStationController -> FrontEnd: List<GasStationDto>
@enduml

```
## UC10 - Evaluate price

### Scenario 10.1 - Increase Reputation

```plantuml
@startuml
    FrontEnd -> UserController : increaseUserReputation(userId)
    UserController -> UserService: increaseUserReputation(userId)
    UserService -> UserRepository: getOne(userId)
    UserRepository -> UserService: user
    UserService -> User: user.setReputation(user.getReputation()+1) 
    note right
            if user.getReputation()<5
    end note
    UserService -> UserRepository: save(user)
    UserService -> UserController: getReputation()
    UserController -> FrontEnd: getReputation()
@enduml
```

### Scenario 10.2 - Decrease Reputation

```plantuml
@startuml
    FrontEnd -> UserController : decreaseUserReputation(userId)
    UserController -> UserService: decreaseUserReputation(userId)
    UserService -> UserRepository: getOne(userId)
    UserRepository -> UserService: user
    UserService -> User: user.setReputation(user.getReputation()-1) 
    note right
            if user.getReputation()>-5
    end note
    UserService -> UserRepository: save(user)
    UserService -> UserController: getReputation()
    UserController -> FrontEnd: getReputation()
@enduml
```



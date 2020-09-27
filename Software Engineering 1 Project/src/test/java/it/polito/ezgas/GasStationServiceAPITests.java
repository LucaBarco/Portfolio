package it.polito.ezgas;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.test.context.junit4.SpringRunner;

import exception.GPSDataException;
import exception.InvalidCarSharingException;
import exception.InvalidGasStationException;
import exception.InvalidGasTypeException;
import exception.InvalidUserException;
import exception.PriceException;

import it.polito.ezgas.converter.GasStationConverter;
import it.polito.ezgas.converter.UserConverter;
import it.polito.ezgas.dto.GasStationDto;
import it.polito.ezgas.dto.IdPw;
import it.polito.ezgas.dto.UserDto;
import it.polito.ezgas.entity.GasStation;
import it.polito.ezgas.entity.User;
import it.polito.ezgas.repository.GasStationRepository;
import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.service.GasStationService;
import it.polito.ezgas.service.impl.GasStationServiceimpl;
import it.polito.ezgas.service.impl.UserServiceimpl;

import static org.junit.Assert.*;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@RunWith(SpringRunner.class)
@DataJpaTest
public class GasStationServiceAPITests {

	@Autowired
	private GasStationRepository gasStationRepository;
	@Autowired
	private UserRepository userRepository;

	private GasStationServiceimpl gasStationService;
	private GasStationConverter gasStationConverter;
	private GasStation gasStation;
	private GasStationDto gasStationDto;
	private UserServiceimpl userService;
	private UserConverter userConverter;
	private UserDto userDto;
	private User user;
	private IdPw credentials;

	@Before
	public void setUp() {
		gasStationConverter = new GasStationConverter();
		gasStationService = new GasStationServiceimpl(gasStationRepository, gasStationConverter, userRepository);
		userConverter = new UserConverter();
		userService= new UserServiceimpl(userRepository,userConverter);
		gasStation = new GasStation("ENI", "corso Duca", true, true, true, true, true,true, "Enjoy", 40.0005, 25.0010, 0.99,
				0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-03", 0.88);
		gasStationDto = new GasStationDto(null, "ENI", "corso Duca", true, true, true, true, true,true, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-03", 0.88);
		user = new User("nome", "password", "email", 0);
		credentials = new IdPw("user", "pwd");
		userDto = new UserDto(null, "Test", "TestPw", "Test@email", 2);
		userDto.setAdmin(false);
	}

	@After
	public void destroy() {
		gasStationRepository.deleteAll();
		userRepository.deleteAll();
	}

	@Test
	public void TC1_getGasStationById() {
		// try to get a gas station with invalid id
		Boolean thrown = false;
		try {
			gasStationService.getGasStationById(-1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_getGasStationById() {
		// try to retrieve a gas station with a non existing id
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationById(65), null);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_getGasStationById() throws PriceException, GPSDataException {
		// try to retrieve a gas station with an existing id
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		GasStationDto res = gasStationService.saveGasStation(gasStationDto);
		assertNotNull(res);
		try {
			assertNotNull(gasStationService.getGasStationById(res.getGasStationId()));
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC1_saveGasStation() {
		// try to save a gas station which has no fuels -> ERROR?
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", false, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.saveGasStation(gsDto));
			// Nota: Posso salvare la gas station anche se ho false su tutti i fuel type, ma
			// ho i prezzi?
			// Nota: Posso salvare una gas station con ID nullo o negativo? La lista
			// dovrebbe essere vuota?
//			assertEquals(gasStationService.getAllGasStations().isEmpty());
		} catch (GPSDataException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC2_saveGasStation() throws PriceException, GPSDataException {
		// saving without errors (all prices and no ID)
		Boolean thrown = false;
		gasStationDto.setGasStationId(1);
		try {
			assertEquals(gasStationDto, gasStationService.saveGasStation(gasStationDto));
		} catch (GPSDataException | PriceException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC5_saveGasStation() throws PriceException, GPSDataException {
		// try to update an already existing gas station
		GasStationDto myDto = new GasStationDto(1, gasStationDto.getGasStationName(),
				gasStationDto.getGasStationAddress(), gasStationDto.getHasDiesel(), gasStationDto.getHasSuper(),
				gasStationDto.getHasSuperPlus(), gasStationDto.getHasGas(), gasStationDto.getHasMethane(), gasStationDto.getHasPremiumDiesel(),
				gasStationDto.getCarSharing(), gasStationDto.getLat(), gasStationDto.getLon(),
				gasStationDto.getDieselPrice(), gasStationDto.getSuperPrice(), gasStationDto.getSuperPlusPrice(),
				gasStationDto.getGasPrice(), gasStationDto.getMethanePrice(),gasStationDto.getPremiumDieselPrice(), gasStationDto.getReportUser(),
				gasStationDto.getReportTimestamp(), gasStationDto.getReportDependability());
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.saveGasStation(myDto));
		} catch (GPSDataException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC6_saveGasStation() {
		// try to update an already existing gas station with wrong long and/or lat
		GasStationDto myDto = new GasStationDto(1, gasStationDto.getGasStationName(),
				gasStationDto.getGasStationAddress(), gasStationDto.getHasDiesel(), gasStationDto.getHasSuper(),
				gasStationDto.getHasSuperPlus(), gasStationDto.getHasGas(), gasStationDto.getHasMethane(), gasStationDto.getHasPremiumDiesel(),
				gasStationDto.getCarSharing(), gasStationDto.getLat(), gasStationDto.getLon(),
				gasStationDto.getDieselPrice(), gasStationDto.getSuperPrice(), gasStationDto.getSuperPlusPrice(),
				gasStationDto.getGasPrice(), gasStationDto.getMethanePrice(),gasStationDto.getPremiumDieselPrice(), gasStationDto.getReportUser(),
				gasStationDto.getReportTimestamp(), gasStationDto.getReportDependability());
		myDto.setLat(-100.0);
		myDto.setLon(200.0);
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.saveGasStation(myDto));
		} catch (GPSDataException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}
	
	@Test
	public void TC7_saveGasStation() {
		// try to update an already existing gas station with wrong price (negative)
		GasStationDto myDto = new GasStationDto(1, gasStationDto.getGasStationName(),
				gasStationDto.getGasStationAddress(), gasStationDto.getHasDiesel(), gasStationDto.getHasSuper(),
				gasStationDto.getHasSuperPlus(), gasStationDto.getHasGas(), gasStationDto.getHasMethane(), gasStationDto.getHasPremiumDiesel(),
				gasStationDto.getCarSharing(), gasStationDto.getLat(), gasStationDto.getLon(),
				gasStationDto.getDieselPrice(), gasStationDto.getSuperPrice(), gasStationDto.getSuperPlusPrice(),
				gasStationDto.getGasPrice(), gasStationDto.getMethanePrice(),gasStationDto.getPremiumDieselPrice(), gasStationDto.getReportUser(),
				gasStationDto.getReportTimestamp(), gasStationDto.getReportDependability());
		myDto.setDieselPrice(-1.69);
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.saveGasStation(myDto));
		} catch (GPSDataException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}
	
	@Test
	public void TC1_getAllGasStations() {
		// try to retrieve an empty list
		assertEquals(gasStationService.getAllGasStations().isEmpty(), true);
	}

	@Test
	public void TC2_getAllGasStations() throws PriceException, GPSDataException {
		// try to retrieve a list not empty
		//gasStationService.setUpdateDependability(true);
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		assertFalse(gasStationService.getAllGasStations().isEmpty());
	}

	@Test
	public void TC1_deleteGasStation() {
		// try to delete a gas station with a negtive id (exception)
		Boolean thrown = false;
		try {
			gasStationService.deleteGasStation(-1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_deleteGasStation() throws PriceException, GPSDataException {
		// try to delete an existing gas station
		Boolean thrown = false;
		GasStationDto res = gasStationService.saveGasStation(gasStationDto);
		try {
			assertEquals(gasStationService.deleteGasStation(res.getGasStationId()), true);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_deleteGasStation() {
		// try to delete a non existing gas station
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.deleteGasStation(1), null);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC1_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with invalid fuel type
		Boolean thrown = false;
		try {
			assertTrue(gasStationService.getGasStationsByGasolineType("water").isEmpty());
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with valid fuel type (Diesel)
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByGasolineType("diesel").isEmpty());
		} catch (InvalidGasTypeException e2) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with valid fuel type (Super)
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByGasolineType("super").isEmpty());
		} catch (InvalidGasTypeException e2) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC4_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with valid fuel type (Methane)
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByGasolineType("methane").isEmpty());
		} catch (InvalidGasTypeException e2) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC5_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with valid fuel type (Gas)
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByGasolineType("gas").isEmpty());
		} catch (InvalidGasTypeException e2) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC6_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with valid fuel type (SuperPlus)
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByGasolineType("superplus").isEmpty());
		} catch (InvalidGasTypeException e2) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC7_getGasStationsByGasolineType() throws InvalidGasTypeException {
		// try to get a gas station with valid fuel type (PremiumDiesel)
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByGasolineType("premiumdiesel").isEmpty());
		} catch (InvalidGasTypeException e2) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC1_getGasStationsByProximity() throws GPSDataException {
		// valid coordinates
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByProximity(40.0005, 25.0010).isEmpty());
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC2_getGasStationsByProximity() throws GPSDataException {
		// valid coordinates + radius<=0
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByProximity(40.0005, 25.0010, -1).isEmpty());
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC3_getGasStationsByProximity() throws GPSDataException {
		// valid coordinates + radius>0
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertFalse(gasStationService.getGasStationsByProximity(40.0005, 25.0010, 1).isEmpty());
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC4_getGasStationsByProximity() throws GPSDataException {
		// invalid coordinates
		Boolean thrown = false;
		//gasStationService.setUpdateDependability(true);
		try {
			gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			assertTrue(gasStationService.getGasStationsByProximity(999.9999, -999.9999).isEmpty());
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	// one test for each fuel type;
	@Test
	public void TC1_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// null fuel type and null car sharing -> the returned list contains
		// gasStationDto and gasStationDto2
		//gasStationService.setUpdateDependability(true);
		// radius<=0
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, true, true, true, true,true,
				"Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00, 1.32,1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		GasStationDto gasStationDto3 = new GasStationDto(null, "Shell", "via Risorgimento", false, true, true, true,true,
				true, "Car2go", 20.0005, 35.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto3));
		Boolean thrown = false;
		try {
			List<GasStationDto> list = gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,-1, "null",
					"null");
			assertEquals(list.isEmpty(), false);
			for (GasStationDto gs : list) {
				assert (gs.getGasStationName().equals(gasStationDto.getGasStationName())
						|| gs.getGasStationName().equals(gasStationDto2.getGasStationName()));
				assertFalse(gs.getGasStationName().equals(gasStationDto3.getGasStationName()));
			}

		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);

	}
	
	@Test
	public void TC2_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// null fuel type and null car sharing -> the returned list contains
		// gasStationDto and gasStationDto2
		//gasStationService.setUpdateDependability(true);
		// radius>0
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, true, true, true, true,true,
				"Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00, 1.32,1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		GasStationDto gasStationDto3 = new GasStationDto(null, "Shell", "via Risorgimento", false, true, true, true,true,
				true, "Car2go", 20.0005, 35.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto3));
		Boolean thrown = false;
		try {
			List<GasStationDto> list = gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,2, "null",
					"null");
			assertEquals(list.isEmpty(), false);
			for (GasStationDto gs : list) {
				assert (gs.getGasStationName().equals(gasStationDto.getGasStationName())
						|| gs.getGasStationName().equals(gasStationDto2.getGasStationName()));
				assertFalse(gs.getGasStationName().equals(gasStationDto3.getGasStationName()));
			}

		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);

	}
	
	@Test
	public void TC3_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// Select ANY fuel type and car sharing (Enjoy) -> one gas station matches
		// (gasStationDto)
		//gasStationService.setUpdateDependability(true);
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, true, true, true, true,true,
				"Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		GasStationDto gasStationDto3 = new GasStationDto(null, "Shell", "via Risorgimento", false, true, true, true,true,
				true, "Car2go", 20.0005, 35.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto3));
		Boolean thrown = false;
		try {
			List<GasStationDto> list = gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "null",
					"Enjoy");
			assertEquals(list.isEmpty(), false);
			for (GasStationDto gs : list) {
				System.out.println(gs);
			}
			assertEquals(list.size(), 1, 0);
			for (GasStationDto gs : list) {
				assertEquals(gs.getGasStationName(), gasStationDto.getGasStationName());
			}

		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC4_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// ANY fuel type and car sharing (Car2GO) -> no gas station matches
		//gasStationService.setUpdateDependability(true);
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		Boolean thrown = false;
		try {
			List<GasStationDto> list = gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010, 1,"null",
					"Car2Go");
			assertEquals(list.isEmpty(), true);
			// assertEquals(list.contains(gasStationDto));
			for (GasStationDto gs : list) {
				System.out.println(gs);
			}
			assertTrue(list.isEmpty());

		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC5_getGasStationsWithCoordinates() throws PriceException, GPSDataException, InvalidCarSharingException {
		// INVALID fuel type and ANY car sharing
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		try {
			gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "d1esel!!!!", "null");
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC6_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->diesel YES) and ANY car sharing
		// The repository has only gasStationDto and gasStationDto2 -> only
		// gasStationDto is present in the returned list

		//gasStationService.setUpdateDependability(true);
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));

		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "diesel", "null").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC7_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->diesel NO) and ANY car sharing
		// The repository has only gasStationDto2 ->the returned list is empty

		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "diesel", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC8_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->super YES) and ANY car sharing
		// The repository has only gasStationDto and gasStationDto2 -> only
		// gasStationDto is present in the returned list
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "super", "null").size(), 1);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC9_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->super NO) and ANY car sharing
		// The repository has only gasStationDto2 ->the returned list is empty

		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;

		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00, 1.32,1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "super", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC10_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->methane YES) and ANY car sharing
		// The repository has only gasStationDto and gasStationDto2 -> only
		// gasStationDto is present in the returned list
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "methane", "null").size(),
					1);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC11_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->methane NO) and ANY car sharing
		// The repository has only gasStationDto2 ->the returned list is empty
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;

		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00, 1.32,1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "methane", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC12_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->gas YES) and ANY car sharing
		// The repository has only gasStationDto and gasStationDto2 -> only
		// gasStationDto is present in the returned list
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "gas", "null").size(), 1);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);

	}

	@Test
	public void TC13_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->gas NO) and ANY car sharing
		// The repository has only gasStationDto2 ->the returned list is empty
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;

		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "gas", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC14_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->superplus YES) and ANY car sharing
		// The repository has only gasStationDto and gasStationDto2 -> only
		// gasStationDto is present in the returned list
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "superplus", "null").size(),
					1);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC15_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->superplus NO) and ANY car sharing
		// The repository has only gasStationDto2 ->the returned list is empty
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		try {
			assertEquals(
					gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "superplus", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC16_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->premiumdiesel YES) and ANY car sharing
		// The repository has only gasStationDto and gasStationDto2 -> only
		// gasStationDto is present in the returned list
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "premiumdiesel", "null").size(),
					1);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC17_getGasStationsWithCoordinates() throws PriceException, GPSDataException {
		// non-null fuel type (VALID->premiumdiesel NO) and ANY car sharing
		// The repository has only gasStationDto2 ->the returned list is empty
		//gasStationService.setUpdateDependability(true);
		Boolean thrown = false;
		GasStationDto gasStationDto2 = new GasStationDto(null, "Agip", "corso Vittorio", false, false, false, false,false,
				false, "Car2go", 40.0005, 25.0010, 0.89, 0.89, 1.29, 0.99, 1.00,1.32, 1, "2020-05-03", 0.88);
		assertNotNull(gasStationService.saveGasStation(gasStationDto2));
		try {
			assertEquals(
					gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "premiumdiesel", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC1_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// null fuel type and null car sharing
		//gasStationService.setUpdateDependability(true);
		gasStationService.saveGasStation(gasStationDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("null", "null").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// null fuel type and SET car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("null", "Enjoy").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and SET car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", false, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("diesel", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC4_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and null car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("super", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC5_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and null car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("methane", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC6_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and null car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false, false,"Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("gas", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC7_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and null car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertTrue(gasStationService.getGasStationsWithoutCoordinates("   super plus", "Enjoy").isEmpty());
		} catch (InvalidGasTypeException e) {
			thrown = true;
			System.out.println(e.getMessage());

		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC8_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and null car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertTrue(gasStationService.getGasStationsWithoutCoordinates("premiumdiesel", "Enjoy").isEmpty());
		} catch (InvalidGasTypeException e) {
			thrown = true;
			System.out.println(e.getMessage());

		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	
	@Test
	public void TC9_getGasStationsWithoutCoordinates() throws PriceException, GPSDataException {
		// SET fuel type and SET car sharing
		//gasStationService.setUpdateDependability(true);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		gasStationService.saveGasStation(gsDto);
		Boolean thrown = false;
		try {
			assertFalse(gasStationService.getGasStationsWithoutCoordinates("diesel", "null").isEmpty());
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC1_getGasStationByCarSharing() throws PriceException, GPSDataException {
		//gasStationService.setUpdateDependability(true);
		assertNotNull(gasStationService.saveGasStation(gasStationDto));
		assertEquals(gasStationService.getGasStationByCarSharing("Enjoy").size(), 1);
	}

	@Test
	public void TC1_setReport() throws InvalidGasStationException, PriceException, InvalidUserException {
		// existing user sets all prices -> no errors
		Boolean thrown = false;
		gasStationDto.setGasStationId(null);
		GasStationDto gsDto=new GasStationDto();
		try {
			 gsDto=gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			gasStationService.setReport(gsDto.getGasStationId(), 0.99, 0.98, 0.97, 0.96, 0.95,1.0, 1);
		} catch (InvalidGasStationException | PriceException | InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC2_setReport() throws InvalidGasStationException, PriceException, InvalidUserException {
		// invalid user -> should throw InvalidUserException
		Boolean thrown = false;
		gasStationDto.setGasStationId(null);
		GasStationDto gsDto=new GasStationDto();
		try {
			gsDto=gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			gasStationService.setReport(gsDto.getGasStationId(), 0.99, 0.98, 0.97, 0.96, 0.95,1.0, -1);

		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}
	
	@Test
	public void TC3_setReport() throws InvalidGasStationException, PriceException, InvalidUserException {
		// existing user sets price, has a lower reputation than previous one, but day difference is > 4
		UserDto userDto2 = new UserDto(2, "Test", "TestPw", "Test@email", 0);
		gasStationDto.setUserDto(userService.saveUser(userDto));
		userService.saveUser(userDto2);
		Boolean thrown = false;
		gasStationDto.setGasStationId(null);
		GasStationDto gsDto=new GasStationDto();
		try {
			 gsDto=gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			gasStationService.setReport(gsDto.getGasStationId(),3.0, 3.0, 3.0, 3.0, 3.0,3.0, userDto2.getUserId());
			gsDto=gasStationService.getGasStationById(gsDto.getGasStationId());
		} catch (InvalidGasStationException | PriceException | InvalidUserException e) {
			thrown = true;
		}
		assertEquals(gsDto.getDieselPrice(),3.0,0);
		assertEquals(gsDto.getPremiumDieselPrice(),3.0,0);
		assertEquals(gsDto.getSuperPrice(),3.0,0);
		assertEquals(gsDto.getSuperPlusPrice(),3.0,0);
		assertEquals(gsDto.getMethanePrice(),3.0,0);
		assertEquals(gsDto.getGasPrice(),3.0,0);
		assertEquals(gsDto.getReportUser(),2,0);
		assertFalse(thrown);
	}
	
	@Test
	public void TC4_setReport() throws InvalidGasStationException, PriceException, InvalidUserException {
		// existing user sets price, has a lower reputation than previous one, and day difference is < 4
		DateFormat formatter = new SimpleDateFormat("MM-dd-YYYY");
		UserDto userDto2 = new UserDto(null, "Test", "TestPw", "Test2@email", -3);
		userDto2.setAdmin(false);
		GasStationDto gsDto= gasStationDto;
		gsDto.setUserDto(userService.saveUser(userDto));
		gsDto.setReportUser(gasStationDto.getUserDto().getUserId());
		userDto2=userService.saveUser(userDto2);
		Boolean thrown = false;
		gsDto.setGasStationId(null);
		gsDto.setReportTimestamp(formatter.format(new Date(System.currentTimeMillis())));
		try {
			 gsDto=gasStationService.saveGasStation(gsDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}

		try {
			gasStationService.setReport(gsDto.getGasStationId(),3.0, 3.0, 3.0, 3.0, 3.0,3.0, userDto2.getUserId());
			gsDto=gasStationService.getGasStationById(gsDto.getGasStationId());
		} catch (InvalidGasStationException | PriceException | InvalidUserException e) {
			thrown = true;
		}
		assertEquals(gsDto.getDieselPrice(),gasStationDto.getDieselPrice(),0);
		assertEquals(gsDto.getPremiumDieselPrice(),gasStationDto.getPremiumDieselPrice(),0);
		assertEquals(gsDto.getSuperPrice(),gasStationDto.getSuperPrice(),0);
		assertEquals(gsDto.getSuperPlusPrice(),gasStationDto.getSuperPlusPrice(),0);
		assertEquals(gsDto.getMethanePrice(),gasStationDto.getMethanePrice(),0);
		assertEquals(gsDto.getGasPrice(),gasStationDto.getGasPrice(),0);
		assertFalse(thrown);
	}

	@Test
	public void TC5_setReport() throws InvalidGasStationException, PriceException, InvalidUserException {
		// non existing user -> the reportUser attribute of the gasStation with the
		// given ID should be empty
		Boolean thrown = false;
		gasStationDto.setGasStationId(null);
		GasStationDto gsDto=new GasStationDto();
		try {
			gsDto=gasStationService.saveGasStation(gasStationDto);
		} catch (PriceException | GPSDataException e1) {
			thrown = true;
		}
		try {
			gasStationService.setReport(gsDto.getGasStationId(), 0.99, 0.98, 0.97, 0.96, 0.95,1.0, 2);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}

		assertTrue(thrown);
//		assertEquals(gasStationService.getGasStationById(1).getUserDto(), null);
	}
	

	@Test
	public void TC6_setReport() throws InvalidGasStationException, PriceException, InvalidUserException {
		// non-existing gas station
		Boolean thrown = false;
		try {
			gasStationService.setReport(0, 0.99, 0.98, 0.97, 0.96, 0.95,1.0, 1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

}

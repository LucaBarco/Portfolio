package it.polito.ezgas;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.test.context.junit4.SpringRunner;

import exception.GPSDataException;
import exception.InvalidCarSharingException;
import exception.InvalidGasStationException;
import exception.InvalidGasTypeException;
import exception.InvalidUserException;
import exception.PriceException;

import org.mockito.Mock;

import it.polito.ezgas.converter.GasStationConverter;
import it.polito.ezgas.dto.GasStationDto;
import it.polito.ezgas.dto.IdPw;
import it.polito.ezgas.entity.GasStation;
import it.polito.ezgas.entity.User;
import it.polito.ezgas.repository.GasStationRepository;
import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.service.impl.GasStationServiceimpl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.*;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@RunWith(SpringRunner.class)

public class GasStationServiceTests {

	@Mock
	private GasStationRepository gasStationRepositoryMock;
	@Mock
	private GasStationConverter gasStationConverterMock;
	@Mock
	private IdPw credentialsMock;
	@Mock
	private UserRepository userRepositoryMock;

	private GasStationServiceimpl gasStationService;

	private GasStation gasStation = new GasStation("ENI", "corso Duca", true, true, true, true, true, true,"Enjoy", 40.0005,
			25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
	private GasStationDto gasStationDto = new GasStationDto(null, "ENI", "corso Duca", true, true, true, true, true,true,
			"Enjoy", 40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
	private User user = new User("nome", "password", "email", 0);

	@Before
	public void setUp() {
		gasStationRepositoryMock = mock(GasStationRepository.class);
		userRepositoryMock = mock(UserRepository.class);
		gasStationConverterMock = mock(GasStationConverter.class);
		gasStationService = new GasStationServiceimpl(gasStationRepositoryMock, gasStationConverterMock,
				userRepositoryMock);
		gasStationService.setUpdateDependability(true);

	}

	@Test
	public void TC1_getGasStationById() {
		// try to get a gas station with invalid id
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(gasStation);
		when(gasStationConverterMock.toGasStationDto(any(GasStation.class))).thenReturn(gasStationDto);
		Boolean thrown = false;
		try {
			gasStationService.getGasStationById(-1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

	@Test
	public void TC2_getGasStationById() {
		// try to retrieve a gas station with a non existing id
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(null);
		when(gasStationConverterMock.toGasStationDto(any(GasStation.class))).thenReturn(gasStationDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationById(1), null);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC3_getGasStationById() {
		// try to retrieve a gas station with an existing id
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(gasStation);
		when(gasStationConverterMock.toGasStationDto(any(GasStation.class))).thenReturn(gasStationDto);
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.getGasStationById(1));
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC1_saveGasStation() {
		// try to save a gas station which has no fuels -> ERROR?
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", false, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		when(gasStationRepositoryMock.saveAndFlush(any(GasStation.class))).thenReturn(gs);
		when(gasStationConverterMock.toGasStation(any(GasStationDto.class))).thenReturn(gs);
		when(gasStationConverterMock.toGasStationDto(any(GasStation.class))).thenReturn(gsDto);
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
		assertEquals(thrown, false);
	}

	@Test
	public void TC2_saveGasStation() {
		// saving without errors (all prices and no ID)
		GasStation gs = new GasStation("ENI", "corso Duca", true, true, true, true, true,true, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, true, true, true, true,true, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		when(gasStationRepositoryMock.saveAndFlush(any(GasStation.class))).thenReturn(gs);
		when(gasStationConverterMock.toGasStation(any(GasStationDto.class))).thenReturn(gs);
		when(gasStationConverterMock.toGasStationDto(any(GasStation.class))).thenReturn(gsDto);
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.saveGasStation(gsDto));
//			assertEquals(!gasStationService.getAllGasStations().isEmpty());
		} catch (GPSDataException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC5_saveGasStation() {
		// try to update an already existing gas station
		GasStationDto myDto = new GasStationDto(1, gasStationDto.getGasStationName(),
				gasStationDto.getGasStationAddress(), gasStationDto.getHasDiesel(), gasStationDto.getHasSuper(),
				gasStationDto.getHasSuperPlus(), gasStationDto.getHasGas(), gasStationDto.getHasMethane(), gasStationDto.getHasPremiumDiesel(),
				gasStationDto.getCarSharing(), gasStationDto.getLat(), gasStationDto.getLon(),
				gasStationDto.getDieselPrice(), gasStationDto.getSuperPrice(), gasStationDto.getSuperPlusPrice(),
				gasStationDto.getGasPrice(), gasStationDto.getMethanePrice(), gasStationDto.getPremiumDieselPrice(),gasStationDto.getReportUser(),
				gasStationDto.getReportTimestamp(), gasStationDto.getReportDependability());
		Boolean thrown = false;
		try {
			assertNotNull(gasStationService.saveGasStation(myDto));
		} catch (GPSDataException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC6_saveGasStation() {
		// try to update an already existing gas station with wrong long and/or lat
		GasStationDto myDto = new GasStationDto(1, gasStationDto.getGasStationName(),
				gasStationDto.getGasStationAddress(), gasStationDto.getHasDiesel(), gasStationDto.getHasSuper(),
				gasStationDto.getHasSuperPlus(), gasStationDto.getHasGas(), gasStationDto.getHasMethane(),gasStationDto.getHasPremiumDiesel(),
				gasStationDto.getCarSharing(), gasStationDto.getLat(), gasStationDto.getLon(),
				gasStationDto.getDieselPrice(), gasStationDto.getSuperPrice(), gasStationDto.getSuperPlusPrice(),
				gasStationDto.getGasPrice(), gasStationDto.getMethanePrice(), gasStationDto.getPremiumDieselPrice(),gasStationDto.getReportUser(),
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
				gasStationDto.getHasSuperPlus(), gasStationDto.getHasGas(), gasStationDto.getHasMethane(),gasStationDto.getHasPremiumDiesel(),
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
		when(gasStationRepositoryMock.findAll()).thenReturn(new ArrayList<GasStation>());
		when(gasStationConverterMock.toGasStationDtoList(any(List.class))).thenReturn(new ArrayList<GasStationDto>());
		assertEquals(gasStationService.getAllGasStations().isEmpty(), true);
	}

	@Test
	public void TC2_getAllGasStations() {
		// try to retrieve a list not empty
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findAll()).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		assertEquals(gasStationService.getAllGasStations().isEmpty(), false);
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
		assertEquals(thrown, true);
	}

	@Test
	public void TC2_deleteGasStation() {
		// try to delete an existing gas station
		Boolean thrown = false;
		when(gasStationRepositoryMock.exists(any(Integer.class))).thenReturn(true);
		try {
			assertEquals(gasStationService.deleteGasStation(1), true);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC3_deleteGasStation() {
		// try to delete a non existing gas station
		Boolean thrown = false;
		doThrow(EmptyResultDataAccessException.class).when(gasStationRepositoryMock).delete(1);
		try {
			assertEquals(gasStationService.deleteGasStation(1), null);
		} catch (InvalidGasStationException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC1_getGasStationsByGasolineType() {
		// try to get a gas station with invalid fuel type
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("water").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

	@Test
	public void TC2_getGasStationsByGasolineType() {
		// try to get a gas station with valid fuel type (Diesel)
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByhasDiesel(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("diesel").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC3_getGasStationsByGasolineType() {
		// try to get a gas station with valid fuel type (Super)
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByhasSuper(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("super").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC4_getGasStationsByGasolineType() {
		// try to get a gas station with valid fuel type (Methane)
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByhasMethane(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("methane").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC5_getGasStationsByGasolineType() {
		// try to get a gas station with valid fuel type (Gas)
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByhasGas(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("gas").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC6_getGasStationsByGasolineType() {
		// try to get a gas station with valid fuel type (SuperPlus)
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByhasSuperPlus(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("superplus").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC7_getGasStationsByGasolineType() {
		// try to get a gas station with valid fuel type (PremiumDiesel)
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByhasPremiumDiesel(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByGasolineType("premiumdiesel").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC1_getGasStationsByProximity() {
		// valid coordinates
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByProximity(40.0005, 25.0010), listDto);
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC2_getGasStationsByProximity() {
		// valid coordinates + radius<=0
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByProximity(40.0005, 25.0010, -1), listDto);
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC3_getGasStationsByProximity() {
		// valid coordinates + radius>0
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByProximity(40.0005, 25.0010, 2), listDto);
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC4_getGasStationsByProximity() {
		// invalid coordinates
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsByProximity(999.9999, -999.9999).isEmpty(), false);
		} catch (GPSDataException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

	// one test for each fuel type;
	@Test
	public void TC1_getGasStationsWithCoordinates() {
		// null fuel type and null car sharing -> all gas stations
		// radius<=0
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,-1, "null", "null").isEmpty(),
					false);
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,-1, "null", "null"), listDto);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC2_getGasStationsWithCoordinates() {
		// null fuel type and null car sharing -> all gas stations
		// radius>0
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,2, "null", "null").isEmpty(),
					false);
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,2, "null", "null"), listDto);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC3_getGasStationsWithCoordinates() {
		// Select ANY fuel type and car sharing (Enjoy) -> one gas station matches (just
		// inserted)
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "null", "Enjoy").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC4_getGasStationsWithCoordinates() {
		// ANY fuel type and car sharing (Car2GO) -> no gas station matches
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010, 1,"null", "Car2GO").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC5_getGasStationsWithCoordinates() {
		// INVALID fuel type and ANY car sharing
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gasStation));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010, 1,"d1esel!!!!", "null");
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

	@Test
	public void TC6_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->diesel YES) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
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
		assertEquals(thrown, false);
	}

	@Test
	public void TC7_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->diesel NO) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010, 1,"diesel", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC8_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->super YES) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, true, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "super", "null").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC9_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->super NO) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "super", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC10_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->methane YES) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, true, false,"Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "methane", "null").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC11_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->methane NO) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false, false,"Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "methane", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC12_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->gas YES) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, true, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "gas", "null").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC13_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->diesel NO) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "gas", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC14_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->superplus YES) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, true, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(
					gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010, 1,"superplus", "null").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC15_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->superplus NO) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(
					gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "superplus", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC16_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->premiumdiesel YES) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,true, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(
					gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010, 1,"premiumdiesel", "null").isEmpty(),
					false);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC17_getGasStationsWithCoordinates() {
		// non-null fuel type (VALID->premiumdiesel NO) and ANY car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		when(gasStationRepositoryMock.findBylatBetweenAndLonBetween(any(Double.class), any(Double.class),
				any(Double.class), any(Double.class))).thenReturn(list);
		list.remove(list.indexOf(gs));
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		Boolean thrown = false;
		try {
			assertEquals(
					gasStationService.getGasStationsWithCoordinates(40.0005, 25.0010,1, "premiumdiesel", "null").isEmpty(),
					true);
		} catch (GPSDataException e) {
			thrown = true;
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC1_getGasStationsWithoutCoordinates() {
		// null fuel type and null car sharing
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		Boolean thrown = false;
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("null", "null").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

	@Test
	public void TC2_getGasStationsWithoutCoordinates() {
		// null fuel type and SET car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false, false,"Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gsDto);
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByCarSharing(any(String.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("null", "Enjoy").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC3_getGasStationsWithoutCoordinates() {
		// SET fuel type and SET car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", false, false, false, false, false,false, "Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", false, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasDieselAndCarSharing(any(Boolean.class), any(String.class)))
				.thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("diesel", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC4_getGasStationsWithoutCoordinates() {
		// SET fuel type and null car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false, false,"Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false, false,"Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasSuperAndCarSharing(any(Boolean.class), any(String.class)))
				.thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("super", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC5_getGasStationsWithoutCoordinates() {
		// SET fuel type and null car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasMethaneAndCarSharing(any(Boolean.class), any(String.class)))
				.thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("methane", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC6_getGasStationsWithoutCoordinates() {
		// SET fuel type and null car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasDieselAndCarSharing(any(Boolean.class), any(String.class)))
				.thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("gas", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC7_getGasStationsWithoutCoordinates() {
		// SET fuel type and null car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasSuperPlusAndCarSharing(any(Boolean.class), any(String.class)))
				.thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("   super plus", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
			System.out.println(e.getMessage());

		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC8_getGasStationsWithoutCoordinates() {
		// SET fuel type and null car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false,false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false,false, "Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 1.32,1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasSuperPlusAndCarSharing(any(Boolean.class), any(String.class)))
				.thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("premiumdiesel", "Enjoy").isEmpty(), true);
		} catch (InvalidGasTypeException e) {
			thrown = true;
			System.out.println(e.getMessage());

		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}
	
	@Test
	public void TC9_getGasStationsWithoutCoordinates() {
		// SET fuel type and SET car sharing
		GasStation gs = new GasStation("ENI", "corso Duca", true, false, false, false, false, false, "Enjoy", 40.0005, 25.0010,
				0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		GasStationDto gsDto = new GasStationDto(null, "ENI", "corso Duca", true, false, false, false, false, false,"Enjoy",
				40.0005, 25.0010, 0.99, 0.99, 0.99, 0.99, 0.99,1.32, 1, "2020-05-20", 0.88);
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gs);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gsDto);
		Boolean thrown = false;
		when(gasStationRepositoryMock.findByhasDiesel(any(Boolean.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		try {
			assertEquals(gasStationService.getGasStationsWithoutCoordinates("diesel", "null").isEmpty(), false);
		} catch (InvalidGasTypeException e) {
			thrown = true;
		}catch (InvalidCarSharingException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC1_getGasStationByCarSharing() {
		List<GasStation> list = new ArrayList<GasStation>();
		list.add(gasStation);
		List<GasStationDto> listDto = new ArrayList<GasStationDto>();
		listDto.add(gasStationDto);
		when(gasStationRepositoryMock.findByCarSharing(any(String.class))).thenReturn(list);
		when(gasStationConverterMock.toGasStationDtoList(list)).thenReturn(listDto);
		assertEquals(gasStationService.getGasStationByCarSharing("Enjoy"), listDto);
	}

	@Test
	public void TC1_setReport() {
		// existing user sets all prices
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(gasStation);
		when(userRepositoryMock.findOne(any(Integer.class))).thenReturn(user);
		Boolean thrown = false;
		try {
			gasStationService.setReport(1, 0.99, 0.98, 0.97, 0.96, 0.95,1.0, 1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertEquals(thrown, false);
	}

	@Test
	public void TC2_setReport() {
		// invalid user
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(gasStation);
		when(userRepositoryMock.findOne(-1)).thenReturn(null);
		Boolean thrown = false;
		try {
			gasStationService.setReport(1, 0.99, 0.98, 0.97, 0.96, 0.95,1.0, -1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}
	
	@Test
	public void TC3_setReport() {
		// existing user has lower trust level but difference in days is >4
		User user2= new User("nome2", "password2", "email2", -1);
		user2.setUserId(2);
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(gasStation);
		when(userRepositoryMock.findOne(1)).thenReturn(user);
		when(userRepositoryMock.findOne(2)).thenReturn(user2);
		Boolean thrown = false;
		try {
			gasStationService.setReport(1, 3.0, 3.0, 3.0, 3.0, 3.0,3.0, 2);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertEquals(gasStation.getDieselPrice(), 3.0,0);
		assertEquals(gasStation.getPremiumDieselPrice(), 3.0,0);
		assertEquals(gasStation.getSuperPrice(), 3.0,0);
		assertEquals(gasStation.getSuperPlusPrice(), 3.0,0);
		assertEquals(gasStation.getGasPrice(), 3.0,0);
		assertEquals(gasStation.getMethanePrice(), 3.0,0);
		assertEquals(gasStation.getReportUser(), 2,0);
		assertFalse(thrown);
	}
	
	@Test
	public void TC4_setReport() {
		// existing user has lower trust level and gs is not updated
		User user2= new User("nome2", "password2", "email2", -1);
		DateFormat formatter = new SimpleDateFormat("MM-dd-YYYY");
		GasStation gasStation2 = new GasStation("ENI", "corso Duca", true, true, true, true, true, true,"Enjoy", 40.0005,
				25.0010, 0.99, 0.99, 0.99, 0.99, 0.99, 0.99, 1, "", 0.88);
		gasStation2.setReportTimestamp(formatter.format(new Date(System.currentTimeMillis())));
		gasStation2.setUser(user);
		user2.setUserId(2);
		when(gasStationRepositoryMock.findOne(1)).thenReturn(gasStation2);
		when(userRepositoryMock.findOne(1)).thenReturn(user);
		when(userRepositoryMock.findOne(2)).thenReturn(user2);
		Boolean thrown = false;
		try {
			gasStationService.setReport(1, 3.0, 3.0, 3.0, 3.0, 3.0,3.0, 2);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertEquals(gasStation2.getDieselPrice(), 0.99,0);
		assertEquals(gasStation2.getPremiumDieselPrice(), 0.99,0);
		assertEquals(gasStation2.getSuperPrice(), 0.99,0);
		assertEquals(gasStation2.getSuperPlusPrice(), 0.99,0);
		assertEquals(gasStation2.getGasPrice(), 0.99,0);
		assertEquals(gasStation2.getMethanePrice(), 0.99,0);
		assertEquals(gasStation2.getReportUser(), 1,0);
		assertFalse(thrown);
	}
	

	@Test
	public void TC5_setReport() {
		// non existing user
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(gasStation);
		when(userRepositoryMock.findOne(1)).thenReturn(null);
		Boolean thrown = false;
		try {
			gasStationService.setReport(1, 0.99, 0.98, 0.97, 0.96, 0.95,1.0, 1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

	@Test
	public void TC6_setReport() {
		// invalid gas station
		when(gasStationRepositoryMock.findOne(any(Integer.class))).thenReturn(null);
		when(userRepositoryMock.findOne(any(Integer.class))).thenReturn(user);
		Boolean thrown = false;
		try {
			gasStationService.setReport(-1, 0.99, 0.98, 0.97, 0.96, 0.95,1.0, 1);
		} catch (InvalidGasStationException e) {
			thrown = true;
		} catch (PriceException e) {
			thrown = true;
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertEquals(thrown, true);
	}

}

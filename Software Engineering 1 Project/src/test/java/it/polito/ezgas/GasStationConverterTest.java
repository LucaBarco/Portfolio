package it.polito.ezgas;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import it.polito.ezgas.converter.GasStationConverter;
import it.polito.ezgas.dto.GasStationDto;
import it.polito.ezgas.dto.UserDto;
import it.polito.ezgas.entity.GasStation;
import it.polito.ezgas.entity.User;

@RunWith(SpringRunner.class)
@SpringBootTest
public class GasStationConverterTest {
	@Autowired
	GasStationConverter gasStationConverter;

	@Test
	public void testToGasStationDto() {
		GasStation gasStation = new GasStation("Test", "TestAddress", true, true, true, true, true,true, "Test", 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TestDate", 0);
		gasStation.setUser(new User("test", "test", "test", 5));
		GasStationDto gasStationDto = gasStationConverter.toGasStationDto(gasStation);
		assertEquals(gasStationDto.getCarSharing(), gasStation.getCarSharing());
		assertEquals(gasStationDto.getGasStationName(), gasStation.getGasStationName());
		assertEquals(gasStationDto.getGasStationAddress(), gasStation.getGasStationAddress());
		assertEquals(gasStationDto.getReportTimestamp(), gasStation.getReportTimestamp());
		assertEquals(gasStationDto.getHasDiesel(), gasStation.getHasDiesel());
		assertEquals(gasStationDto.getHasSuper(), gasStation.getHasSuper());
		assertEquals(gasStationDto.getHasSuperPlus(), gasStation.getHasSuperPlus());
		assertEquals(gasStationDto.getHasGas(), gasStation.getHasGas());
		assertEquals(gasStationDto.getHasPremiumDiesel(), gasStation.getHasPremiumDiesel());
		assertEquals(gasStationDto.getLat(), gasStation.getLat(), 0);
		assertEquals(gasStationDto.getLon(), gasStation.getLon(), 0);
		assertEquals(gasStationDto.getDieselPrice(), gasStation.getDieselPrice(), 0);
		assertEquals(gasStationDto.getSuperPrice(), gasStation.getSuperPrice(), 0);
		assertEquals(gasStationDto.getSuperPlusPrice(), gasStation.getSuperPlusPrice(), 0);
		assertEquals(gasStationDto.getGasPrice(), gasStation.getGasPrice(), 0);
		assertEquals(gasStationDto.getMethanePrice(), gasStation.getMethanePrice(), 0);
		assertEquals(gasStationDto.getPremiumDieselPrice(), gasStation.getPremiumDieselPrice(), 0);
		assertEquals(gasStationDto.getReportUser(), gasStation.getReportUser(), 0);
		assertEquals(gasStationDto.getReportDependability(), gasStation.getReportDependability(), 0);
		assertEquals(gasStationDto.getGasStationId(), gasStation.getGasStationId());
		assertEquals(gasStationDto.getUserDto().getUserName(), "test");
	}

	@Test
	public void testToGasStation() {
		GasStationDto gasStationDto = new GasStationDto(1, "Pompa", "corso duca 24", true, true, false, false, true, false,
				"Enjoy", 45.6666, 7.6666, 1.234, 1.3432, -1.0, -1.0, 0.3232,-1.0, -1, "28/02/2020", 100);
		gasStationDto.setUserDto(new UserDto(1, "test", "test", "test", 5));
		GasStation gasStation = gasStationConverter.toGasStation(gasStationDto);
		assertEquals(gasStation.getCarSharing(), gasStationDto.getCarSharing());
		assertEquals(gasStation.getGasStationName(), gasStationDto.getGasStationName());
		assertEquals(gasStation.getGasStationAddress(), gasStationDto.getGasStationAddress());
		assertEquals(gasStation.getReportTimestamp(), gasStationDto.getReportTimestamp());
		assertEquals(gasStation.getHasDiesel(), gasStationDto.getHasDiesel());
		assertEquals(gasStation.getHasSuper(), gasStationDto.getHasSuper());
		assertEquals(gasStation.getHasSuperPlus(), gasStationDto.getHasSuperPlus());
		assertEquals(gasStation.getHasGas(), gasStationDto.getHasGas());
		assertEquals(gasStation.getHasPremiumDiesel(), gasStationDto.getHasPremiumDiesel());
		assertEquals(gasStation.getLat(), gasStationDto.getLat(), 0);
		assertEquals(gasStation.getLon(), gasStationDto.getLon(), 0);
		assertEquals(gasStation.getDieselPrice(), gasStationDto.getDieselPrice(), 0);
		assertEquals(gasStation.getSuperPrice(), gasStationDto.getSuperPrice(), 0);
		assertEquals(gasStation.getSuperPlusPrice(), gasStationDto.getSuperPlusPrice(), 0);
		assertEquals(gasStation.getGasPrice(), gasStationDto.getGasPrice(), 0);
		assertEquals(gasStation.getMethanePrice(), gasStationDto.getMethanePrice(), 0);
		assertEquals(gasStation.getPremiumDieselPrice(), gasStationDto.getPremiumDieselPrice(), 0);
		assertEquals(gasStation.getReportUser(), gasStationDto.getReportUser(), 0);
		assertEquals(gasStation.getReportDependability(), gasStationDto.getReportDependability(), 0);
		assertEquals(gasStation.getGasStationId(), gasStationDto.getGasStationId());
		assertEquals(gasStation.getUser().getUserId(), 1, 0);

	}

	@Test
	public void testToGasStationDtoList() {
		List<GasStation> gasStationList = Arrays.asList(
				new GasStation("Pompa", "corso duca 24", true, true, false, false, true,false, "Enjoy", 45.6666, 7.6666,
						1.234, 1.3432, -1.0, -1.0, 0.3232, -1.0, 1, "28/02/2020", 100),
				new GasStation("GSNameTest", "AddressTest", false, false, false, false, false,false, "CarSharingTest", 0.0,
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest", 0.0),
				new GasStation("GSNameTest3", "AddressTest3", false, false, false, false, false, false, "CarSharingTest3",
						11.0, 11.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0));
		List<GasStationDto> gasStationDtoList = gasStationConverter.toGasStationDtoList(gasStationList);
		assertEquals(gasStationDtoList.isEmpty(), false);
		for (int i = 0; i < 3; i++) {
			assertEquals(gasStationList.get(i).getCarSharing(), gasStationDtoList.get(i).getCarSharing());
			assertEquals(gasStationList.get(i).getGasStationName(), gasStationDtoList.get(i).getGasStationName());
			assertEquals(gasStationList.get(i).getGasStationAddress(), gasStationDtoList.get(i).getGasStationAddress());
			assertEquals(gasStationList.get(i).getReportTimestamp(), gasStationDtoList.get(i).getReportTimestamp());
			assertEquals(gasStationList.get(i).getHasDiesel(), gasStationDtoList.get(i).getHasDiesel());
			assertEquals(gasStationList.get(i).getHasSuper(), gasStationDtoList.get(i).getHasSuper());
			assertEquals(gasStationList.get(i).getHasSuperPlus(), gasStationDtoList.get(i).getHasSuperPlus());
			assertEquals(gasStationList.get(i).getHasGas(), gasStationDtoList.get(i).getHasGas());
			assertEquals(gasStationList.get(i).getHasPremiumDiesel(), gasStationDtoList.get(i).getHasPremiumDiesel());
			assertEquals(gasStationList.get(i).getLat(), gasStationDtoList.get(i).getLat(), i);
			assertEquals(gasStationList.get(i).getLon(), gasStationDtoList.get(i).getLon(), i);
			assertEquals(gasStationList.get(i).getDieselPrice(), gasStationDtoList.get(i).getDieselPrice(), i);
			assertEquals(gasStationList.get(i).getSuperPrice(), gasStationDtoList.get(i).getSuperPrice(), i);
			assertEquals(gasStationList.get(i).getSuperPlusPrice(), gasStationDtoList.get(i).getSuperPlusPrice(), i);
			assertEquals(gasStationList.get(i).getGasPrice(), gasStationDtoList.get(i).getGasPrice(), i);
			assertEquals(gasStationList.get(i).getMethanePrice(), gasStationDtoList.get(i).getMethanePrice(), i);
			assertEquals(gasStationList.get(i).getPremiumDieselPrice(), gasStationDtoList.get(i).getPremiumDieselPrice(), i);
			assertEquals(gasStationList.get(i).getReportUser(), gasStationDtoList.get(i).getReportUser(), i);
			assertEquals(gasStationList.get(i).getReportDependability(),
					gasStationDtoList.get(i).getReportDependability(), i);
			assertEquals(gasStationList.get(i).getGasStationId(), gasStationDtoList.get(i).getGasStationId());
		}
	}

	@Test
	public void testToGasStationList() {
		List<GasStationDto> gasStationDtoList = Arrays.asList(
				new GasStationDto(0, "Pompa", "corso duca 24", true, true, false, false, true,false ,"Enjoy", 45.6666, 7.6666,
						1.234, 1.3432, -1.0, -1.0, 0.3232, -1.0, 1, "28/02/2020", 100),
				new GasStationDto(1, "GSNameTest", "AddressTest", false, false, false, false, false, false, "CarSharingTest",
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest", 0.0),
				new GasStationDto(2, "GSNameTest3", "AddressTest3", false, false, false, false, false, false,
						"CarSharingTest3", 11.0, 11.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest3", 0.0));
		List<GasStation> gasStationList = gasStationConverter.toGasStationList(gasStationDtoList);
		assertEquals(gasStationList.isEmpty(), false);
		assertEquals(gasStationList.size(), 3);
		for (int i = 0; i < 3; i++) {
			assertEquals(gasStationList.get(i).getCarSharing(), gasStationDtoList.get(i).getCarSharing());
			assertEquals(gasStationList.get(i).getGasStationName(), gasStationDtoList.get(i).getGasStationName());
			assertEquals(gasStationList.get(i).getGasStationAddress(), gasStationDtoList.get(i).getGasStationAddress());
			assertEquals(gasStationList.get(i).getReportTimestamp(), gasStationDtoList.get(i).getReportTimestamp());
			assertEquals(gasStationList.get(i).getHasDiesel(), gasStationDtoList.get(i).getHasDiesel());
			assertEquals(gasStationList.get(i).getHasSuper(), gasStationDtoList.get(i).getHasSuper());
			assertEquals(gasStationList.get(i).getHasSuperPlus(), gasStationDtoList.get(i).getHasSuperPlus());
			assertEquals(gasStationList.get(i).getHasGas(), gasStationDtoList.get(i).getHasGas());
			assertEquals(gasStationList.get(i).getHasPremiumDiesel(), gasStationDtoList.get(i).getHasPremiumDiesel());
			assertEquals(gasStationList.get(i).getLat(), gasStationDtoList.get(i).getLat(), i);
			assertEquals(gasStationList.get(i).getLon(), gasStationDtoList.get(i).getLon(), i);
			assertEquals(gasStationList.get(i).getDieselPrice(), gasStationDtoList.get(i).getDieselPrice(), i);
			assertEquals(gasStationList.get(i).getSuperPrice(), gasStationDtoList.get(i).getSuperPrice(), i);
			assertEquals(gasStationList.get(i).getSuperPlusPrice(), gasStationDtoList.get(i).getSuperPlusPrice(), i);
			assertEquals(gasStationList.get(i).getGasPrice(), gasStationDtoList.get(i).getGasPrice(), i);
			assertEquals(gasStationList.get(i).getMethanePrice(), gasStationDtoList.get(i).getMethanePrice(), i);
			assertEquals(gasStationList.get(i).getPremiumDieselPrice(), gasStationDtoList.get(i).getPremiumDieselPrice(), i);
			assertEquals(gasStationList.get(i).getReportUser(), gasStationDtoList.get(i).getReportUser(), i);
			assertEquals(gasStationList.get(i).getReportDependability(),
					gasStationDtoList.get(i).getReportDependability(), i);
			assertEquals(gasStationList.get(i).getGasStationId(), gasStationDtoList.get(i).getGasStationId());
		}
	}

}

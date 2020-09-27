package it.polito.ezgas;

import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;
import it.polito.ezgas.dto.GasStationDto;
import it.polito.ezgas.dto.PriceReportDto;
import it.polito.ezgas.dto.UserDto;

@RunWith(SpringRunner.class)

public class GasStationDtoTests {
	private GasStationDto gs = new GasStationDto(5, "Eni - Station 24", "Corso Palermo, 12 Torino", true, true, true,
			true, true, true, "Enjoy", 41.023, 40.069, 1.17, 1.57, 1.69, 0.95, 0.89,0.55, 1, "2020-05-12T01:00:00", 2.34);
	private GasStationDto emptyGs = new GasStationDto();

	@Test
	public void TC1_GasStationID() {
		gs.setGasStationId(1250);
		assertEquals (gs.getGasStationId() , 1250,0);
	}

	@Test
	public void TC2_GasStationID() {
		gs.setGasStationId(Integer.MAX_VALUE + 1);
		assertEquals (gs.getGasStationId() , Integer.MIN_VALUE,0);
	}

	@Test
	public void TC3_GasStationID() {
		gs.setGasStationId(Integer.MIN_VALUE - 1);
		assertEquals (gs.getGasStationId() , Integer.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationName() {
		gs.setGasStationName("ENI Station 23");
		assertEquals (gs.getGasStationName(),"ENI Station 23");
	}

	@Test
	public void TC1_GasStationAddress() {
		gs.setGasStationAddress("Corso Duca 23");
		assertEquals (gs.getGasStationAddress(),"Corso Duca 23");
	}

	@Test
	public void TC1_GasStationReportDependability() {
		Double value = 2.069;
		gs.setReportDependability(value);
		assertEquals (gs.getReportDependability() , value,0);
	}

	@Test
	public void TC2_GasStationReportDependability() {
		gs.setReportDependability(-Double.MAX_VALUE - 1);
		assertEquals (gs.getReportDependability() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationReportDependability() {
		gs.setReportDependability(Double.MAX_VALUE + 1);
		assertEquals (gs.getReportDependability() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationReportUser() {
		gs.setReportUser(1250);
		assertEquals (gs.getReportUser() , 1250,0);
	}

	@Test
	public void TC2_GasStationReportUser() {
		gs.setReportUser(Integer.MAX_VALUE + 1);
		assertEquals (gs.getReportUser() , Integer.MIN_VALUE,0);
	}

	@Test
	public void TC3_GasStationReportUser() {
		gs.setReportUser(Integer.MIN_VALUE - 1);
		assertEquals (gs.getReportUser() , Integer.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationReportTimestamp() {
		gs.setReportTimestamp("20200503T10:20:31");
		assertEquals (gs.getReportTimestamp(),"20200503T10:20:31");
	}

	@Test
	public void TC1_GasStationHasDiesel() {
		gs.setHasDiesel(true);
		assertEquals (gs.getHasDiesel() , true);
	}

	@Test
	public void TC1_GasStationHasSuper() {
		Boolean hasSuper= new Boolean(true);
		gs.setHasSuper(hasSuper);
		assertEquals (gs.getHasSuper() , hasSuper);
	}
	
	@Test
	public void TC2_GasStationHasSuper() {
		gs.setHasSuper(true);
		assertEquals (gs.getHasSuper() , true);
	}
	
	

	@Test
	public void TC1_GasStationHasSuperPlus() {
		Boolean hasSuperPlus= new Boolean(true);

		gs.setHasSuperPlus(hasSuperPlus);
		assertEquals (gs.getHasSuperPlus() , hasSuperPlus);
	}
	
	@Test
	public void TC2_GasStationHasSuperPlus() {

		gs.setHasSuperPlus(true);
		assertEquals (gs.getHasSuperPlus() , true);
	}

	@Test
	public void TC1_GasStationHasGas() {
		Boolean hasGas= new Boolean(true);

		gs.setHasGas(hasGas);
		assertEquals (gs.getHasGas() , hasGas);
	}
	

	@Test
	public void TC2_GasStationHasGas() {

		gs.setHasGas(true);
		assertEquals (gs.getHasGas() , true);
	}


	@Test
	public void TC1_GasStationHasMethane() {
		gs.setHasMethane(true);
		assertEquals (gs.getHasMethane() , true);
	}
	@Test
	public void TC1_GasStationHasPremiumDiesel() {
		gs.setHasPremiumDiesel(true);
		assertEquals (gs.getHasPremiumDiesel() , true);
	}
	@Test
	public void TC1_GasStationLat() {
		Double value = 12.45;
		gs.setLat(value);
		assertEquals (gs.getLat() , value,0);
	}

	@Test
	public void TC2_GasStationLat() {

		gs.setLat(-Double.MAX_VALUE - 1);
		assertEquals (gs.getLat() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationLat() {
		gs.setLat(Double.MAX_VALUE + 1);
		assertEquals (gs.getLat() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationLon() {
		Double value = 12.45;
		gs.setLon(value);
		assertEquals (gs.getLon() , value,0);
	}

	@Test
	public void TC2_GasStationLon() {
		gs.setLon(-Double.MAX_VALUE - 1);
		assertEquals (gs.getLon() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationLon() {
		gs.setLon(Double.MAX_VALUE + 1);
		assertEquals (gs.getLon() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationDieselPrice() {
		Double value = 12.45;
		gs.setDieselPrice(value);
		assertEquals (gs.getDieselPrice() , value,0);
	}

	@Test
	public void TC2_GasStationDieselPrice() {
		gs.setDieselPrice(-Double.MAX_VALUE - 1);
		assertEquals (gs.getDieselPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationDieselPrice() {
		gs.setDieselPrice(Double.MAX_VALUE + 1);
		assertEquals (gs.getDieselPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationSuperPrice() {
		Double value = 12.45;
		gs.setSuperPrice(value);
		assertEquals (gs.getSuperPrice() , value,0);
	}

	@Test
	public void TC2_GasStationSuperPrice() {
		gs.setSuperPrice(-Double.MAX_VALUE - 1);
		assertEquals (gs.getSuperPrice() , -Double.MAX_VALUE,0);

	}

	@Test
	public void TC3_GasStationSuperPrice() {
		gs.setSuperPrice(Double.MAX_VALUE + 1);
		assertEquals (gs.getSuperPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationSuperPlusPrice() {
		Double value = 12.45;
		gs.setSuperPlusPrice(value);
		assertEquals (gs.getSuperPlusPrice() , value,0);
	}

	@Test
	public void TC2_GasStationSuperPlusPrice() {
		gs.setSuperPlusPrice(-Double.MAX_VALUE - 1);
		assertEquals (gs.getSuperPlusPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationSuperPlusPrice() {
		gs.setSuperPlusPrice(Double.MAX_VALUE + 1);
		assertEquals (gs.getSuperPlusPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationGasPrice() {
		Double value = 12.45;
		gs.setGasPrice(value);
		assertEquals (gs.getGasPrice() , value,0);
	}

	@Test
	public void TC2_GasStationGasPrice() {
		gs.setGasPrice(-Double.MAX_VALUE - 1);
		assertEquals (gs.getGasPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationGasPrice() {
		gs.setGasPrice(Double.MAX_VALUE + 1);
		assertEquals (gs.getGasPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_GasStationMethanePrice() {
		Double value = 12.45;
		gs.setMethanePrice(value);
		assertEquals (gs.getMethanePrice() , value,0);
	}

	@Test
	public void TC2_GasStationMethanPrice() {
		gs.setMethanePrice(-Double.MAX_VALUE - 1);
		assertEquals (gs.getMethanePrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationMethanPrice() {
		gs.setMethanePrice(Double.MAX_VALUE + 1);
		assertEquals (gs.getMethanePrice() , Double.MAX_VALUE,0);
	}
	@Test
	public void TC1_GasStationPremiumDieselPrice() {
		Double value = 12.45;
		gs.setPremiumDieselPrice(value);
		assertEquals (gs.getPremiumDieselPrice() , value,0);
	}

	@Test
	public void TC2_GasStationPremiumDieselPrice() {
		gs.setPremiumDieselPrice(-Double.MAX_VALUE - 1);
		assertEquals (gs.getPremiumDieselPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_GasStationPremiumDieselPrice() {
		gs.setPremiumDieselPrice(Double.MAX_VALUE + 1);
		assertEquals (gs.getPremiumDieselPrice() , Double.MAX_VALUE,0);
	}
	@Test
	public void TC1_GasStationCarSharing() {
		gs.setCarSharing("Enjoy");
		assertEquals (gs.getCarSharing(),"Enjoy");
	}

	@Test
	public void TC1_GasStationUser() {
		UserDto u = new UserDto();
		gs.setUserDto(u);
		assertEquals (gs.getUserDto() , u);
	}

	
}

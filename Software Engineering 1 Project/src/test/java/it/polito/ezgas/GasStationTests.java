package it.polito.ezgas;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;
import it.polito.ezgas.entity.GasStation;
import it.polito.ezgas.entity.User;

@RunWith(SpringRunner.class)

public class GasStationTests {
	private GasStation gs = new GasStation("Eni - Station 24", "Corso Palermo, 12 Torino", true, true, true, true,true, true,
			"Enjoy", 41.023, 40.069, 1.17, 1.57, 1.69, 0.95, 0.89,1.32,1, "2020-05-12T01:00:00", 2.34);
	private GasStation emptyGs = new GasStation();

	@Test
	public void TC1_GasStationID() {
		gs.setGasStationId(1250);
		assert (gs.getGasStationId() == 1250);
	}

	@Test
	public void TC2_GasStationID() {
		gs.setGasStationId(Integer.MAX_VALUE + 1);
		assert (gs.getGasStationId() == Integer.MIN_VALUE);
	}

	@Test
	public void TC3_GasStationID() {
		gs.setGasStationId(Integer.MIN_VALUE - 1);
		assert (gs.getGasStationId() == Integer.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationName() {
		gs.setGasStationName("ENI Station 23");
		assert (gs.getGasStationName().equals("ENI Station 23"));
	}

	@Test
	public void TC1_GasStationAddress() {
		gs.setGasStationAddress("Corso Duca 23");
		assert (gs.getGasStationAddress().equals("Corso Duca 23"));
	}

	@Test
	public void TC1_GasStationReportDependability() {
		Double value = 2.069;
		gs.setReportDependability(value);
		assert (gs.getReportDependability() == value);
	}

	@Test
	public void TC2_GasStationReportDependability() {
		gs.setReportDependability(-Double.MAX_VALUE - 1);
		assert (gs.getReportDependability() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationReportDependability() {
		gs.setReportDependability(Double.MAX_VALUE + 1);
		assert (gs.getReportDependability() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationReportUser() {
		gs.setReportUser(1250);
		assert (gs.getReportUser() == 1250);
	}

	@Test
	public void TC2_GasStationReportUser() {
		gs.setReportUser(Integer.MAX_VALUE + 1);
		assert (gs.getReportUser() == Integer.MIN_VALUE);
	}

	@Test
	public void TC3_GasStationReportUser() {
		gs.setReportUser(Integer.MIN_VALUE - 1);
		assert (gs.getReportUser() == Integer.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationReportTimestamp() {
		gs.setReportTimestamp("20200503T10:20:31");
		assert (gs.getReportTimestamp().equals("20200503T10:20:31"));
	}

	@Test
	public void TC1_GasStationHasDiesel() {
		gs.setHasDiesel(true);
		assert (gs.getHasDiesel() == true);
	}

	@Test
	public void TC1_GasStationHasSuper() {
		gs.setHasSuper(true);
		assert (gs.getHasSuper() == true);
	}

	@Test
	public void TC1_GasStationHasSuperPlus() {
		gs.setHasSuperPlus(true);
		assert (gs.getHasSuperPlus() == true);
	}

	@Test
	public void TC1_GasStationHasGas() {
		gs.setHasGas(true);
		assert (gs.getHasGas() == true);
	}

	@Test
	public void TC1_GasStationHasMethane() {
		gs.setHasMethane(true);
		assert (gs.getHasMethane() == true);
	}
	@Test
	public void TC1_GasStationHasPremiumDiesel() {
		gs.setHasPremiumDiesel(true);
		assert (gs.getHasPremiumDiesel() == true);
	}
	@Test
	public void TC1_GasStationLat() {
		Double value = 12.45;
		gs.setLat(value);
		assert (gs.getLat() == value);
	}

	@Test
	public void TC2_GasStationLat() {

		gs.setLat(-Double.MAX_VALUE - 1);
		assert (gs.getLat() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationLat() {
		gs.setLat(Double.MAX_VALUE + 1);
		assert (gs.getLat() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationLon() {
		Double value = 12.45;
		gs.setLon(value);
		assert (gs.getLon() == value);
	}

	@Test
	public void TC2_GasStationLon() {
		gs.setLon(-Double.MAX_VALUE - 1);
		assert (gs.getLon() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationLon() {
		gs.setLon(Double.MAX_VALUE + 1);
		assert (gs.getLon() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationDieselPrice() {
		Double value = 12.45;
		gs.setDieselPrice(value);
		assert (gs.getDieselPrice() == value);
	}

	@Test
	public void TC2_GasStationDieselPrice() {
		gs.setDieselPrice(-Double.MAX_VALUE - 1);
		assert (gs.getDieselPrice() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationDieselPrice() {
		gs.setDieselPrice(Double.MAX_VALUE + 1);
		assert (gs.getDieselPrice() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationSuperPrice() {
		Double value = 12.45;
		gs.setSuperPrice(value);
		assert (gs.getSuperPrice() == value);
	}

	@Test
	public void TC2_GasStationSuperPrice() {
		gs.setSuperPrice(-Double.MAX_VALUE - 1);
		assert (gs.getSuperPrice() == -Double.MAX_VALUE);

	}

	@Test
	public void TC3_GasStationSuperPrice() {
		gs.setSuperPrice(Double.MAX_VALUE + 1);
		assert (gs.getSuperPrice() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationSuperPlusPrice() {
		Double value = 12.45;
		gs.setSuperPlusPrice(value);
		assert (gs.getSuperPlusPrice() == value);
	}

	@Test
	public void TC2_GasStationSuperPlusPrice() {
		gs.setSuperPlusPrice(-Double.MAX_VALUE - 1);
		assert (gs.getSuperPlusPrice() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationSuperPlusPrice() {
		gs.setSuperPlusPrice(Double.MAX_VALUE + 1);
		assert (gs.getSuperPlusPrice() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationGasPrice() {
		Double value = 12.45;
		gs.setGasPrice(value);
		assert (gs.getGasPrice() == value);
	}

	@Test
	public void TC2_GasStationGasPrice() {
		gs.setGasPrice(-Double.MAX_VALUE - 1);
		assert (gs.getGasPrice() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationGasPrice() {
		gs.setGasPrice(Double.MAX_VALUE + 1);
		assert (gs.getGasPrice() == Double.MAX_VALUE);
	}

	@Test
	public void TC1_GasStationMethanePrice() {
		Double value = 12.45;
		gs.setMethanePrice(value);
		assert (gs.getMethanePrice() == value);
	}

	@Test
	public void TC2_GasStationMethanPrice() {
		gs.setMethanePrice(-Double.MAX_VALUE - 1);
		assert (gs.getMethanePrice() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationMethanPrice() {
		gs.setMethanePrice(Double.MAX_VALUE + 1);
		assert (gs.getMethanePrice() == Double.MAX_VALUE);
	}
	@Test
	public void TC1_GasStationPremiumDieselPrice() {
		Double value = 12.45;
		gs.setPremiumDieselPrice(value);
		assert (gs.getPremiumDieselPrice() == value);
	}

	@Test
	public void TC2_GasStationPremiumDieselPrice() {
		gs.setPremiumDieselPrice(-Double.MAX_VALUE - 1);
		assert (gs.getPremiumDieselPrice() == -Double.MAX_VALUE);
	}

	@Test
	public void TC3_GasStationPremiumDieselPrice() {
		gs.setPremiumDieselPrice(Double.MAX_VALUE + 1);
		assert (gs.getPremiumDieselPrice() == Double.MAX_VALUE);
	}
	@Test
	public void TC1_GasStationCarSharing() {
		gs.setCarSharing("Enjoy");
		assert (gs.getCarSharing().equals("Enjoy"));
	}

	@Test
	public void TC1_GasStationUser() {
		User u = new User();
		gs.setUser(u);
		assert (gs.getUser() == u);
	}
}

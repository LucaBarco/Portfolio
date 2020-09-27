package it.polito.ezgas;


import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;
import it.polito.ezgas.dto.PriceReportDto;
import it.polito.ezgas.dto.UserDto;

@RunWith(SpringRunner.class)

public class PriceReportDtoTests {
	private PriceReportDto pr = new PriceReportDto(5,1.17, 1.57, 1.69, 0.95, 0.89,0.55, 1);
	private PriceReportDto emptypr = new PriceReportDto();

	@Test
	public void TC1_PriceReportDtoGasStationID() {
		pr.setGasStationId(1250);
		assertEquals(pr.getGasStationId() ,1250,0);
	}

	@Test
	public void TC2_PriceReportDtoGasStationID() {
		pr.setGasStationId(Integer.MAX_VALUE + 1);
		assertEquals (pr.getGasStationId() , Integer.MIN_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoGasStationID() {
		pr.setGasStationId(Integer.MIN_VALUE - 1);
		assertEquals (pr.getGasStationId() , Integer.MAX_VALUE,0);
	}


	@Test
	public void TC1_PriceReportDtoDieselPrice() {
		Double value = 12.45;
		pr.setDieselPrice(value);
		assertEquals (pr.getDieselPrice() , value);
	}

	@Test
	public void TC2_PriceReportDtoDieselPrice() {
		pr.setDieselPrice(-Double.MAX_VALUE - 1);
		assertEquals (pr.getDieselPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoDieselPrice() {
		pr.setDieselPrice(Double.MAX_VALUE + 1);
		assertEquals (pr.getDieselPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_PriceReportDtoSuperPrice() {
		Double value = 12.45;
		pr.setSuperPrice(value);
		assertEquals (pr.getSuperPrice() , value);
	}

	@Test
	public void TC2_PriceReportDtoSuperPrice() {
		pr.setSuperPrice(-Double.MAX_VALUE - 1);
		assertEquals (pr.getSuperPrice() , -Double.MAX_VALUE,0);

	}

	@Test
	public void TC3_PriceReportDtoSuperPrice() {
		pr.setSuperPrice(Double.MAX_VALUE + 1);
		assertEquals (pr.getSuperPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_PriceReportDtoSuperPlusPrice() {
		Double value = 12.45;
		pr.setSuperPlusPrice(value);
		assertEquals (pr.getSuperPlusPrice() , value);
	}

	@Test
	public void TC2_PriceReportDtoSuperPlusPrice() {
		pr.setSuperPlusPrice(-Double.MAX_VALUE - 1);
		assertEquals (pr.getSuperPlusPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoSuperPlusPrice() {
		pr.setSuperPlusPrice(Double.MAX_VALUE + 1);
		assertEquals (pr.getSuperPlusPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_PriceReportDtoGasPrice() {
		Double value = 12.45;
		pr.setGasPrice(value);
		assertEquals (pr.getGasPrice() , value);
	}

	@Test
	public void TC2_PriceReportDtoGasPrice() {
		pr.setGasPrice(-Double.MAX_VALUE - 1);
		assertEquals (pr.getGasPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoGasPrice() {
		pr.setGasPrice(Double.MAX_VALUE + 1);
		assertEquals (pr.getGasPrice() , Double.MAX_VALUE,0);
	}

	@Test
	public void TC1_PriceReportDtoMethanePrice() {
		Double value = 12.45;
		pr.setMethanePrice(value);
		assertEquals (pr.getMethanePrice() , value,0);
	}

	@Test
	public void TC2_PriceReportDtoMethanPrice() {
		pr.setMethanePrice(-Double.MAX_VALUE - 1);
		assertEquals (pr.getMethanePrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoMethanPrice() {
		pr.setMethanePrice(Double.MAX_VALUE + 1);
		assertEquals (pr.getMethanePrice() , Double.MAX_VALUE,0);
	}
	@Test
	public void TC1_PriceReportDtoPremiumDieselPrice() {
		Double value = 12.45;
		pr.setPremiumDieselPrice(value);
		assertEquals (pr.getPremiumDieselPrice() , value,0);
	}

	@Test
	public void TC2_PriceReportDtoPremiumDieselPrice() {
		pr.setPremiumDieselPrice(-Double.MAX_VALUE - 1);
		assertEquals (pr.getPremiumDieselPrice() , -Double.MAX_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoPremiumDieselPrice() {
		pr.setPremiumDieselPrice(Double.MAX_VALUE + 1);
		assertEquals (pr.getPremiumDieselPrice() , Double.MAX_VALUE,0);
	}
	
	
	@Test
	public void TC1_PriceReportDtoUserId() {
		pr.setUserId(1250);
		assertEquals (pr.getUserId() , 1250,0);
	}

	@Test
	public void TC2_PriceReportDtoUserId() {
		pr.setUserId(Integer.MAX_VALUE + 1);
		assertEquals (pr.getUserId() , Integer.MIN_VALUE,0);
	}

	@Test
	public void TC3_PriceReportDtoUserId() {
		pr.setUserId(Integer.MIN_VALUE - 1);
		assertEquals (pr.getUserId() , Integer.MAX_VALUE,0);
	}

	
	
}

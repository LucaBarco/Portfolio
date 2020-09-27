package it.polito.ezgas;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.context.junit4.SpringRunner;
import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import it.polito.ezgas.repository.GasStationRepository;
import it.polito.ezgas.entity.GasStation;

@RunWith(SpringRunner.class)
@DataJpaTest
public class GasStationRepositoryTests {

	@Autowired
	private TestEntityManager entityManager;

	@Autowired
	private GasStationRepository gsrep;

	@Test
	public void TestfindBygasStationName() {

		GasStation gs = new GasStation("GSNameTest", "AddressTest", false, false, false, false, false, false, "CarSharingTest",
				0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest", 0.0);

		entityManager.persist(gs);
		entityManager.flush();

		assertEquals(gsrep.findBygasStationName(gs.getGasStationName()), gs);
	}

	@Test
	public void TestfindBylatBetweenAndLonBetween() {

		GasStation gs1 = new GasStation("GSgoodone1", "AddressTest1", false, false, false, false, false, false,
				"CarSharingTest1", 7.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSNameTest3", "AddressTest3", false, false, false, false, false,false,
				"CarSharingTest3", 11.0, 11.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSGoodOne4", "AddressTest4", false, false, false, false, false,false,
				"CarSharingTest4", 6.0, 6.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", false, false, false, false, false, false,
				"CarSharingTest5", 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest5", 0.0);
		GasStation gs6 = new GasStation("GSNameTest6", "AddressTest6", false, false, false, false, false,false,
				"CarSharingTest6", 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest6", 0.0);
		GasStation gs7 = new GasStation("GSNameTest7", "AddressTest7", false, false, false, false, false,false,
				"CarSharingTest7", 0.0, 11.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest7", 0.0);
		GasStation gs8 = new GasStation("GSNameTest8", "AddressTest8", false, false, false, false, false,false,
				"CarSharingTest8", 11.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest8", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.persist(gs6);
		entityManager.persist(gs7);
		entityManager.persist(gs8);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs4);

		assertEquals(gsrep.findBylatBetweenAndLonBetween(5.0, 10.0, 5.0, 10.0), gslist);
	}

	@Test
	public void TestfindByhasDiesel() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", true, false, false, false, false,false,
				"CarSharingTest1", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", true, false, false, false, false,false,
				"CarSharingTest3", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasDiesel(true), gslist);
	}

	@Test
	public void TestfindByhasSuper() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, true, false, false, false,false,
				"CarSharingTest1", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, false, false, false,false,
				"CarSharingTest3", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasSuper(true), gslist);
	}

	@Test
	public void TestfindByhasGas() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, false, false, true, false,false,
				"CarSharingTest1", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, false, false, true, false,false,
				"CarSharingTest3", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasGas(true), gslist);
	}

	@Test
	public void TestfindByhasSuperPlus() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, false, true, false, false,false,
				"CarSharingTest1", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, false, true, false, false,false,
				"CarSharingTest3", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasSuperPlus(true), gslist);
	}

	@Test
	public void TestfindByhasMethane() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, false, false, false, true,false,
				"CarSharingTest1", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, false, false, true,false,
				"CarSharingTest3", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasMethane(true), gslist);
	}
	
	@Test
	public void TestfindByhasPremiumDiesel() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, false, false, false, false,true,
				"CarSharingTest1", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, false, false, false,true,
				"CarSharingTest3", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasPremiumDiesel(true), gslist);
	}
	
	@Test
	public void TestfindByhasDieselAndCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", true, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", true, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSNameTest4", "AddressTest4", false, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", true, false, false, false, false,false,
				"CarSharingTest5", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest5", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasDieselAndCarSharing(true, "CarSharingToBeFound"), gslist);
	}

	@Test
	public void TestfindByhasSuperAndCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, true, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSNameTest4", "AddressTest4", false, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", false, true, false, false, false,false,
				"CarSharingTest5", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest5", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasSuperAndCarSharing(true, "CarSharingToBeFound"), gslist);
	}

	@Test
	public void TestfindByhasGasAndCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, false, false, true, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, true, true, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSNameTest4", "AddressTest4", false, false, true, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", false, true, false, true, false,false,
				"CarSharingTest5", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest5", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasGasAndCarSharing(true, "CarSharingToBeFound"), gslist);
	}

	@Test
	public void TestfindByhasSuperPlusAndCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, true, true, true, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, true, true, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSNameTest4", "AddressTest4", false, false, false, true, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", false, false, true, false, false,false,
				"CarSharingTest5", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest5", 0.0);
		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasSuperPlusAndCarSharing(true, "CarSharingToBeFound"), gslist);
	}
	
	@Test
	public void TestfindByhasMethaneAndCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, true, false, false, true,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, true, false, false, true,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSNameTest4", "AddressTest4", false, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", false, true, false, false, true,false,
				"CarSharingTest5", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest5", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasMethaneAndCarSharing(true, "CarSharingToBeFound"), gslist);
	}
	
	@Test
	public void TestfindByhasPremiumDieselAndCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, true, false, false, true,true,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, false, false, false, true,true,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest3", 0.0);
		GasStation gs4 = new GasStation("GSNameTest4", "AddressTest4", false, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest4", 0.0);
		GasStation gs5 = new GasStation("GSNameTest5", "AddressTest5", false, true, false, false, true,true,
				"CarSharingTest5", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, "TimeStampTest5", 0.0);

		entityManager.persist(gs1);
		entityManager.persist(gs2);
		entityManager.persist(gs3);
		entityManager.persist(gs4);
		entityManager.persist(gs5);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByhasPremiumDieselAndCarSharing(true, "CarSharingToBeFound"), gslist);
	}
	
	@Test
	public void TestfindByCarSharing() {

		GasStation gs1 = new GasStation("GSGoodOne1", "AddressTest1", false, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest1", 0.0);
		GasStation gs2 = new GasStation("GSNameTest2", "AddressTest2", false, false, false, false, false,false,
				"CarSharingTest2", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest2", 0.0);
		GasStation gs3 = new GasStation("GSGoodOne3", "AddressTest3", false, false, false, false, false,false,
				"CarSharingToBeFound", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0, "TimeStampTest3", 0.0);

		entityManager.persist(gs1);
		entityManager.flush();
		entityManager.persist(gs2);
		entityManager.flush();
		entityManager.persist(gs3);
		entityManager.flush();

		List<GasStation> gslist = new ArrayList<>();
		gslist.add(gs1);
		gslist.add(gs3);

		assertEquals(gsrep.findByCarSharing("CarSharingToBeFound"), gslist);
	}

}

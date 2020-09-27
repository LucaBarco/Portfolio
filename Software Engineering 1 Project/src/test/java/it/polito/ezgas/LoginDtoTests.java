package it.polito.ezgas;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;
import it.polito.ezgas.dto.LoginDto;

@RunWith(SpringRunner.class)
public class LoginDtoTests {
	private LoginDto log = new LoginDto(1, "lukeb", "tok1209", "email@ezgas.com", 0);

	@Test
	public void TC1_LoginDtoUserID() {
		log.setUserId(8888);
		assertEquals(log.getUserId(), 8888, 0);
	}

	@Test
	public void TC2_LoginDtoUserID() {
		log.setUserId(Integer.MAX_VALUE + 1);
		assertEquals(log.getUserId(), Integer.MIN_VALUE, 0);
	}

	@Test
	public void TC3_LoginDtoUserID() {
		log.setUserId(Integer.MIN_VALUE - 1);
		assertEquals(log.getUserId(), Integer.MAX_VALUE, 0);
	}

	@Test
	public void TC1_LoginDtoUserName() {
		log.setUserName("Enrico Mattei");
		assertEquals(log.getUserName(), "Enrico Mattei");
	}

	@Test
	public void TC1_LoginDtoToken() {
		log.setToken("tk2100");
		assertEquals(log.getToken(), "tk2100");
	}

	@Test
	public void TC1_LoginDtoUserEmail() {
		log.setEmail("enrico.mattei@eni.it");
		assertEquals(log.getEmail(), "enrico.mattei@eni.it");
	}

	@Test
	public void TC1_LoginDtoUserReputation() {
		log.setReputation(100);
		assertEquals(log.getReputation(), 100, 0);
	}

	@Test
	public void TC2_LoginDtoUserReputation() {
		log.setReputation(Integer.MAX_VALUE + 1);
		assertEquals(log.getReputation(), Integer.MIN_VALUE, 0);
	}

	@Test
	public void TC3_LoginDtoUserReputation() {
		log.setReputation(Integer.MIN_VALUE - 1);
		assertEquals(log.getReputation(), Integer.MAX_VALUE, 0);
	}

	@Test
	public void TC1_LoginDtoUserAdmin() {
		log.setAdmin(true);
		assertTrue(log.getAdmin());
	}

}

package it.polito.ezgas;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;
import it.polito.ezgas.entity.User;

@RunWith(SpringRunner.class)

public class UserTests {
	private User us = new User("lukeb", "psw", "luke@ezgas.com", 1);
	private User emptyUs = new User();

	@Test
	public void TC1_UserID() {
		us.setUserId(8888);
		assertEquals(us.getUserId(), 8888, 0);
	}

	@Test
	public void TC2_UserID() {
		us.setUserId(Integer.MAX_VALUE + 1);
		assertEquals(us.getUserId(), Integer.MIN_VALUE, 0);
	}

	@Test
	public void TC3_UserID() {
		us.setUserId(Integer.MIN_VALUE - 1);
		assertEquals(us.getUserId(), Integer.MAX_VALUE, 0);
	}

	@Test
	public void TC1_UserName() {
		us.setUserName("Enrico Mattei");
		assertEquals(us.getUserName(), "Enrico Mattei");
	}

	@Test
	public void TC1_UserPassword() {
		us.setPassword("Th1s@ppISc00l");
		assertEquals(us.getPassword(), "Th1s@ppISc00l");
	}

	@Test
	public void TC1_UserEmail() {
		us.setEmail("enrico.mattei@eni.it");
		assertEquals(us.getEmail(), "enrico.mattei@eni.it");
	}

	@Test
	public void TC1_UserReputation() {
		us.setReputation(100);
		assertEquals(us.getReputation(), 100, 0);
	}

	@Test
	public void TC2_UserReputation() {
		us.setReputation(Integer.MAX_VALUE + 1);
		assertEquals(us.getReputation(), Integer.MIN_VALUE, 0);
	}

	@Test
	public void TC3_UserReputation() {
		us.setReputation(Integer.MIN_VALUE - 1);
		assertEquals(us.getReputation(), Integer.MAX_VALUE, 0);
	}

	@Test
	public void TC1_UserAdmin() {
		us.setAdmin(true);
		assertTrue(us.getAdmin());
	}
}

package it.polito.ezgas;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.context.junit4.SpringRunner;
import static org.junit.Assert.*;

import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.entity.User;

@RunWith(SpringRunner.class)
@DataJpaTest
public class UserRepositoryTests {

	@Autowired
	private TestEntityManager entityManager;

	@Autowired
	private UserRepository usrep;

	@Test
	public void TestfindByEmail() {

		User user = new User("usertest", "pswtest", "test@mail.com", 1);

		entityManager.persist(user);
		entityManager.flush();

		assertEquals(usrep.findByEmail(user.getEmail()), user);
	}

}
package it.polito.ezgas;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.junit4.SpringRunner;
import exception.InvalidLoginDataException;
import exception.InvalidUserException;
import org.mockito.Mock;
import it.polito.ezgas.converter.UserConverter;
import it.polito.ezgas.dto.IdPw;
import it.polito.ezgas.dto.UserDto;
import it.polito.ezgas.entity.User;
import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.service.*;
import it.polito.ezgas.service.impl.UserServiceimpl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.*;
import java.util.ArrayList;
import java.util.List;

@RunWith(SpringRunner.class)

public class UserServiceTests {

	@Mock
	private UserRepository userRepositoryMock;
	@Mock
	private UserConverter userConverterMock;

	private UserDto userDto;

	private User user;

	private IdPw credentials;

	@Before
	public void setUp() {
		userRepositoryMock = mock(UserRepository.class);
		userConverterMock = mock(UserConverter.class);
		user = new User("lukeb", "password", "prova@email.com", 5);
		userDto = new UserDto(2, "lukeb", "password", "prova@email.com", 5);
		credentials = new IdPw("user", "psw"); //
	}

	@Test
	public void TC1_saveUserTest() {
		// Test: saving without errors
		when(userRepositoryMock.saveAndFlush(any(User.class))).thenReturn(user);
		when(userConverterMock.toUser(any(UserDto.class))).thenReturn(user);
		when(userConverterMock.toUserDto(any(User.class))).thenReturn(userDto);
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(null);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		UserDto u = new UserDto(null, "lukeb", "password", "prova@email.com", 5);
		assertNotNull(userService.saveUser(u));
	}

	@Test
	public void TC2_saveUserTest() {
		// Test: try to save an already existing user
		when(userRepositoryMock.saveAndFlush(any(User.class))).thenReturn(user);
		when(userConverterMock.toUser(any(UserDto.class))).thenReturn(user);
		when(userConverterMock.toUserDto(any(User.class))).thenReturn(userDto);
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(user);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		UserDto u = new UserDto(null, "lukeb", "password", "prova@email.com", 5);
		assertNull(userService.saveUser(u));
	}

	@Test
	public void TC3_saveUserTest() {
		// Test: update a user
		user.setUserId(2);
		when(userRepositoryMock.saveAndFlush(any(User.class))).thenReturn(user);
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(user);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		assertNotNull(userService.saveUser(userDto));
	}

	@Test
	public void TC4_saveUserTest() {
		// Test: try to update a non existing or a different user (different UserIds)
		user.setUserId(1);
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(user);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		assertEquals(userService.saveUser(userDto), userDto);
	}

	@Test
	public void TC1_getUserById() {
		// Test: try to get a user with negative id
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		Boolean thrown = false;
		try {
			userService.getUserById(-1);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_getUserById() {
		// Test: try to retrieve an user with a non existing id
		Boolean thrown = false;
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(false);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertNull(userService.getUserById(1));
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_getUserById() {
		// Test: try to retrieve an user with an existing id
		Boolean thrown = false;
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(true);
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(user);
		when(userConverterMock.toUserDto(any(User.class))).thenReturn(userDto);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertNotNull(userService.getUserById(1));
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC1_getAllUsers() {
		// Test: try to retrieve an empty list
		when(userRepositoryMock.findAll()).thenReturn(new ArrayList<User>());
		when(userConverterMock.toUserDtoList(any(List.class))).thenReturn(new ArrayList<UserDto>());
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		assertEquals(userService.getAllUsers().isEmpty(), true);
	}

	@Test
	public void TC2_getAllUsers() {
		// Test: try to retrieve a list not empty
		List<User> list = new ArrayList<User>();
		list.add(user);
		List<UserDto> listDto = new ArrayList<UserDto>();
		listDto.add(userDto); //
		when(userRepositoryMock.findAll()).thenReturn(list);
		when(userConverterMock.toUserDtoList(list)).thenReturn(listDto);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		assertEquals(userService.getAllUsers().isEmpty(), false);
	}

	@Test
	public void TC1_deleteUser() {
		// Test: try to delete a user with a negative id
		Boolean thrown = false;
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.deleteUser(-1);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_deleteUser() {
		// Test: try to correctly delete a user
		Boolean thrown = false;
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(true);

		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertTrue(userService.deleteUser(1));
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_deleteUser() {
		// Test: try to delete a user with a non existing id
		Boolean thrown = false;
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(false);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertFalse(userService.deleteUser(1));
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC1_login() {
		// Test: try to login with null psw
		Boolean thrown = false;
		credentials.setPw(null);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.login(credentials);
		} catch (InvalidLoginDataException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_login() {
		// Test: try to login with null username
		Boolean thrown = false;
		credentials.setUser(null);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.login(credentials);
		} catch (InvalidLoginDataException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC3_login() {
		// Test: user does not exists
		Boolean thrown = false;
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(null);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.login(credentials);
		} catch (InvalidLoginDataException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC4_login() {
		// Test: passwords do not correspond
		Boolean thrown = false;
		User u = user; //
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(u);
		u.setPassword("psw2");
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.login(credentials);
		} catch (InvalidLoginDataException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC5_login() {
		// Test: correct login
		Boolean thrown = false;
		User u = new User();
		when(userRepositoryMock.findByEmail(any(String.class))).thenReturn(u);
		u.setEmail("user");
		u.setPassword("psw");
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertNotNull(userService.login(credentials));
		} catch (InvalidLoginDataException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC1_increaseUserReputation() {
		// Test: try to update a user with negative id

		Boolean thrown = false;

		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.increaseUserReputation(-1);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_increaseUserReputation() {
		// Test: try to increase reputation for a user that already has the max value
		// (5)

		Boolean thrown = false;
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(user);
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(true);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertEquals(userService.increaseUserReputation(1), 5, 0);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_increaseUserReputation() {
		// Test: try to increase reputation for a user

		User u = new User();
		Boolean thrown = false;
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(u);
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(true);
		u.setReputation(3);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertEquals(userService.increaseUserReputation(1), 4, 0);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	@Test
	public void TC4_increaseUserReputation() {
		// Test: try to increase reputation for a user

		User u = new User();
		Boolean thrown = false;
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(u);
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(false);
		u.setReputation(3);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertEquals(userService.increaseUserReputation(1), 4, 0);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC1_decreaseUserReputation() {
		// Test: try to decrease reputation of a user with a negative id

		Boolean thrown = false;

		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			userService.decreaseUserReputation(-1);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}

	@Test
	public void TC2_decreaseUserReputation() {
		// Test: try to decrease reputation of a user that already has the minimum value
		// (-5)

		Boolean thrown = false;
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(user);
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(true);
		user.setReputation(-5);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertEquals(userService.decreaseUserReputation(1), -5, 0);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}

	@Test
	public void TC3_decreaseUserReputation() {
		// Test: try to decrease reputation of a user
		User u = new User();
		Boolean thrown = false;
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(u);
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(true);
		u.setReputation(-3);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertEquals(userService.decreaseUserReputation(1), -4, 0);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertFalse(thrown);
	}
	@Test
	public void TC4_decreaseUserReputation() {
		// Test: try to decrease reputation of a user
		User u = new User();
		Boolean thrown = false;
		when(userRepositoryMock.getOne(any(Integer.class))).thenReturn(u);
		when(userRepositoryMock.exists(any(Integer.class))).thenReturn(false);
		u.setReputation(-3);
		UserService userService = new UserServiceimpl(userRepositoryMock, userConverterMock);
		try {
			assertEquals(userService.decreaseUserReputation(1), -4, 0);
		} catch (InvalidUserException e) {
			thrown = true;
		}
		assertTrue(thrown);
	}
}

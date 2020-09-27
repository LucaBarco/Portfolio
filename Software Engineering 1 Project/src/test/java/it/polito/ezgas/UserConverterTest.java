package it.polito.ezgas;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import it.polito.ezgas.converter.UserConverter;
import it.polito.ezgas.dto.UserDto;
import it.polito.ezgas.entity.User;

@RunWith(SpringRunner.class)
@SpringBootTest
public class UserConverterTest {
	@Autowired
	UserConverter userConverter;

	@Test
	public void testToUserDto() {
		User user = new User("Test", "TestPw", "Test@email", 0);
		user.setAdmin(false);
		user.setUserId(3);
		UserDto userDto = userConverter.toUserDto(user);
		assertEquals(userDto.getAdmin(), user.getAdmin());
		assertEquals(userDto.getEmail(), user.getEmail());
		assertEquals(userDto.getUserName(), user.getUserName());
		assertEquals(userDto.getPassword(), user.getPassword());
		assertEquals(userDto.getReputation(), user.getReputation());
		assertEquals(userDto.getUserId(), user.getUserId());
	}

	@Test
	public void testToUser() {
		UserDto userDto = new UserDto(0, "Test", "TestPw", "Test@email", 0);
		userDto.setAdmin(false);
		userDto.setUserId(3);
		User user = userConverter.toUser(userDto);
		assertEquals(user.getAdmin(), userDto.getAdmin());
		assertEquals(user.getEmail(), userDto.getEmail());
		assertEquals(user.getUserName(), userDto.getUserName());
		assertEquals(user.getPassword(), userDto.getPassword());
		assertEquals(user.getReputation(), userDto.getReputation());
		assertEquals(user.getUserId(), userDto.getUserId());
	}

	@Test
	public void testToUserDtoList() {
		List<User> userList = Arrays.asList(new User("Test", "Test", "email", 0),
				new User("test2", "pswtest2", "test@mail.com", 0));
		userList.get(0).setAdmin(false);
		userList.get(0).setUserId(0);
		userList.get(1).setAdmin(true);
		userList.get(1).setUserId(1);
		List<UserDto> userDtoList = userConverter.toUserDtoList(userList);
		assertEquals(userDtoList.isEmpty(), false);

		for (int i = 0; i < 2; i++) {
			assertEquals(userDtoList.get(i).getAdmin(), userList.get(i).getAdmin());
			assertEquals(userDtoList.get(i).getEmail(), userList.get(i).getEmail());
			assertEquals(userDtoList.get(i).getUserName(), userList.get(i).getUserName());
			assertEquals(userDtoList.get(i).getPassword(), userList.get(i).getPassword());
			assertEquals(userDtoList.get(i).getReputation(), userList.get(i).getReputation());
			assertEquals(userDtoList.get(i).getUserId(), userList.get(i).getUserId());
		}
	}

	@Test
	public void testToUserList() {

		List<UserDto> userDtoList = Arrays.asList(new UserDto(0, "Test", "test", "email", 0, false),
				new UserDto(1, "usertest", "pswtest", "test@mail.com", 1, true));
		List<User> userList = userConverter.toUserList(userDtoList);
		assertEquals(userList.isEmpty(), false);
		assertEquals(userList.size(), 2);
		for (int i = 0; i < 2; i++) {
			assertEquals(userList.get(i).getAdmin(), userList.get(i).getAdmin());
			assertEquals(userList.get(i).getEmail(), userDtoList.get(i).getEmail());
			assertEquals(userList.get(i).getUserName(), userDtoList.get(i).getUserName());
			assertEquals(userList.get(i).getPassword(), userDtoList.get(i).getPassword());
			assertEquals(userList.get(i).getReputation(), userDtoList.get(i).getReputation());
			assertEquals(userList.get(i).getUserId(), userDtoList.get(i).getUserId());
		}
	}

}
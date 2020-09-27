package it.polito.ezgas.converter;

import it.polito.ezgas.entity.User;
import it.polito.ezgas.dto.UserDto;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Component;

@Component
public class UserConverter {

	public UserDto toUserDto(User user) {

		UserDto udto = new UserDto(user.getUserId(), user.getUserName(), user.getPassword(), user.getEmail(),
				user.getReputation(), user.getAdmin());

		return udto;
	}

	public User toUser(UserDto userdto) {

		User us = new User(userdto.getUserName(), userdto.getPassword(), userdto.getEmail(), userdto.getReputation());
		us.setUserId(userdto.getUserId());
		us.setAdmin(userdto.getAdmin());

		return us;
	}

	public List<User> toUserList(List<UserDto> userDtolist) {

		List<User> userlist = new ArrayList<>();

		for (UserDto usdto : userDtolist)
			userlist.add(this.toUser(usdto));

		return userlist;
	}

	public List<UserDto> toUserDtoList(List<User> userlist) {

		List<UserDto> userDtolist = new ArrayList<>();

		for (User us : userlist)
			userDtolist.add(this.toUserDto(us));

		return userDtolist;
	}

}

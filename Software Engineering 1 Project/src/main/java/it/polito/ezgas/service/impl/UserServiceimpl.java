package it.polito.ezgas.service.impl;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import exception.InvalidLoginDataException;
import exception.InvalidUserException;
import it.polito.ezgas.converter.UserConverter;
import it.polito.ezgas.dto.IdPw;
import it.polito.ezgas.dto.LoginDto;
import it.polito.ezgas.dto.UserDto;
import it.polito.ezgas.entity.User;
import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.service.UserService;

/**
 * Created by softeng on 27/4/2020.
 */
@Service
public class UserServiceimpl implements UserService {

	/*
	 * @Autowired UserRepository userRepository;
	 */

	private UserRepository userRepository;
	/*
	 * @Autowired UserConverter userConverter;
	 */
	private UserConverter userConverter;

	public UserServiceimpl(UserRepository userRepository, UserConverter userConverter) {
		this.userRepository = userRepository;
		this.userConverter = userConverter;
	}

	@Override
	public UserDto getUserById(Integer userId) throws InvalidUserException {
		if (userId < 0)
			throw new InvalidUserException("Invalid user ID");
		if (userRepository.exists(userId)) {
			User user = userRepository.getOne(userId);
			return userConverter.toUserDto(user);
		}
		return null;
	}

	@Override
	public UserDto saveUser(UserDto userDto) {
		if (userDto.getUserId() == null) {
			if (userRepository.findByEmail(userDto.getEmail()) != null) {
				return null;
			}
			User user = userConverter.toUser(userDto);
			user = userRepository.saveAndFlush(user);
			return userConverter.toUserDto(user);
		} else {

			if (userRepository.findByEmail(userDto.getEmail()).getUserId() != userDto.getUserId()) {
				return userDto;
			}
			userRepository.saveAndFlush(userConverter.toUser(userDto));
			return userDto;
		}
	}

	@Override
	public List<UserDto> getAllUsers() {
		List<UserDto> userDtolist = new ArrayList<>();
		userDtolist = userConverter.toUserDtoList(userRepository.findAll());
		return userDtolist;
	}

	@Override
	public Boolean deleteUser(Integer userId) throws InvalidUserException {
		if (userId < 0)
			throw new InvalidUserException("Invalid user ID");
		if (userRepository.exists(userId)) {
			userRepository.delete(userId);
			return true;
		}
		return false;
	}

	@Override
	public LoginDto login(IdPw credentials) throws InvalidLoginDataException {
		// token considered as null, will be used later
		if (credentials.getPw() == null || credentials.getUser() == null)
			throw new InvalidLoginDataException("Invalid user and/or password");
		User user = userRepository.findByEmail(credentials.getUser());
		if (user == null)
			throw new InvalidLoginDataException("Invalid email");
		if (!user.getPassword().equals(credentials.getPw()))
			throw new InvalidLoginDataException("Invalid password for user: " + user.getEmail());
		LoginDto loginDto = new LoginDto(user.getUserId(), user.getUserName(), null, user.getEmail(),
				user.getReputation());
		loginDto.setAdmin(user.getAdmin());
		return loginDto;
	}

	@Override
	public Integer increaseUserReputation(Integer userId) throws InvalidUserException {
		if (userId < 0 || (!userRepository.exists(userId)))
			throw new InvalidUserException("Invalid user ID");
		User user = userRepository.getOne(userId);
		if (user.getReputation() < 5) {
			user.setReputation(user.getReputation() + 1);
			userRepository.saveAndFlush(user);
		}
		return user.getReputation();
	}

	@Override
	public Integer decreaseUserReputation(Integer userId) throws InvalidUserException {
		if (userId < 0 || (!userRepository.exists(userId)))
			throw new InvalidUserException("Invalid user ID");
		User user = userRepository.getOne(userId);
		if (user.getReputation() > -5) {
			user.setReputation(user.getReputation() - 1);
			userRepository.saveAndFlush(user);
		}
		return user.getReputation();
	}

}

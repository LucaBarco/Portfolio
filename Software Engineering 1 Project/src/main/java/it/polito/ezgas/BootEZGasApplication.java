package it.polito.ezgas;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.List;

import javax.annotation.PostConstruct;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import it.polito.ezgas.entity.User;
import it.polito.ezgas.repository.UserRepository;


@SpringBootApplication
public class BootEZGasApplication {
	@Autowired
	UserRepository userRepository;

	

	public static void main(String[] args) {
		SpringApplication.run(BootEZGasApplication.class, args);
	}
	
	@PostConstruct
	public void setupDbWithData() throws SQLException{
	
		
		Connection conn = DriverManager.getConnection("jdbc:h2:./data/memo", "sa", "password");
		conn.close();
		boolean admin=false;
		List<User> users = userRepository.findAll();
		if(!users.isEmpty()) {
		for(User user: users) {
			if(user.getAdmin()) {
				admin=user.getAdmin();
			}
		}
			}
	 if(!admin || users.isEmpty()) {
			User user= new User("admin", "admin", "admin@ezgas.com", 5);
			user.setAdmin(true);
			userRepository.saveAndFlush(user);
		} 
		
		
		/*
		 
		list all the users stored in the database and, if there is no an admin user create it
		 
			User user= new User("admin", "admin", "admin@ezgas.com", 5);
			user.setAdmin(true);
			
		and then save it in the db
	
			
		*/

	}

}

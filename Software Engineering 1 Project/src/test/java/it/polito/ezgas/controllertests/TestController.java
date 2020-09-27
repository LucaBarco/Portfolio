package it.polito.ezgas.controllertests;

import org.junit.Before;
import org.junit.Test;
import org.springframework.beans.factory.annotation.Autowired;

import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;

import exception.GPSDataException;
import exception.PriceException;
import it.polito.ezgas.converter.GasStationConverter;
import it.polito.ezgas.dto.GasStationDto;
import it.polito.ezgas.dto.LoginDto;
import it.polito.ezgas.dto.UserDto;
import it.polito.ezgas.repository.GasStationRepository;
import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.service.GasStationService;
import it.polito.ezgas.service.impl.GasStationServiceimpl;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

import org.apache.http.HttpResponse;
import org.apache.http.client.*;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpDelete;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.FixMethodOrder;
import org.junit.runners.MethodSorters;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class TestController {

	@Autowired
	private GasStationRepository gsRepository;
	@Autowired
	private UserRepository userRepository;

	private GasStationServiceimpl gsService;
	private GasStationConverter gsConverter;

	private GasStationDto gsDto;

	// TEST ON /gasstation
	@Test
	public void TC01_TestsaveGasStation() throws ClientProtocolException, IOException { // /saveGasStation
		CloseableHttpClient client = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost("http://localhost:8080/gasstation/saveGasStation");

		String json = "{\"gasStationName\":\"APItest\","
				+ "\"gasStationAddress\":\"Via Attilio Spinelli, 102 Latiano BR 72022\"," + "\"carSharing\":\"Enjoy\","
				+ "\"hasDiesel\":\"true\"," + "\"hasSuper\":\"true\"," + "\"hasSuperPlus\":\"true\","
				+ "\"hasGas\":\"true\"," + "\"hasMethane\":\"true\"," + "\"lat\":40.5555662," + "\"lon\":17.715888,"
				+ "\"dieselPrice\":0," + "\"superPrice\":0," + "\"superPlusPrice\":0," + "\"gasPrice\":0,"
				+ "\"methanePrice\":0," + "\"reportUser\":0," + "\"reportTimestamp\":\"2020-05-29\"}";

		StringEntity entity = new StringEntity(json);
		httpPost.setEntity(entity);
		httpPost.setHeader("Accept", "application/json");
		httpPost.setHeader("Content-type", "application/json");

		CloseableHttpResponse response = client.execute(httpPost);
		assert (response.getStatusLine().getStatusCode() == 200);
		client.close();
	}

	@Test
	public void TC02_TestgetAllGasStations() throws ClientProtocolException, IOException { // getAllGasStations

		HttpUriRequest request = new HttpGet("http://localhost:8080/gasstation/getAllGasStations");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		System.out.println("--------> Resp getAll: " + response.getEntity().toString());
		assert (response.getStatusLine().getStatusCode() == 200);
		System.out.println("--------> Resp: " + response.toString());
		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		GasStationDto[] gsArray = mapper.readValue(jsonFromResponse, GasStationDto[].class);
		System.out.println(gsArray);
		for (GasStationDto gs : gsArray) {
			System.out.println(gs.getGasStationId() + " " + gs.getGasStationName());
		}
		assert (gsArray.length > 0);
	}
	
	//considering the return type of controller methods (for gs) and the fact that controller tests must be  
	//independent from each other, it is necessary to write the explicit id of a gas station/user. However, it could 
	//work only for a specific DB without the risk to modify/delete a real gas station/user needed by the app.
	@Test
	public void TC03_TestgetGasStationById() throws ClientProtocolException, IOException { // /getGasStation
		HttpUriRequest request = new HttpGet("http://localhost:8080/gasstation/getGasStation/495");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		System.out.println("--------> Resp getAll: " + response.getEntity().toString());

		assert (response.getStatusLine().getStatusCode() == 200);

		System.out.println("--------> Resp: " + response.toString());

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		GasStationDto gs = mapper.readValue(jsonFromResponse, GasStationDto.class);
		System.out.println(gs.getGasStationId());

		assert (gs.getGasStationId().equals(495));

	}

	@Test
	public void TC04_TestgetGasStationByProximity() throws ClientProtocolException, IOException { // /searchGasStationByProximity

		HttpUriRequest request = new HttpGet(
				"http://localhost:8080/gasstation/searchGasStationByProximity/40.5555662/17.715888/1");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		System.out.println("--------> Resp getAll: " + response.getEntity().toString());

		assert (response.getStatusLine().getStatusCode() == 200);

		System.out.println("--------> Resp: " + response.toString());

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		GasStationDto[] gs = mapper.readValue(jsonFromResponse, GasStationDto[].class);

		assert (gs.length > 0);
	}

	@Test
	public void TC06_TestsearchGasStationsByGasolineType() throws ClientProtocolException, IOException { // /searchGasStationByGasolineType
		HttpUriRequest request = new HttpGet("http://localhost:8080/gasstation//searchGasStationByGasolineType/diesel");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		System.out.println("--------> Resp getAll: " + response.getEntity().toString());

		assert (response.getStatusLine().getStatusCode() == 200);

		System.out.println("--------> Resp: " + response.toString());

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		GasStationDto[] gs = mapper.readValue(jsonFromResponse, GasStationDto[].class);

		assert (gs.length > 0);
	}

	@Test
	public void TC07_TestgetGasStationsWithCoordinates() throws ClientProtocolException, IOException { // /getGasStationsWithCoordinates
		HttpUriRequest request = new HttpGet(
				"http://localhost:8080/gasstation/getGasStationsWithCoordinates/40.5555662/17.715888/1/null/Enjoy");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		System.out.println("--------> Resp getAll: " + response.getEntity().toString());

		assert (response.getStatusLine().getStatusCode() == 200);

		System.out.println("--------> Resp: " + response.toString());

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		GasStationDto[] gs = mapper.readValue(jsonFromResponse, GasStationDto[].class);

		assert (gs.length > 0);
	}

	@Test
	public void TC09_TestsetReport() throws ClientProtocolException, IOException { // /setGasStationReport
		CloseableHttpClient client = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost("http://localhost:8080/gasstation/setGasStationReport/");
		String json = "{\"gasStationId\":495,"
				+ "\"dieselPrice\":1.1," + "\"superPrice\":1.16,"
				+ "\"superPrice\":1.29," + "\"superPlusPrice\":1.9," + "\"gasPrice\":0.87,"
				+ "\"methanePrice\":0.96," + "\"premiumDieselPrice\":1.36," + "\"userId\":1," + "\"lon\":17.715888,"
				+ "\"dieselPrice\":0," + "\"superPrice\":0," + "\"superPlusPrice\":0," + "\"gasPrice\":0,"
				+ "\"methanePrice\":0," + "\"reportUser\":0," + "\"reportTimestamp\":\"2020-05-29\"}";

		StringEntity entity = new StringEntity(json);
		httpPost.setEntity(entity);
		httpPost.setHeader("Accept", "application/json");
		httpPost.setHeader("Content-type", "application/json");

		CloseableHttpResponse response = client.execute(httpPost);
		assert (response.getStatusLine().getStatusCode() == 200);

		client.close();
	}

	@Test
	public void TC10_TestdeleteGasStation() throws ClientProtocolException, IOException { // /deleteGasStation,
		HttpUriRequest request = new HttpDelete(
				"http://localhost:8080/gasstation/deleteGasStation/495");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);
		assert (response.getStatusLine().getStatusCode() == 200);
	}

	// TEST ON /user

	@Test
	public void TC11_TestsaveUser() throws ClientProtocolException, IOException { // /saveUser

		CloseableHttpClient client = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost("http://localhost:8080/user/saveUser");

		String json = "{\"userName\":\"test11\"," + "\"password\":\"test11\"," + "\"email\":\"test@test.com\","
				+ "\"reputation\":0," + "\"admin\":false}";

		StringEntity entity = new StringEntity(json);
		httpPost.setEntity(entity);
		httpPost.setHeader("Accept", "application/json");
		httpPost.setHeader("Content-type", "application/json");

		CloseableHttpResponse response = client.execute(httpPost);
		assert (response.getStatusLine().getStatusCode() == 200);

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		Boolean thrown = false;
		JSONObject obj;
		try {
			obj = new JSONObject(jsonFromResponse);
			int newUsId = new Integer(obj.getInt("userId"));
			assert(newUsId>0);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			thrown = true;
			e.printStackTrace();
		}
		assert (thrown == false);
		client.close();
	}

	@Test
	public void TC12_TestgetUserById() throws ClientProtocolException, IOException { // /getUser
		HttpUriRequest request = new HttpGet("http://localhost:8080/user/getUser/1806");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		assert (response.getStatusLine().getStatusCode() == 200);

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		UserDto user = mapper.readValue(jsonFromResponse, UserDto.class);
		assert (user.getUserId().equals(1806));
	}

	@Test
	public void TC13_TestgetAllUsers() throws ClientProtocolException, IOException { // /getAllUsers

		HttpUriRequest request = new HttpGet("http://localhost:8080/user/getAllUsers");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);

		assert (response.getStatusLine().getStatusCode() == 200);

		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		assert (jsonFromResponse.contains("userId"));

		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		UserDto[] userArray = mapper.readValue(jsonFromResponse, UserDto[].class);
		assert (userArray.length > 0);
	}

	@Test
	public void TC14_TestincreaseUserReputation() throws ClientProtocolException, IOException { // /increaseUserReputation
		HttpUriRequest request = new HttpPost(
				"http://localhost:8080/user/increaseUserReputation/1806");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);
		assert (response.getStatusLine().getStatusCode() == 200);
		
		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		Integer reputation = mapper.readValue(jsonFromResponse, Integer.class);
		assert (reputation <= 5);
	}

	@Test
	public void TC15_TestdecreaseUserReputation() throws ClientProtocolException, IOException { // /decreaseUserReputation
		HttpUriRequest request = new HttpPost(
				"http://localhost:8080/user/decreaseUserReputation/1806");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);
		assert (response.getStatusLine().getStatusCode() == 200);
		
		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		Integer reputation = mapper.readValue(jsonFromResponse, Integer.class);
		assert (reputation >= -5);
	}

	@Test
	public void TC16_Testlogin() throws ClientProtocolException, IOException, JSONException { // /login

		CloseableHttpClient client = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost("http://localhost:8080/user/login");

		String json = "{\"user\":\"test@test.com\"," + "\"pw\":\"test11\"}";

		StringEntity entity = new StringEntity(json);
		httpPost.setEntity(entity);
		httpPost.setHeader("Accept", "application/json");
		httpPost.setHeader("Content-type", "application/json");

		CloseableHttpResponse response = client.execute(httpPost);
		assert (response.getStatusLine().getStatusCode() == 200);
		
		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		ObjectMapper mapper = new ObjectMapper().configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
		LoginDto login = mapper.readValue(jsonFromResponse, LoginDto.class);
		assert(login.getUserId().equals(1806));
	}

	@Test
	public void TC17_TestdeleteUser() throws ClientProtocolException, IOException { // /deleteUser
		HttpUriRequest request = new HttpDelete("http://localhost:8080/user/deleteUser/1806");
		HttpResponse response = HttpClientBuilder.create().build().execute(request);
		assert (response.getStatusLine().getStatusCode() == 200);
		
		String jsonFromResponse = EntityUtils.toString(response.getEntity());
		assert (jsonFromResponse.equals("true"));
	}
}

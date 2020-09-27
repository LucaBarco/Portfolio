package it.polito.ezgas.service.impl;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import exception.GPSDataException;
import exception.InvalidCarSharingException;
import exception.InvalidGasStationException;
import exception.InvalidGasTypeException;
import exception.InvalidUserException;
import exception.PriceException;
import it.polito.ezgas.converter.GasStationConverter;
import it.polito.ezgas.dto.GasStationDto;
import it.polito.ezgas.entity.GasStation;
import it.polito.ezgas.entity.User;
import it.polito.ezgas.repository.GasStationRepository;
import it.polito.ezgas.repository.UserRepository;
import it.polito.ezgas.service.GasStationService;

/**
 * Created by softeng on 27/4/2020.
 */
@EnableScheduling
@Service
public class GasStationServiceimpl implements GasStationService {
	private static final int MILLIS_TO_DAYS = 1000 * 3600 * 24;
	private static final int OBSOLESCENCE_50 = 50;
	private static final double LON_DIFF = 0.012733784;
	private static final double LAT_DIFF = 0.0089977776;
//	@Autowired
//	GasStationRepository gasStationRepository;
//	@Autowired
//	GasStationConverter gasStationConverter;
//	@Autowired
//	UserRepository userRepository;

	private boolean updateDependability = false;

	private GasStationRepository gasStationRepository;
	private GasStationConverter gasStationConverter;
	private UserRepository userRepository;

	public GasStationServiceimpl(GasStationRepository gasStationRepository, GasStationConverter gasStationConverter,
			UserRepository userRepository) {
		this.gasStationRepository = gasStationRepository;
		this.gasStationConverter = gasStationConverter;
		this.userRepository = userRepository;
	}

	/*
	 * retrieve a gas station from the DataBase and returns the DTO
	 */
	@Override
	public GasStationDto getGasStationById(Integer gasStationId) throws InvalidGasStationException {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}
		this.checkId(gasStationId);
		GasStation gasStation = gasStationRepository.findOne(gasStationId);
		if (gasStation == null) {
			return null;
		}
		return gasStationConverter.toGasStationDto(gasStation);
	}

	/*
	 * checks if the carSharing has been set to "null" from frontend (BTW the
	 * frontend doesn't do that anymore, but the acceptance tests V2 does), then
	 * creates a list of prices, with only the avaiable ones and calls for
	 * checkPrices. in the end if the gasStationDto refers to a gas station already
	 * in the DB is useless to create a new dto
	 */
	@Override
	public GasStationDto saveGasStation(GasStationDto gasStationDto) throws PriceException, GPSDataException {
		if (gasStationDto.getCarSharing() != null && gasStationDto.getCarSharing().equals("null")) {
			gasStationDto.setCarSharing(null);
		}
		this.checkCoordinates(gasStationDto.getLat(), gasStationDto.getLon());
		List<Double> prices = new ArrayList<Double>();
		if (gasStationDto.getHasDiesel() && gasStationDto.getDieselPrice() != null) {
			prices.add(gasStationDto.getDieselPrice());
		}
		if (gasStationDto.getHasMethane() && gasStationDto.getMethanePrice() != null) {
			prices.add(gasStationDto.getMethanePrice());
		}
		if (gasStationDto.getHasGas() && gasStationDto.getGasPrice() != null) {
			prices.add(gasStationDto.getGasPrice());
		}
		if (gasStationDto.getHasSuper() && gasStationDto.getSuperPrice() != null) {
			prices.add(gasStationDto.getSuperPrice());
		}
		if (gasStationDto.getHasSuperPlus() && gasStationDto.getSuperPlusPrice() != null) {
			prices.add(gasStationDto.getSuperPlusPrice());
		}
		if (gasStationDto.getHasPremiumDiesel() && gasStationDto.getPremiumDieselPrice() != null) {
			prices.add(gasStationDto.getPremiumDieselPrice());
		}
		this.checkPriceList(prices);
		if (gasStationDto.getGasStationId() == null) {
			return gasStationConverter.toGasStationDto(
					gasStationRepository.saveAndFlush(gasStationConverter.toGasStation(gasStationDto)));

		}
		gasStationRepository.saveAndFlush(gasStationConverter.toGasStation(gasStationDto));
		return gasStationDto;
	}

	/*
	 * first checks if the gas stations report dependabilities have been updated
	 * since the startup then returns all the gas stations in the db
	 */
	@Override
	public List<GasStationDto> getAllGasStations() {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}

		return gasStationConverter.toGasStationDtoList(gasStationRepository.findAll());
	}

	public boolean isUpdateDependability() {
		return updateDependability;
	}

	public void setUpdateDependability(boolean updateDependability) {
		this.updateDependability = updateDependability;
	}

	/*
	 * deletes a gas station in the DB, if the repository throws an
	 * EmptyResultDataAccessException the gas station is not present in the DB so it
	 * returns null
	 */
	@Override
	public Boolean deleteGasStation(Integer gasStationId) throws InvalidGasStationException {
		this.checkId(gasStationId);
		try {
			gasStationRepository.delete(gasStationId);
		} catch (EmptyResultDataAccessException e) {
			return null;
		}
		return true;
	}

	/*
	 * first checks if the gas stations report dependabilities have been updated
	 * since the startup calls the right repository method based on the gasolinetype
	 * provided throws an InvalidGasTypeException if the provided gasolinetype
	 * doesn't match with the avaiable ones
	 */
	@Override
	public List<GasStationDto> getGasStationsByGasolineType(String gasolinetype) throws InvalidGasTypeException {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}
		gasolinetype = gasolinetype.toLowerCase().replaceAll("\\s+", "");
		switch (gasolinetype) {
		case "diesel":
			return gasStationConverter.toGasStationDtoList(gasStationRepository.findByhasDiesel(true));
		case "super":
			return gasStationConverter.toGasStationDtoList(gasStationRepository.findByhasSuper(true));
		case "methane":
			return gasStationConverter.toGasStationDtoList(gasStationRepository.findByhasMethane(true));
		case "gas":
			return gasStationConverter.toGasStationDtoList(gasStationRepository.findByhasGas(true));
		case "superplus":
			return gasStationConverter.toGasStationDtoList(gasStationRepository.findByhasSuperPlus(true));
		case "premiumdiesel":
			return gasStationConverter.toGasStationDtoList(gasStationRepository.findByhasPremiumDiesel(true));
		default:
			throw new InvalidGasTypeException("invalid fuel type " + gasolinetype);
		}
	}

	/*
	 * calls for gasStationByProximity with radius 1
	 */
	@Override
	public List<GasStationDto> getGasStationsByProximity(double lat, double lon) throws GPSDataException {
		return this.getGasStationsByProximity(lat, lon, 1);
	}

	/*
	 * first checks if the gas stations report dependabilities have been updated
	 * since the startup returns all the gas stations in the circle specified by
	 * {[x1: lat-(LAT_DIFF *radius), y1:lat-(LON_DIFF *radius)], [x2: lat+(LAT_DIFF
	 * *radius), y2: lat+(LON_DIFF *radius)]} where LAT_DIFF is the difference in
	 * latitude of 2 points distant 1km, same for longitude
	 */
	@Override
	public List<GasStationDto> getGasStationsByProximity(double lat, double lon, int radius) throws GPSDataException {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}
		this.checkCoordinates(lat, lon);
		if (radius <= 0) {
			radius = 1;
		}
		return gasStationConverter
				.toGasStationDtoList(gasStationRepository.findBylatBetweenAndLonBetween(lat - (LAT_DIFF * radius),
						lat + (LAT_DIFF * radius), lon - (LON_DIFF * radius), lon + (LON_DIFF * radius)));
	}

	/*
	 * first checks if the gas stations report dependabilities have been updated
	 * since the startup returns all the gas stations that have the fueltype and
	 * carsharing specified (no filtering if it's null) in the circle specified by
	 * {[x1: lat-(LAT_DIFF *radius), y1:lat-(LON_DIFF *radius)], [x2: lat+(LAT_DIFF
	 * *radius), y2: lat+(LON_DIFF *radius)]} where LAT_DIFF is the difference in
	 * latitude of 2 points distant 1km, same for longitude it generates a list of
	 * all the gas stations in the area and then removes some according to filters
	 * using two different lists to avoid concurrent access to memory
	 */
	@Override
	public List<GasStationDto> getGasStationsWithCoordinates(double lat, double lon, int radius, String gasolinetype,
			String carsharing) throws InvalidGasTypeException, GPSDataException, InvalidCarSharingException {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}
		this.checkCoordinates(lat, lon);
		this.checkCarSharing(carsharing);
		if (radius <= 0) {
			radius = 1;
		}
		List<GasStation> gasStationList = gasStationRepository.findBylatBetweenAndLonBetween(lat - (LAT_DIFF * radius),
				lat + (LAT_DIFF * radius), lon - (LON_DIFF * radius), lon + (LON_DIFF * radius));
		List<GasStation> gasStationListNew = new ArrayList<>(gasStationList);
		if (carsharing != null && !carsharing.equals("null")) {
			for (GasStation gs : gasStationList) {
				if (gs.getCarSharing() == null || !gs.getCarSharing().equals(carsharing)) {
					gasStationListNew.remove(gs);
				}
			}
		}
		if (gasolinetype != null && !gasolinetype.equals("null")) {
			gasolinetype = gasolinetype.toLowerCase().replaceAll("\\s+", "");
			switch (gasolinetype) {
			case "diesel":
				for (GasStation gs : gasStationList) {
					if (!gs.getHasDiesel()) {
						gasStationListNew.remove(gs);

					}
				}
				break;
			case "super":
				for (GasStation gs : gasStationList) {
					if (!gs.getHasSuper()) {
						gasStationListNew.remove(gs);
					}
				}
				break;
			case "methane":
				for (GasStation gs : gasStationList) {
					if (!gs.getHasMethane()) {
						gasStationListNew.remove(gs);
					}
				}
				break;
			case "gas":
				for (GasStation gs : gasStationList) {
					if (!gs.getHasGas()) {
						gasStationListNew.remove(gs);
					}
				}
				break;
			case "superplus":
				for (GasStation gs : gasStationList) {
					if (!gs.getHasSuperPlus()) {
						gasStationListNew.remove(gs);
					}
				}
				break;
			case "premiumdiesel":
				for (GasStation gs : gasStationList) {
					if (!gs.getHasPremiumDiesel()) {
						gasStationListNew.remove(gs);
					}
				}
				break;
			default:
				throw new InvalidGasTypeException("invalid gas type " + gasolinetype);
			}
		}
		return gasStationConverter.toGasStationDtoList(gasStationListNew);
	}

	/*
	 * first checks if the gas stations report dependabilities have been updated
	 * since the startup returns all the gas stations that have the fueltype and
	 * carsharing specified (no filtering if it's null)
	 */
	@Override
	public List<GasStationDto> getGasStationsWithoutCoordinates(String gasolinetype, String carsharing)
			throws InvalidGasTypeException, InvalidCarSharingException {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}
		checkCarSharing(carsharing);

		if ((carsharing == null || carsharing.equals("null"))
				&& (gasolinetype != null && !gasolinetype.equals("null"))) {
			return getGasStationsByGasolineType(gasolinetype);
		}
		if ((carsharing != null && !carsharing.equals("null"))
				&& (gasolinetype == null || gasolinetype.equals("null"))) {
			return getGasStationByCarSharing(carsharing);
		}
		gasolinetype = gasolinetype.toLowerCase().replaceAll("\\s+", "");
		switch (gasolinetype) {
		case "diesel":
			return gasStationConverter
					.toGasStationDtoList(gasStationRepository.findByhasDieselAndCarSharing(true, carsharing));
		case "super":
			return gasStationConverter
					.toGasStationDtoList(gasStationRepository.findByhasSuperAndCarSharing(true, carsharing));
		case "methane":
			return gasStationConverter
					.toGasStationDtoList(gasStationRepository.findByhasMethaneAndCarSharing(true, carsharing));
		case "gas":
			return gasStationConverter
					.toGasStationDtoList(gasStationRepository.findByhasGasAndCarSharing(true, carsharing));
		case "superplus":
			return gasStationConverter
					.toGasStationDtoList(gasStationRepository.findByhasSuperPlusAndCarSharing(true, carsharing));
		case "premiumdiesel":
			return gasStationConverter
					.toGasStationDtoList(gasStationRepository.findByhasPremiumDieselAndCarSharing(true, carsharing));
		default:
			throw new InvalidGasTypeException("invalid gas type " + gasolinetype);
		}
	}

	/*
	 * updates the prices of a gas station (CR4) checks if the user trying to update
	 * prices has a lower reputation if it is lower then checks how many days passed
	 * if the update attempt is consistent with UC7 the prices are updated
	 */
	@Override
	public void setReport(Integer gasStationId, Double dieselPrice, Double superPrice, Double superPlusPrice,
			Double gasPrice, Double methanePrice, Double premiumDieselPrice, Integer userId)
			throws InvalidGasStationException, PriceException, InvalidUserException {
		this.checkId(gasStationId);
		DateFormat formatter = new SimpleDateFormat("MM-dd-YYYY");
		GasStation gasStation = gasStationRepository.findOne(gasStationId);
		if (gasStation != null) {
			User user1 = userRepository.findOne(userId);
			if (user1 == null || userId < 0) {
				throw new InvalidUserException("User id non valid " + userId);
			}
			if (gasStation != null && gasStation.getReportUser()!= null) {
				User user2 = userRepository.findOne(gasStation.getReportUser());
				if (user2 != null) { // otherwise gasStation has never had a report
					Date oldDate;
					Date newDate; // current date, the one of user1

					try {
						newDate =  formatter.parse(formatter.format(new Date(System.currentTimeMillis()))); 
						oldDate = formatter.parse(gasStation.getReportTimestamp());
					} catch (ParseException e) {
						e.printStackTrace();
						return;
					}
					
					int passedDays =  (int) ((newDate.getTime() - oldDate.getTime())/MILLIS_TO_DAYS);
					if (user2.getReputation() > user1.getReputation()
							&& passedDays<4) { // time in milliseconds
						// in this case, the last report is still valid -> no update
						return;
					}
				}
			}

			List<Double> prices = new ArrayList<Double>();
			if (gasStation.getHasDiesel()) {
				prices.add(dieselPrice);
				gasStation.setDieselPrice(dieselPrice);
			}
			if (gasStation.getHasMethane()) {
				prices.add(methanePrice);
				gasStation.setMethanePrice(methanePrice);
			}
			if (gasStation.getHasGas()) {
				prices.add(gasPrice);
				gasStation.setGasPrice(gasPrice);
			}
			if (gasStation.getHasSuper()) {
				prices.add(superPrice);
				gasStation.setSuperPrice(superPrice);
			}
			if (gasStation.getHasSuperPlus()) {
				prices.add(superPlusPrice);
				gasStation.setSuperPlusPrice(superPlusPrice);
			}
			if (gasStation.getHasPremiumDiesel()) {
				prices.add(premiumDieselPrice);
				gasStation.setPremiumDieselPrice(premiumDieselPrice);
			}
			this.checkPriceList(prices);
			User user = userRepository.findOne(userId);
			gasStation.setUser(user);
			gasStation.setReportTimestamp(formatter.format(new Date(System.currentTimeMillis())));
			gasStation.setReportDependability((OBSOLESCENCE_50 * (user.getReputation() + 5) / 10) + OBSOLESCENCE_50);
			gasStation.setReportUser(user.getUserId());
			gasStationRepository.saveAndFlush(gasStation);
		} else {
			throw new InvalidGasStationException("Invalid gas station " + gasStationId);
		}
	}

	/*
	 * first checks if the gas stations report dependabilities have been updated
	 * then returns all gas stations having the right carsharing specified in
	 * carSharing
	 */
	@Override
	public List<GasStationDto> getGasStationByCarSharing(String carSharing) {
		if (!updateDependability) {
			this.calculateDependability();
			this.updateDependability = true;
		}
		return gasStationConverter.toGasStationDtoList(gasStationRepository.findByCarSharing(carSharing));
	}

	/*
	 * checks if a gas station id is positive otherwise throws an
	 * InvalidGasStationException
	 */
	private void checkId(Integer gasStationId) throws InvalidGasStationException {
		if (gasStationId <= 0) {
			throw new InvalidGasStationException("No gas station with this ID " + gasStationId);
		}
	}

	/*
	 * checks if a carSharing is supported otherwise throws an
	 * InvalidCarSharingException
	 */
	private void checkCarSharing(String carsharing) throws InvalidCarSharingException {
		if (carsharing != null) {
			carsharing = carsharing.toLowerCase().replaceAll("\\s+", "");
			if (!carsharing.equals("null") && !carsharing.equals("enjoy") && !carsharing.equals("car2go")) {
				throw new InvalidCarSharingException("invalid car sharing " + carsharing);
			}
		}
	}

	/*
	 * checks if a list of prices is valid (positive and not null) otherwise throws
	 * a PriceException
	 */
	private void checkPriceList(List<Double> prices) throws PriceException {
		for (Double price : prices) {
			if (price != null && price < 0) {

				throw new PriceException("Negative price is not valid");
			}
		}
	}

	/*
	 * checks if coordinates are consistent with the NFR6 coordinate format
	 * otherwise throws a GPSDataException
	 */
	private void checkCoordinates(double lat, double lon) throws GPSDataException {
		if (!String.valueOf(lat).matches("^[-+]?([1-8]?\\d(\\.\\d+)?|90(\\.0+)?)$")) {
			throw new GPSDataException("Invalid latitude");
		}
		if (!String.valueOf(lon).matches("^[-+]?(180(\\.0+)?|((1[0-7]\\d)|([1-9]?\\d))(\\.\\d+)?)$")) {
			throw new GPSDataException("Invalid longitude");
		}
	}

	/*
	 * scheduled to start every day at midnight updates all gas station report
	 * dependabilities with the current day 
	 * in case of date parsing error skips that gas station
	 * 
	 */
	@Scheduled(cron = "0 0 0 * * *")
	private void calculateDependability() {
		DateFormat formatter = new SimpleDateFormat("MM-dd-YYYY");
		for (GasStation gs : gasStationRepository.findAll()) {
			if (gs.getReportUser() != null && gs.getReportUser() > 0 && gs.getUser() != null) {
				Date oldDate;
				Date newDate;
				try {
					newDate =  formatter.parse(formatter.format(new Date(System.currentTimeMillis()))); 
					oldDate = formatter.parse(gs.getReportTimestamp());
				} catch (ParseException e) {
					e.printStackTrace();
					continue;
				}
			
				if ((newDate.getTime() - oldDate.getTime())/MILLIS_TO_DAYS > 7) // if it's the same year just count days
				{
					gs.setReportDependability(Math.round(OBSOLESCENCE_50 * (gs.getUser().getReputation() + 5) / 10));
					gasStationRepository.saveAndFlush(gs);
				} else {
					gs.setReportDependability(
							Math.round(OBSOLESCENCE_50 * (gs.getUser().getReputation() + 5) / 10 + OBSOLESCENCE_50
									* (1 - ((double) ((newDate.getTime() - oldDate.getTime())/MILLIS_TO_DAYS ) / 7))));
					gasStationRepository.saveAndFlush(gs);
				}
			}
		}
	}
}

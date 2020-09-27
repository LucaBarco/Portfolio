package it.polito.ezgas.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import it.polito.ezgas.entity.GasStation;

@Repository
public interface GasStationRepository extends JpaRepository<GasStation, Integer> {

	GasStation findBygasStationName(String name);

	List<GasStation> findBylatBetweenAndLonBetween(double lat1, double lat2, double lon1, double lon2);

	List<GasStation> findByhasDiesel(boolean fuel);

	List<GasStation> findByhasSuper(boolean fuel);

	List<GasStation> findByhasGas(boolean fuel);

	List<GasStation> findByhasSuperPlus(boolean fuel);

	List<GasStation> findByhasMethane(boolean fuel);
	
	List<GasStation> findByhasPremiumDiesel(boolean fuel);
	
	List<GasStation> findByhasDieselAndCarSharing(boolean fuel, String carSharing);

	List<GasStation> findByhasSuperAndCarSharing(boolean fuel, String carSharing);

	List<GasStation> findByhasGasAndCarSharing(boolean fuel, String carSharing);

	List<GasStation> findByhasSuperPlusAndCarSharing(boolean fuel, String carSharing);

	List<GasStation> findByhasMethaneAndCarSharing(boolean fuel, String carSharing);
	
	List<GasStation> findByhasPremiumDieselAndCarSharing(boolean fuel, String carSharing);
		
	List<GasStation> findByCarSharing(String carSharing);

}

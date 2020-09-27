package it.polito.ezgas.converter;

import it.polito.ezgas.entity.GasStation;
import it.polito.ezgas.dto.GasStationDto;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class GasStationConverter {
	
	UserConverter userConverter= new UserConverter();

	public GasStationDto toGasStationDto(GasStation gasStation) {
		

		GasStationDto gsDto = new GasStationDto(gasStation.getGasStationId(), gasStation.getGasStationName(),
				gasStation.getGasStationAddress(), gasStation.getHasDiesel(), gasStation.getHasSuper(),
				gasStation.getHasSuperPlus(), gasStation.getHasGas(), gasStation.getHasMethane(), gasStation.getHasPremiumDiesel(),
				gasStation.getCarSharing(), gasStation.getLat(), gasStation.getLon(), gasStation.getDieselPrice(),
				gasStation.getSuperPrice(), gasStation.getSuperPlusPrice(), gasStation.getGasPrice(),
				gasStation.getMethanePrice(), gasStation.getPremiumDieselPrice(), gasStation.getReportUser(), gasStation.getReportTimestamp(),
				gasStation.getReportDependability());
		if(gasStation.getUser()!=null) 
		gsDto.setUserDto(userConverter.toUserDto(gasStation.getUser()));
		
		return gsDto;
	}

	public GasStation toGasStation(GasStationDto gasStationdto) {

		GasStation gs = new GasStation(gasStationdto.getGasStationName(), gasStationdto.getGasStationAddress(),
				gasStationdto.getHasDiesel(), gasStationdto.getHasSuper(), gasStationdto.getHasSuperPlus(),
				gasStationdto.getHasGas(), gasStationdto.getHasMethane(), gasStationdto.getHasPremiumDiesel(), gasStationdto.getCarSharing(),
				gasStationdto.getLat(), gasStationdto.getLon(), gasStationdto.getDieselPrice(),
				gasStationdto.getSuperPrice(), gasStationdto.getSuperPlusPrice(), gasStationdto.getGasPrice(),
				gasStationdto.getMethanePrice(), gasStationdto.getPremiumDieselPrice(), gasStationdto.getReportUser(), gasStationdto.getReportTimestamp(),
				gasStationdto.getReportDependability());

		gs.setGasStationId(gasStationdto.getGasStationId());
		
		if(gasStationdto.getUserDto()!=null) 
			gs.setUser(userConverter.toUser(gasStationdto.getUserDto()));

		return gs;
	}

	public List<GasStation> toGasStationList(List<GasStationDto> gasStationdtolist) {

		List<GasStation> gasStationlist = new ArrayList<>();

		for (GasStationDto gsDto : gasStationdtolist)
			gasStationlist.add(this.toGasStation(gsDto));

		return gasStationlist;
	}

	public List<GasStationDto> toGasStationDtoList(List<GasStation> gasStationlist) {

		List<GasStationDto> gasStationdtolist = new ArrayList<>();

		for (GasStation gs : gasStationlist)
			gasStationdtolist.add(this.toGasStationDto(gs));

		return gasStationdtolist;
	}

}

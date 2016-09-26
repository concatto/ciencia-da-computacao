package drivermanager.factories;

import drivermanager.ResolutionType;

public class DriverFactoryCreator {
	public static DriverFactory createDriverFactory(ResolutionType type) {
		switch (type) {
		case HIGH:
			return new HighResolutionDriverFactory();
		case LOW:
			return new LowResolutionDriverFactory();
		}
		
		return null;
	}
}

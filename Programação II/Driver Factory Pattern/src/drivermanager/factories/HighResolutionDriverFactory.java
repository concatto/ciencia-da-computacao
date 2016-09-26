package drivermanager.factories;

import drivermanager.drivers.PrinterDriver;
import drivermanager.drivers.VideoDriver;
import drivermanager.drivers.highres.HighResolutionPrinterDriver;
import drivermanager.drivers.highres.HighResolutionVideoDriver;

public class HighResolutionDriverFactory implements DriverFactory {

	@Override
	public PrinterDriver createPrinterDriver() {
		return new HighResolutionPrinterDriver();
	}

	@Override
	public VideoDriver createVideoDriver() {
		return new HighResolutionVideoDriver();
	}

}

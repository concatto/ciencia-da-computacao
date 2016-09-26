package drivermanager.factories;

import drivermanager.drivers.PrinterDriver;
import drivermanager.drivers.VideoDriver;
import drivermanager.drivers.lowres.LowResolutionPrinterDriver;
import drivermanager.drivers.lowres.LowResolutionVideoDriver;

public class LowResolutionDriverFactory implements DriverFactory {

	@Override
	public PrinterDriver createPrinterDriver() {
		return new LowResolutionPrinterDriver();
	}

	@Override
	public VideoDriver createVideoDriver() {
		return new LowResolutionVideoDriver();
	}

}

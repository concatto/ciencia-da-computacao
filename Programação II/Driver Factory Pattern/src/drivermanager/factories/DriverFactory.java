package drivermanager.factories;

import drivermanager.drivers.PrinterDriver;
import drivermanager.drivers.VideoDriver;

public interface DriverFactory {
	PrinterDriver createPrinterDriver();
	VideoDriver createVideoDriver();
}

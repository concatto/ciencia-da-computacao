package drivermanager.drivers.lowres;

import drivermanager.drivers.PrinterDriver;

public class LowResolutionPrinterDriver implements PrinterDriver {

	@Override
	public void print() {
		System.out.println("Printing with low resolution.");
	}

}

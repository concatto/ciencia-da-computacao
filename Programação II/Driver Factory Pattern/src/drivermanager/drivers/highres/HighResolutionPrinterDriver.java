package drivermanager.drivers.highres;

import drivermanager.drivers.PrinterDriver;

public class HighResolutionPrinterDriver implements PrinterDriver {

	@Override
	public void print() {
		System.out.println("Printing with high resolution!");
	}
	
}

package drivermanager.drivers.lowres;

import drivermanager.drivers.VideoDriver;

public class LowResolutionVideoDriver implements VideoDriver{

	@Override
	public void display() {
		System.out.println("Displaying video with low resolution.");
	}

}

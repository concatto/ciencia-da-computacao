package drivermanager.drivers.highres;

import drivermanager.drivers.VideoDriver;

public class HighResolutionVideoDriver implements VideoDriver {

	@Override
	public void display() {
		System.out.println("Displaying video with high resolution!");
	}

}

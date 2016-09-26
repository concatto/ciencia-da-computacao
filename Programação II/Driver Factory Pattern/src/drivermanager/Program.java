package drivermanager;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;

import drivermanager.factories.DriverFactory;
import drivermanager.factories.DriverFactoryCreator;

public class Program {
	private DriverFactory driverFactory;
	
	public Program() {
		try {
			UIManager.setLookAndFeel(new NimbusLookAndFeel());
		} catch (UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
		
		MainWindow window = new MainWindow();
		
		window.onCreateVideo(() -> driverFactory.createVideoDriver().display());
		window.onCreatePrinter(() -> driverFactory.createPrinterDriver().print());
		window.onSelect(() -> initDriverFactory(window.getSelectedResolution()));
		
		
		initDriverFactory(window.getSelectedResolution());
		window.setVisible(true);
	}
	
	private void initDriverFactory(ResolutionType type) {
		driverFactory = DriverFactoryCreator.createDriverFactory(type);
	}

	public static void main(String[] args) {
		new Program();
	}

}

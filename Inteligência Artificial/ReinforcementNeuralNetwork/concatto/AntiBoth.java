package concatto;
import robocode.*;
import robocode.util.*;
import java.util.*;
import java.io.*;
//import java.awt.Color;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

public class AntiBoth extends AdvancedRobot
{
	static class TrackingEvent {
		public double selfX;
		public double selfY;
		public double selfEnergy;
		public double selfGunHeading;
		public int enemyCount;
		public double targetDistance;
		public double targetHeading;
		public double targetBearing;
		public double targetEnergy;
		public double targetVelocity;
		public double deltaGunHeading;
		public boolean hit;
	}

	private final double MAX_ENERGY = 200;
	private double maxDistance;
	private List<TrackingEvent> events = new ArrayList<TrackingEvent>();
	private TrackingEvent currentEvent = new TrackingEvent();
	private boolean collecting = false;

	private int totalEvents = 0;
	private int hits = 0;
	private int misses = 0;

	// Neural network weights
	private double[][] hiddenWeights;
	private double[] hiddenBiases;

	private double[][] outputWeights;
	private double[] outputBiases;

	private double coefficient = 0;

	public void run() {
		double w = getBattleFieldWidth();
		double h = getBattleFieldHeight();
		maxDistance = Math.sqrt(w * w + h * h);
		// Initialization of the robot should be put here

		// After trying out your robot, try uncommenting the import at the top,
		// and the next line:

		setAdjustGunForRobotTurn(true); // Keep the gun still when we turn
		// setColors(Color.red,Color.blue,Color.green); // body,gun,radar

		double[][] hiddenWeights = {{-0.8464529199731088, 0.18678671180039352, 0.3846671774594549, 1.7026463668767133, -0.28810728735643604, -0.69768252200725, 1.8070418628102094, 0.9753904208224662, 1.3066199789162913, 3.120958847292515},                                                                  
{-0.06374396598366275, 0.20914371440699342, -0.9336429978559994, 0.7321766473666029, 0.6636120381140443, -1.7323174022640908, 0.004053879298701576, 1.356421848210041, 1.3439755414279257, 2.0923027518857937},                                                               
{-2.7093767954363304, -0.6305559869563921, -0.27915292073637327, -0.7582647772475859, -0.4542724044822048, -2.267830150870737, 1.441850414537509, 2.7161203070880586, 0.36347480499704354, 4.366349031963982},                                                                
{-1.1472542020892833, 1.2161478431377688, -0.6819488586566537, 2.805797659190632, 1.641145642851932, -3.036241068969049, -0.3938564854750717, 1.0667104386133537, 1.9406859074247358, 1.265683184817125},                                                                     
{-2.2133182661104494, -0.9662126348530545, -0.8313356174498917, -0.18539031351551916, 0.219376929726792, -0.9956289238093873, 0.5291389318196201, 1.322094606817329, 0.6097794022042826, 0.5677350140604792},                                                                 
{0.5982059196968399, 0.4253814329167033, -1.2160183413116024, 0.27500110476562856, 1.0995277444450493, -2.5976476193332134, 1.1233667751721736, 1.3653274911078463, 0.42127723370473363, 1.6759928521559562},                                                                 
{0.14899405758332132, -1.5025871590844617, 0.24727150281899749, 0.2210407701021572, -0.7459274686208964, -1.7323553738848672, 0.3671559725264182, 0.540171369738498, 1.7481423572855783, 3.710167695910891},                                                                  
{-0.8966593430148002, 1.436724178923774, -2.602665828211898, 1.1363294748080648, 0.8447278038520638, 0.4414426357119893, 0.552530323163388, 0.30541567556073923, 0.09969113282882892, 0.6625027417724096},                                                                    
{-0.9561938622905244, -0.2650573807497027, 0.34492098061410764, 0.4238606737486469, 0.8782934124441047, -1.487203375215565, -0.7585193245657571, 2.976075640218801, 0.2899758324078636, 0.6443167479430361}};

		double[] hiddenBiases = {-0.40223892065114214, 2.919110750069938, -1.0467497176423162, 0.3184481812165982, 0.4717305036627897, 0.3988325803776176, 1.452484932236769, 0.26525732595463614, 1.1108753474668345, -0.5775030161586392};

		double[][]outputWeights = {{0.3428871914020611},                                                                                                                                                                                                                                                         
{-0.7198811304874183},
{1.3820719662117589},
{0.29826411112893875},
{-0.16648795197509816},
{-0.8729272221847241},
{0.18863159614860822},
{0.9269017316502609},
{2.094414542869688},
{-1.2902925509709542}};


		double[] outputBiases = {-0.40938988514810476};
		
		this.hiddenWeights = hiddenWeights;
		this.hiddenBiases = hiddenBiases;
		this.outputWeights = outputWeights;
		this.outputBiases = outputBiases;
		this.coefficient = 106.92661716848468;

		while(true) {
			// Replace the next 4 lines with any behavior you would like
			ahead(100);
			turnGunRight(360);
			back(100);
			turnGunRight(360);
		}
	}

	/**
	 * onScannedRobot: What to do when you see another robot
	 */
	public void onScannedRobot(ScannedRobotEvent e) {
		// Replace the next line with any behavior you would like
		
		if (getGunHeat() == 0) {

			double absoluteBearing = getHeading() + e.getBearing();
			double bearingFromGun = Utils.normalRelativeAngleDegrees(absoluteBearing - getGunHeading());
			out.println("Bearing from gun: " + bearingFromGun);			

			currentEvent.selfX = getX() / getBattleFieldWidth();
			currentEvent.selfY = getY() / getBattleFieldHeight();
			currentEvent.selfEnergy = getEnergy() / MAX_ENERGY;
			currentEvent.selfGunHeading = getGunHeading() / 360;
			currentEvent.enemyCount = getOthers();
			currentEvent.targetDistance = e.getDistance() / maxDistance;
			currentEvent.targetHeading = e.getHeading() / 360;
			currentEvent.targetBearing = e.getBearing() / 360;
			currentEvent.targetEnergy = e.getEnergy() / MAX_ENERGY;
			currentEvent.targetVelocity = e.getVelocity() / Rules.MAX_VELOCITY;
	
			double deltaHeading = 0;
			if (collecting) {
				double degrees = 180;
				deltaHeading = (Math.random() * degrees) - (degrees * 0.5) + bearingFromGun;
			} else {
				deltaHeading = feedforward(currentEvent);
			}
			out.println("Change in gun heading: " + deltaHeading);
	
			turnGunRight(deltaHeading);
			
			currentEvent.deltaGunHeading = deltaHeading;
			fire(1);
		}
	}

	/**
	 * onHitByBullet: What to do when you're hit by a bullet
	 */
	public void onHitByBullet(HitByBulletEvent e) {
		// Replace the next line with any behavior you would like
		back(50);
	}
	
	/**
	 * onHitWall: What to do when you hit a wall
	 */
	public void onHitWall(HitWallEvent e) {
		// Bounce off!
		back(50);
	}
	
	public void onRoundEnded(RoundEndedEvent e) {
		writeAccuracy();
		writeData();
	}
	
	public void onDeath(DeathEvent e) {
		writeData();
	}
	
	private void writeData() {
		if (collecting) {
			try {
				BufferedWriter writer = new BufferedWriter(new RobocodeFileWriter(getDataFile("track.csv").toString(), true));
				for (TrackingEvent event : events) {
					writer.write(String.valueOf(event.selfX) + ",");
					writer.write(String.valueOf(event.selfY) + ",");
					writer.write(String.valueOf(event.selfEnergy) + ",");
					writer.write(String.valueOf(event.selfGunHeading) + ",");
					writer.write(String.valueOf(event.enemyCount) + ",");
					writer.write(String.valueOf(event.targetDistance) + ",");
					writer.write(String.valueOf(event.targetHeading) + ",");
					writer.write(String.valueOf(event.targetBearing) + ",");
					writer.write(String.valueOf(event.targetEnergy) + ",");
					writer.write(String.valueOf(event.targetVelocity) + ",");
					writer.write(String.valueOf(event.deltaGunHeading) + ",");
					writer.write(String.valueOf(event.hit));
					writer.newLine();
				}
				
				writer.close();
				events.clear();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}
	
	public void onBulletHit(BulletHitEvent e) {
		currentEvent.hit = true;
		writeEvent();		
	}
	
	public void onBulletMissed(BulletMissedEvent e) {
		currentEvent.hit = false;
		writeEvent();
	}
	
	private void writeEvent() {
		if (currentEvent.selfEnergy > 0) {
			totalEvents++;
			if (currentEvent.hit == true) {
				hits++;
			} else {
				misses++;
			}
			events.add(currentEvent);
			currentEvent = new TrackingEvent();
		}
	}
	
	public void writeAccuracy() {
		try {
			BufferedWriter writer = new BufferedWriter(new RobocodeFileWriter(getDataFile("accuracies.csv").toString(), true));

			double accuracy = totalEvents == 0 ? 0 : hits / (double) totalEvents;
			writer.write(getRoundNum() + "," + accuracy);
			writer.newLine();
			
			writer.close();
			
			totalEvents = 0;
			hits = 0;
			misses = 0;
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	
	private double feedforward(TrackingEvent input) {
		double[][] a = new double[1][9];
		
		a[0][0] = input.selfX;
		a[0][1] = input.selfY;
		a[0][2] = input.selfEnergy;
		a[0][3] = input.selfGunHeading;
		a[0][4] = input.targetDistance;
		a[0][5] = input.targetHeading;
		a[0][6] = input.targetBearing;
		a[0][7] = input.targetEnergy;
		a[0][8] = input.targetVelocity;
		
		double[][] values = multiply(a, hiddenWeights);
		addBiases(values, hiddenBiases);
		activate(values);
		
		values = multiply(values, outputWeights);
		addBiases(values, outputBiases);
		activate(values);
		
		scale(values, coefficient);
		
		return values[0][0];
	}
	
	private double[][] multiply(double[][] a, double[][] b) {
		int aCols = a[0].length;
        int bRows = b.length;

		if (aCols != bRows) {
			System.out.println("Can't multiply " + aCols + " columns with " + bRows + " rows!!!");
			return null;
		}

        int aRows = a.length;
        int bCols = b[0].length;
		
        double[][] result = new double[aRows][bCols];
        for (int i = 0; i < aRows; i++) {
            for (int j = 0; j < bCols; j++) {
                for (int k = 0; k < aCols; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
		
        return result;
	}
	
	private void addBiases(double[][] matrix, double[] biases) {
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[i].length; j++) {
				matrix[i][j] += biases[j];
			}
		}
	}
	
	private void activate(double[][] matrix) {
		for (int i = 0; i < matrix.length; i++) {			
			for (int j = 0; j < matrix[i].length; j++) {
				matrix[i][j] = applyActivation(matrix[i][j]);
			}
		}
	}
	
	private double applyActivation(double value) {
		return Math.tanh(value);
	}
	
	private void scale(double[][] matrix, double alpha) {
		for (int i = 0; i < matrix.length; i++) {			
			for (int j = 0; j < matrix[i].length; j++) {
				matrix[i][j] *= alpha;
			}
		}
	}
}

package concatto;
import robocode.*;
import robocode.util.*;
import java.util.*;
import java.io.*;
//import java.awt.Color;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

public class AntiWalls extends AdvancedRobot
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

		double[][] hiddenWeights = {{1.4668931330296784, 1.3242007893605838, 1.4659034334127594, -0.9974692588767827, -0.04498000717155601, 1.9715913100302807, -0.8151842353863871, -0.08287049806249995, 0.8521960653582107, 1.7721767710929928},                                                              
{-0.5154636597722773, -0.22952251831731482, 1.1156423928823516, -1.969777907633632, 1.7230946142237007, 0.07793689799506992, -0.8949583448594455, -1.4966762726784235, 0.9551232103293814, 0.663889125912044},                                                                
{1.3825402206790247, 1.2626763736874809, -0.0978041621364441, -1.2258714482656823, 0.20052954283153637, 1.5276320661206126, -0.9538602950942469, -1.456744116567031, 1.1833142192084714, 3.1541319091081217},                                                                 
{0.11406122403591823, 0.8794116282553432, 0.04378113452142435, -1.090183443148731, 1.927770599553607, 0.2851555343671114, -0.18552156394012995, -2.290290137109638, 0.20574007847216386, 1.7534212017515078},                                                                 
{-0.7723603757845496, -1.1633579659057098, 0.10724045582061817, 0.6537148356849739, -0.17737406662985625, 1.5078800276030182, -1.609928177287737, 0.009311338423875576, -1.5915267354138116, 1.7637886642653244},                                                             
{-0.4169229437961726, 1.4835810393326678, 1.6113614044291202, -0.4896552014657103, 0.06712069110447969, -0.580646377211007, -0.3301210787571963, -1.2947281025060626, -0.8311438867550902, -0.06460773731763522},                                                             
{0.9919223573061382, -0.3321154477939898, -0.34023134650606457, -0.43900414909260244, 0.859158972649957, 1.684295327795676, -1.0584272120197025, -2.507706655421921, -1.0081970875846575, -1.0177029211292625},                                                               
{1.5336627468413988, 2.4719143960029206, 0.9605455911456746, -0.8904234480256398, 3.14924093310811, 1.9176606155473546, -1.823276454036642, 0.44367690178460817, -0.8957001914084133, -0.313490663351786},                                                                    
{-0.06528463433325918, 0.897801628140207, 0.6406299065465146, -1.9480791693746942, 1.4666279015190689, -1.2437751082551203, -0.4332230285383514, -0.5140523332957813, 1.0041375741800689, 1.2486389712318198}};

		double[] hiddenBiases = {1.1435359557059492, 0.7771621752219603, 0.8377809457423792, -0.5544191764755904, 0.6575640089594929, 1.4857546231582557, -0.414391072079661, -0.21159744931550076, -0.39619927985036235, 0.8243185232153258};

		double[][] outputWeights = {{0.7022451510198481},
{-1.8294496552679607},
{-1.7501170378139763},
{-0.8024813742094962},
{1.49109841343242},
{-1.6018789767058368},
{-1.26779306437567},
{-0.2022717859002915},
{0.05380988933022734},
{1.6342821448414215}};


		double[] outputBiases = {-0.8342455499845837};
		
		this.hiddenWeights = hiddenWeights;
		this.hiddenBiases = hiddenBiases;
		this.outputWeights = outputWeights;
		this.outputBiases = outputBiases;
		this.coefficient = 98.01334779632978;

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

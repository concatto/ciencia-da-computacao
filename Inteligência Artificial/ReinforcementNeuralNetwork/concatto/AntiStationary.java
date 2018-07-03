package concatto;
import robocode.*;
import robocode.util.*;
import java.util.*;
import java.io.*;
//import java.awt.Color;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

/**
 * NeuralBot - a robot by (your name here)
 */
public class AntiStationary extends AdvancedRobot
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

	/**
	 * run: NeuralBot's default behavior
	 */
	public void run() {
		double w = getBattleFieldWidth();
		double h = getBattleFieldHeight();
		maxDistance = Math.sqrt(w * w + h * h);
		// Initialization of the robot should be put here

		// After trying out your robot, try uncommenting the import at the top,
		// and the next line:

		setAdjustGunForRobotTurn(true); // Keep the gun still when we turn
		// setColors(Color.red,Color.blue,Color.green); // body,gun,radar

		double[][] hiddenWeights = {{-1.1432976084715227, -0.20374098184026385, 1.6885845792726337, -0.8200975100244668, 1.5871307178474114, -0.037996434192604345, 1.3873298006466943, 3.1460700243134787, 1.0928780961091864, -0.756402901109176},                                                             
{0.33317629978440955, 0.2976885800186065, 0.6244952022186016, -2.234118543773075, 1.8793069264146163, -0.7924557034863974, 2.324975948574194, -0.39399432531957096, 1.1833539321562518, -1.1748740349410174},                                                                 
{-1.3625663624420805, 1.035627189783504, -0.47853929590169214, -2.043042243886713, 1.4183520166134627, -2.4352518150123257, -0.613588423052895, -0.22883492266989508, -0.8273679347007863, -2.1958282765192165},                                                              
{-0.9820755172214698, 1.4344265943479588, 2.1188650717653728, -1.7387809943078616, 1.8267504833103876, 1.3363691828993813, 1.5553879831954995, 1.093340995045837, 1.8286542082218604, -0.993505531158626},                                                                    
{-2.7390699251081827, 0.8539945488586307, -0.9214324343134896, -1.5719627698061585, -0.35664199946227587, 0.1925805168942157, 1.4956314386362295, 0.6002212255156132, 1.603375068056154, -3.2421950642693473},                                                                
{-1.4322498521860196, 0.7811222566209454, 0.31166797724859896, -0.19872032638941126, 3.1967349564742817, -1.761883044185299, 1.3054427002316686, 0.6937381168669216, 0.19431327774114968, -2.05858379339104},                                                                 
{0.7499944372993136, -0.9456418970230266, 0.38794100453877767, 0.719162412712889, 1.7528166271313645, -0.5987478273408394, 2.135525423561119, -0.2268771833227614, -1.0717065776938772, -1.322624857016811},                                                                  
{-0.04339600094243096, 1.0803036847903393, 1.050794710480878, -2.458581389267253, 0.927084158913808, -1.2840449928096396, 0.39286009007294764, 0.0951850245984076, 0.16972956772141, -0.6306620708656742},                                                                    
{-0.7184993230569819, 0.807189219328201, -1.077221922167391, -1.7383108166686556, 1.0634959393853713, -1.2736092309880598, 1.462787849381735, 0.6990044754540772, 1.2046170623571448, -0.45116043297048103}};

		double[] hiddenBiases = {-0.24105202702297138, 0.5342555383370955, 0.8894639692224257, 1.012608596117654, 0.09572008982356965, -0.7310230632267243, 0.3371980595657662, 0.8552955333040135, 1.5461378305701856, -0.25709248336945745};

		double[][]outputWeights = {{-0.2986750257053822},                                                                                                                                                                                                                                                       
{-0.25725010228257017},                                                                                                                                                                                                                                                       
{-0.255592901372541},                                                                                                                                                                                                                                                         
{0.33532343100221973},                                                                                                                                                                                                                                                        
{-1.9523732933990445},                                                                                                                                                                                                                                                        
{-0.15300258467985678},                                                                                                                                                                                                                                                       
{0.8303215268223955},                                                                                                                                                                                                                                                         
{0.8318602557165863},                                                                                                                                                                                                                                                         
{-1.6600579542201468},                                                                                                                                                                                                                                                        
{-2.1434710648503086}};


		double[] outputBiases = {0.21004658581591867};
		
		this.hiddenWeights = hiddenWeights;
		this.hiddenBiases = hiddenBiases;
		this.outputWeights = outputWeights;
		this.outputBiases = outputBiases;
		this.coefficient = 99.98672223821787;

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

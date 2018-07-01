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
public class NeuralBot extends AdvancedRobot
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

		double[][] hiddenWeights = {{-0.41480315713650695, -1.07105421585037, 0.25051649955951943, -2.6578245876350355, 1.5790756418675347, 0.5470066118445828, 0.19410976268424712, 1.2625070417755282, -0.41315650393786146, -0.8687331650011081},
{-0.2216010274994951, -0.21446773375124223, 0.9429397559748274, -1.105697718590243, 0.11286870549917993, -1.8283639613717997, -1.7375977614274796, 0.874202715210347, -1.0002576777723058, -0.22128623427808017},
{-1.0759871987073215, 0.9494359386445403, 0.4986424171595692, -2.2188147330362624, -0.4329609480632982, -0.9963751523864647, -0.30669959356239507, -0.782600054818022, -0.8805535772222771, 0.17504620358227677},
{-0.3165205635737375, -0.47122453766213884, -0.19060040359637354, -2.8414326482263794, 0.2262214984974172, -0.5023562666228243, -0.31054662898821095, 0.35799785230175113, -0.920977212463202, -0.23727466638242947},
{0.19610620837763523, -0.22683040238530264, -0.306594170700447, -1.7821872888233687, -0.7490698639726092, 0.28719171878372257, -0.6222311559813108, 0.5018921316228432, -1.843280898746215, 1.658515855391299},
{-3.0819391429948997, -0.2724799474018235, -0.07406140552093401, 0.09172829290323566, -0.17218296846237663, -0.8196043728633832, 0.27828250824392264, 1.7503352686214377, -0.44884777231716416, -0.1406639190611665},
{0.6478726372076873, -1.0280323419252435, -0.3439936162328572, -2.1823770052552454, -1.0284667439782171, -1.2995842703940932, 0.9775271272209195, -1.6714678390902957, 1.4616183501891435, 0.07991903014365712},
{-0.6591107149850454, -1.5879655181449703, 0.07634912386828802, -0.7584942961065038, 0.88794667586573, -1.240016708717432, -1.5581426134548593, 0.7461391232627681, 1.5935187503330888, 0.529823869717296},
{-1.6242154876009551, -1.4072885469348198, 0.49607962522212035, -1.0286119424691622, -0.3092085464266455, -1.2634656542757017, -1.8988155668498643, -0.11830902477692741, 0.051549388833017955, -0.7565280735414464}};

		double[] hiddenBiases = {0.14485581061885044, -1.539302637116477, -1.2994453728173008, 0.10998208807622681, 0.4772555488666491, -0.6679293980433515, -0.8389381559747298, 0.3551911471941461, -1.2964383930793395, 1.147414538436506};

		double[][] outputWeights = {{-0.5764355762781604},
{0.3865736928386039},
{-0.11405935317706063},
{-1.6480559041451508},
{0.03433342302366727},
{1.9213036235005678},
{-0.770310200111196},
{-1.2072358292822443},
{-0.5222387268091605},
{-0.29663609060087126}};

		double[] outputBiases = {0.080725001428262};
		
		this.hiddenWeights = hiddenWeights;
		this.hiddenBiases = hiddenBiases;
		this.outputWeights = outputWeights;
		this.outputBiases = outputBiases;
		this.coefficient = 96.26301795455187;

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
			events.add(currentEvent);
			currentEvent = new TrackingEvent();
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

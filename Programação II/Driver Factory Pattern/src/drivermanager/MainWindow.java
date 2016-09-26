package drivermanager;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.util.Enumeration;

import javax.swing.AbstractButton;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

@SuppressWarnings("serial")
public class MainWindow extends JFrame {
	private Runnable selectionAction;
	private Runnable createVideoAction;
	private Runnable createPrinterAction;
	private JRadioButton highResolutionRadio;
	private JRadioButton lowResolutionRadio;
	private JButton createVideoButton;
	private JButton createPrinterButton;
	
	public MainWindow() {
		super("Driver Manager");
		
		JPanel root = new JPanel();
		root.setLayout(new BoxLayout(root, BoxLayout.Y_AXIS));
		
		highResolutionRadio = new JRadioButton("High Resolution");
		lowResolutionRadio = new JRadioButton("Low Resolution");
		createVideoButton = new JButton("Create video!");
		createPrinterButton = new JButton("Create printer!");
		
		ButtonGroup group = new ButtonGroup();
		group.add(highResolutionRadio);
		group.add(lowResolutionRadio);
		group.setSelected(highResolutionRadio.getModel(), true);
		
		JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 10, 10));
		buttonPanel.add(createVideoButton);
		buttonPanel.add(createPrinterButton);
		
		root.add(Box.createRigidArea(new Dimension(0, 10)));
		root.add(highResolutionRadio);
		root.add(lowResolutionRadio);
		root.add(buttonPanel);
		
		createVideoButton.addActionListener(e -> createVideoAction.run());
		createPrinterButton.addActionListener(e -> createPrinterAction.run());
		
		Enumeration<AbstractButton> buttons = group.getElements();
		while (buttons.hasMoreElements()) {
			AbstractButton button = buttons.nextElement();
			button.addActionListener(e -> selectionAction.run());
			button.setAlignmentX(CENTER_ALIGNMENT);
		}
		
		getContentPane().add(root);
		pack();
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
	}

	public void onCreateVideo(Runnable createVideoAction) {
		this.createVideoAction = createVideoAction;
	}
	
	public void onCreatePrinter(Runnable createPrinterAction) {
		this.createPrinterAction = createPrinterAction;
	}
	
	public void onSelect(Runnable selectionAction) {
		this.selectionAction = selectionAction;
	}
	
	public ResolutionType getSelectedResolution() {
		if (highResolutionRadio.isSelected()) {
			return ResolutionType.HIGH;
		} else if (lowResolutionRadio.isSelected()) {
			return ResolutionType.LOW;
		}
		
		return null;
	}
}
